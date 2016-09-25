#ifndef LOGICGEAR_H
#define LOGICGEAR_H

#include"BaseGameLogic.h"
#include"../Interfaces.h"
#include"../../Utilities/Vector2D.h"
#include"../../Utilities/Common.h"
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

//碰撞盒,AABB和圆形
class BoundBox : public IBoundBox{
public:
	BoundBox(){d_type = BOUND_ROUND;d_ptPosition=d_vecSize=Vec2d(0.0,0.0);d_dRadius=0.0;}
	BoundBox(Vec2d pos, Vec2d size):d_type(BOUND_SQUARE),d_ptPosition(pos),d_vecSize(size){}
	BoundBox(Vec2d pos, double radius):d_type(BOUND_SQUARE),d_ptPosition(pos),d_dRadius(radius),d_vecSize(Vec2d(2*radius, 2*radius)){}

	virtual bool checkCollide(IBoundBox*);
	virtual inline void setPos(double x,double y){d_ptPosition=Vec2d(x,y);}
	virtual inline void setSize(double x,double y){d_vecSize=Vec2d(x,y);}
	virtual inline void setPos(Vec2d pos){d_ptPosition=pos;}
	virtual inline void setSize(Vec2d size){d_vecSize=size;}
	virtual inline void setRadius(double r){d_dRadius = r;}
	virtual inline void setType(BoundType t){d_type = t;}

	virtual inline Vec2d getPos(){return d_ptPosition;}
	virtual inline Vec2d getSize(){return d_vecSize;}
	virtual inline double getRadius(){return d_dRadius;}
	virtual inline BoundType getType(){return d_type;}
	virtual inline bool ifEnabled(){return d_bEnabled;}

private:
	//方形碰撞盒对角线交点，圆形碰撞盒圆心点
	Vec2d d_ptPosition;
	//方形碰撞盒大小
	Vec2d d_vecSize;
	//圆形碰撞盒半径
	double d_dRadius;
	//碰撞盒类型
	BoundType d_type;
	//是否生效
	bool d_bEnabled;
};

enum State{
	STATE_IDLE,
	STATE_MOVING,
	STATE_ATTACK,//攻击、移动攻击
	STATE_CASTING,
	STATE_LOSTCONTROL,
	STATE_DEAD
};

//角色移动控制
class Motor{

public:
	Motor(){
		_l=_r=_u=_d=false;
	}
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
	void setControl(Control, bool pressd);
	Direction getDirection();

private:
	bool _l, _r, _u, _d;//左右上下
};


class FlagMap{

public:
	FlagMap(){d_map.clear();}
	
	void setValue(std::string key, bool val);
	bool getValue(std::string key);

protected:
	std::map<std::string,bool> d_map;
};

#define QUAD_MAX_DEPTH 8

//四叉树节点
struct QuadNode{
	//status
	int _nDepth;
	bool _bSplited;
	//data
	std::list<int> _lsIDlist;
	Vec2d _center;//矩形区域中心点坐标
	Vec2d _halfsize;//中心点到右上顶点的向量
	//link
	QuadNode* _pParent;
	QuadNode* _pChild[4]; //0-3对应1-4象限

	inline void split(){
		_bSplited = true;
		Vec2d _temphalf = _halfsize*0.5;
		for(int i=0; i<4; i++){
			_pChild[i] = new QuadNode(this);
			_pChild[i]->_halfsize=_temphalf;
		}
		_pChild[0]->_center=_center+_temphalf;
		_pChild[1]->_center=_center+_temphalf.ReverseX();
		_pChild[2]->_center=_center+_temphalf.Reverse();
		_pChild[3]->_center=_center+_temphalf.ReverseY();
	}
	enum Quadrant{
		QUAD_FIRST,
		QUAD_SECOND,
		QUAD_THIRD,
		QUAD_FOURTH,
		QUAD_MULTIPLE=-1,
	};
	
	void push(int,Vec2d,Vec2d);
	void getList(std::list<int>&,Vec2d,Vec2d);

	QuadNode(QuadNode* pParent=0){
		if(_pParent)_nDepth = _pParent->_nDepth+1;
		else _nDepth = 0;
		_lsIDlist.clear();
	}
	~QuadNode(){
		_lsIDlist.clear();
		for(int i=0;i<4;i++)
			SAFE_DELETE(_pChild[i]);
	}
private:
	std::list<int> _blacklist;
	Quadrant checkRect(Vec2d lt,Vec2d size);
	void appendToList(std::list<int>&);
};

//四叉树
class QuadTree{
	
public:
	QuadTree(){d_pRoot=new QuadNode();}
	virtual ~QuadTree(){SAFE_DELETE(d_pRoot);}

	//清空四叉树
	void clear();
	//插入一个新值
	void push(int,Vec2d,Vec2d);
	//获取可能的碰撞ID列表
	void getList(std::list<int>&,Vec2d,Vec2d);

private:
	QuadNode* d_pRoot;
};

struct IDpair{
	int _IDa, _IDb;
	bool operator <(const IDpair& tar)const{
		if(_IDa < tar._IDa)
			return true;
		else
			if(_IDa == tar._IDa)
				return _IDb < tar._IDb;

		return false;
	}
	IDpair(int a=0,int b=0):_IDa(a),_IDb(b){}
};
typedef std::set<IDpair> IDcheckSet;

#endif