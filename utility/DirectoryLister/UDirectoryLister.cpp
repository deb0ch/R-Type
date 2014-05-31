#ifdef __linux__

#include "UDirectoryLister.hh"

DirectoryLister::DirectoryLister()
{}

DirectoryLister::~DirectoryLister()
{}

std::vector<std::string> DirectoryLister::listDirectory(const std::string &)
{
  return std::vector<std::string>();
}

#endif
