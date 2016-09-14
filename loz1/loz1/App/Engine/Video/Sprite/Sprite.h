#ifndef SPRITE_H
#define SPRITE_H

#include "..\..\..\..\Utilities\Vector2D.h"

struct ID3DXSprite;
struct IDirect3DTexture9;
struct TextureNode;

class Sprite{

public:
	Sprite();
	virtual ~Sprite();

	void Render();
	inline void SetTexture(IDirect3DTexture9* _tex){
		m_pTexture = _tex;
	}
	void SetTexture(TextureNode node);
	inline void SetPos(int x, int y){
		m_pos = Vec2i(x,y);
	}
	inline void SetPos(Vec2i v){
		m_pos = v;
	}
	inline void SetSize(int x, int y){
		m_size = Vec2i(x,y);
	}
	inline void SetSize(Vec2i v){
		m_size = v;
	}
protected:

	ID3DXSprite* m_pSprite;
	IDirect3DTexture9* m_pTexture;

	Vec2i m_pos;
	Vec2i m_size, m_texSize;
	//textures
};

#endif