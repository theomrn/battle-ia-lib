#include "movement.h"
#include <math.h>
#include <time.h>
#include <stdio.h>


void movePlayer(BC_Connection *connection, double x, double y,BC_PlayerData player,float *vitesse){
    player = bc_get_player_data(connection);
    float vecteur_x = x - player.position.x;
    float vecteur_y = y - player.position.y;

    float distance = sqrt(vecteur_x*vecteur_x + vecteur_y*vecteur_y);

    if (distance > 15) *vitesse = 10;
    else *vitesse = 5;

    // Normalisation du vecteur directionnel 
    float direction_x = vecteur_x / distance;
    float direction_y = vecteur_y / distance;

    // Appliquer une vitesse constante 
    float new_speed_x = direction_x * (*vitesse);
    float new_speed_y = direction_y * (*vitesse);
    bc_set_speed(connection, new_speed_x, new_speed_y, 0);
}