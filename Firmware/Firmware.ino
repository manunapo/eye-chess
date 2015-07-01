#include <Arduino.h>
#include "MotorHandler.h"

#define SRATE 115200

// used for serial communication
char inputchars[10];

int charcount;
float newx, newy;
int sign;
boolean started;
boolean zdown;

// used for sensors 
boolean sensing;
const int ldr[8] = {A8,A9,A10,A11,A12,A13,A14,A15};  
const int vccPin[8] = {22,23,24,25,26,27,28,29};  
const int MAX = 500;
const int MIN = 200;
int ldrValue;
int sensorsStates[8][8];

void setup()
{
	Serial.begin(SRATE);
	started = false;
	zdown = false;
        sensing = false;
        initSensors();
	initMotors();
       
	//wait for host application to connect
	while(!Serial.available())
	{
		if((millis()/1000)%2)
		{
			digitalWrite(13, HIGH);
		}
		else
		{
			digitalWrite(13, LOW);
		}
	}
}

void initSensors()
{
        pinMode(vccPin[0], OUTPUT);   
        pinMode(vccPin[1], OUTPUT); 
        pinMode(vccPin[2], OUTPUT);   
        pinMode(vccPin[3], OUTPUT);
        pinMode(vccPin[4], OUTPUT);   
        pinMode(vccPin[5], OUTPUT);
        pinMode(vccPin[6], OUTPUT);   
        pinMode(vccPin[7], OUTPUT);  
        int state = 0;
        for( int i = 0; i < 8; i++)
        {
                for( int j = 0; j < 8; j++)
                {
                        // empty
                        state = 0;
                        if(i < 2)
                        {
                               // white
                               state = 1; 
                        }
                        if(i > 5)
                        {
                               // black
                               state = 2; 
                        }
                        sensorsStates[i][j] = state;
                } 
        }
}

void loop() 
{
        if(sensing)
        {
               int coords[4] = {0,0,0,0};
               int cantChanged = checkSensors( coords);
               boolean changed = (cantChanged != 0);
               
               
               if( changed)
               {
                     delay( 1500);
                     int coords2[4] = {0,0,0,0};
                     cantChanged = checkSensors( coords2);
                     if((cantChanged == 2) && (sensorsStates[coords[0]][coords[1]] == 2))
                     {
                           if( (coords[0] == coords2[0]) && 
                               (coords[1] == coords2[1]) && 
                               (coords[2] == coords2[2]) && 
                               (coords[3] == coords2[3]))
                           {
                                   sensorsStates[coords[0]][coords[1]] = 0;
                                   sensorsStates[coords[2]][coords[3]] = 2;
                                   Serial.write(coords[0]);
                                   Serial.write(coords[1]);
                                   Serial.write(coords[2]);
                                   Serial.write(coords[3]);
                                   Serial.write('@');
                                   sensing = false;
                           }   
                           
                     }
                      else
                     {
                            if((cantChanged == 1) && (sensorsStates[coords[0]][coords[1]] == 1))
                            {
                                   if( (coords[0] == coords2[0]) && 
                                       (coords[1] == coords2[1]))
                                   {
                                           sensorsStates[coords[0]][coords[1]] = 0;
                                   }
                           
                            }
                     } 
               }
               delay(200);    
        }
        else
        {  
               checkSerial();
        }
}

void checkSerial()
{
        // wait for data to come
	while(Serial.available() < 1);
	
	// start if the char 'S' is sent, finish if 'T' is sent
	if(Serial.peek() == 'S')
	{
		// drawing started
		started = true;
		zdown = false;
		Serial.read(); 
                Serial.write('@');
	}
	else
	if(Serial.peek() == 'T')
	{
		// drawing finished
		started = false;
		Serial.read();
		if(!zdown)
		{
			penDown();
			zdown = true;
		}
		drawLine(0.0, 0.0);
		resetPositions();
		release();
	}else
	if(Serial.peek() == 'A')
	{
		// raise pen
		Serial.read();
		if(zdown)
		{
			penUp();
			zdown = false;
		}
		Serial.write('@');
	}else
	if(Serial.peek() == 'Z')
	{
		// lower pen
		Serial.read();
		if(!zdown)
		{
			penDown();
			zdown = true;
		}
		Serial.write('@');
	}else
        if(Serial.peek() == 'B')
	{
                Serial.read(); 
                sensing = true;
                int coords[4] = {0,0,0,0};
                while(Serial.available() < 1);
                coords[0] = convertCharToInt(Serial.read());
                while(Serial.available() < 1);
                coords[1] = convertCharToInt(Serial.read());
                while(Serial.available() < 1);
                coords[2] = convertCharToInt(Serial.read());
                while(Serial.available() < 1);
                coords[3] = convertCharToInt(Serial.read());     
                
                //origin ever changes, but destination depends if its empty or not.
                sensorsStates[coords[0]][coords[1]] = !sensorsStates[coords[0]][coords[1]];
                sensorsStates[coords[2]][coords[3]] = !sensorsStates[coords[2]][coords[3]];
                /*if(sensorsStates[coords[2]][coords[3]] == 0)
                        sensorsStates[coords[2]][coords[3]] = 1;*/
		
                Serial.write('@');
	}else
	if(started)
	{
		reBuildCoordenate();
		// now we have newx and newy.
		drawLine(newx, newy);
                while(Serial.available() > 0)
		{
			Serial.read(); // clear the port
		}
		Serial.write('%'); // send verification byte
	}
	else
	{
		// it was some unexpected transmission
		// clear it
		Serial.read();
	}
}

