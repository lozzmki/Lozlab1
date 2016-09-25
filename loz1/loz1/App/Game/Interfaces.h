#ifndef INTERFACES_H
#define INTERFACES_H

#include"../Utilities/Vector2D.h"

#define gameinterface struct

enum BoundType{
		BOUND_SQUARE,
		BOUND_ROUND,
};

gameinterface IRenderable{
	//virtual void loadmodel()=0;
	virtual void requestAnimation(std::string)=0;
	virtual void updateVisual(double deltaTime, Vec2d pos, Vec2d scale, double rotation)=0;
	virtual void doRender() = 0;
};

gameinterface IBoundBox{
	virtual bool checkCollide(IBoundBox*)=0;
	virtual void setPos(double,double)=0;
	virtual void setSize(double,double)=0;
	virtual void setPos(Vec2d)=0;
	virtual void setSize(Vec2d)=0;
	virtual void setRadius(double)=0;
	virtual void setType(BoundType)=0;
	virtual double getRadius()=0;
	virtual Vec2d getPos()=0;
	virtual Vec2d getSize()=0;
	virtual BoundType getType()=0;
	virtual bool ifEnabled()=0;
};

struct GameMsg;

gameinterface ICallback{
	virtual void operator()(GameMsg&)=0;
};

gameinterface ICamera{
	virtual void pan(Vec2d)=0;
	virtual void setSpeed(double)=0;
	virtual void setHeight(double)=0;
	virtual double getSpeed()=0;
	virtual double getHeight()=0;
};

#endif