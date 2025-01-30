#include "movement.h"
#include <math.h>
#include <time.h>
#include <stdio.h>


void movePlayer(BC_Connection *connection, double x, double y,BC_PlayerData player,float vitesse){
    static clock_t last_set_speed = 0;

    float vecteur_x = x - player.position.x;
    float vecteur_y = y - player.position.y;

    float distance = sqrt(vecteur_x*vecteur_x + vecteur_y*vecteur_y);

    // printf("vecteur x = %f vecteur y = %f distance = %f\n",vecteur_x,vecteur_y,distance);

    if (distance < 2.0) {  
        bc_set_speed(connection, 0, 0, 0);
        return;
    }

    // Normalisation du vecteur directionnel 
    float direction_x = vecteur_x / distance;
    float direction_y = vecteur_y / distance;

    // Appliquer une vitesse constante 
    float new_speed_x = direction_x * vitesse;
    float new_speed_y = direction_y * vitesse;

    clock_t now = clock();
    printf("sls = %f, now = %f \n", last_set_speed, now);
    fflush(stdout);
    if((now - last_set_speed) / CLOCKS_PER_SEC > 1) {
        last_set_speed = clock();
        printf("setSpeed\n");
        fflush(stdout);
        // Définir la nouvelle vitesse
        bc_set_speed(connection, new_speed_x, new_speed_y, 0);
    }
}