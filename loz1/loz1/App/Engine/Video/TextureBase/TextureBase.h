#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H


#include<string>
#include<map>
#include<d3d9.h>
#include<d3dx9.h>

struct TextureNode{
	TextureNode();
	D3DXIMAGE_INFO _info;
	IDirect3DTexture9* _texture;
	
};

typedef std::map<std::string, TextureNode> TextureMap;
typedef TextureMap::const_iterator TextureMapIterator;

class TextureBase{

public:
	TextureBase();
	virtual ~TextureBase();

	void PreloadTexture(std::string, LPTSTR);
	TextureNode GetTexture(std::string);
protected:
	TextureMap m_Texture;
};

extern TextureBase* g_TexBase;

#define _TEX(t) (g_TexBase->GetTexture(t)._texture)
#define _TEXINFO(t) (g_TexBase->GetTexture(t)._info)
#define _TEXNODE(t) (g_TexBase->GetTexture(t))


#endif