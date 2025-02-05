#include "radar.h"
#include "shoot.h"
#include "stdio.h"
#include "stdlib.h"
#include "tool.h"
#include "unistd.h"
#include "movement.h"


int main(int argc, char *argv[])
{

    // Connect to the server
    BC_Connection *conn = bc_connect("5.135.136.236", 8080);
    printf("Connection réussi\n");
    fflush(stdout);

    // Retrieve the world informations
    BC_WorldInfo world = bc_get_world_info(conn);
    printf("Arena size\nX: %ld, Y: %ld\n", world.map_x, world.map_y);
    fflush(stdout);
    bc_get_world_info(conn);

    // Retrive user informations
    BC_PlayerData data = bc_get_player_data(conn);
    fflush(stdout);

    // Initialize the radar lists
    Radar *player_list = NULL;
    Radar *wall_list = NULL;
    Radar *boost_list = NULL;

    // Initialize the speed
    float speed = 20.0;
    float *speedf = &speed;

    int loop_count = 0;
    while (!data.is_dead)
    {
        printf("Itération %d\n", loop_count++);

        //BC_PlayerData data = bc_get_player_data(conn);
        //Print_BC_PlayerData(data);

        printf("Scan radar\n");
        fflush(stdout);

        // Ping the map and provide the list of players, walls and boosts
        process_radar_ping(conn, world, &player_list, &wall_list, &boost_list);

        // Retrieve the nearest boost
        BC_MapObject nearest_boost = nearest(boost_list, data);
        printf("Boost le plus proche : ID: %d | Position: (x = %f, y = %f)\n", nearest_boost.id, nearest_boost.position.x, nearest_boost.position.y);
        fflush(stdout);

        // Move to the nearest boost or random position
        if (nearest_boost.id == NULL)
        {
            printf("Aucun boost détecté.\n");
            fflush(stdout);
            movePlayer(conn, rand() % world.map_x, rand() % world.map_y, data, &speed);
        }
        else{
        printf("Déplacement vers le boost le plus proche aux coorodonnées x = %f, y = %f\n", nearest_boost.position.x, nearest_boost.position.y);
        fflush(stdout);
        movePlayer(conn, nearest_boost.position.x, nearest_boost.position.y, data, &speed);
        //movePlayer(conn, 50.0, 50.0, data, &speed);
        }

        // Retrieve the nearest player
        BC_MapObject nearest_player = nearest(player_list, data);
        if (nearest_player.id == -1)
        {
            printf("Aucun joueur ennemi détecté.\n");
            fflush(stdout);
        }
        else{
        printf("Joueur le plus proche : ID: %d | Position: (x = %f, y = %f)\n", nearest_player.id, nearest_player.position.x, nearest_player.position.y);
        fflush(stdout);
        // Shoot on the nearest ennemy
        printShootInfo(ShootOnTarget(conn, data.position.x, nearest_player.position.x, data.position.y, nearest_player.position.y));
        }

    }

    free_list(player_list);
    free_list(wall_list);
    free_list(boost_list);

    printf('Fin de script');
    return EXIT_SUCCESS;
}