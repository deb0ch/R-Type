#include <sstream>
#include <cstring>
#include "ImageLoaderException.hh"

ImageLoaderException::ImageLoaderException(const int error)
  : RTException("ImageLoaderException : ", error)
{}

ImageLoaderException::ImageLoaderException(const std::string &error)
  : RTException("ImageLoaderException : ", error)
{}
