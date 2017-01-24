#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include"Interfaces.h"
#include<map>
#include<list>

typedef std::list<IEventListener*> ListenerList;
typedef std::map<int, ListenerList> ListenerMap;

enum EventType{

	//Gauge
	EVENT_TYPE_KEYDOWN,
	EVENT_TYPE_KEYUP,

	EVENT_TYPE_MAX,
};

class EventDispatcher{
public:
	~EventDispatcher();
	static EventDispatcher* getSingleton();
	void fireEvent(const IEvent& e);

	void addListener(int eventid, IEventListener* plistener);
	void removeListener(int eventid, IEventListener* plistener);

private:
	EventDispatcher();
	static EventDispatcher* _instance;
	ListenerMap _listeners;
};

#endif