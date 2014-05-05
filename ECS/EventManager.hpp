#ifndef EVENTMANAGER_H_
# define EVENTMANAGER_H_

# include <map>
# include <string>
# include <algorithm>
# include "IEvent.hh"

template <typename T>
class EventManager
{
public:
		EventManager()
  {}

  virtual	~EventManager()
  {}

  void		addHandler(const std::string &type, T *obj, void (T::*e)(IEvent *))
  {
    if (!this->hasHandler(type))
      this->_event_handlers.insert(std::make_pair(type, std::make_pair(obj, e)));
  }

  bool		hasHandler(const std::string &type) const
  {
    return (this->_event_handlers.find(type) !=
	    this->_event_handlers.end());
  }

  /**
   * @todo Change the parameter from IEvent* to IEvent.
   */
  void		sendEvent(IEvent *event)
  {
    auto it = this->_event_handlers.begin();

    do
      {
	it = std::find_if(it, this->_event_handlers.end(),
			  [event] (std::pair<std::string,
				   std::pair<T *, void (T::*)(IEvent *)> > value) -> bool {
	    if (value.first == event->getType())
	      return (true);
	    return (false);
	  });

	if (it != this->_event_handlers.end())
	  {
	    (((it->second).first)->*((it->second.second)))(event);
	    ++it;
	  }

      } while (it != this->_event_handlers.end());
  }

protected:
  std::map<std::string, std::pair<T *, void (T::*)(IEvent *)> >	_event_handlers;
};

#endif /* !EVENTMANAGER_H_ */
