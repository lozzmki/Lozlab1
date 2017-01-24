#include"LogicGear.h"
#include"../Events/EventSystem.h"


bool dEqual(double d1, double d2){
	double delta = d1-d2;
	return delta>-1e-6 && delta<1e-6;
}


void Gauge::update(double deltaTime){
	double _temp = d_dRegenSpeed * deltaTime;

	adjustValue(Gauge::GAUGE_VALUE, _temp);
}

void Gauge::adjustValue(Gauge::ValueType vtype, double val, bool bIncrease){
	GameMsg _msg, _msg2;
	double _tempval;
	double _tempval2;
	switch (vtype)
	{
	case Gauge::GAUGE_VALUE:
		
		if(!bIncrease)
			_tempval = -val;
		else
			_tempval = val;

		if(d_dValue >= d_dMaxValue || dEqual(_tempval,0.0))return;

		//打包数据发送逻辑进行计算
		memset(&_msg, 0, sizeof(GameMsg));
		_msg.dValue1=val;
		if(_tempval>0.0 && d_handleBeforeValueIncrease)
			(*d_handleBeforeValueIncrease)(_msg);
		if(_tempval<0.0 && d_handleBeforeValueDecrease)
			(*d_handleBeforeValueDecrease)(_msg);

		//取出结果
		_tempval = _msg.dValue1;
		_tempval2 = d_dValue+_tempval;

		memset(&_msg,0,sizeof(GameMsg));
		memset(&_msg2,0,sizeof(GameMsg));
		if(_tempval>0.0){
			//数值增加
			if(_tempval2 >= d_dMaxValue){
				//数值变化量
				_msg.dValue1=d_dMaxValue-d_dValue;
				//改变数值
				d_dValue = d_dMaxValue;

				if(d_handleFullValue)
					(*d_handleFullValue)(_msg2);
			}else{
				//数值变化量
				_msg.dValue1=_tempval;
				//改变数值
				d_dValue=_tempval2;
			}
			//fire event
			if(d_handleAfterValueIncrease)
				(*d_handleAfterValueIncrease)(_msg);
		}else{
			//数值减少
			if(_tempval2 <= 0.0){
				_msg.dValue1 = d_dValue;
				d_dValue = 0.0;

				if(d_handleZeroValue)
					(*d_handleZeroValue)(_msg2);
			}else{
				_msg.dValue1 = -_tempval;
				d_dValue = _tempval2;
			}
			//fire event
			if(d_handleAfterValueDecrease)
				(*d_handleAfterValueDecrease)(_msg);
		}
		break;
	case Gauge::GAUGE_MAXVALUE:
		//改变上限造成的数值变化不激发事件
		_tempval = d_dMaxValue + val;
		if(_tempval < 0.0) _tempval = 0.0;

		d_dMaxValue = _tempval;
		if(d_dValue<d_dMaxValue)
			d_dValue = d_dMaxValue;

		break;
	case Gauge::GAUGE_REGENSPEED:
		d_dRegenSpeed += val;

		break;
	default:
		break;
	}
}

void Gauge::setValue(Gauge::ValueType vtype, double val){
	double _temp;
	switch (vtype)
	{
	case Gauge::GAUGE_VALUE:
		
		if(val > d_dMaxValue)
			_temp=d_dMaxValue;
		else if(val < 0.0)
			_temp = 0.0;
		else
			_temp = val;

		d_dValue = _temp;

		break;
	case Gauge::GAUGE_MAXVALUE:

		if(val < 0.0)
			_temp = 0.0;
		else
			_temp = val;

		d_dMaxValue = val;
		if(d_dValue > d_dMaxValue)
			d_dValue = d_dMaxValue;

		break;
	case Gauge::GAUGE_REGENSPEED:

		d_dRegenSpeed = val;
		break;
	default:
		break;
	}
}

template<class T>
void Gauge::setHandler(Gauge::Event e, CallbackFunction<T>* callback){
	switch (e)
	{
	case Gauge::GAUGE_EVENT_VALUEHITZERO:
		d_handleZeroValue = callback;
		break;
	case Gauge::GAUGE_EVENT_VALUEDECREASING:
		d_handleBeforeValueDecrease = callback;
		break;
	case Gauge::GAUGE_EVENT_VALUEINCREASING:
		d_handleBeforeValueIncrease = callback;
		break;
	case Gauge::GAUGE_EVENT_VALUEDECREASED:
		d_handleAfterValueDecrease = callback;
		break;
	case Gauge::GAUGE_EVENT_VALUEINCREASED:
		d_handleAfterValueIncrease = callback;
		break;
	case Gauge::GAUGE_EVENT_VALUEHITLIMIT:
		d_handleFullValue = callback;
		break;
	default:
		break;
	}
}

