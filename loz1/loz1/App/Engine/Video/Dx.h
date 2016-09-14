#ifndef DX_H
#define DX_H

#include<d3d9.h>
#include<d3dx9.h>
#include"TextureBase\TextureBase.h"


struct Vertex{
	float _x, _y, _z;
	//float _nx, _ny, _nz;
	//unsigned long _color;
	float _u, _v;
	static unsigned long FVF;

	Vertex():_x(0.0f), _y(0.0f), _z(0.0f), _u(0.0f), _v(0.0f){}
	Vertex(float x, float y, float z, float u, float v);
};

//Create & handle Direct3D Device
class D3D{

public:
	D3D();
	virtual ~D3D();

	bool OnInit();
	void OnRender(float timeDelta);
	void EndAndPresent();
	void OnDestroy();

	IDirect3DDevice9* m_pDevice;
	TextureBase* m_pTextureBase;

	inline ID3DXFont* GetFont(){return m_pFont;}

protected:

	IDirect3DVertexBuffer9* m_pVertexBuffer;

	ID3DXFont* m_pFont;

};

#define g_Device g_d3d->m_pDevice
#define g_TextureBase g_d3d->m_pTextureBase

extern D3D* g_d3d;

#endif