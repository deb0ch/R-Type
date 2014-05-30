#include <algorithm>
#include "TagComponent.hh"

TagComponent::TagComponent() : ACopyableComponent("TagComponent"){
  this->_tags = std::vector<std::string >();
}

TagComponent::~TagComponent(){

}

TagComponent *TagComponent::addTag(const std::string& tag)
{
  auto it = std::find(this->_tags.begin(), this->_tags.end(), tag);

  if (it == this->_tags.end()) {
    this->_tags.push_back(tag);
  }
  return this;
}

bool TagComponent::hasTag(const std::string& tag) const
{
  auto it = std::find(this->_tags.begin(), this->_tags.end(), tag);

  return (it != this->_tags.end());
}

void TagComponent::removeTag(const std::string& tag)
{
  auto it = std::find(this->_tags.begin(), this->_tags.end(), tag);

  if (it != this->_tags.end()) {
    this->_tags.erase(it);
  }
}

void	TagComponent::serialize(IBuffer &buffer) const
{
  auto itEnd = this->_tags.end();

  buffer << static_cast<unsigned int>(this->_tags.size());
  for (auto it = this->_tags.begin(); it != itEnd; ++it) {
    buffer << *it;
  }
}

void	TagComponent::unserialize(IBuffer &buffer)
{
  unsigned int nb_string;
  buffer >> nb_string;

  this->_tags.clear();
  for (unsigned int i = 0; i < nb_string; ++i)
    {
      std::string s;
      buffer >> s;
      this->_tags.push_back(s);
    }
}

void	TagComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("tag=.+")))
    this->addTag(lastline.substr(4));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	TagComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  std::for_each(this->_tags.begin(), this->_tags.end(), [&output, indent](const std::string &tag)
		{
		  output << std::string(indent, '\t') << "tag=" << tag << std::endl;
		});
}
