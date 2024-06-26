//=============================================================================
//
// ボタン処理 [button.h]
// Author : 
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_
#pragma once

#include <map>
#include <string>
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEF_BUTTON_COLOR {0.6f,0.6f,0.6f,1.0f}
#define OVERLAP_BUTTON_COLOR {1.0f,1.0f,1.0f,1.0f}
#define BASE_BUTTTON_SIZE {400,100}

//*****************************************************************************
// クラス
//*****************************************************************************
class Button {
private:
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2  m_Size;
	D3DXCOLOR m_DefaultColor;
	D3DXCOLOR m_OverLapColor;
	bool m_OverLap;
	void IsOverLap(D3DXVECTOR2& pos);
public:
	Button() = default;
	Button(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	Button(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR def, D3DXCOLOR overlap);
	~Button() = default;
	const D3DXVECTOR2& RefPos(void) const;
	const D3DXVECTOR2& RefSize(void) const;
	const D3DXCOLOR& RefColor(void) const;
	const bool& RefOverLap(void) const;
	bool IsPush(D3DXVECTOR2& pos, BOOL trigger);
};

inline Button::Button(D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:m_Pos(pos), m_Size(size), m_DefaultColor(DEF_BUTTON_COLOR), m_OverLapColor(OVERLAP_BUTTON_COLOR), m_OverLap(false) {
}

inline Button::Button(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR def, D3DXCOLOR overlap)
	:m_Pos(pos), m_Size(size), m_DefaultColor(def), m_OverLapColor(overlap), m_OverLap(false) {
}

inline const D3DXVECTOR2& Button::RefPos(void) const {
	return m_Pos;
}

inline const D3DXVECTOR2& Button::RefSize(void) const {
	return m_Size;
}

inline const D3DXCOLOR& Button::RefColor(void) const {
	return m_OverLap ? m_OverLapColor : m_DefaultColor;
}

inline const bool& Button::RefOverLap(void) const {
	return m_OverLap;
}

inline void Button::IsOverLap(D3DXVECTOR2& pos){

	D3DXVECTOR2 max, min;
	max = m_Pos + m_Size * 0.5f;
	min = m_Pos - m_Size * 0.5f;

	if (pos.x>=min.x&&pos.x<=max.x) {
		if (pos.y >= min.y && pos.y <= max.y) {
			m_OverLap = true;
			return;
		}
	}

	m_OverLap = false;
}

inline bool Button::IsPush(D3DXVECTOR2& pos, BOOL trigger) {
	IsOverLap(pos);
	if (m_OverLap && trigger) {
		return true;
	}
	return false;
}

#endif // !_BUTTON_H_


