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
const int MAX = 600;
const int MIN = 0;
int ldrValue;
int sensorsStates[8][8];

void setup()
{
	Serial.begin(SRATE);
	started = false;
	zdown = false;
        sensing = false;
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
                        state = 0;
                        if( (i < 2) || (i > 5))
                        {
                               state = 1; 
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
               boolean changed = checkSensors( coords);
               if( changed)
               {
                      while( checkSensors( coords))
                     {
                            delay( 2000);
                     } 
               }
               delay(500);     
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
                sensing = true;
		Serial.read(); 
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

boolean checkSensors(int coords[4])
{
        int i = 0;
        int j = 0;
        boolean someSensorChanged = false;
        boolean firstPosFound = false;
        while( (i < 8) && !someSensorChanged)
        {
                digitalWrite( vccPin[i], HIGH);
                while( (j < 8) && !someSensorChanged)
                {
                        ldrValue = analogRead( ldr[j]);  // le o LDR correspondente  
                        ldrValue = constrain( ldrValue, MIN, MAX); // ajusta valor lido  
                        ldrValue = map( ldrValue, MIN, MAX, 0, 1);  // ajusta valor lido  
                        if( sensorsStates[i][j] != ldrValue)
                        {
                                if( ldrValue == 1)
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
                        j++;        
                }
                digitalWrite( vccPin[i], LOW); 
                i++;  
        }
        if( someSensorChanged)
        {
               sensorsStates[coords[0]][coords[1]] = !sensorsStates[coords[0]][coords[1]];
               sensorsStates[coords[2]][coords[3]] = !sensorsStates[coords[2]][coords[3]];
        }
        return someSensorChanged;   
}
