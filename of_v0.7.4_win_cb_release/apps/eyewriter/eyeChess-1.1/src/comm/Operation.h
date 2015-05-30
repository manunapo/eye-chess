#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

class Operation
{
private:
    char type;
    float x;
    float y;

public:
    Operation(char theType);
    Operation(char theTypem, float nx, float ny);
    void setCoords(float newX, float newY);
    char getType();
    float getX();
    float getY();
};

#endif // OPERATION_H_INCLUDED
