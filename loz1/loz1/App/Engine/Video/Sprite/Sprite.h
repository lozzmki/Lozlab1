#ifndef SPRITE_H
#define SPRITE_H

#include "..\..\..\Utilities\Vector2D.h"

struct ID3DXSprite;
struct IDirect3DTexture9;
struct TextureNode;

class Sprite{

public:
	Sprite();
	virtual ~Sprite();

	void render();
	inline void setTexture(IDirect3DTexture9* _tex){
		m_pTexture = _tex;
	}
	void setTexture(TextureNode node);
	inline void setPos(double x, double y){
		m_pos = Vec2d(x,y);
	}
	inline void setPos(Vec2d v){
		m_pos = v;
	}
	inline void setScale(double x, double y){
		m_scale = Vec2d(x,y);
	}
	inline void setScale(Vec2d v){
		m_scale = v;
	}
	inline void setRotate(double angle){
		m_rotation = angle;
	}
protected:

	ID3DXSprite* m_pSprite;
	IDirect3DTexture9* m_pTexture;

	Vec2d m_pos;
	Vec2d m_scale, m_texSize;
	double m_rotation;
	//textures
};

#endif