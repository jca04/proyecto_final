#ifndef PHYSICS_H
#define PHYSICS_H

class Physics
{
public:
    Physics();
    void checkGravity(float &x, float &y);

private:
    float time;
    float velocity;
    float y0;
    float v0;

protected:
    void parabolicMotion();
    void freeFall();
    void circularMotion();

};

#endif // PHYSICS_H
