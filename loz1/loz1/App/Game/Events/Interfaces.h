#ifndef EVENTINTERFACE_H
#define EVENTINTERFACE_H

struct IEvent{
	int _type;
	int _arg1, _arg2;
};

struct IEventListener{
	virtual bool handleEvent(const IEvent& e)=0;
};

#endif