#include "UDirectoryLister.hh"

DirectoryLister::DirectoryLister()
{}

DirectoryLister::~DirectoryLister()
{}

virtual std::vector<std::string> DirectoryLister::listDirectory(const std::string &)
{
  return std::vector<std::string>();
}
