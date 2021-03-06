#ifndef NETWORKPLAYERCOMPONENT_H_
# define NETWORKPLAYERCOMPONENT_H_

# include "ASerializableComponent.hh"
# include "ActionComponent.hh"

class NetworkPlayerComponent : public ASerializableComponent
{
public:
  NetworkPlayerComponent(unsigned int hash = 0, const std::string &entity_name = "PLAYER_RED");
  NetworkPlayerComponent(const NetworkPlayerComponent &);
  virtual				~NetworkPlayerComponent();
  NetworkPlayerComponent		&operator=(const NetworkPlayerComponent &);

  NetworkPlayerComponent		*setRemoteId(unsigned int);
  unsigned int				getRemoteId() const;
  virtual ASerializableComponent	*cloneSerializable() const;
  virtual void				serialize(IBuffer &) const;
  virtual void				unserialize(IBuffer &);
  virtual void				networkSerialize(Remote *remote, IBuffer &,
							 bool send_force = false) const;
  void					setRespawn(bool);
  bool					canRespawn() const;
  const std::string			&getEntityName() const;

  NetworkPlayerComponent		*addPlayerComponent(ASerializableComponent *component);
  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  unsigned int				_remote_hash;
  std::string				_entity_name;
  std::vector<ASerializableComponent *>	_components;
  bool					_can_respawn;
  const static std::vector<std::string>	_non_update_component;
};

#endif /* !NETWORKPLAYERCOMPONENT_H_ */
