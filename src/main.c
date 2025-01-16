#include "battle_c.h"
#include "tool.h"

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);

  BC_WorldInfo world = bc_get_world_info(conn);
  printf("Arena size\nX: %d, Y: %d\n", world.map_x, world.map_y);

  // Retrive user informations
  BC_PlayerData data = bc_get_player_data(conn);
  Print_BC_PlayerData(data);

  while (data.is_dead != true)
  {
    //Mise à jour des informations
    BC_PlayerData data = bc_get_player_data(conn); 

    // --------------------------------------------------------------------------------------
    //                                  Section - Radar
    // --------------------------------------------------------------------------------------
    // Create a linked list and ping every object in the arena to retrieve their informations
    BC_List *list = bc_radar_ping(conn);

    // While the linked list is read, print informations in the terminal
    do {
      BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
      printf("id %d,map_object x = %d, y = %d, type (int/Text) = %d / %s \n",
            map_object->id,
            map_object->position.x,
            map_object->position.y,
            map_object->type,
            BC_ObjectTypeToString(map_object->type)     //Convert from int to text the enum
            );
    } while (((list = bc_ll_next(list)) != NULL));
    // --------------------------------------------------------------------------------------
    //                                 End Section - Radar
    // --------------------------------------------------------------------------------------

  }

  return EXIT_SUCCESS;
}
