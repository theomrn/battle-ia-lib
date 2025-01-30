#include "battle_c.h"
#include "tool.h"

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("Initialisation du bot\n");
  fflush(stdout);

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);
  printf("Connection réussi\n");
  fflush(stdout);

  BC_WorldInfo world = bc_get_world_info(conn);
  printf("Arena size\nX: %d, Y: %d\n", world.map_x, world.map_y);
  fflush(stdout);

  // Retrive user informations
  BC_PlayerData data = bc_get_player_data(conn);
  Print_BC_PlayerData(&data);
  // Mise à jour des informations
  // BC_PlayerData data = bc_get_player_data(conn);

  while (true)
  {
    BC_List *list = bc_radar_ping(conn);

    // While the linked list is read, print informations in the terminal
    int i = 0;
    do
    {
      BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
      i++;
      printf("index : %d ,id %d,map_object x = %f, y = %f, type (int/Text) = %d / %s \n",
             i,
             map_object->id,
             map_object->position.x,
             map_object->position.y,
             map_object->type,
             BC_ObjectTypeToString(map_object->type) // Convert from int to text the enum
      );
      fflush(stdout);
    } while (((list = bc_ll_next(list)) != NULL));
    bc_ll_free(list);
  }

  return EXIT_SUCCESS;
}
