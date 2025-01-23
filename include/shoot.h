#ifndef _SHOOT_H_
#define _SHOOT_H_

#include "battle_c.h"
#include "math.h"
#include "stdbool.h"
#include <stdio.h>

float Get_Radius_Angle(float x,float y);

float Calculate_Position(float x_a, float x_b, float y_a, float y_b);

BC_ShootResult ShootOnTarget(BC_Connection *connection, float x_a, float x_b, float y_a, float y_b);

char* BC_ShootResultFailReasonToString(enum BC_ShootResultFailReason_ type);

void printShootInfo(BC_ShootResult shootresult);

#endif
