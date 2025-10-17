//=============================================
//
//オブジェクト[object.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT_H_ //これが定義されてないとき

#define _OBJECT_H_
#include "main.h"

//=============================================
//オブジェクトクラス
//=============================================
class CObject
{
public:
	static const int MAX_OBJECT = 256; //オブジェクトの最大数

	static const int PRI_MAX = 30; //プライオリティの最大値

	enum OBJECT_TYPE
	{
		OBJECT_TYPE_NONE = 0,
		OBJECT_TYPE_TITLE,
		OBJECT_TYPE_TUTORIAL,
		OBJECT_TYPE_RESULT,
		OBJECT_TYPE_FADE,
		OBJECT_TYPE_UI_BOX,
		OBJECT_TYPE_ULT_ICON,
		OBJECT_TYPE_PAUSE_SELECT,
		OBJECT_TYPE_HIT_CAMERA_EFFECT,
		OBJECT_TYPE_ULT_CAMERA_EFFECT,
		OBJECT_TYPE_GAUGE,
		OBJECT_TYPE_NUMBER,
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_ENEMY,
		OBJECT_TYPE_BLOCK,
		OBJECT_TYPE_BLOCK_PIECE,
		OBJECT_TYPE_MUZZLE_FLUSH,
		OBJECT_TYPE_FIELD,
		OBJECT_TYPE_WALL,
		OBJECT_TYPE_EFFECT,
		OBJECT_TYPE_DUSH_EFFECT,
		OBJECT_TYPE_BG,
		OBJECT_TYPE_BULLET,
		OBJECT_TYPE_RETICLE,
		OBJECT_TYPE_SMOKE,
		OBJECT_TYPE_SMOKE_GRENADE,
		OBJECT_TYPE_SMOKE_RANGE,
		OBJECT_TYPE_SHADOW,
		OBJECT_TYPE_ULT_EFFECT,
		OBJECT_TYPE_MAX,
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CObject(int nPriority = PRI_MAX);
	/**
	 * @brief デストラクタ
	 */
	virtual ~CObject();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	virtual HRESULT Init() = 0;
	/**
	 * @brief 終了
	 */
	virtual void Uninit() = 0;
	/**
	 * @brief 更新
	 */
	virtual void Update() = 0;
	/**
	 * @brief 描画
	 */
	virtual void Draw() = 0;
	/**
	 * @brief 全オブジェクト解放
	 */
	static void ReleaseAll();
	/**
	 * @brief 全オブジェクト更新
	 */
	static void UpdateAll();
	/**
	 * @brief 全オブジェクト描画
	 */
	static void DrawAll();
	/**
	 * @brief オブジェクト
	 * @param [in]プライオリティ
	 * @param [in]番号
	 * @return 
	 */
	static CObject* Getobject(int nPri,int nIdx);

	/**
	 * @brief タイプ取得
	 * @return オブジェクトタイプ
	 */
	inline OBJECT_TYPE GetType()
	{
		return m_type;
	}

	/**
	 * @brief 描画するかどうか設定
	 * @param [in]描画するか
	 */
	inline void SetisDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/**
	 * @brief 処理を止めるかどうか設定
	 * @param [in]処理を止めるか
	 */
	inline void SetisActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief 描画するかどうか取得
	 * @return 描画するか
	 */
	inline bool& GetisDraw()
	{
		return m_isDraw;
	}

	/**
	 * @brief 動かすどうか取得
	 * @return 動かすか
	 */
	inline bool& GetisActive()
	{
		return m_isActive;
	}

	/**
	 * @brief オブジェクトタイプ設定 
	 * @param [in]オブジェクトタイプ
	 */
	inline void SetType(OBJECT_TYPE type)
	{
		m_type = type;
	}

	/**
	 * @brief 自分自身の解放
	 */
	void Release();
private:
	static CObject* m_apObject[CObject::PRI_MAX][MAX_OBJECT];

	int m_nPriority; //描画優先度

	OBJECT_TYPE m_type;

	static int m_nNumAll; //総数

	bool m_isActive;	//動かせるか

	bool m_isDraw;	//描画するか

	int m_nID; //オブジェクトのID
};
#endif