#ifndef IMAGELOADEREXCEPTION_H_
# define IMAGELOADEREXCEPTION_H_

# include "RTException.hh"

class ImageLoaderException : public RTException
{

public:
  ImageLoaderException(const int error);
  ImageLoaderException(const std::string &error);
  ~ImageLoaderException() throw() {}

};


#endif /* !IMAGELOADEREXCEPTION_H_ */
