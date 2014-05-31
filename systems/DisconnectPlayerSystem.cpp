#include "DisconnectPlayerSystem.hh"
#include "DisconnectPlayerEvent.hh"
#include "EntityDeletedEvent.hh"
#include "NetworkPlayerComponent.hh"

DisconnectPlayerSystem::DisconnectPlayerSystem() : ASystem("DisconnectPlayerSystem")
{}

DisconnectPlayerSystem::~DisconnectPlayerSystem()
{}

void		DisconnectPlayerSystem::init()
{
  this->_world->addEventHandler("DisconnectPlayerEvent", this, &DisconnectPlayerSystem::disconnectPlayerHandler);
}

bool		DisconnectPlayerSystem::canProcess(Entity *)
{
  return false;
}

void		DisconnectPlayerSystem::processEntity(Entity *, const float)
{}

void		DisconnectPlayerSystem::disconnectPlayerHandler(IEvent *event)
{
  DisconnectPlayerEvent *disconnect_event = dynamic_cast<DisconnectPlayerEvent *>(event);

  std::for_each(this->_world->getEntities().begin(), this->_world->getEntities().end(),
		[&disconnect_event, this] (Entity *entity)
		{
		  NetworkPlayerComponent *player_comp;

		  if ((player_comp = entity->getComponent<NetworkPlayerComponent>("NetworkPlayerComponent")))
		    {
		      player_comp->setRespawn(false);
		      if (player_comp->getRemoteId() == disconnect_event->getRemoteId())
			this->_world->sendEvent(new EntityDeletedEvent(entity));
		    }
		});
}
