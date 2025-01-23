#include "shoot.h"
#include "battle_c.h"

float Get_Radius_Angle(float x,float y){
    return atan2f(y,x); 
}

float Calculate_Position(float x_a, float x_b, float y_a, float y_b){
    int delta_x = x_a - x_b;
    int delta_y = y_a - y_b;
    return Get_Radius_Angle(delta_x, delta_y);
}

BC_ShootResult ShootOnTarget(BC_Connection *connection, float x_a, float x_b, float y_a, float y_b){
    BC_ShootResult shootresult =  bc_shoot(connection, Calculate_Position(x_a, x_b, y_a, y_b));
    printf("Succès : %b\n",shootresult.success);
    printf("Target ID = %d\n",(int) shootresult.target_id);
    printf("Dégats : %d\n",(int) shootresult.damage_points);
    printf("Cible détruite ? : %b\n",shootresult.target_destroyed);
}