#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "AComponent.hpp"
# include "ImageLoader.hh"
# include "ISerializableComponent.hh"
# include "INetworkSerializableComponent.hh"

class		SFMLSpriteComponent : public AComponent<SFMLSpriteComponent>,
	public INetworkSerializableComponent
{
protected:
	std::string	_fileName;
	ImageLoader::NbSprite _sprites;
	int _counter;
	unsigned int _tickCounter;
	unsigned int _tickChange;
	std::string _previousAction;
	int _currentSprite;
	std::map<std::string, std::pair<int, int> > _map;

public:
	SFMLSpriteComponent();
	SFMLSpriteComponent(const std::string &filename, const ImageLoader::NbSprite& sprites,
		const std::map<std::string, std::pair<int, int> > &map, unsigned int tickChange = 10);

	virtual	~SFMLSpriteComponent();

	virtual	void serialize(IBuffer &buffer) const;
	virtual	void unserialize(IBuffer &buffer);

	sf::Sprite	*getSprite(ImageLoader &imageLoader, const std::string & action = "");
	bool		hasAction(const std::string & action);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
