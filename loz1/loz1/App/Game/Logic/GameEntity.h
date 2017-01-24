#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "BaseGameLogic.h"
#include "LogicGear.h"
#include "../../Utilities/Vector2D.h"
#include"../View/ViewGear.h"

//存在于游戏场景中，有具体位置的实体对象
class GameEntity : public GameObject{

	//not a final class
protected:
	GameEntity(){}
public:
	virtual ~GameEntity(){}

	virtual void update(double deltaTime){}
	virtual void render(){}

	//member functions
	inline void setPos(Vec2d pos){m_vecPosition = pos;}
	inline void setSize(Vec2d size){m_vecSize = size;}
	inline void setRotation(double rotation){m_dRotation = rotation;}
	inline double getRotation(){return m_dRotation;}
	inline Vec2d getPos(){return m_vecPosition;}
	inline Vec2d getSize(){return m_vecSize;}

protected:
	Vec2d m_vecPosition;
	Vec2d m_vecSize;
	double m_dRotation;
};

//可交互的游戏对象（加入碰撞、渲染组件）
class InteractEntity : public GameEntity
{
	//not a final class
protected:
	InteractEntity(){}
public:
	virtual ~InteractEntity(){}

	virtual void update(double deltaTime);
	virtual void render();

	//Triggers
	virtual void onCollide(GameMsg&){}

protected:
	Renderable m_renderable;
	//碰撞盒在旋转角度为0时的位置偏移量
	Vec2d m_vecBoundOffset;

};

//不可破坏地形物体
class BarrierEntity : public InteractEntity{

public:
};

//生命实体（可破坏物、生物等）
class LivingEntity : public InteractEntity{
public:
	LivingEntity(){}
	virtual ~LivingEntity(){}

	virtual void update(double deltaTime);
	virtual void render();

	//needs a set_up_from_xml function

	bool isBusy(){return d_State != STATE_IDLE;}
	bool isDead(){return d_State == STATE_DEAD;}

	Attribute& getAttribute(){return d_Attribute;}

	//Triggers
	virtual void onCollide(GameMsg&){}

	//加入各种效果函数，开放给脚本
protected:
	Attribute d_Attribute;
	State d_State;
	Vec2d d_movDirection;
	FlagMap d_FlagMap;
};

//投射物实体
class ProjectileEntity : public InteractEntity{

public:
	ProjectileEntity(){}
	virtual ~ProjectileEntity(){}

	virtual void update(double deltaTime);
	virtual void render();

	//Triggers
	virtual void onCollide(GameMsg&){}
protected:
};

//寄生实体，可以单独存在，也可以放置在宿主实体上,for items and spells
class ParasiteEntity : public InteractEntity{

};

//玩家实体类，加入输入控制函数等
class PlayerEntity : public LivingEntity{

public:
	PlayerEntity(){}
	virtual ~PlayerEntity(){}

	virtual void update(double deltaTime);
	virtual void render();

protected:
	Motor m_motor;
};

#endif