#ifdef _WIN32

# include <iostream>
# include <windows.h>
# include <tchar.h>
# include <cstdio>
# include <strsafe.h>

#include "WDirectoryLister.hh"

#pragma comment(lib, "User32.lib")

DirectoryLister::DirectoryLister()
{}

DirectoryLister::~DirectoryLister()
{}

std::vector<std::string> DirectoryLister::listDirectory(const std::string &str) const
{
  WIN32_FIND_DATA ffd;
  TCHAR szDir[MAX_PATH];
  size_t length_of_arg;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  DWORD dwError = 0;
  std::vector<std::string> res;

  TCHAR *path = new TCHAR[str.size() + 1];
  path[str.size()] = 0;
  std::copy(str.begin(), str.end(), path);
  StringCchLength(path, MAX_PATH, &length_of_arg);
  StringCchCopy(szDir, MAX_PATH, path);
  StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
  hFind = FindFirstFile(szDir, &ffd);	// Find the first file in the directory.
  if (INVALID_HANDLE_VALUE == hFind)
    return std::vector<std::string>();
  do	// List all the files in the directory with some info about them.
    {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	continue;
      else
	{
	  std::string tempo(ffd.cFileName);
	  res.push_back(tempo);
	}
    } while (FindNextFile(hFind, &ffd) != 0);
  dwError = GetLastError();
  if (dwError != ERROR_NO_MORE_FILES)
    return std::vector<std::string>();
  FindClose(hFind);
  return res;
}

#endif /* !_WIN32 */
