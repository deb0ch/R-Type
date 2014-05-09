#include <sstream>
#include <cstring>
#include "ImageLoaderException.hh"

ImageLoaderException::ImageLoaderException(const int error)
  : RTException(error, "ImageLoaderException : ")
{}

ImageLoaderException::ImageLoaderException(const std::string &error)
  : RTException(error, "ImageLoaderException : ")
{}
