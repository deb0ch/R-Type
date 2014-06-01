#ifndef SFMLRENDERSCORESYSTEM_H_
# define SFMLRENDERSCORESYSTEM_H_

# include		"Pos2DComponent.hh"
# include		"ASystem.hh"

class			SFMLDisplayScoreSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

public:
  SFMLDisplayScoreSystem();
  virtual		~SFMLDisplayScoreSystem();

};

#endif /* !SFMLRENDERSCORESYSTEM_H_ */
