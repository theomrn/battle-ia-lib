#include "movement.h"
#include <math.h>
#include <time.h>
#include <stdio.h>


void movePlayer(BC_Connection *connection, double x, double y,BC_PlayerData player,float *vitesse){
    player = bc_get_player_data(connection);
    float vecteur_x = x - player.position.x;
    float vecteur_y = y - player.position.y;

    float distance = sqrt(vecteur_x*vecteur_x + vecteur_y*vecteur_y);

    if (distance < 25) *vitesse /= 2;
    if (distance < 20) *vitesse = 2;
    if (distance < 10) *vitesse /= 0.5;
    
    // Si on est suffisamment proche, on arrête le mouvement
    if (distance < 2) {  // Seuil ajustable
        *vitesse = 0;
        bc_set_speed(connection, 0, 0, 0);
        return;
    }

    // Normalisation du vecteur directionnel 
    float direction_x = vecteur_x / distance;
    float direction_y = vecteur_y / distance;

    // Appliquer une vitesse constante 
    float new_speed_x = direction_x * (*vitesse);
    float new_speed_y = direction_y * (*vitesse);
    bc_set_speed(connection, new_speed_x, new_speed_y, 0);
}