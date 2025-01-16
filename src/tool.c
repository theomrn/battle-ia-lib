#include "battle_c.h"
#include "tool.h"

char* BC_ObjectTypeToString(enum BC_ObjectType type) {
    switch (type) {
        case OT_PLAYER: return "PLAYER";
        case OT_WALL:   return "WALL";
        case OT_BOOST:  return "BOOST";
        default:        return "UNKNOWN";
    }
}

void Print_BC_PlayerData(struct BC_PlayerData_ data) {
    printf("Player id : %d, health : %d, armor : %d, score : %d\n",
    data.id,
    data.health,
    data.armor,
    data.score
    );
    return;
}