Attribute::Attribute(){
	d_hp = d_mp = Gauge();

	const double_pair zero_pair = {buffered_double(), buffered_double()};
	d_physical = d_fire = d_frost = d_lightning = d_darkness = d_terra = d_light = zero_pair;
	d_movespeed = d_criticalrate = d_criticalboost = buffered_double();
}


void FlagMap::setValue(std::string key, bool val){
	std::map<std::string ,bool>::iterator it = d_map.find(key);
	if(it != d_map.end())
		it->second = val;
	else
		d_map.insert(std::make_pair(key,val));
}

bool FlagMap::getValue(std::string key){
	std::map<std::string,bool>::const_iterator it = d_map.find(key);
	if(it != d_map.end())
		return it->second;
	else
		return false;
}

Motor::Motor(){
	_l=_r=_u=_d=false;
	EventDispatcher::getSingleton()->addListener(EventType::EVENT_TYPE_KEYDOWN, this);
	EventDispatcher::getSingleton()->addListener(EventType::EVENT_TYPE_KEYUP, this);
}
Motor::~Motor(){
	EventDispatcher::getSingleton()->removeListener(EventType::EVENT_TYPE_KEYDOWN, this);
	EventDispatcher::getSingleton()->removeListener(EventType::EVENT_TYPE_KEYUP, this);
}

void Motor::setControl(Control ctrl, bool pressed){
	switch (ctrl)
	{
	case Motor::MOTOR_RIGHT:
		_r=pressed;
		break;
	case Motor::MOTOR_UP:
		_u=pressed;
		break;
	case Motor::MOTOR_LEFT:
		_l=pressed;
		break;
	case Motor::MOTOR_DOWN:
		_d=pressed;
		break;
	default:
		break;
	}
}
Motor::Direction Motor::getDirection(){
	int flag = _r+_l+_u+_d;
	if(flag>=3) return Motor::DIRECTION_UNKNOWN;

	if(flag==2){
		if(_l&&_u)return Motor::DIRECTION_UPLEFT;
		if(_r&&_u)return Motor::DIRECTION_UPRIGHT;
		if(_l&&_d)return Motor::DIRECTION_DOWNLEFT;
		if(_r&&_d)return Motor::DIRECTION_DOWNRIGHT;
	}else
		return Motor::DIRECTION_UNKNOWN;

	if(flag==1){
		if(_l)return Motor::DIRECTION_LEFT;
		if(_r)return Motor::DIRECTION_RIGHT;
		if(_u)return Motor::DIRECTION_UP;
		if(_d)return Motor::DIRECTION_DOWN;
	}

	return Motor::DIRECTION_UNKNOWN;
	
}

bool Motor::handleEvent(const IEvent& e){

	//判断游戏状态
	//if in game

	switch (e._type)
	{
	case EventType::EVENT_TYPE_KEYDOWN:
		switch (e._arg1)
		{
		case 'a':
		case 'A':
			_l = true;return true;
		case 's':
		case 'S':
			_d = true;return true;
		case 'd':
		case 'D':
			_r = true;return true;
		case 'w':
		case 'W':
			_u = true;return true;
		default:
			return false;
		}
	case EventType::EVENT_TYPE_KEYUP:
		switch (e._arg1)
		{
		case 'a':
		case 'A':
			_l = false;return true;
		case 's':
		case 'S':
			_d = false;return true;
		case 'd':
		case 'D':
			_r = false;return true;
		case 'w':
		case 'W':
			_u = false;return true;
		default:
			return false;
		}
	default:
		return false;
	}
}

Collider::Collider(double radius){
	m_dRadius = radius;
}

Collider::~Collider(){}

bool Collider::checkCollide(Vec2d& force, const Collider& target){
	Vec2d _delta = m_vPos - target.getPos();
	if(_delta.GetLength() < m_dRadius+target.getRadius()){
		force = _delta;
		return true;
	}else
		return false;
}