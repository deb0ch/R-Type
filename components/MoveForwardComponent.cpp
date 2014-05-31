#include "MoveForwardComponent.hh"
#include "Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveForwardComponent::MoveForwardComponent(const std::string &dir1, const std::string &dir2)
: ACopyableComponent("MoveForwardComponent")
{
  this->_direction1 = dir1;
  this->_direction2 = dir2;
}

//----- ----- Destructor ----- ----- //
MoveForwardComponent::~MoveForwardComponent()
{}

//----- ----- Methods ----- ----- //

const std::pair<std::string, std::string>	MoveForwardComponent::getDirection() const
{
	return (std::make_pair(this->_direction1, this->_direction2));
}

void	MoveForwardComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_direction1;
  buffer << this->_direction2;
}

void	MoveForwardComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_direction1;
  buffer >> this->_direction2;
}

void	MoveForwardComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("dir1=.+")))
    this->_direction1 = lastline.substr(5);
  else if (std::regex_match(lastline, std::regex("dir2=.+")))
    this->_direction2 = lastline.substr(5);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void		MoveForwardComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  if (this->_direction1 != "")
    output << std::string(indent, '\t') << "dir1=" << this->_direction1 << std::endl;
  if (this->_direction2 != "")
    output << std::string(indent, '\t') << "dir2=" << this->_direction2 << std::endl;
}
