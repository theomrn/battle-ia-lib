#include "battle_c.h"
#include "battle_c.pb.h"
#include "list.hpp"
#include "tcp_client.hpp"
#include <cstddef>

extern "C" {
BC_Connection *bc_connect(const char *host, int port) {
  try {
    // Create a new TCPClient instance
    TCPClient *client = new TCPClient();

    // Attempt to connect
    client->Connect(std::string(host), port);
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
    }

    // Send initial client message
    {
      ClientServerMessage message;
      ClientInit *client_init = new ClientInit();
      client_init->set_is_spectator(false);
      message.set_allocated_client_init(client_init);
      client->QueueMessage(message);
    }

    // Return the connection handle
    return (BC_Connection *)client;
  } catch (const boost::system::system_error &e) {
    std::cerr << "Boost.Asio error during connection: " << e.what()
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Standard exception during connection: " << e.what()
              << std::endl;
  } catch (...) {
    std::cerr << "Unknown error occurred during connection." << std::endl;
  }

  // Return NULL if an error occurred
  return nullptr;
}

bool filter_wo(ServerClientMessage message) {
  return message.has_world_options();
}

BC_WorldInfo bc_get_world_info(BC_Connection *connection) {
  TCPClient *client = (TCPClient *)connection;

  ClientServerMessage message;

  message.set_get_world_info(true);

  client->QueueMessage(message);

  ServerClientMessage response = client->WaitForMessage(filter_wo);
  std::cout << "Got response, mapX=" << response.world_options().map_x()
            << " mapY=" << response.world_options().map_y() << std::endl;

  return {};
}
BC_PlayerData bc_get_player_data(BC_Connection *connection) {
  TCPClient *client = (TCPClient *)connection;
  return client->GetPlayerData();
}

void bc_set_speed(BC_Connection *connection, double x, double y, double z) {
  TCPClient *client = (TCPClient *)connection;
  ClientServerMessage message;
  message.mutable_set_speed()->set_x(x);
  message.mutable_set_speed()->set_y(y);
  message.mutable_set_speed()->set_z(z);

  client->QueueMessage(message);
}

bool filter_rr(ServerClientMessage message) {
  return message.has_radar_result();
}
BC_List *bc_radar_ping(BC_Connection *connection) {
  TCPClient *client = (TCPClient *)connection;

  ClientServerMessage message;

  message.set_radar_ping(100);

  client->QueueMessage(message);

  ServerClientMessage response = client->WaitForMessage(filter_rr);
  std::cout << "Got response " << response.DebugString() << std::endl;
  auto radar_result = response.radar_result();
  size_t radar_return_size = radar_result.radar_return_size();

  LinkedList *ll = nullptr;

  for (size_t i = 0; i < radar_return_size; i++) {
    auto radar_return = radar_result.radar_return(i);

    BC_MapObject *bc_map_object = (BC_MapObject *)malloc(sizeof(BC_MapObject));
    bc_map_object->position.x = radar_return.position().x();
    bc_map_object->position.y = radar_return.position().y();

    bc_map_object->speed.x = radar_return.speed().x();
    bc_map_object->speed.y = radar_return.speed().y();

    bc_map_object->id = radar_return.id();

    LinkedList *entry = new LinkedList(bc_map_object);
    LinkedList::Add(ll, entry);
    ll = entry;
  }

  return (BC_List *)LinkedList::Rewind(ll);
}

BC_List *bc_ll_next(BC_List *linked_list) {
  return (BC_List *)LinkedList::Next((LinkedList *)linked_list);
}
void *bc_ll_value(BC_List *linked_list) {
  return (void *)LinkedList::Value((LinkedList *)linked_list);
}
}
