//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ؓc�C���l
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "xaudio2.h"

//*****************************************************************************
// �\����
//*****************************************************************************
struct SoundData {
	IXAudio2SourceVoice* m_apSourceVoice;		// �\�[�X�{�C�X
	BYTE* m_apDataAudio;						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio;							// �I�[�f�B�I�f�[�^�T�C�Y
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void LoadSound(std::string pFilename, std::string name);
void PlaySound(std::string name, int loopCount, float vol);
void PlaySound(std::string name, int loopCount, float vol, UINT32 sample);
void PuaseSound(std::string name);
void StopSound(std::string name);
void StopSoundAll(void);
void SetVolume(std::string name, float vol);
IXAudio2SourceVoice* GetSoundData(std::string name);
void RegisterSound(void);

#endif // !_SOUND_H_