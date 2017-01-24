#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "BaseGameLogic.h"
#include "LogicGear.h"
#include "../../Utilities/Vector2D.h"
#include"../View/ViewGear.h"

//��������Ϸ�����У��о���λ�õ�ʵ�����
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

//�ɽ�������Ϸ���󣨼�����ײ����Ⱦ�����
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
	//��ײ������ת�Ƕ�Ϊ0ʱ��λ��ƫ����
	Vec2d m_vecBoundOffset;

};

//�����ƻ���������
class BarrierEntity : public InteractEntity{

public:
};

//����ʵ�壨���ƻ������ȣ�
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

	//�������Ч�����������Ÿ��ű�
protected:
	Attribute d_Attribute;
	State d_State;
	Vec2d d_movDirection;
	FlagMap d_FlagMap;
};

//Ͷ����ʵ��
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

//����ʵ�壬���Ե������ڣ�Ҳ���Է���������ʵ����,for items and spells
class ParasiteEntity : public InteractEntity{

};

//���ʵ���࣬����������ƺ�����
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