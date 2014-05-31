#ifndef IDIRECTORYLISTER_H_
# define IDIRECTORYLISTER_H_

#include <vector>

class IDirectoryLister
{
public:
  virtual ~IDirectoryLister()
  {}

  virtual std::vector<std::string> listDirectory(const std::string &) = 0;
};

#endif /* !IDIRECTORYLISTER_H_ */
