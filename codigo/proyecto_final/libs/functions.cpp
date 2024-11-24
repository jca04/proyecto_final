#include "libs/functions.h"
#include <iostream>
#include <cmath>

float angleBetween(float x1, float x2, float y1, float y2){

    float deltaX = x2 - x1;
    float deltaY = y2 - y1;

    float angleInRadians = std::atan2(deltaY, deltaX);
    float angleToGrades = angleInRadians * (180.0 / M_PI);

    return angleToGrades;
}
