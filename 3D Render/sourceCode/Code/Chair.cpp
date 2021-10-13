#include "Chair.h"
#include "TexturedCube.h"

void Chair::Display()
{
    glPushMatrix();
        glTranslatef(pos[0], pos[1] + LegLength, pos[2]);
        glScalef(scale[0], scale[0], scale[0]);

        glPushMatrix();
            DrawSeat();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-LegPosH,-LegPosV, -LegPosH);
            DrawLeg();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(LegPosH,-LegPosV, -LegPosH);
            DrawLeg();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-LegPosH,-LegPosV, LegPosH);
            DrawLeg();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(LegPosH,-LegPosV, LegPosH);
            DrawLeg();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, SeatSize/2, -LegPosH);
            DrawBack();
        glPopMatrix();
    glPopMatrix();
    
}
void Chair::DrawBack(){
    glScalef(SeatSize,SeatSize, Thickness);
    TexturedCube("../Textures/wood1.bmp");
}

void Chair::DrawSeat(){
    glScalef(SeatSize,Thickness,SeatSize);
    TexturedCube("../Textures/wood.bmp");
}

void Chair::DrawLeg(){
    glScalef(Thickness,LegLength,Thickness);
    TexturedCube("../Textures/wood1.bmp");
}
