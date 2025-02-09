#include "radar.h"
#include "shoot.h"
#include "stdio.h"
#include "stdlib.h"
#include "tool.h"
#include "unistd.h"
#include "movement.h"
#include <pthread.h>

// Function to be executed by the thread
void *fetch_and_print_data(void *arg)
{
    BC_Connection *conn = (BC_Connection *)arg;
    while (1)
    {
        BC_PlayerData data = bc_get_player_data(conn);
        Print_BC_PlayerData(data);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

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

        // Create a new thread to fetch and print data every 1 second
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, fetch_and_print_data, (void *)conn) != 0)
        {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }

        printf("Scan radar\n");
        fflush(stdout);

        // Ping the map and provide the list of players, walls and boosts
        process_radar_ping(conn, world, data, &player_list, &wall_list, &boost_list);

        // Retrieve the nearest boost and move to the nearest boost or random position
        BC_MapObject nearest_boost = nearest(boost_list, data);
        if (nearest_boost.position.x < 1 && nearest_boost.position.y < 1) // The radar retrieves the nearest boost with the coordinates (0,0) if null
        {
            printf("Aucun boost détecté.\n");
            fflush(stdout);
            movePlayer(conn, rand() % world.map_x, rand() % world.map_y, data, &speed);
        }
        else
        {
            printf("Déplacement vers le boost le plus proche aux coorodonnées x = %f, y = %f\n", nearest_boost.position.x, nearest_boost.position.y);
            fflush(stdout);
            movePlayer(conn, nearest_boost.position.x, nearest_boost.position.y, data, &speed);
        }

        // Retrieve the nearest player
        if (player_list == NULL)
        {
            printf("Aucun joueur détecté.\n");
            fflush(stdout);
        }
        else
        {
            BC_MapObject nearest_player = nearest(player_list, data);
            printf("Joueur le plus proche : ID: %d | Position: (x = %f, y = %f)\n", nearest_player.id, nearest_player.position.x, nearest_player.position.y);
            fflush(stdout);
            // Shoot on the nearest ennemy
            printShootInfo(ShootOnTarget(conn, data.position.x, nearest_player.position.x, data.position.y, nearest_player.position.y));
        }

        print_list(player_list, "Joueurs");
    }

    free_list(player_list);
    free_list(wall_list);
    free_list(boost_list);

    bc_disconnect(conn);

    printf('Fin de script');
    return EXIT_SUCCESS;
}