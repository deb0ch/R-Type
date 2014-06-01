#ifndef WDIRECTORYLISTER_H_
# define WDIRECTORYLISTER_H_

# include "IDirectoryLister.hh"

class DirectoryLister : public IDirectoryLister
{
public:
  DirectoryLister();
  virtual ~DirectoryLister();

  virtual std::vector<std::string> listDirectory(const std::string &) const;
};

#endif /* !WDIRECTORYLISTER_H_ */
