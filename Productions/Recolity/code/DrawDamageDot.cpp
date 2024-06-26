#include "DrawDamageDot.h"
#include "sprite.h"
#include "Game.h"
#include "material.h"
DrawDmageDot::DrawDmageDot(){
	m_coler = DIK_COLER_DRAKGRAY;
	m_Life = 0;
	m_Nowdamage = 0;
}

void DrawDmageDot::IsDamageDot(float damage)
{
		m_Life = 60;
		m_Damage += damage;
}

void DrawDmageDot::Update(D3DXVECTOR3 pos)
{

	if (m_Life > 0)
	{
		m_Life--;
	}
	if (m_Life <= 0)
	{
		m_Damage = 0;
		m_Nowdamage = 0;
	}
	if (m_Damage > m_Nowdamage)
	{
		m_Nowdamage += (m_Damage - m_Nowdamage) / m_Life;
	}
	D3DXVECTOR3 plpos = GetPlayer()->GetPos();
	D3DXVECTOR3 vec = pos - plpos;
	m_Length = 0.025f * D3DXVec3Length(&vec);
	m_pos= pos;
}

void DrawDmageDot::Draw(void)
{
	if (m_Life > 0)
	{

		Object obj;
	
		ZeroMemory(&obj.m_Material, sizeof(obj.m_Material));
		obj.m_Material.Ambient = m_coler;
		obj.m_Material.Diffuse = m_coler;
		obj.m_Material.noTexSampling = 0;
		obj.m_Material.Emission = m_coler;
		float size = m_Length;
		obj.m_Scl = { size, size * 1.4f, size };
		obj.m_Pos = m_pos;
		obj.m_Uv_f = { 0.2f,0.5f };
		//ï\é¶ÇµÇΩÇ¢êîéöÇïœä∑
		std::string text = std::to_string((int)m_Nowdamage);
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
			case 0x30:obj.m_Uv_v = { 0.8f,0.5f }; textlength -= hufsize * 0.78f;
				break;
			case 0x31:obj.m_Uv_v = { 0.0f,0.0f }; textlength -= hufsize * 0.65f;
				break;
			case 0x32:obj.m_Uv_v = { 0.2f,0.0f }; textlength -= hufsize * 0.86f;
				break;
			case 0x33:obj.m_Uv_v = { 0.4f,0.0f }; textlength -= hufsize * 0.78f;
				break;
			case 0x34:obj.m_Uv_v = { 0.6f,0.0f }; textlength -= hufsize * 0.78f;
				break;
			case 0x35:obj.m_Uv_v = { 0.8f,0.0f }; textlength -= hufsize * 0.73f;
				break;
			case 0x36:obj.m_Uv_v = { 0.0f,0.5f }; textlength -= hufsize * 0.82f;
				break;
			case 0x37:obj.m_Uv_v = { 0.2f,0.5f }; textlength -= hufsize * 0.72f;
				break;
			case 0x38:obj.m_Uv_v = { 0.4f,0.5f }; textlength -= hufsize * 0.78f;
				break;
			case 0x39:obj.m_Uv_v = { 0.6f,0.5f }; textlength -= hufsize * 0.78f;
				break;
			default:
				break;
			}
			// 2Dï`âÊÇ»ÇÃÇ≈ê[ìxñ≥å¯
			SetDepthEnable(false);
			DrawPolygonBillX(obj, RefImageMaterial().m_Suzi, -textlength);
			SetDepthEnable(true);
			switch (b)
			{
			case 0x30: textlength -= hufsize * 0.78f;
				break;
			case 0x31: textlength -= hufsize * 0.65f;
				break;
			case 0x32: textlength -= hufsize * 0.86f;
				break;
			case 0x33: textlength -= hufsize * 0.78f;
				break;
			case 0x34: textlength -= hufsize * 0.78f;
				break;
			case 0x35: textlength -= hufsize * 0.73f;
				break;
			case 0x36: textlength -= hufsize * 0.82f;
				break;
			case 0x37: textlength -= hufsize * 0.72f;
				break;
			case 0x38: textlength -= hufsize * 0.78f;
				break;
			case 0x39: textlength -= hufsize * 0.78f;
				break;
			default:
				break;
			}
		}
	}
	
}

float DrawDmageDot::GetLength()
{
	return m_Length;
}
