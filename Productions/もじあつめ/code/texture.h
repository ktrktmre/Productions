//=============================================================================
//
// �e�N�`���[���� [texture.h]
// Author :�ؓc �C���l 
//
//=============================================================================
#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "renderer.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int LoadTexture(char* fileName);
void UninitTexture(void);
ID3D11ShaderResourceView** GetTexture(int index);

#endif // !_TEXTURE_H_