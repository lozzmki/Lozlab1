#include"TextureBase.h"
#include "..\..\..\Utilities\Common.h"
#include"..\Dx.h"

TextureBase* g_TexBase = 0;

TextureNode::TextureNode(){
		_texture=0;
		::ZeroMemory(&_info,sizeof(_info));
}

TextureBase::TextureBase(){
	m_Texture.clear();
}
TextureBase::~TextureBase(){
	for(TextureMapIterator it = m_Texture.begin(); it!=m_Texture.end();){
		IDirect3DTexture9* _tex = it->second._texture;
		SAFE_DELETE(_tex);
		it=m_Texture.erase(it);
	}
	m_Texture.clear();
}

void TextureBase::PreloadTexture(std::string sName, LPTSTR sPath){
	IDirect3DTexture9* _tex;
	D3DXIMAGE_INFO _info;
	D3DXCreateTextureFromFileEx(g_Device, sPath,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,
								D3DPOOL_DEFAULT,D3DFMT_FROM_FILE,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,0.0f),&_info,0,&_tex);
	TextureNode _node;
	_node._info=_info;
	_node._texture=_tex;
	m_Texture.insert(std::make_pair(sName,_node));
}

TextureNode TextureBase::GetTexture(std::string sName){
	TextureMapIterator it=m_Texture.find(sName);
	if(it != m_Texture.end())
		return it->second;
	else
		return TextureNode();
}