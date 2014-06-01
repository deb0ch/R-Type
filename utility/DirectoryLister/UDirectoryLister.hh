#ifndef UDIRECTORYLISTER_H_
# define UDIRECTORYLISTER_H_

# include "IDirectoryLister.hh"

class DirectoryLister : public IDirectoryLister
{
public:
  DirectoryLister();
  virtual ~DirectoryLister();

  virtual std::vector<std::string> listDirectory(const std::string &) const;
};

#endif /* !UDIRECTORYLISTER_H_ */
