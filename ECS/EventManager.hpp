#ifndef EVENTMANAGER_H_
# define EVENTMANAGER_H_

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include <algorithm>
# include "IEvent.hh"

template <typename T>
/**
 * @todo removeHandler
 */
class EventManager
{
protected:
  std::map<std::string, std::vector<std::pair<T *, void (T::*)(IEvent *)> > >	_event_handlers;

public:
		EventManager()
  {}

  virtual	~EventManager()
  {}

  bool		hasHandler(const std::string &type) const {
    auto it = this->_event_handlers.find(type);
    return  it != this->_event_handlers.end();
  }

  /**
   * @todo template
   */
  void		addHandler(const std::string &type, T *obj, void (T::*e)(IEvent *))
  {
    auto it = this->_event_handlers.find(type);
    if (it != this->_event_handlers.end()) {
      auto itSecond = it->second.begin();
      for (itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
	if (itSecond->second == e)
	  return ;
      }
      it->second.push_back(std::make_pair(obj, e));
      return ;
    }
    this->_event_handlers[type].push_back(std::make_pair(obj, e));
  }

  /**
   * @todo Change the parameter from IEvent* to IEvent.
   */
  void		sendEvent(IEvent *event) {
    auto it = this->_event_handlers.find(event->getType());
    if (it != this->_event_handlers.end()) {
      for (auto itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
	((itSecond->first)->*((itSecond->second)))(event);
      }
    }
  }

  /*
  void		removeHandler(T *obj)
  {
    removeHandler([obj] (std::pair<std::string,
			 std::pair<T *, void (T::*)(IEvent *)> > value) -> bool {
		    if (value.second.first == obj)
		      return (true);
		    return (false);
		  });
  }

  void		removeHandler(T *obj, const std::string &type)
  {
    removeHandler([obj, type] (std::pair<std::string,
			 std::pair<T *, void (T::*)(IEvent *)> > value) -> bool {
		    if (value.second.first == obj && value.first == type)
		      return (true);
		    return (false);
		  });
  }
  */
private:
  /*
  template <typename U>
  void		removeHandler(U cond)
  {
    auto it = this->_event_handlers.begin();

    do
      {
	it = std::find_if(it, this->_event_handlers.end(), cond);

	if (it != this->_event_handlers.end())
	  it = this->_event_handlers.erase(it);

      } while (it != this->_event_handlers.end());
  }
  */
};

#endif /* !EVENTMANAGER_H_ */
