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
    printf("\nScan radar --------------------------------------------------\n");
    fflush(stdout);

    BC_List *list = bc_radar_ping(conn);
    if (list == NULL)
    {
      printf("Aucun objet détecté.\n");
      fflush(stdout);
    }
    else
    {

      free_list(player_list);
      free_list(wall_list);
      free_list(boost_list);
      player_list = NULL;
      wall_list = NULL;
      boost_list = NULL;


      BC_List *head = list;
      do
      {
        BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
        if (map_object->type == OT_PLAYER)
        {
          player_list = Radar_list(player_list, map_object);
        }
        else if (map_object->type == OT_WALL)
        {
          wall_list = Radar_list(wall_list, map_object);
        }
        else if (map_object->type == OT_BOOST){
          printf("Boost détecté\n");
          boost_list = Radar_list(boost_list, map_object);
        }
        /*do {
            printShootInfo(ShootOnTarget(conn, data.position.x, player_list -> radar.position.x, data.position.y, player_list -> radar.position.y));
            //movePlayer(conn, player_list -> radar.position.x , player_list -> radar.position.y, data, speedf);
            printf("%d",player_list -> radar.type);
            fflush(stdout);
            player_list = player_list -> next;
        } while (player_list -> radar.id != data.id && player_list -> radar.health != 0 );*/
      } while ((list = bc_ll_next(list)) != NULL);
      bc_ll_free(head);
    }

    print_list(player_list, "Joueurs");
    fflush(stdout);
    print_list(boost_list, "Boost");
    //print_list(wall_list, "Murs");
    //fflush(stdout);
    movePlayer(conn,boost_list->radar.position.x,boost_list->radar.position.y,data,&speed);
  }

  free_list(player_list);
  free_list(wall_list);
  free_list(boost_list);


  printf('Fin de script');
  return EXIT_SUCCESS;
}