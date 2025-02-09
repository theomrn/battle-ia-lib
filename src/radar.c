// Custom libraries
#include "battle_c.h"
#include "tool.h"
#include "radar.h"

// Standard libraries
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <math.h>

// Create a list for the radar
Radar *Radar_list(Radar *head, BC_MapObject *obj)
{
    Radar *new_radar = (Radar *)malloc(sizeof(Radar));
    if (!new_radar)
    {
        fprintf(stderr, "Erreur d'allocation mémoire !\n");
        return head;
    }
    new_radar->radar = *obj;
    new_radar->next = head;
    return new_radar;
}

// Free the radar list
void free_list(Radar *head)
{
    while (head)
    {
        Radar *temp = head;
        head = head->next;
        free(temp);
    }
}

// Print the radar list
void print_list(Radar *head, const char *type)
{
    printf("\nListe des %s détectés :\n", type);
    if (!head)
    {
        printf("Aucun %s détecté.\n", type);
        return;
    }

    int i = 0;
    while (head)
    {
        i++;
        printf("   🔹 %s #%d | ID: %d | Position: (x = %f, y = %f)\n",
               type, i, head->radar.id, head->radar.position.x, head->radar.position.y);
        head = head->next;
    }
}

// Ping the map
void process_radar_ping(BC_Connection *conn, BC_WorldInfo world, Radar **player_list, Radar **wall_list, Radar **boost_list)
{
    BC_List *list = bc_radar_ping(conn);
    if (list == NULL)
    {
        printf("Aucun objet détecté.\n");
        fflush(stdout);
    }
    else
    {
        free_list(*player_list);
        free_list(*wall_list);
        free_list(*boost_list);
        *player_list = NULL;
        *wall_list = NULL;
        *boost_list = NULL;

        BC_List *head = list;
        do
        {
            BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(list);
            if (map_object->type == OT_PLAYER)
            {
                *player_list = Radar_list(*player_list, map_object);
            }
            else if (map_object->type == OT_WALL)
            {
                *wall_list = Radar_list(*wall_list, map_object);
            }
            else if (map_object->type == OT_BOOST)
            {
                // Check if the boost is in the walls, the tank may be stuck if the boost is near the limit of the map
                if ((map_object->position.x > 1.0) && (map_object->position.x < world.map_x - 1.0) && (map_object->position.y > 1.0) && (map_object->position.y < world.map_y - 1.0))
                {
                    *boost_list = Radar_list(*boost_list, map_object);
                }
            }

        } while ((list = bc_ll_next(list)) != NULL);
        bc_ll_free(head);
    }
}

// Nearest object
BC_MapObject nearest(Radar *list, BC_PlayerData data){
    BC_MapObject nearest;
    float distance = 142; // Maximum distance between two points if the arena is 100x100
    while (list)
    {
        float x = list->radar.position.x - data.position.x;
        float y = list->radar.position.y - data.position.y;
        float d = sqrt(x * x + y * y);
        if (d < distance && data.id != list->radar.id)
        {
            distance = d;
            nearest = list->radar;
        }
        list = list->next;
    }
    printf("nearest: %d, x: %f, y: %f\n", nearest.id, nearest.position.x, nearest.position.y);
    return nearest;
}