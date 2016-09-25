#include"LogicGear.h"

//structs
struct RectPts{
	Vec2d _lt, _rt, _lb, _rb;
};

//functions
bool dEqual(double d1, double d2){
	double delta = d1-d2;
	return delta>-1e-6 && delta<1e-6;
}
bool pt_in_rect(Vec2d pt, RectPts rct){
	Vec2d rlt = rct._lt, rrb = rct._rb;
	bool bx = pt.x >= rlt.x && pt.x <= rrb.x;
	bool by = pt.y >= rrb.y && pt.y <= rlt.y;
	return bx&&by;
}
bool pt_in_round(Vec2d pt, Vec2d rlt, double r){
	Vec2d _vec = rlt - pt;
	return _vec.GetLength()<=r;
}
RectPts getPts(Vec2d pos, Vec2d size){
	RectPts _r;
	_r._lt = Vec2d(pos.x - size.x, pos.y + size.y);
	_r._rt = Vec2d(pos.x + size.x, pos.y + size.y);
	_r._lb = Vec2d(pos.x - size.x, pos.y - size.y);
	_r._rb = Vec2d(pos.x + size.x, pos.y - size.y);

	return _r;
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

bool BoundBox::checkCollide(IBoundBox* ptar){

	if(!ptar->ifEnabled() || !d_bEnabled) return false;

	RectPts _ownpts;
	RectPts _tarpts;
	Vec2d _delta;
	bool _temp;
	switch (d_type)
	{
	case BOUND_SQUARE:

		_ownpts = getPts(d_ptPosition, d_vecSize);

		switch (ptar->getType())
		{
		case BOUND_SQUARE:
			//square with square

			_tarpts = getPts(ptar->getPos(), ptar->getSize());
			_temp = pt_in_rect(_ownpts._lt, _tarpts) ||
					pt_in_rect(_ownpts._rt, _tarpts) ||
					pt_in_rect(_ownpts._lb, _tarpts) ||
					pt_in_rect(_ownpts._rb, _tarpts) ||
					pt_in_rect(_tarpts._lt, _ownpts);

			if(_temp) return true;

			_temp = (_ownpts._lt.x <= _tarpts._lt.x && _ownpts._rb.x >= _tarpts._rb.x && _ownpts._lt.y <= _tarpts._lt.y && _ownpts._rb.y >= _tarpts._rb.y) ||
					(_ownpts._lt.x >= _tarpts._lt.x && _ownpts._rb.x <= _tarpts._rb.x && _ownpts._lt.y >= _tarpts._lt.y && _ownpts._rb.y <= _tarpts._rb.y);

			if(_temp) return true;

			break;
		case BOUND_ROUND:
			// square with round

			//取中心点差向量
			_delta = ptar->getPos() - d_ptPosition;
			//正化
			_delta.Positive();

			_temp = ( _delta.x > d_vecSize.x/2 + ptar->getRadius() ) || ( _delta.y > d_vecSize.y/2 + ptar->getRadius() );
			if(_temp)return false;

			_temp = _delta.GetLength() <= (d_vecSize/2).GetLength() + ptar->getRadius();
			return _temp;

			break;
		default:
			break;
		}
		break;
	case BOUND_ROUND:
		switch (ptar->getType())
		{
		case BOUND_SQUARE:
			//round with square

			_delta = ptar->getPos() - d_ptPosition;
			//正化
			_delta.Positive();

			_temp = ( _delta.x > ptar->getSize().x/2 + d_dRadius ) || ( _delta.y > ptar->getSize().y/2 + d_dRadius );
			if(_temp)return false;

			_temp = _delta.GetLength() <= (ptar->getSize()/2).GetLength() + d_dRadius;
			return _temp;

			break;
		case BOUND_ROUND:
			//round with round
			_delta = ptar->getPos() - d_ptPosition;
			return _delta.GetLength() < d_dRadius + ptar->getRadius();

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return false;
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

QuadNode::Quadrant QuadNode::checkRect(Vec2d lt, Vec2d size){
	double _l=lt.x , _t = lt.y, _r = lt.x + size.x , _b = lt.y - size.y;
	double _x = _center.x, _y=_center.y;

	if(_l>_x && _b>_y)	return QUAD_FIRST;
	if(_r<_x && _b>_y)	return QUAD_SECOND;
	if(_r<_x && _t<_y)	return QUAD_THIRD;
	if(_l>_x && _t<_y)	return QUAD_FOURTH;

	return QUAD_MULTIPLE;
}

void QuadNode::push(int ID,Vec2d lt, Vec2d size){

	if(_nDepth>=QUAD_MAX_DEPTH) {
		_lsIDlist.push_back(ID);
		return;
	}

	switch (checkRect(lt,size))
	{
	case QUAD_FIRST:
		if(!_bSplited)split();
		_pChild[0]->push(ID,lt,size);
		break;
	case QUAD_SECOND:
		if(!_bSplited)split();
		_pChild[1]->push(ID,lt,size);
		break;
	case QUAD_THIRD:
		if(!_bSplited)split();
		_pChild[2]->push(ID,lt,size);
		break;
	case QUAD_FOURTH:
		if(!_bSplited)split();
		_pChild[3]->push(ID,lt,size);
		break;
	case QUAD_MULTIPLE:
		_lsIDlist.push_back(ID);
		break;
	default:
		break;
	}
}

void QuadNode::getList(std::list<int>& list,Vec2d lt, Vec2d size){

	appendToList(list);

	if(_nDepth>=QUAD_MAX_DEPTH)	return;
	switch (checkRect(lt,size))
	{
	case QUAD_FIRST:
		_pChild[0]->getList(list,lt,size);
		break;
	case QUAD_SECOND:
		_pChild[1]->getList(list,lt,size);
		break;
	case QUAD_THIRD:
		_pChild[2]->getList(list,lt,size);
		break;
	case QUAD_FOURTH:
		_pChild[3]->getList(list,lt,size);
		break;
	case QUAD_MULTIPLE:
	default:
		break;
	}

}

void QuadNode::appendToList(std::list<int>& list){
	std::list<int>::const_iterator it = _lsIDlist.begin();
	for(;it != _lsIDlist.end();){
		list.push_back(*it);
	}
}

void QuadTree::clear(){
	SAFE_DELETE(d_pRoot);
	d_pRoot = new QuadNode();
}

void QuadTree::getList(std::list<int>&_list, Vec2d lt, Vec2d size){
	d_pRoot->getList(_list, lt, size);
}

void QuadTree::push(int ID,Vec2d lt,Vec2d size){
	d_pRoot->push(ID, lt, size);
}