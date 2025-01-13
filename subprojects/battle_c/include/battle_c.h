#ifndef BATTLE_C_H
#define BATTLE_C_H

#include "stdbool.h"
#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque Connection object
 */
typedef struct BC_Connection_ {
} BC_Connection;

/**
 * Opaque List
 */
typedef struct BC_List_ {

} BC_List;

typedef struct BC_Vector3_ {
  int x;
  int y;
  int z;
} BC_Vector3;

typedef struct BC_Vector2_ {
  int x;
  int y;
  int z;
} BC_Vector2;

enum BC_ObjectType { OT_PLAYER, OT_WALL, OT_BOOST };

typedef struct BC_PlayerData_ {
  int id;
  BC_Vector3 position;
  BC_Vector3 speed;
  int health;
} BC_PlayerData;

typedef struct BC_BoostObjectData_ {
  int health;
} BC_BoostObjectData;

typedef struct BC_MapObject_ {
  enum BC_ObjectType type;
  int id;
  BC_Vector3 position;
  BC_Vector3 speed;
  int health;
} BC_MapObject;

typedef struct BC_WorldInfo_ {
  uint64_t map_x;
  uint64_t map_y;
  uint32_t player_count;
  bool auto_shoot_enabled;
  bool radar_enabled;
} BC_WorldInfo;

/**
 * @brief Creates a connection to {address} on {port}
 * @return an opaque Connection object
 */
BC_Connection *bc_connect(const char *address, int port);

BC_WorldInfo bc_get_world_info(BC_Connection *connection);

void bc_disconnect(BC_Connection *connection);

/**
 * @brief Returns local player's data
 * @return BC_PlayerData object
 */
BC_PlayerData bc_get_player_data(BC_Connection *connection);

void bc_set_speed(BC_Connection *connection, double x, double y, double z);

/**
 * @brief Sends a radar ping
 * @return An opaque list of MapObject_
 */
BC_List *bc_radar_ping(BC_Connection *connection);

BC_List *bc_ll_next(BC_List *bc_list);

void *bc_ll_value(BC_List *bc_list);

#ifdef __cplusplus
}
#endif

#endif
