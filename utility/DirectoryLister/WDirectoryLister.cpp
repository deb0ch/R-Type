#ifdef _WIN32

#include "WDirectoryLister.hh"

DirectoryLister::DirectoryLister()
{}

DirectoryLister::~DirectoryLister()
{}

std::vector<std::string> DirectoryLister::listDirectory(const std::string &)
{
  return std::vector<std::string>();
}

#endif
