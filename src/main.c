#include "battle_c.h"
#include "tool.h"

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

typedef struct Radar {
    BC_MapObject radar;
    struct Radar *next;
} Radar;

Radar *Radar_list(Radar *head, BC_MapObject *obj) {
    Radar *new_radar = (Radar *)malloc(sizeof(Radar));
    if (!new_radar) {
        fprintf(stderr, "Erreur d'allocation mémoire !\n");
        return head;
    }
    new_radar->radar = *obj;
    new_radar->next = head;
    return new_radar;
}

void free_list(Radar *head) {
    while (head) {
        Radar *temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(Radar *head, const char *type) {
    printf("\nListe des %s détectés :\n", type);
    if (!head) {
        printf("Aucun %s détecté.\n", type);
        return;
    }
    
    int i = 0;
    while (head) {
        i++;
        printf("   🔹 %s #%d | ID: %d | Position: (x = %f, y = %f)\n",
               type, i, head->radar.id, head->radar.position.x, head->radar.position.y);
        head = head->next;
    }
}

int main(int argc, char *argv[]) {
    printf("Initialisation du bot\n");
    fflush(stdout);

    BC_Connection *conn = bc_connect("5.135.136.236", 8080);
    if (conn == NULL) {
        fprintf(stderr, "Erreur : Échec de la connexion au serveur.\n");
        return EXIT_FAILURE;
    }
    printf("Connexion réussie\n");
    fflush(stdout);

    BC_WorldInfo world = bc_get_world_info(conn);
    printf("Taille d'arene\nX: %d, Y: %d\n", world.map_x, world.map_y);
    fflush(stdout);

    BC_PlayerData data = bc_get_player_data(conn);
    Print_BC_PlayerData(&data);

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

        print_list(player_list, "Joueurs");
        print_list(wall_list, "Murs");

        usleep(3000000); 
    }

    free_list(player_list);
    free_list(wall_list);

    return EXIT_SUCCESS;
}
