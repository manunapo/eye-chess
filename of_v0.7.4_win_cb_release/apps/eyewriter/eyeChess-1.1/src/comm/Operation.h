#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

class Operation
{
private:
    char type;
    float number;

public:
    Operation(char theType);
    Operation(char theTypem, float nn);
    void setCoords(float newN);
    char getType();
    float getN();
};

#endif // OPERATION_H_INCLUDED
