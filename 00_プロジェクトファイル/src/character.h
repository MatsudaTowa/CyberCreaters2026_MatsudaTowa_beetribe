//=============================================
//
//キャラクター処理[character.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //これが定義されてないとき

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
#include "model_parts.h"
#include "bullet.h"
#include "gun.h"
#include "character_behavior.h"
#include "character_state.h"
#include "wall.h"
#include "block.h"
#include "shadow.h"

//=============================================
//前方宣言
//=============================================
class CMove;
class CGunAttack;
class CStan;
class CConfusion;
class CCharacterState;

//=============================================
//キャラクタークラス
//=============================================
class CCharacter : public CObjectX
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int CHARACTER_PRIORITY = 8;
	static const int MAX_MOTION = 100;
	static const int MAX_PARTS = 64; //最大パーツ数
	static constexpr float  BOSS_FIELD_X = 600.0f; //ボス戦のX座標

	struct RayHitInfo
	{
		float distance;
		BOOL hit;
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X軸に当たっている
		bool bColision_Y; //Y軸に当たっている
		bool bColision_Z; //Z軸に当たっている
		float radius;
	};

	enum CHARACTER_STATE
	{
		CHARACTER_NORMAL = 0, //通常状態
		CHARACTER_DAMAGE, //ダメージ状態
		CHARACTER_STATE_MAX,
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CCharacter(int nPriority = CHARACTER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CCharacter()override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init()override;
	/**
	 * @brief 終了
	 */
	void Uninit()override;
	/**
	 * @brief 更新
	 */
	void Update()override;
	/**
	 * @brief 描画
	 */
	void Draw()override;
	/**
	 * @brief モーション描画
	 */
	void MotionDraw();

	/**
	 * @brief パーツ読み込み
	 * @param [in]ファイルの名前
	 */
	void Load_Parts(const char* FileName);
	/**
	 * @brief モーション処理
	 */
	void Motion();
	/**
	 * @brief モーション設定
	 * @param [in]どのモーションか
	 */
	void SetMotion(int Motion);
	/**
	 * @brief 重力処理
	 */
	void Gravity();
	/**
	 * @brief リロード
	 */
	virtual void Reload() = 0;
	/**
	 * @brief ジャンプ処理
	 */
	void Jump();
	/**
	 * @brief ブロックとの判定
	 * @param [in]パーツ数
	 */
	virtual void HitBlock(int NumParts);
	/**
	 * @brief 床との判定
	 */
	void HitField(); 
	/**
	 * @brief スモークとレイの判定
	 * @param [in]方向
	 * @param [in]キャラクターポインタ
	 * @return ヒット情報
	 */
	RayHitInfo PerformRaycast_Smoke(D3DXVECTOR3 vector, CCharacter* character);
	/**
	 * @brief ブロックとレイの判定
	 * @param [in]方向
	 * @param [in]キャラクターポインタ
	 * @return ヒット情報
	 */
	RayHitInfo PerformRaycast_Block(D3DXVECTOR3 vector, CCharacter* character);
	/**
	 * @brief ワールドマトリックス変換
	 */
	void ConversionMtxWorld();

	/**
	 * @brief ダメージのステート変更
	 */
	void ChangeDamageState();

	/**
	 * @brief 移動量設定
	 * @param [in]移動量
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	/**
	 * @brief 過去の位置設定
	 * @param [in]過去の位置
	 */
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	/**
	 * @brief 着地してるか設定
	 * @param [in]着地しているか
	 */
	inline void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	/**
	 * @brief リロードしてるか設定
	 * @param [in]リロードしているか
	 */
	inline void SetReload(bool bReload)
	{
		m_bReload = bReload;
	}

	/**
	 * @brief 体力設定
	 * @param [in]体力
	 */
	inline void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	/**
	 * @brief ステート設定
	 * @param [in]ステートポインタ
	 */
	inline void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	/**
	 * @brief スタンフレーム数設定
	 * @param [in]スタンフレーム
	 */
	inline void SetStanFrame(int StanFrame)
	{
		m_StanFrame = StanFrame;
	}

	/**
	 * @brief ステートのカウント設定
	 * @param [in]ステートカウント
	 */
	inline void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	/**
	 * @brief ステートのフレーム設定
	 * @param [in]ステートフレーム
	 */
	inline void SetStateFrame(int nStateFrame)
	{
		m_nStateFrame = nStateFrame;
	}

	/**
	 * @brief ジャンプ数設定
	 * @param [in]ジャンプ数
	 */
	inline void SetJumpCnt(int nJumpCnt)
	{
		m_nJumpCnt = nJumpCnt;
	}

	/**
	 * @brief モーションが終わったか設定
	 * @param [in]モーション終了フラグ
	 */
	inline void SetFinish(bool bFinish)
	{
		m_bLoopFinish = bFinish;
	}

	/**
	 * @brief 影のサイズ設定
	 * @param [in]影のサイズ
	 */
	inline void SetShadowSize(D3DXVECTOR3 shadow_size)
	{
		m_ShadowSize = shadow_size;
	}

	/**
	 * @brief 銃の設定
	 * @param [in]銃のポインタ
	 */
	inline void SetGun(CGun* gun)
	{
		m_pGun = gun;
	}

	/**
	 * @brief 移動のストラテジー設定
	 * @param [in]移動のストラテジーポインタ
	 */
	inline void SetMoveStrategy(CMove* move)
	{
		m_pMove = move;
	}

	/**
	 * @brief スタンのストラテジー設定
	 * @param [in]スタンストラテジーポインタ
	 */
	inline void SetStan(CStan* stan)
	{
		m_pStan = stan;
	}

	/**
	 * @brief 混乱のストラテジー設定
	 * @param [in]混乱のストラテジー
	 */
	inline void SetConfusion(CConfusion* confusion)
	{
		m_pConfusion = confusion;
	}

	/**
	 * @brief 銃の攻撃のストラテジー設定
	 * @param [in]銃の攻撃のストラテジーポインタ
	 */
	inline void SetGunAttack(CGunAttack* gun_attack)
	{
		m_pGunAttack =  gun_attack;
	}

	/**
	 * @brief 移動量取得
	 * @return 移動量
	 */
	inline D3DXVECTOR3 GetMove()
	{
		return m_move;
	}

	/**
	 * @brief 過去の位置取得
	 * @return 過去の位置
	 */
	inline D3DXVECTOR3& GetOldPos()
	{
		return m_oldpos;
	}

	/**
	 * @brief 影のサイズ取得
	 * @return 影のサイズ
	 */
	inline D3DXVECTOR3& GetShadowSize()
	{
		return m_ShadowSize;
	}

	/**
	 * @brief 着地してるか取得
	 * @return 着地してるか
	 */
	inline bool GetLaunding()
	{
		return m_bLanding;
	}

	/**
	 * @brief リロードしてるか取得
	 * @return リロードしてるか
	 */
	inline bool GetReload()
	{
		return m_bReload;
	}

	/**
	 * @brief モーション終了してるか取得
	 * @return モーション終了フラグ
	 */
	inline bool GetFinish()
	{
		return m_bLoopFinish;
	}

	/**
	 * @brief 体力取得
	 * @return 体力
	 */
	inline int GetLife()
	{
		return m_nLife;
	}

	/**
	 * @brief パーツ数取得
	 * @return パーツ数
	 */
	inline int GetNumParts()
	{
		return m_PartsCnt;
	}
	/**
	 * @brief スピード取得
	 * @return スピード
	 */
	inline float GetSpeed()
	{
		return m_Speed;
	}

	/**
	 * @brief ステート取得
	 * @return ステート
	 */
	inline CHARACTER_STATE GetState()
	{
		return m_State;
	}

	/**
	 * @brief ステート変更カウント取得
	 * @return ステート変更カウント
	 */
	inline int GetStateCnt()
	{
		return m_nStateCnt;
	}

	/**
	 * @brief ステート変更フレーム取得
	 * @return ステート変更フレーム
	 */
	inline int GetStateFrame()
	{
		return m_nStateFrame;
	}

	/**
	 * @brief ジャンプ数取得
	 * @return ジャンプ数
	 */
	inline int GetJumpCnt()
	{
		return m_nJumpCnt;
	}

	/**
	 * @brief スタンフレーム取得
	 * @return スタンフレーム
	 */
	inline int GetStanFrame()
	{
		return m_StanFrame;
	}

	/**
	 * @brief ステート変更
	 * @param [in]ステート
	 */
	void ChangeState(CCharacterState* state);

	/**
	 * @brief 銃の取得
	 * @return 銃のポインタ
	 */
	inline CGun* GetGun()
	{
		return m_pGun;
	}

	/**
	 * @brief 移動ストラテジーの取得
	 * @return 移動のストラテジーポインタ
	 */
	inline CMove* GetMoveStrategy()
	{
		return m_pMove;
	}

	/**
	 * @brief スタンストラテジー取得
	 * @return スタンストラテジーポインタ
	 */
	inline CStan* GetStan()
	{
		return m_pStan;
	}

	/**
	 * @brief 混乱ストラテジー取得
	 * @return 混乱ストラテジーポインタ
	 */
	inline CConfusion* GetConfusion()
	{
		return m_pConfusion;
	}

	/**
	 * @brief 銃の攻撃ストラテジー取得
	 * @return 銃の攻撃ストラテジーポインタ
	 */
	inline CGunAttack* GetGunAttack()
	{
		return m_pGunAttack;
	}

	//キャラクターのステートパターン
	CCharacterState* m_pCharacterState;

	//パーツ
	CModel_Parts* m_apModel[MAX_PARTS];

private:

	static constexpr float GRAVITY_MOVE = 2.0f; //重力値
	static constexpr float GRAVITY_MAX = 100.0f; //重力最大値
	static constexpr float SHADOW_POS_Y = 0.5f; //影のY座標(地面から少し浮かす)
	static constexpr float MOVE_FRICTION = 0.3f; //移動抵抗
	static constexpr float COLLISION_SLACK = 20.0f; //壁との判定のゆとり
	static constexpr float RAY_CORRECTION_VALUE = 20.0f; //レイを飛ばすYの補正値

	/**
	 * @brief ブロックとX軸の判定
	 * @param [in]パーツ番号
	 * @param [in]位置
	 * @param [in]最小座標
	 * @param [in]最大座標
	 * @param [in]ブロックポインタ
	 */
	void ColisionBlock_X(int PartsIdx,D3DXVECTOR3 CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	/**
	 * @brief ブロックとY軸の判定
	 * @param [in]パーツ番号
	 * @param [in][out]位置
	 * @param [in]最小座標
	 * @param [in]最大座標
	 * @param [in]ブロックポインタ
	 */
	void ColisionBlock_Y(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	/**
	 * @brief ブロックとZ軸の判定
	 * @param [in]パーツ番号
	 * @param [in][out]位置
	 * @param [in]最小座標
	 * @param [in]最大座標
	 * @param [in]ブロックポインタ
	 */
	void ColisionBlock_Z(int PartsIdx,D3DXVECTOR3 CharacterPos, const D3DXVECTOR3 CharacterMin, const D3DXVECTOR3 CharacterMax, CBlock* pBlock);

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bLanding; //着地してるかどうか
	bool m_bLoopFinish; //ループモーションが終わったか
	bool m_bReload; //リロードするかどうか

	int m_nLife; //体力
	int m_nShotBullet; //撃った弾数
	int m_nStateCnt; //ステート切り替え計測カウント
	int m_nStateFrame; //ステート切り替え計測フレーム数
	int m_PartsCnt; //パーツ数
	int m_nMotionFrameCnt; //切り替えフレームカウント
	int m_nKeySetCnt; //キー切り替えカウント
	int m_nJumpCnt; //ジャンプカウント
	int m_Motion; //モーション(各オブジェクトから列挙を受け取る)
	int m_StanFrame; //スタンのフレーム数
	float m_Speed; //スピード
	float m_Jump; //ジャンプ
	CHARACTER_STATE m_State; //プレイヤー状態
	D3DXCOLOR m_col; //カラー
	D3DXVECTOR3 m_ShadowSize; //影のサイズ

	CShadow* m_pShadow; //影

	//キー情報構造体
	struct Key
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 Trot;
	};

	//キー設定構造体
	struct KeySet
	{
		int nFrame; //フレーム数
		Key key[MAX_KEY];
	};

	//モーション設定構造体
	struct MotionSet
	{
		int nLoop; //ループするかどうか
		int nNumKey; //キー数
		KeySet keySet[MAX_PARTS];
	};

	struct MotionData
	{
		MotionSet motion_set[MAX_MOTION]; //モーション設定
		int parts;
		int idx[MAX_PARTS];
		int parent[MAX_PARTS];
		float speed;
		float jump;
		char path[MAX_PARTS][MAX_TXT];
		D3DXVECTOR3 parts_pos[MAX_PARTS];
		D3DXVECTOR3 parts_rot[MAX_PARTS];
	};
	MotionData m_motion_data;
	//銃
	CGun* m_pGun;

	CMove* m_pMove;

	CStan* m_pStan;

	CConfusion* m_pConfusion;

	CGunAttack* m_pGunAttack;
};
#endif