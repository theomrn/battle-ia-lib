#ifndef _RADAR_H_
#define _RADAR_H_

#include "battle_c.h"

typedef struct Radar {
    BC_MapObject radar;
    struct Radar *next;
} Radar;

Radar *Radar_list(Radar *head, BC_MapObject *obj);
void free_list(Radar *head);
void print_list(Radar *head, const char *type);

#endif