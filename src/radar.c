#include "battle_c.h"
#include "tool.h"
#include "radar.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

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