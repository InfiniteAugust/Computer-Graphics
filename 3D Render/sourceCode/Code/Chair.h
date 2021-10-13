#pragma once

#include "DisplayableObject.h"

class Chair :
    public DisplayableObject
{
public:
    Chair(){};
    ~Chair(){};

    void Display();
    void DrawLeg();
    void DrawSeat();
    void DrawBack();
private:
    float LegLength = 50;
    float Thickness = 7;
    float SeatSize =60;
    float LegPosH = (SeatSize - Thickness)/2;
    float LegPosV = (LegLength + Thickness)/2;
    
};
