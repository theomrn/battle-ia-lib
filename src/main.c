#include "battle_c.h"
#include "tool.h"

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Initialisation du bot\n");

    BC_Connection *conn = bc_connect("5.135.136.236", 8080);
    if (conn == NULL) {
        fprintf(stderr, "Erreur : Échec de la connexion au serveur.\n");
        return EXIT_FAILURE;
    }
    printf("Connexion réussie\n");

    BC_WorldInfo world = bc_get_world_info(conn);
    printf("Arena size\nX: %d, Y: %d\n", world.map_x, world.map_y);

    BC_PlayerData data = bc_get_player_data(conn);
    Print_BC_PlayerData(data);

    while (!data.is_dead) {
        printf("Nouveau scan --------------------------------------------------------------------\n");

        BC_List *list = bc_radar_ping(conn);
        if (list == NULL) {
            printf("Aucun objet détecté.\n");
        } else {
            int i = 0, wall_count = 0;
            do {
                BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
                i++;

                if (map_object->type == OT_WALL) {
                    wall_count++;
                }

                printf("Index : %d, ID : %d, Position x = %d, y = %d, Type (Int/Text) = %d / %s\n",
                       i,
                       map_object->id,
                       map_object->position.x,
                       map_object->position.y,
                       map_object->type,
                       BC_ObjectTypeToString(map_object->type));
            } while ((list = bc_ll_next(list)) != NULL);

            printf("Nombre de murs détectés : %d\n", wall_count);

            bc_ll_free(list);
        }

        usleep(1000000);

        data = bc_get_player_data(conn);
    }

    printf("Fin de la partie : le joueur est mort.\n");
    return EXIT_SUCCESS;
}
