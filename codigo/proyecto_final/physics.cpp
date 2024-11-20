#include "physics.h"
#include "qdebug.h"

Physics::Physics() {}

void Physics::parabolicMotion(){

}

void Physics::freeFall(){

}

void Physics::circularMotion(){

}

void Physics::checkGravity(float &x, float &y){

    y0 = y;

    const float gravity = 9.8f;
    const float deltaTime = 0.036;

    velocity += gravity * deltaTime;
    time += deltaTime;

    float newY = y0 + velocity * time - 0.5f * gravity * time * time;

    y = newY;
}
