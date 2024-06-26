#include "DrawDamage.h"
#include "sprite.h"
#include "Game.h"
#include "material.h"
DrawDmage::DrawDmage(int damage, D3DXVECTOR3 pos, D3DXCOLOR coler)
	:m_Damage(damage),
	Base_Object(pos, NO_VECTOR3, NO_VECTOR3, NO_VECTOR3, coler, inviolability, true) {
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;
}


HRESULT DrawDmage::Init(void)
{
	return E_NOTIMPL;
}

void DrawDmage::Uninit(void)
{
}

void DrawDmage::Update(void)
{
	m_Life--;
	if (m_Life < 0)
	{
		IsDiscard();
	}
	D3DXVECTOR3 pos = GetPlayer()->GetPos();
	D3DXVECTOR3 vec = RefPos() - pos;
	m_Length = 0.025f * D3DXVec3Length(&vec);
}

void DrawDmage::Draw(void)
{
	D3DXVECTOR2			m_Uv_v;
	D3DXVECTOR2			m_Uv_f = {0.2f,0.5f};

	
	float size = m_Length;
	SetScl({ size, size * 1.4f, size });
	//ï\é¶ÇµÇΩÇ¢êîéöÇïœä∑
	std::string text = std::to_string(m_Damage);
	float textlength = 0.0f;
	//ï∂éöÇÃëççáïùÇì¸ÇÍÇÈ
	for (char a : text)
	{
		switch (a)
		{
		case 0x30:textlength += size * 0.78f;
			break;
		case 0x31:textlength += size * 0.65f;
			break;
		case 0x32:textlength += size * 0.86f;
			break;
		case 0x33:textlength += size * 0.78f;
			break;
		case 0x34:textlength += size * 0.78f;
			break;
		case 0x35:textlength += size * 0.73f;
			break;
		case 0x36:textlength += size * 0.82f;
			break;
		case 0x37:textlength += size * 0.72f;
			break;
		case 0x38:textlength += size * 0.78f;
			break;
		case 0x39:textlength += size * 0.78f;
			break;
		default:
			break;
		}
	}
	textlength *= 0.5f;
	float hufsize = size * 0.5f;
	for (char b : text) {
		switch (b)
		{
		case 0x30:m_Uv_v = { 0.8f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x31:m_Uv_v = { 0.0f,0.0f }; textlength -= hufsize * 0.65f;
			break;
		case 0x32:m_Uv_v = { 0.2f,0.0f }; textlength -= hufsize * 0.86f;
			break;
		case 0x33:m_Uv_v = { 0.4f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x34:m_Uv_v = { 0.6f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x35:m_Uv_v = { 0.8f,0.0f }; textlength -= hufsize * 0.73f;
			break;
		case 0x36:m_Uv_v = { 0.0f,0.5f }; textlength -= hufsize * 0.82f;
			break;
		case 0x37:m_Uv_v = { 0.2f,0.5f }; textlength -= hufsize * 0.72f;
			break;
		case 0x38:m_Uv_v = { 0.4f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x39:m_Uv_v = { 0.6f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		default:
			break;
		}
		// 2Dï`âÊÇ»ÇÃÇ≈ê[ìxñ≥å¯
		SetDepthEnable(false);
		DrawPolygonBillX(*this, RefImageMaterial().m_Suzi, m_Uv_v, m_Uv_f,-textlength);
		SetDepthEnable(true);
		switch (b)
		{
		case 0x30:m_Uv_v = { 0.8f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x31:m_Uv_v = { 0.0f,0.0f }; textlength -= hufsize * 0.65f;
			break;
		case 0x32:m_Uv_v = { 0.2f,0.0f }; textlength -= hufsize * 0.86f;
			break;
		case 0x33:m_Uv_v = { 0.4f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x34:m_Uv_v = { 0.6f,0.0f }; textlength -= hufsize * 0.78f;
			break;
		case 0x35:m_Uv_v = { 0.8f,0.0f }; textlength -= hufsize * 0.73f;
			break;
		case 0x36:m_Uv_v = { 0.0f,0.5f }; textlength -= hufsize * 0.82f;
			break;
		case 0x37:m_Uv_v = { 0.2f,0.5f }; textlength -= hufsize * 0.72f;
			break;
		case 0x38:m_Uv_v = { 0.4f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		case 0x39:m_Uv_v = { 0.6f,0.5f }; textlength -= hufsize * 0.78f;
			break;
		default:
			break;
		}
	}
}

float DrawDmage::GetLength()
{
	return m_Length;
}
