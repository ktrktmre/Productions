//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "sound.h"


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
std::map<std::string,SoundData> g_SoundDataList;

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}

	RegisterSound();

	return true;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitSound(void)
{
	// �S�ẴT�E���h���~����
	for (auto& data:g_SoundDataList)
	{
		if (data.second.m_apSourceVoice) {
			// �ꎞ��~
			data.second.m_apSourceVoice->Stop(0);

			// �\�[�X�{�C�X�̔j��
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

/*------------------------------------------------------------------------------
   �T�E���h�t�@�C���̓ǂݍ���
------------------------------------------------------------------------------*/
void LoadSound(std::string pFilename, std::string name)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	//�ǂݍ��܂�Ă���T�E���h���𒲂ׂāA�����̂��̂�
	//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
	for (auto& data:g_SoundDataList)
	{
		//�T�E���h�����r
		if (data.first == name)
			return;
	}

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(pFilename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return;
	}

	HRESULT hr;

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
		return;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return;
	}

	// �\�[�X�{�C�X�̐���
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return;
	}

	g_SoundDataList[name] = data;
}

void SetVolume(std::string name, float vol)
{
	g_SoundDataList[name].m_apSourceVoice->SetVolume(vol);
}

IXAudio2SourceVoice* GetSoundData(std::string name)
{
	return g_SoundDataList[name].m_apSourceVoice;
}

/*------------------------------------------------------------------------------
   �����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol)
{
	SetVolume(name, vol);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList[name].m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList[name].m_apDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// ��Ԏ擾
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_SoundDataList[name].m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_SoundDataList[name].m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   �����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol, UINT32 sample)
{
	SetVolume(name, vol);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList[name].m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList[name].m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.PlayBegin = sample;
	buffer.LoopCount = loopCount;

	// ��Ԏ擾
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_SoundDataList[name].m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_SoundDataList[name].m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   �����̈ꎞ��~
------------------------------------------------------------------------------*/
void PuaseSound(std::string name)
{
	XAUDIO2_VOICE_STATE xa2state;


	// ��Ԏ擾
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList[name].m_apSourceVoice->Stop(0);
	}
}

/*------------------------------------------------------------------------------
   �����̒�~
------------------------------------------------------------------------------*/
void StopSound(std::string name)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   �ǂݍ���ł��邷�ׂẲ������~
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	// �ꎞ��~
	for (auto& data:g_SoundDataList)
	{
		if (data.second.m_apSourceVoice)
			data.second.m_apSourceVoice->Stop(0);
	}
}

/*------------------------------------------------------------------------------
   WAVE�t�H�[�}�b�g�̃`�F�b�N
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
   WAVE�t�H�[�}�b�g�̓ǂݍ���
------------------------------------------------------------------------------*/
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

void RegisterSound(void)
{
	LoadSound("data/BGM/Over_Speed.wav", "game_bgm");
	LoadSound("data/BGM/hukamaru nazo.wav", "title_bgm"); 
	LoadSound("data/SE/����{�^��������41.wav", "crystal");
	LoadSound("data/SE/����{�^��������28.wav", "torus");
	LoadSound("data/SE/Hit05-1.wav", "hit");
	LoadSound("data/SE/se_jump.wav", "jump");
	LoadSound("data/SE/swish1_2.wav", "rotate");
	LoadSound("data/SE/���E�L���[��07.wav", "avoid");
	LoadSound("data/SE/Cyber18-1.wav", "result");
}