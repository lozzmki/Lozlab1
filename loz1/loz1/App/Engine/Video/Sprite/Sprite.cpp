#include "Sprite.h"

#include "..\..\..\..\Utilities\Common.h"
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

void Sprite::SetTexture(TextureNode node){
	m_pTexture = node._texture;
	m_texSize = Vec2i(node._info.Width, node._info.Height);
}

void Sprite::Render(){
	if(m_pSprite){

		D3DXMATRIX _mat, _matpos;

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		if(m_size.x && m_size.y && m_texSize.x && m_texSize.y){
			D3DXMatrixScaling(&_mat, (float)m_size.x/(float)m_texSize.x, (float)m_size.y/(float)m_texSize.y, 1.0f);
			//m_pSprite->SetTransform(&_mat);
		}
		//m_pSprite->Draw(m_pTexture, &_r, 0, &_pos, 0xffffffff);
		//D3DXVECTOR3 _pos(m_pos.x, m_pos.y, 0.0f);//计划 动画控制
		D3DXMatrixTranslation(&_matpos, m_pos.x, m_pos.y, 0.0f);
		D3DXMatrixMultiply(&_mat, &_mat, &_matpos);

		m_pSprite->SetTransform(&_mat);
		m_pSprite->Draw(m_pTexture, 0, 0, 0, 0xffffffff);

		m_pSprite->End();

	}
}