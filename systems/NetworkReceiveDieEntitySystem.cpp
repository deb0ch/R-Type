#include "Entity.hh"
#include "NetworkSendUpdateSystem.hh"
#include "ASerializableComponent.hh"
#include "NetworkBuffer.hh"
#include "ComponentFactory.hpp"
#include "Hash.hh"
#include "EntityDeletedEvent.hh"
#include "NetworkReceiveDieEntitySystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "LockGuard.hpp"

NetworkReceiveDieEntitySystem::NetworkReceiveDieEntitySystem()
  : ASystem("NetworkReceiveDieEntitySystem")
{
}

NetworkReceiveDieEntitySystem::~NetworkReceiveDieEntitySystem() {}


void NetworkReceiveDieEntitySystem::beforeProcess(const float) {
  this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}


bool NetworkReceiveDieEntitySystem::canProcess(Entity *) {return (false);}
void NetworkReceiveDieEntitySystem::processEntity(Entity *, const float) {}

void NetworkReceiveDieEntitySystem::afterProcess(const float)
{
  Room *room;

  if (_network && _room_name && (room = this->_network->getRoom(*this->_room_name)))
    {
      auto guard = create_lock(*room, true);

      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this] (Remote *remote) -> void
		    {
		      LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		      auto guard = create_lock(recv_buffer);

		      for (auto it = recv_buffer.begin(); it != recv_buffer.end();)
			{
			  this->parsePacket(recv_buffer, it);
			}
		    });
    }
}

// -------------- Private functions --------------
void NetworkReceiveDieEntitySystem::parsePacket(LockVector<IBuffer *> &vector,
						LockVector<IBuffer *>::iterator &it)
{
  unsigned int	id_entity;
  char		packet_type;
  IBuffer	*buffer;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == KILL_ENTITY)
    {
      *buffer >> id_entity;
      std::vector<Entity *> &entites = this->_world->getEntities();
      std::for_each(entites.begin(), entites.end(),
		    [&id_entity, this] (Entity *entity)
		    {
		      NetworkReceiveUpdateComponent *update_comp;

		      update_comp =
			entity->getComponent<NetworkReceiveUpdateComponent>
			("NetworkReceiveUpdateComponent");
		      if (update_comp)
			{
			  if (update_comp->getRemoteID() == id_entity)
			    {
			      this->_world->sendEvent(new EntityDeletedEvent(entity));
			    }
			}
		    });
      this->_network->disposeUDPBuffer(buffer);
      it = vector.erase(it);
    }
  else
    ++it;
}
