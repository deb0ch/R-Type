#ifndef SFMLSPRITECOMPONENT_H_
# define SFMLSPRITECOMPONENT_H_

# include "ACopyableComponent.hpp"

class		SFMLSpriteComponent : public ACopyableComponent<SFMLSpriteComponent>
{
protected:
  std::string					_fileName;
  std::pair<int, int>				_sprites;
  int						_counter;
  unsigned int					_tickCounter;
  unsigned int					_tickChange;
  std::string					_previousAction;
  int						_currentSprite;
  std::map<std::string, std::pair<int, int> >	_map;
  int						_first;
  int						_nbSprite;

public:
  SFMLSpriteComponent();
  SFMLSpriteComponent(const std::string &filename, const std::pair<int, int>& sprites,
		      const std::map<std::string, std::pair<int, int> > &map,
		      unsigned int tickChange = 10);

  virtual		~SFMLSpriteComponent();

  virtual	void	serialize(IBuffer &buffer) const;
  virtual	void	unserialize(IBuffer &buffer);
  const std::string	&getFileName() const;

  int			getCurrentSpriteNumber(const std::string &action);

  const std::pair<int, int> &getSpriteDim() const;

  // sf::Sprite	*getSprite(ImageLoader &imageLoader, const std::string & action = "");

  bool		hasAction(const std::string & action);
  virtual void		deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

private:
  // sf::Sprite	*getSpriteWithoutMap(ImageLoader &imageLoader, const std::string & action = "");
  // sf::Sprite	*getSpriteFromMap(ImageLoader &imageLoader, const std::string & action = "");
};

#endif /* !SFMLSPRITECOMPONENT_H_ */
