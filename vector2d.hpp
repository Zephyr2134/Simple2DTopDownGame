#pragma once

class vector2d
{
public:
    vector2d(float xPos, float yPos);
    ~vector2d();
    void changeX(float value){x += value;}
    void changeY(float value){y += value;}
    void setX(float value){x = value;}
    void setY(float value){y = value;}
    float getX(){return x;}
    float getY(){return y;}

private:
    float x;
    float y;
};