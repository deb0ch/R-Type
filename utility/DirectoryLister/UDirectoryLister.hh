#ifndef UDIRECTORYLISTER_H_
# define UDIRECTORYLISTER_H_

# include "IDirectoryLister.hh"

class DirectoryLister : public IDirectoryLister
{
public:
  DirectoryLister();
  virtual ~DirectoryLister();
  virtual std::vector<std::string> listDirectory(const std::string &);
};

#endif /* !UDIRECTORYLISTER_H_ */
