#ifndef		ISOCKET_H_
# define	ISOCKET_H_

# include <string>
# include <iostream>

# define MSG_INVALID_SOCKET "The socket is invalid"

class ISocket
{
public:
  virtual ~ISocket(){};
  virtual void	setBlocking(const bool blocking) = 0;
  virtual bool	isBlocking() const = 0;
  virtual void	bind(const int port, const std::string & address = "") = 0;
  virtual int	getHandle() const = 0;

  virtual void	close() = 0;
  virtual void	init() = 0;
};

#endif /* !ISOCKET_H_ */
