#include "battle_c.h"
#include "shoot.c"
#include "shoot.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char *argv[]) {
  
  BC_Connection *conn = bc_connect("5.135.136.236", 8080);

  bc_get_world_info(conn);

  bc_set_speed(conn, 0, 0, 0);

  BC_PlayerData data = bc_get_player_data(conn);
  float target_x = 29.857883;        // Position de la cible
  float target_y = 82.468407;        // Position de la cible
  BC_List *list = bc_radar_ping(conn);
  sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
    sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
    sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
  while (true){
    int a = 0;
    a++;
  }
  do {
    BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
    printf("map_object x = %f, y = %f", map_object->position.x,
           map_object->position.y);

  } while (((list = bc_ll_next(list)) != NULL));
  return EXIT_SUCCESS;
}
