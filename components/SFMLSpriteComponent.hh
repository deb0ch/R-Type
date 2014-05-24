#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "SFML/Graphics.hpp"
# include "ImageLoader.hh"
# include "ACopyableComponent.hpp"

class		SFMLSpriteComponent : public ACopyableComponent<SFMLSpriteComponent>
{
protected:
	std::string					_fileName;
	ImageLoader::NbSprite				_sprites;
	int						_counter;
	unsigned int					_tickCounter;
	unsigned int					_tickChange;
	std::string					_previousAction;
	int						_currentSprite;
	std::map<std::string, std::pair<int, int> >	_map;
	bool						_mapexist;

public:
	SFMLSpriteComponent();
	SFMLSpriteComponent(const std::string &filename, const ImageLoader::NbSprite& sprites,
			    const std::map<std::string, std::pair<int, int> > &map,
			    unsigned int tickChange = 10);

	virtual		~SFMLSpriteComponent();

	virtual	void	serialize(IBuffer &buffer) const;
	virtual	void	unserialize(IBuffer &buffer);

	sf::Sprite	*getSprite(ImageLoader &imageLoader, const std::string & action = "");
	bool		hasAction(const std::string & action);
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
