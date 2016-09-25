#include"ViewGear.h"
#include"../../Engine/Video/Sprite/Sprite.h"

Renderable::~Renderable(){
		SAFE_DELETE(d_pSprite);
}

void Renderable::updateVisual(double deltaTime, Vec2d pos, Vec2d scale, double rotation){
	d_pSprite->setPos(pos);
	d_pSprite->setScale(scale);
	d_pSprite->setRotate(rotation);

	if(d_bRequested){
		//update animator , set animation as buffer
	}else{
		//simply update animator
	}
	//get texture from animator
	//d_pSprite->setTexture()
}
void Renderable::requestAnimation(std::string name){
	d_sAnimation = name;
}
void Renderable::doRender(){
	d_pSprite->render();
}