#include "physics.h"
#include "qdebug.h"

Physics::Physics() {}

void Physics::parabolicMotion(){

}

void Physics::freeFall(){

}

void Physics::circularMotion(){

}



bool Physics::jumping(float &x, float &y, float floor, float angle){

    float vx = 5 * cos(angle * M_PI / 180);
    float vy = 5 * sin(angle * M_PI / 180);
    float vyCurrent = vy -g * time;

    x = x + vx * time;
    y = y - (vy * time - 0.5f * g * time * time);

    time += 0.056;

    if (vyCurrent < 0.0){ // esta cayendo

        if (abs(y - floor) < 2){
            return true;
        }
    }

    return false;


}
