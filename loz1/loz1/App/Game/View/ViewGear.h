#ifndef VIEWGEAR_H
#define VIEWGEAR_H

#include<string>
#include"../Interfaces.h"
#include"../../Utilities/Common.h"

class Sprite;

class Renderable:
	public IRenderable
{
public:
	Renderable():
		d_pSprite(0)
	{}

	virtual ~Renderable();

	virtual void requestAnimation(std::string);
	virtual void updateVisual(double deltaTime, Vec2d pos, Vec2d scale, double rotation);
	virtual void doRender();
private:
	Sprite* d_pSprite;
	std::string d_sAnimation;
	//if requested animation
	bool d_bRequested;
	//animation controller
};

//¾µÍ·
class Camera:
	public ICamera
{

};

#endif