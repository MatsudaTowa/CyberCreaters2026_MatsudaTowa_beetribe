//=============================================
//
//モデル管理[model.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MODEL_H_ //これが定義されてないとき

#define _MODEL_H_
#include "main.h"

//=============================================
// モデル管理クラス
//=============================================
class CModel
{
public:
	static const int MAX_MODEL = 256; //モデルの数

	//モデル情報構造体定義
	struct MODEL_INFO
	{
		LPD3DXMESH pMesh; //メッシュ情報
		LPD3DXBUFFER pBuffMat; //マテリアル情報
		DWORD dwNumMat; //マテリアル数;
		const char* ModelName; //モデルネーム保存用
	};

	/**
	 * @brief コンストラクタ
	 */
	CModel();
	/**
	 * @brief デストラクタ
	 */
	~CModel();
	/**
	 * @brief アンロード
	 */
	void Unload();
	/**
	 * @brief 登録
	 * @param [in]モデルのパス
	 * @return 登録番号
	 */
	int Regist(const char* pModel);

	/**
	 * @brief モデル情報取得
	 * @param [in]番号
	 * @return モデル情報
	 */
	MODEL_INFO GetModelInfo(int nIdx);

private:
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //モデル情報
	int m_nNumAll; //モデル総数
};
#endif