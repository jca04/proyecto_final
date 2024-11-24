#include "physics.h"
#include "qdebug.h"

Physics::Physics() {}

void Physics::parabolicMotion(float &x, float &y, float angle){
    float vx = 8 * cos(angle * M_PI / 180);
    float vy = 8 * sin(angle * M_PI / 180);

    x = x + vx * time;
    y = y - (vy * time - 0.5f * g * time * time);

    time += 0.056;
}

void Physics::freeFall(){

}

void Physics::circularMotion(float radio, float period, float deltaTime,float &x, float &y){
    double omega = (2 * M_PI) / period;

    time += deltaTime;

    x = x + radio * cos(omega * time);
    y = y + radio * sin(omega * time);
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
