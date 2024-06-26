//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 切田海畝斗
//
//=============================================================================
#include "sound.h"


/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2オブジェクトへのインターフェイス
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
std::map<std::string,SoundData> g_SoundDataList;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return false;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return false;
	}

	RegisterSound();

	return true;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitSound(void)
{
	// 全てのサウンドを停止する
	for (auto& data:g_SoundDataList)
	{
		if (data.second.m_apSourceVoice) {
			// 一時停止
			data.second.m_apSourceVoice->Stop(0);

			// ソースボイスの破棄
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// オーディオデータの開放
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

/*------------------------------------------------------------------------------
   サウンドファイルの読み込み
------------------------------------------------------------------------------*/
void LoadSound(std::string pFilename, std::string name)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	//読み込まれているサウンド名を調べて、同名のものが
	//すでに読み込まれていたらその番号を返す
	for (auto& data:g_SoundDataList)
	{
		//サウンド名を比較
		if (data.first == name)
			return;
	}

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(pFilename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	HRESULT hr;

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	// オーディオデータ読み込み
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	// ソースボイスの生成
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
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
   音声の再生
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol)
{
	SetVolume(name, vol);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList[name].m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList[name].m_apDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// 状態取得
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_SoundDataList[name].m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	g_SoundDataList[name].m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   音声の再生
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol, UINT32 sample)
{
	SetVolume(name, vol);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList[name].m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList[name].m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.PlayBegin = sample;
	buffer.LoopCount = loopCount;

	// 状態取得
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_SoundDataList[name].m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	g_SoundDataList[name].m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   音声の一時停止
------------------------------------------------------------------------------*/
void PuaseSound(std::string name)
{
	XAUDIO2_VOICE_STATE xa2state;


	// 状態取得
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList[name].m_apSourceVoice->Stop(0);
	}
}

/*------------------------------------------------------------------------------
   音声の停止
------------------------------------------------------------------------------*/
void StopSound(std::string name)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_SoundDataList[name].m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList[name].m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList[name].m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   読み込んでいるすべての音声を停止
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	// 一時停止
	for (auto& data:g_SoundDataList)
	{
		if (data.second.m_apSourceVoice)
			data.second.m_apSourceVoice->Stop(0);
	}
}

/*------------------------------------------------------------------------------
   WAVEフォーマットのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
   WAVEフォーマットの読み込み
------------------------------------------------------------------------------*/
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

void RegisterSound(void)
{
	LoadSound("data/BGM/Over_Speed.wav", "game_bgm");
	LoadSound("data/BGM/hukamaru nazo.wav", "title_bgm"); 
	LoadSound("data/SE/決定ボタンを押す41.wav", "crystal");
	LoadSound("data/SE/決定ボタンを押す28.wav", "torus");
	LoadSound("data/SE/Hit05-1.wav", "hit");
	LoadSound("data/SE/se_jump.wav", "jump");
	LoadSound("data/SE/swish1_2.wav", "rotate");
	LoadSound("data/SE/星・キラーン07.wav", "avoid");
	LoadSound("data/SE/Cyber18-1.wav", "result");
}