int convertCharToInt(char c)
{
        if(c == '0')
               return 0;
        if(c == '1')
               return 1;
        if(c == '2')
               return 2;
        if(c == '3')
               return 3;
        if(c == '4')
               return 4;
        if(c == '5')
               return 5;
        if(c == '6')
               return 6;
        if(c == '7')
               return 7;
        if(c == '8')
               return 8;
        if(c == '9')
               return 9;     
}

void reBuildCoordenate()
{
        // if there is some serial data, read it, parse it, use it
        boolean complete = false;
        char tmpchar;
        if (Serial.available() > 0)
        {
                charcount = 0;
        	complete = false;
        	newx = 0;
        	sign = 1;
        	while(!complete)
        	{
        		// wait for x data
        		while(Serial.available() < 1);
        		tmpchar = Serial.read();
        		if(tmpchar == '.')
        		{
        			// signals end of number
        			complete = true;
        			continue;
        		}
        		if(tmpchar == '-')
        		{
        			sign = -1;
        		}
        		else
        		{
        			newx = newx*10.0 + tmpchar-'0';
        		}
        		charcount++;
        	}
        	newx = newx*sign/10000.0;
        	while(Serial.available() > 0)
        	{
        		Serial.read(); // clear the port
        	}
        	Serial.write('@'); // write a verification byte
        }
        		
        // wait for the y data
        while(Serial.available() < 1);
        if (Serial.available() > 0)
        {
        	charcount = 0;
        	complete = false;
        	newy = 0;
        	sign = 1;
        	while(!complete)
        	{
        		while(Serial.available() < 1)
        		{
        			delay(1);
        		}
        		tmpchar = Serial.read();
        		if(tmpchar == '.')
        		{
        			complete = true;
        			continue;
        		}
        		if(tmpchar == '-')
        		{
        			sign = -1;
        		}
        		else
        		{
        			newy = newy*10.0 + tmpchar-'0';
        		}
        		charcount++;
        	}
        	newy = newy*sign/10000.0;
        	while(Serial.available() > 0)
        	{
        		Serial.read(); // clear the port
        	}
        }
}

// returns 0 if no change, 1 if 1 position change, 2 if 2 positions change.
int checkSensors(int coords[4])
{
        int i = 0;
        int j = 0;
        boolean someSensorChanged = false;
        boolean firstPosFound = false;
        for(int i = 0; i < 8; i++)  
        {  
              digitalWrite( vccPin[i],HIGH);  
              for(int j = 0; j < 8; j++)  
                    {  
                    ldrValue = analogRead(ldr[j]); 
                    ldrValue = constrain(ldrValue, MIN, MAX);   
                    int aux = MAX - MIN / 2;
                    
                    if( ldrValue < aux)
                            ldrValue = 1;
                    else
                            ldrValue = 0; 
                    
                    int state = 1;
                    if( sensorsStates[i][j] == 0) 
                          state = 0;
                    if( state != ldrValue)
                    {
                            if( ldrValue)
                            {
                                   coords[2] = i;
                                   coords[3] = j;  
                            }
                            else
                            {
                                  coords[0] = i;
                                  coords[1] = j; 
                            }
                            if( firstPosFound)
                            {
                                  someSensorChanged = true;     
                            }
                            else
                            {
                                 firstPosFound = true; 
                            }
                    }  
              }  
              digitalWrite( vccPin[i],LOW);  
        }
        if( someSensorChanged)
              return 2;
        if( firstPosFound)
              return 1;
        return 0; 
}
