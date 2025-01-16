#ifndef _SHOOT_H_
#define _SHOOT_H_

#include "math.h"
#include "stdbool.h"

float Get_Radius_Angle(float x,float y);

float Calculate_Position(float x_a, float x_b, float y_a, float y_b);

bool ShootOnTarget(float x_a, float x_b, float y_a, float y_b);

#endif