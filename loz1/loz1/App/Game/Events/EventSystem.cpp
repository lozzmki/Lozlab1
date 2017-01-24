#include"EventSystem.h"

EventDispatcher* EventDispatcher::_instance = 0;

EventDispatcher::EventDispatcher(){}
EventDispatcher::~EventDispatcher(){}

EventDispatcher* EventDispatcher::getSingleton(){
	if(_instance)return _instance;
	else return _instance = new EventDispatcher();
}

void EventDispatcher::addListener(int eventid, IEventListener* plistener){
	if(!plistener)return;
	ListenerMap::iterator it = _listeners.find(eventid);
	if(it != _listeners.end()){
		ListenerList::iterator it2 = it->second.begin();
		for(;it2 != it->second.end();++it2){
			if(*it2 == plistener)return;
		}
		it->second.push_back(plistener);
	}else{
		ListenerList l;
		l.push_back(plistener);
		_listeners.insert(std::make_pair(eventid, l));
	}
}

void EventDispatcher::removeListener(int eventid, IEventListener* plistener){
	if(!plistener)return;
	ListenerMap::iterator it = _listeners.find(eventid);
	if(it != _listeners.end()){
		ListenerList::iterator it2 = it->second.begin();
		for(;it2 != it->second.end();++it2){
			if(*it2 == plistener){
				it->second.erase(it2);
				return;
			}
		}
	}
}

void EventDispatcher::fireEvent(const IEvent& e){
	ListenerMap::iterator it = _listeners.find(e._type);
	if(it != _listeners.end()){
		for(ListenerList::iterator it2 = it->second.begin();it2 != it->second.end(); ++it2){
			(*it2)->handleEvent(e);
		}
	}
}