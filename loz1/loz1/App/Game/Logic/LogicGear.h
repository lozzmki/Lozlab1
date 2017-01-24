#ifndef LOGICGEAR_H
#define LOGICGEAR_H

#include"BaseGameLogic.h"
#include"../Interfaces.h"
#include"../../Utilities/Vector2D.h"
#include"../../Utilities/Common.h"
#include"../Events/Interfaces.h"
#include<map>
#include<string>
#include<list>
#include<set>

class Gauge{
	
public:
	Gauge(double max=10.0, double reg=1.0, double val=10.0):d_dMaxValue(max),d_dValue(val),d_dRegenSpeed(reg){
	}
	enum ValueType{
		GAUGE_VALUE,
		GAUGE_MAXVALUE,
		GAUGE_REGENSPEED
	};
	enum Event{
		GAUGE_EVENT_VALUEHITZERO,
		GAUGE_EVENT_VALUEDECREASING,
		GAUGE_EVENT_VALUEINCREASING,
		GAUGE_EVENT_VALUEDECREASED,
		GAUGE_EVENT_VALUEINCREASED,
		GAUGE_EVENT_VALUEHITLIMIT,
	};
	void update(double deltaTime);
	void adjustValue(ValueType, double val, bool bIncrease=true);
	void setValue(ValueType, double val);

	template<class T>
	void setHandler(Event, CallbackFunction<T>*);

private:
	double d_dMaxValue;
	double d_dValue;
	double d_dRegenSpeed;

	ICallback* d_handleZeroValue;
	ICallback* d_handleFullValue;
	ICallback* d_handleBeforeValueIncrease;
	ICallback* d_handleBeforeValueDecrease;
	ICallback* d_handleAfterValueIncrease;
	ICallback* d_handleAfterValueDecrease;
};

template<typename T>
struct ValuePair{
	T offense, defense;
};

template<typename T>
struct BufferedValue{
	T value, buffer;
	T real(){return value+buffer;}
	BufferedValue(){value=0;buffer=0;}
};

typedef BufferedValue<double> buffered_double;
typedef BufferedValue<int> buffered_int;
typedef ValuePair<buffered_double> double_pair;

class Attribute{
public:
	Attribute();

	//hit point mana point
	Gauge d_hp, d_mp;
	//offense & defense pairs
	double_pair d_physical;
	double_pair d_fire;
	double_pair d_frost;
	double_pair d_lightning;
	double_pair d_terra;
	double_pair d_light;
	double_pair d_darkness;

	//speed
	buffered_double d_movespeed;
	
	//crit
	buffered_double d_criticalrate;
	buffered_double d_criticalboost;
};

class FlagMap{

public:
	FlagMap(){d_map.clear();}
	
	void setValue(std::string key, bool val);
	bool getValue(std::string key);

protected:
	std::map<std::string,bool> d_map;
};

enum State{
	STATE_IDLE,
	STATE_MOVING,
	STATE_ATTACK,//¹¥»÷¡¢ÒÆ¶¯¹¥»÷
	STATE_CASTING,
	STATE_LOSTCONTROL,
	STATE_DEAD
};

//½ÇÉ«ÒÆ¶¯¿ØÖÆ
class Motor:public IEventListener{

public:
	Motor();
	virtual ~Motor();
	enum Direction{
		DIRECTION_RIGHT,
		DIRECTION_UPRIGHT,
		DIRECTION_UP,
		DIRECTION_UPLEFT,
		DIRECTION_LEFT,
		DIRECTION_DOWNLEFT,
		DIRECTION_DOWN,
		DIRECTION_DOWNRIGHT,
		DIRECTION_UNKNOWN
	};
	enum Control{
		MOTOR_RIGHT,
		MOTOR_UP,
		MOTOR_LEFT,
		MOTOR_DOWN
	};
	
	Direction getDirection();
	virtual bool handleEvent(const IEvent& e);

private:
	bool _l, _r, _u, _d;//×óÓÒÉÏÏÂ
	void setControl(Control, bool pressd);
	
};

//Åö×²Ìå	
class Collider{
public:
	Collider(double radius=0.0);
	virtual ~Collider();

	bool checkCollide(Vec2d& force, const Collider& target);
	inline void updatePosition(Vec2d pos){m_vPos = pos;}

	inline Vec2d getPos() const{return m_vPos;}
	inline double getRadius() const{return m_dRadius;}
private:
	Vec2d m_vPos;
	double m_dRadius;
};

#endif