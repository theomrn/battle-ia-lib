#include "radar.h"
#include "shoot.h"
#include "stdio.h"
#include "stdlib.h"
#include "tool.h"
#include "unistd.h"
#include "movement.h"

int main(int argc, char *argv[])
{

    BC_Connection *conn = bc_connect("5.135.136.236", 8080);
    printf("Connection réussi\n");
    fflush(stdout);

    BC_WorldInfo world = bc_get_world_info(conn);
    printf("Arena size\nX: %ld, Y: %ld\n", world.map_x, world.map_y);
    fflush(stdout);
    bc_get_world_info(conn);
    float speed = 20.0;

    // Retrive user informations
    BC_PlayerData data = bc_get_player_data(conn);
    Print_BC_PlayerData(data);
    fflush(stdout);

    Radar *player_list = NULL;
    Radar *wall_list = NULL;
    Radar *boost_list = NULL;

    while (!data.is_dead)
    {
        printf("\nScan radar\n");
        fflush(stdout);

        // Ping the map and provide the list of players, walls and boosts
        process_radar_ping(conn, world, &player_list, &wall_list, &boost_list);

        /*print_list(player_list, "Joueurs");
        fflush(stdout);
        print_list(boost_list, "Boost");
        fflush(stdout);*/
    }

    free_list(player_list);
    free_list(wall_list);
    free_list(boost_list);

    printf('Fin de script');
    return EXIT_SUCCESS;
}