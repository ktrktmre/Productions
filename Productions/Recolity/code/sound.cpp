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
   構造体の定義
------------------------------------------------------------------------------*/
struct SoundData {
	std::string m_Kinds;						// 種類名
	IXAudio2SourceVoice* m_apSourceVoice;		// ソースボイス
	BYTE* m_apDataAudio;						// オーディオデータ
	DWORD m_aSizeAudio;							// オーディオデータサイズ
	UINT64 m_Smaple;
	UINT32 m_LoopCount;
	float m_CurrentVolume;
};

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2オブジェクトへのインターフェイス
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
std::unordered_map<std::string, std::string> g_SoundPathList;
std::unordered_map<int, SoundData> g_SoundDataList;
std::unordered_map<std::string, SoundData> g_ShareSoundDataList;
float g_WorldVolume;
float g_BGMVolume;
float g_SEVolume;

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

	//サウンドの登録
	RegisterSound();
	//各ボリュームの初期化
	g_WorldVolume = 0.5f;
	g_BGMVolume = 0.1f;
	g_SEVolume = 0.5f;

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

			// オーディオバッファの削除
			data.second.m_apSourceVoice->FlushSourceBuffers();

			// ソースボイスの破棄
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// オーディオデータの開放
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	for (auto& data : g_ShareSoundDataList)
	{
		if (data.second.m_apSourceVoice) {
			// 一時停止
			data.second.m_apSourceVoice->Stop(0);

			// オーディオバッファの削除
			data.second.m_apSourceVoice->FlushSourceBuffers();

			// ソースボイスの破棄
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// オーディオデータの開放
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	g_SoundDataList.clear();
	g_ShareSoundDataList.clear();
	g_SoundPathList.clear();
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
int LoadSound(std::string name)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(g_SoundPathList.at(name).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	HRESULT hr;

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// オーディオデータ読み込み
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// ソースボイスの生成
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
		return -1;
	}


	int index = (int)g_SoundDataList.size();
	for (int i = 0; i < g_SoundDataList.size(); i++)
	{
		if (!g_SoundDataList.count(i)) {
			index = i;
			break;
		}
	}

	//サウンドの種類設定
	auto chara = g_SoundPathList.at(name)[5];
	if (chara == 'B')
		data.m_Kinds = BGM;
	else
		data.m_Kinds = SE;

	//サウンドデータの格納
	g_SoundDataList[index] = data;


	return index;
}

/*------------------------------------------------------------------------------
   サウンドファイルの読み込み
------------------------------------------------------------------------------*/
bool LoadShareSound(std::string name)
{
	//既に共有されているサウンドの返り値
	if (g_ShareSoundDataList.count(name)) {
		return false;
	}


	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(g_SoundPathList.at(name).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}

	HRESULT hr;

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return false;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}

	// オーディオデータ読み込み
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return false;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return false;
	}

	// ソースボイスの生成
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
		return false;
	}

	//サウンドの種類設定
	auto chara = g_SoundPathList.at(name)[5];
	if (chara == 'B')
		data.m_Kinds = BGM;
	else
		data.m_Kinds = SE;

	//サウンドデータの格納
	g_ShareSoundDataList[name] = data;

	return true;
}

