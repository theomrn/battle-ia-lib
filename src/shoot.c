#include "shoot.h"

float Get_Radius_Angle(float x,float y){
    return atan2f(y,x); 
}

float Calculate_Position(float x_a, float x_b, float y_a, float y_b){
    int delta_x = x_a - x_b;
    int delta_y = y_a - y_b;
    return Get_Radius_Angle(delta_x, delta_y);
}

bool ShootOnTarget(float x_a, float x_b, float y_a, float y_b){
    float radiant = Calculate_Position(x_a, x_b, y_a, y_b);
    
}