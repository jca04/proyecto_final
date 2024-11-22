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
    void parabolicMotion();
    void freeFall();
    void circularMotion();
    void jumping();

    bool isFalling;

};

#endif // PHYSICS_H
