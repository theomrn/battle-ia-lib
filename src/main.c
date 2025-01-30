#include "shoot.c"
#include "shoot.h"
#include "radar.c"
#include "radar.h"
#include "stdio.h"
#include "stdlib.h"
#include "tool.h"
#include "unistd.h"

int main(int argc, char *argv[]) {

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);
  printf("Connection réussi\n");
  fflush(stdout);

  BC_WorldInfo world = bc_get_world_info(conn);
  printf("Arena size\nX: %ld, Y: %ld\n", world.map_x, world.map_y);
  fflush(stdout);
  bc_get_world_info(conn);

  // Retrive user informations
  BC_PlayerData data = bc_get_player_data(conn);
  Print_BC_PlayerData(data);
  fflush(stdout);


    Radar *player_list = NULL;
    Radar *wall_list = NULL;

    while (true) {
        printf("\nScan radar --------------------------------------------------\n");
        
        BC_List *list = bc_radar_ping(conn);
        if (list == NULL) {
            printf("Aucun objet détecté.\n");
        } else {
            free_list(player_list);
            free_list(wall_list);
            player_list = NULL;
            wall_list = NULL;

             BC_List *head = list;
            do {
                BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);

                if (map_object->type == OT_PLAYER) {
                    player_list = Radar_list(player_list, map_object);
                } else if (map_object->type == OT_WALL) {
                    wall_list = Radar_list(wall_list, map_object);
                }

            } while ((list = bc_ll_next(list)) != NULL);

            bc_ll_free(head);
        }
        sleep(1);
        printf("Id du joueur ciblé : %d\n",player_list -> radar.id);
        printf("Mon id : %d\n",data.id);
        printf("Santé de la cible : %d",player_list -> radar.health);
        do {
            printShootInfo(ShootOnTarget(conn, data.position.x, player_list -> radar.position.x, data.position.y, player_list -> radar.position.y));
            player_list = player_list -> next;
        } while (player_list -> radar.id == data.id && player_list -> radar.health != 0 );

        //print_list(player_list, "Joueurs");
        //print_list(wall_list, "Murs");

    }

    free_list(player_list);
    free_list(wall_list);

  return EXIT_SUCCESS;
}