/*------------------------------------------------------------------------------
   音声の再生
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount, float vol)
{
	// 索引に無い数
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// 状態取得
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ループカウントの登録
	g_SoundDataList.at(index).m_LoopCount = loopCount;

	// ボリュームの設定
	SetVolume(index, vol);

	// 再生
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   音声の再生
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount, float vol, UINT32 sample)
{
	// 索引に無い数
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.PlayBegin = sample;
	buffer.LoopCount = loopCount;

	// 状態取得
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ループカウントの登録
	g_SoundDataList.at(index).m_LoopCount = loopCount;

	//ボリュームの設定
	SetVolume(index, vol);

	// 再生
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   共有音声の再生
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol)
{
	// 索引に無い数
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount = loopCount;

	// 状態取得
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ループカウントの登録
	g_ShareSoundDataList.at(name).m_LoopCount = loopCount;

	//ボリュームの設定
	SetVolume(name, vol);

	// 再生
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   共有音声の再生
------------------------------------------------------------------------------*/
void PlaySound(std::string name, float vol)
{
	// 索引に無い数
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 0;

	// 状態取得
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ループカウントの登録
	g_ShareSoundDataList.at(name).m_LoopCount = 0;

	//ボリュームの設定
	SetVolume(name, vol);

	// 再生
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   音声の再開
------------------------------------------------------------------------------*/
void ResumeSound(int index)
{
	// 索引に無い数
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		return;
	}

	XAUDIO2_BUFFER buffer;
	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.PlayBegin = g_SoundDataList.at(index).m_Smaple;
	buffer.LoopCount = g_SoundDataList.at(index).m_LoopCount;

	// オーディオバッファの削除
	g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();

	// オーディオバッファの登録
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   共有音声の再開
------------------------------------------------------------------------------*/
void ResumeSound(std::string name)
{
	// 索引に無い数
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		return;
	}

	XAUDIO2_BUFFER buffer;
	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.PlayBegin = g_ShareSoundDataList.at(name).m_Smaple;
	buffer.LoopCount = g_ShareSoundDataList.at(name).m_LoopCount;

	// オーディオバッファの削除
	g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();

	// オーディオバッファの登録
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   音声の一時停止
------------------------------------------------------------------------------*/
void PuaseSound(int index)
{
	// 索引に無い数
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// サンプルの取得
		g_SoundDataList.at(index).m_Smaple = xa2state.SamplesPlayed;

		// オーディオバッファの削除
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   共有音声の一時停止
------------------------------------------------------------------------------*/
void PuaseSound(std::string name)
{
	// 索引に無い数
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// サンプルの取得
		g_ShareSoundDataList.at(name).m_Smaple = xa2state.SamplesPlayed;

		// オーディオバッファの削除
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   流れているすべての音声一時停止
------------------------------------------------------------------------------*/
void PuaseSoundAll(void)
{
	XAUDIO2_VOICE_STATE xa2state;

	for (auto& data : g_SoundDataList)
	{
		// 状態取得
		data.second.m_apSourceVoice->GetState(&xa2state);
		if (xa2state.BuffersQueued != 0) {// 再生中
			// 一時停止
			data.second.m_apSourceVoice->Stop(0);

			// サンプルの取得
			data.second.m_Smaple = xa2state.SamplesPlayed;

			// オーディオバッファの削除
			data.second.m_apSourceVoice->FlushSourceBuffers();
		}
		// メモリーのリセット
		ZeroMemory(&xa2state, sizeof(XAUDIO2_VOICE_STATE));
	}
}

/*------------------------------------------------------------------------------
   音声の停止
------------------------------------------------------------------------------*/
void StopSound(int index)
{
	// 索引に無い数
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();

	}

	// ソースボイスの破棄
	g_SoundDataList.at(index).m_apSourceVoice->DestroyVoice();
	g_SoundDataList.at(index).m_apSourceVoice = NULL;

	// オーディオデータの開放
	free(g_SoundDataList.at(index).m_apDataAudio);
	g_SoundDataList.at(index).m_apDataAudio = NULL;


	//サウンドリストの一部削除
	g_SoundDataList.erase(g_SoundDataList.find(index));
}

/*------------------------------------------------------------------------------
   共有音声の停止
------------------------------------------------------------------------------*/
void StopSound(std::string name)
{
	// 索引に無い数
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// ソースボイスの破棄
	g_ShareSoundDataList.at(name).m_apSourceVoice->DestroyVoice();
	g_ShareSoundDataList.at(name).m_apSourceVoice = NULL;

	// オーディオデータの開放
	free(g_ShareSoundDataList.at(name).m_apDataAudio);
	g_ShareSoundDataList.at(name).m_apDataAudio = NULL;

	//サウンドリストの一部削除
	g_ShareSoundDataList.erase(g_ShareSoundDataList.find(name));
}

/*------------------------------------------------------------------------------
   読み込んでいるすべての音声を停止
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 一時停止
	for (auto& data:g_SoundDataList)
	{
		// 一時停止
		data.second.m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		data.second.m_apSourceVoice->FlushSourceBuffers();

		// ソースボイスの破棄
		data.second.m_apSourceVoice->DestroyVoice();
		data.second.m_apSourceVoice = NULL;

		// オーディオデータの開放
		free(data.second.m_apDataAudio);
		data.second.m_apDataAudio = NULL;

		// メモリーのリセット
		ZeroMemory(&xa2state, sizeof(XAUDIO2_VOICE_STATE));
	}

	//サウンドリストの全消去
	g_SoundDataList.clear();
}

/*------------------------------------------------------------------------------
	音量設定
------------------------------------------------------------------------------ */
void SetVolume(int index, float vol)
{
	//無効値の回避
	if (!g_SoundDataList.count(index)||vol > 1 || vol < 0)
		return;

	//ボリュームの設定
	g_SoundDataList.at(index).m_Kinds == BGM ?
		g_SoundDataList.at(index).m_apSourceVoice->SetVolume(vol * g_BGMVolume * g_WorldVolume) :
		g_SoundDataList.at(index).m_apSourceVoice->SetVolume(vol * g_SEVolume * g_WorldVolume);

	g_SoundDataList.at(index).m_CurrentVolume = vol;
}

/*------------------------------------------------------------------------------
	全ての音声の音量設定
------------------------------------------------------------------------------ */
void SetVolumeAll(float world)
{
	//無効値の回避
	if (world > 1 || world < 0)
		return;

	//ボリュームの設定
	g_WorldVolume = world;
	for (auto& data:g_SoundDataList)
	{
		data.second.m_Kinds == BGM ?
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_BGMVolume * g_WorldVolume) :
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_SEVolume * g_WorldVolume);
			
	}
	for (auto& data : g_ShareSoundDataList)
	{
		data.second.m_Kinds == BGM ?
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_BGMVolume * g_WorldVolume) :
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_SEVolume * g_WorldVolume);

	}
}

