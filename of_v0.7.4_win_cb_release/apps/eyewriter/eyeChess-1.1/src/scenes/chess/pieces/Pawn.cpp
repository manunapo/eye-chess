#import "Pawn.h"

bool Pawn::canMove( int** places, int newFile, int newRow)
{

    /*cout << "\n" << isFreeRoadTo( places, 0, 1) << isFreeRoadTo( places, 0, 2)<< isFreeRoadTo( places, 0, 3)<< isFreeRoadTo( places, 0, 4)<< isFreeRoadTo( places, 0, 5)<< isFreeRoadTo( places, 0, 6)<< isFreeRoadTo( places, 0, 7)<<"\n";
    cout << isFreeRoadTo( places, 1, 1) << isFreeRoadTo( places, 1, 2)<< isFreeRoadTo( places, 1, 3)<< isFreeRoadTo( places, 1, 4)<< isFreeRoadTo( places, 1, 5)<< isFreeRoadTo( places, 1, 6)<< isFreeRoadTo( places, 1, 7)<<"\n";
    cout << isFreeRoadTo( places, 2, 1) << isFreeRoadTo( places, 2, 2)<< isFreeRoadTo( places, 2, 3)<< isFreeRoadTo( places, 2, 4)<< isFreeRoadTo( places, 2, 5)<< isFreeRoadTo( places, 2, 6)<< isFreeRoadTo( places, 2, 7)<<"\n";
    cout << isFreeRoadTo( places, 3, 1) << isFreeRoadTo( places, 3, 2)<< isFreeRoadTo( places, 3, 3)<< isFreeRoadTo( places, 3, 4)<< isFreeRoadTo( places, 3, 5)<< isFreeRoadTo( places, 3, 6)<< isFreeRoadTo( places, 3, 7)<<"\n";
    cout << isFreeRoadTo( places, 4, 1) << isFreeRoadTo( places, 4, 2)<< isFreeRoadTo( places, 4, 3)<< isFreeRoadTo( places, 4, 4)<< isFreeRoadTo( places, 4, 5)<< isFreeRoadTo( places, 4, 6)<< isFreeRoadTo( places, 4, 7)<<"\n";
    cout << isFreeRoadTo( places, 5, 1) << isFreeRoadTo( places, 5, 2)<< isFreeRoadTo( places, 5, 3)<< isFreeRoadTo( places, 5, 4)<< isFreeRoadTo( places, 5, 5)<< isFreeRoadTo( places, 5, 6)<< isFreeRoadTo( places, 5, 7)<<"\n";
    cout << isFreeRoadTo( places, 6, 1) << isFreeRoadTo( places, 6, 2)<< isFreeRoadTo( places, 6, 3)<< isFreeRoadTo( places, 6, 4)<< isFreeRoadTo( places, 6, 5)<< isFreeRoadTo( places, 6, 6)<< isFreeRoadTo( places, 6, 7)<<"\n";
    cout << isFreeRoadTo( places, 7, 1) << isFreeRoadTo( places, 7, 2)<< isFreeRoadTo( places, 7, 3)<< isFreeRoadTo( places, 7, 4)<< isFreeRoadTo( places, 7, 5)<< isFreeRoadTo( places, 7, 6)<< isFreeRoadTo( places, 7, 7)<<"\n";*/
    bool toR = false;
    int maxSteps = 1;
    if(isFirstMove)
    {
        maxSteps = 2;
        isFirstMove = false;
    }
    if(white)
    {
        int aux = newFile - myFile;
        if((newRow == myRow) && (aux <= maxSteps) && (aux > 0))
        {
            if(places[newFile][newRow] == 0)
            {
                toR = true;
            }
        }
        else
        {
            if((aux == 1) && (abs(newRow - myRow) == 1))
            {
                //Diferent colors
                toR = places[newFile][newRow] != places[myFile][myRow];
                toR = toR && places[newFile][newRow] != 0;
            }
        }

    }
    else
    {
        int aux = myFile - newFile;
        if((newRow == myRow) && (aux <= maxSteps) && (aux > 0))
        {
            if(places[newFile][newRow] == 0)
            {
                toR = true;
            }
        }
        else
        {
            if((aux == 1) && (abs(myRow - newRow) == 1))
            {
                //Diferent colors
                toR = places[newFile][newRow] != places[myFile][myRow];
                toR = toR && places[newFile][newRow] != 0;
                cout << "diferent colors: " << toR;
            }
        }
    }

    return toR;
}
