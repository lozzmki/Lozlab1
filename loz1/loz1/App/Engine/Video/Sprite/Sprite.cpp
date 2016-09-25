#include "Sprite.h"

#include "..\..\..\Utilities\Common.h"
#include "..\Dx.h"
#include"..\TextureBase\TextureBase.h"

Sprite::Sprite(){
	D3DXCreateSprite(g_Device, &m_pSprite);
	m_pTexture=0;
}
Sprite::~Sprite(){
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pTexture);
}

void Sprite::setTexture(TextureNode node){
	m_pTexture = node._texture;
	m_texSize = Vec2d(node._info.Width, node._info.Height);
}

void Sprite::render(){
	if(m_pSprite){

		if(!m_pTexture)return;

		D3DXMATRIX _mat, _matpos, _matrotate;

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		/*if(m_size.x && m_size.y && m_texSize.x && m_texSize.y){
			D3DXMatrixScaling(&_mat, (float)m_size.x/(float)m_texSize.x, (float)m_size.y/(float)m_texSize.y, 1.0f);
			//m_pSprite->SetTransform(&_mat);
		}*/
		D3DXMatrixScaling(&_mat, m_scale.x, m_scale.y, 1.0f);

		D3DXMatrixRotationZ(&_matrotate, m_rotation);
		D3DXMatrixMultiply(&_mat, &_mat, &_matrotate);

		D3DXMatrixTranslation(&_matpos, m_pos.x, m_pos.y, 0.0f);
		D3DXMatrixMultiply(&_mat, &_mat, &_matpos);

		m_pSprite->SetTransform(&_mat);
		m_pSprite->Draw(m_pTexture, 0, 0, 0, 0xffffffff);

		m_pSprite->End();

	}
}