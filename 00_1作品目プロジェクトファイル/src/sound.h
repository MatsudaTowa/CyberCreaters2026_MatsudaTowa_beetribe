//=============================================
//
//サウンド[sound.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SOUND_H_ //これが定義されてないとき

#define _SOUND_H_
#include "main.h"

class CSound
{
public:
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM0
		SOUND_LABEL_BGM_GAME,		// BGM1
		SOUND_LABEL_SE_HIT,			// HitSE
		SOUND_LABEL_SE_SHOT,		// ShotSE
		SOUND_LABEL_SE_TACKLE,		// タックルSE
		SOUND_LABEL_SE_BREAK,		// 壊れるSE
		SOUND_LABEL_SE_BLINK,		// 壊れるSE
		SOUND_LABEL_SE_SMOKE,		// スモークSE
		SOUND_LABEL_SE_RELOAD,		// リロードSE
		SOUND_LABEL_SE_ULT,			// ウルトSE
		SOUND_LABEL_MAX
	};

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	struct SOUNDINFO
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
		float fVolume;
	};

	static const SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
	/**
	 * @brief コンストラクタ
	 */
	CSound();
	/**
	 * @brief デストラクタ
	 */
	~CSound();
	/**
	 * @brief 初期化
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT InitSound(HWND hWnd);
	/**
	 * @brief 終了
	 */
	void UninitSound(void);
	/**
	 * @brief 再生
	 * @param [in]サウンドラベル
	 * @return 成功したか
	 */
	HRESULT PlaySound(SOUND_LABEL label);
	/**
	 * @brief 特定のサウンドを止める
	 * @param [in]サウンドラベル
	 */
	void StopSound(SOUND_LABEL label);
	/**
	 * @brief 全てのサウンドを止める
	 */
	void StopSound(void);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	/**
	 * @brief チャンクのチェック
	 * @param [in]ファイル
	 * @param [in]フォーマット
	 * @param [in]チャンクのサイズポインタ
	 * @param [in]チャンクの情報位置ポインタ
	 * @return 成功したか
	 */
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	/**
	 * @brief チャンクデータ読み込み
	 * @param [in]ファイル
	 * @param [in]バッファ
	 * @param [in]バッファサイズ
	 * @param [in]バッファ指定位置
	 * @return 
	 */
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};
#endif