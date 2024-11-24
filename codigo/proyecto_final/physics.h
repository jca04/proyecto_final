#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>

class Physics
{
public:
    Physics();
    bool jumping(float &x, float &y, float floor, float angle);
    float time = 0.0;
    float velocity;
    float y0;
    float v0;
    float g = 9.8;
    float dt = 0.016;


protected:
    void parabolicMotion(float &x, float &y, float angle);
    void freeFall();
    void circularMotion(float radio, float period, float deltaTime, float &x, float &y);
    void jumping();

    bool isFalling;

};

#endif // PHYSICS_H
