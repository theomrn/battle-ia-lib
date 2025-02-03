#include "shoot.c"
#include "shoot.h"
#include "stdio.h"
#include "stdlib.h"
#include "tool.h"
#include "unistd.h"
#include "movement.h"

int main(int argc, char *argv[]) {

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);
  printf("Connection réussi\n");
  fflush(stdout);

  BC_WorldInfo world = bc_get_world_info(conn);
  printf("Arena size\nX: %ld, Y: %ld\n", world.map_x, world.map_y);
  fflush(stdout);
  bc_get_world_info(conn);

  bc_set_speed(conn, 0, 0, 0);

  // Retrive user informations
  BC_PlayerData data = bc_get_player_data(conn);
  Print_BC_PlayerData(data);
  fflush(stdout);


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
  
  float target_x = 23.867260;        // Position de la cible
  float target_y = 49.615505;        // Position de la cible
  BC_List *list = bc_radar_ping(conn);
  sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
    sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
    sleep(3);
  printShootInfo(ShootOnTarget(conn, data.position.x, target_x, data.position.y, target_y));
  /* uncoment to move 
  double coo_x = 10.0; 
  double coo_y = 10.0;
  float vitesse = 10;

  // Boucle tant que le personnage n'est pas dans la zone cible
  while (sqrt(pow(data.position.x - coo_x, 2) + pow(data.position.y - coo_y, 2)) > 2) {
  movePlayer(conn, coo_x, coo_y, data, &vitesse);
        
    // Mettre à jour les données du joueur
    data = bc_get_player_data(conn);
        
    // Debug : afficher les coordonnées actuelles
    printf("coo : x = %f , y = %f \n", data.position.x, data.position.y);
    fflush(stdout);

    // Attendre un peu pour éviter une surcharge CPU
    usleep(50000);  // 50ms
  }

  // Arrêt total une fois la position atteinte
  printf("\n\n\nEnd of program\n");
  while (true){
    bc_set_speed(conn, 0.0, 0.0, 0.0);
  }  
  */
  return EXIT_SUCCESS;
}
