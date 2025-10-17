//=============================================
//
//テクスチャ管理[texture.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TEXTURE_H_ //これが定義されてないとき

#define _TEXTURE_H_
#include "main.h"

//=============================================
// テクスチャ管理クラス
//=============================================
class CTexture
{
public:
	static const int MAX_TEX = 256; //テクスチャの数
	/**
	 * @brief コンストラクタ
	 */
	CTexture();
	/**
	 * @brief デストラクタ
	 */
	~CTexture();
	/**
	 * @brief テクスチャ破棄
	 */
	void Unload();
	/**
	 * @brief 登録
	 * @param [in]テクスチャパス
	 * @return テクスチャ登録番号
	 */
	int Regist(const std::string*pTex);
	/**
	 * @brief アドレス取得
	 * @param [in]番号
	 * @return テクスチャアドレス
	 */
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX]; //テクスチャへのポインタ
	std::string* m_texName[MAX_TEX]; //テクスチャネーム保存用
	int m_nNumAll; //テクスチャ総数
};
#endif