#ifdef __linux__

#include <dirent.h>
#include <cerrno>
#include <cstring>
#include <cstddef>
#include <unistd.h>

#include "UDirectoryLister.hh"
#include "RTException.hh"

DirectoryLister::DirectoryLister()
{}

DirectoryLister::~DirectoryLister()
{}

std::vector<std::string> DirectoryLister::listDirectory(const std::string &directory) const
{
  DIR				*dir;
  struct dirent			file;
  struct dirent			*buffer;
  std::vector<std::string>	result;
  int				name_max;
  int				len;
  int				error_num;

  name_max = pathconf(directory.c_str(), _PC_NAME_MAX);
  if (name_max == -1)
    throw RTException(std::string("Maximum file name size is not defined in directory ")
		      + directory + ": "
		      + std::string(strerror(errno)));
  len = offsetof(struct dirent, d_name) + name_max + 1;
  buffer = reinterpret_cast<struct dirent *>(new char[len]);

  if (!(dir = opendir(directory.c_str())))
    throw RTException(std::string("Cannot open dir ") + directory + ": "
		      + std::string(strerror(errno)));

  error_num = 0;
  while (dir && (error_num = readdir_r(dir, &file, &buffer)) == 0 && buffer)
    {
      if (file.d_name[0] == '.')
	continue ;
      result.push_back(file.d_name);
    }
  if (error_num != 0)
    throw RTException(std::string("Cannot readdir ") + directory + ": "
		      + std::string(strerror(error_num)));
  return result;
}

#endif /* !__linux__ */