/*------------------------------------------------------------------------------
	種類ごとの音声の音量設定
------------------------------------------------------------------------------ */
void SetVolumeKinds(std::string kinds, float vol)
{
	//無効値の回避
	if (vol > 1 || vol < 0)
		return;

	kinds == BGM?g_BGMVolume = vol : g_SEVolume = vol;
	for (auto& data : g_SoundDataList)
	{
		if (data.second.m_Kinds == kinds) {
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * vol * g_WorldVolume);
		}
	}
	for (auto& data : g_ShareSoundDataList)
	{
		if (data.second.m_Kinds == kinds) {
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * vol * g_WorldVolume);
		}

	}
}

/*------------------------------------------------------------------------------
	共有音声の音量設定
------------------------------------------------------------------------------ */
void SetVolume(std::string name, float vol)
{
	//無効値の回避
	if (!g_ShareSoundDataList.count(name) || vol > 1 || vol < 0)
		return;

	//ボリュームの設定
	g_ShareSoundDataList.at(name).m_Kinds == BGM ?
		g_ShareSoundDataList.at(name).m_apSourceVoice->SetVolume(vol * g_BGMVolume * g_WorldVolume) :
		g_ShareSoundDataList.at(name).m_apSourceVoice->SetVolume(vol * g_SEVolume * g_WorldVolume);

	g_ShareSoundDataList.at(name).m_CurrentVolume = vol;
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

/*------------------------------------------------------------------------------
   サウンドパス名の登録
------------------------------------------------------------------------------*/
void RegisterSound(void)
{
	g_SoundPathList["machine"] = "data/SE/se_machine_noise.wav.wav";
	g_SoundPathList["scorpion"] = "data/SE/sasori.wav";
	g_SoundPathList["spider"] = "data/SE/spider_cry.wav";
	g_SoundPathList["use_card"] = "data/SE/attacksound.wav";
	g_SoundPathList["fier"] = "data/SE/fier.wav";
	g_SoundPathList["water"] = "data/SE/water.wav";
	g_SoundPathList["wind"] = "data/SE/wind.wav";
	g_SoundPathList["heal"] = "data/SE/heal.wav";
	g_SoundPathList["run"] = "data/SE/running-1-6846.wav";
	g_SoundPathList["wark"] = "data/SE/concrete-footsteps-6752.wav";
	g_SoundPathList["patrolenemy"] = "data/SE/se_machine_noise.wav";
	g_SoundPathList["enemybullet1"] = "data/SE/bulletenemy1.wav";
	g_SoundPathList["enemybullet2"] = "data/SE/bulletenemy2.wav";
	g_SoundPathList["bottun1"] = "data/SE/bottun1.wav";
	g_SoundPathList["bottun2"] = "data/SE/bottun2.wav";
	g_SoundPathList["bottun3"] = "data/SE/bottun3.wav";
	g_SoundPathList["bossbullet1"] = "data/SE/bossbullet1.wav";
	g_SoundPathList["bossbullet2"] = "data/SE/bossbullet2.wav";
	g_SoundPathList["paper"] = "data/SE/handle-paper-foley-2-172689.wav";
	g_SoundPathList["boss2_attack1"] = "data/SE/boss2_attack1.wav";
	g_SoundPathList["boss2_attack2"] = "data/SE/boss2_attack2.wav";

	g_SoundPathList["menu"] = "data/BGM/menubgm.wav";
	g_SoundPathList["sgatebgm"] = "data/BGM/sgatebgm.wav";
}

/*------------------------------------------------------------------------------
   ワールドボリュームの取得
------------------------------------------------------------------------------*/
float GetWolrdSound()
{
	return g_WorldVolume;
}

/*------------------------------------------------------------------------------
   効果音ボリュームの取得
------------------------------------------------------------------------------*/
float GetSESound()
{
	return g_SEVolume;
}

/*------------------------------------------------------------------------------
   BGMボリュームの取得
------------------------------------------------------------------------------*/
float GetBGMSound()
{
	return g_BGMVolume;
}

#ifdef _DEBUG
/*------------------------------------------------------------------------------
	サウンドデータサイズの取得
------------------------------------------------------------------------------*/
const int DataSize(void)
{
	int size = g_SoundDataList.size() + g_ShareSoundDataList.size();
	return size;
}
#endif // _DEBUG
