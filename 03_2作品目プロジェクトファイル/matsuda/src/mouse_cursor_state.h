//=============================================
//
//マウスカーソルのステートパターン[mouse_cursor_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_CURSOR_STATE_H_
#define _MOUSE_CURSOR_STATE_H_
#include "count.h"
#include "mouse_trail.h"

/** @brief My 名前空間 */
namespace My
{
	//=============================================
	//前方宣言
	//=============================================
	class CGameMouseCursor;

	/** @brief マウスカーソルステートクラス */
	class CMouseCursorState
	{
	public:
		CMouseCursorState() {};
		virtual~CMouseCursorState() {};
		/**
		* @brief 通常処理(親では何もしない)
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Normal([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief 描く(親では何もしない)
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Write([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief 描き終わった(親では何もしない)
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Written([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief ポーズ(親では何もしない)
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Pause([[maybe_unused]] CGameMouseCursor* mouse) {};
	};

	/** @brief 通常状態クラス */
	class CNormalCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CNormalCursol();

		/**
		* @brief デストラクタ
		*/
		~CNormalCursol() override;		

		/**
		* @brief 通常処理
		* @param [in]マウスカーソルポインタ
		*/
		virtual void Normal(CGameMouseCursor* mouse)override;
	private:
	};

	/** @brief 描いてる状態クラス */
	class CWriteCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief コンストラクタ
		*/		
		CWriteCursol();

		/**
		* @brief デストラクタ
		*/		
		~CWriteCursol() override;

		/**
		* @brief 描く
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief カーソルの軌跡生成
		 * @param [in]マウスカーソルのポインタ
		 */
		virtual void CreateTrailPos(CGameMouseCursor* mouse) = 0;

		/**
		 * @brief 線形補間し途切れないように生成
		 * @param [in][out]軌跡の位置
		 */
		virtual void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) = 0;

		/**
		 * @brief 現在のインクの量取得
		 * @return インク量
		 */
		inline int GetAmont()
		{
			return m_current_amont;
		}

		/**
		 * @brief 現在のインクの量設定
		 * @param [in]インク量
		 */
		inline void SetAmont(int amont)
		{
			m_current_amont = amont;
		}

		/**
		 * @brief 何個ポイント生成したか
		 * @return ポイント生成数
		 */
		inline int GetCreateNum()
		{
			return m_create_num;
		}

		/**
		 * @brief 現在のインクの量設定
		 * @param [in]インク量
		 */
		inline void SetCreateNum(int create_num)
		{
			m_create_num = create_num;
		}

		/**
		 * @brief 開始位置取得
		 * @return 書き始め位置
		 */
		inline D3DXVECTOR3 GetStartPos()
		{
			return m_start_pos;
		}

		/**
		 * @brief 開始位置設定
		 * @param [in]開始位置
		 */
		inline void SetStartPos(D3DXVECTOR3 pos)
		{
			m_start_pos = pos;
		}

		/**
		 * @brief 一個あたりのポイントを書くのにかかったフレーム数取得
		 * @param [in]ポイント番号
		 * @return かかったフレーム数
		 */
		inline int GetCreateFrame(unsigned int idx)
		{
			if (idx > m_create_frame.size())
			{
				assert(false && "範囲外のサイズ");
			}

			return m_create_frame[idx];
		}

		/**
		 * @brief 生成カウント用変数取得
		 * @return カウントクラスのポインタ
		 */
		inline CCount* GetCreateCnt()
		{
			return m_pCreateCnt;
		}
	private:

		int m_current_amont;									//!<現在の量
		int m_create_num;										//!<生成した数
		std::vector<int> m_create_frame;							//軌跡ごとの生成フレーム
		D3DXVECTOR3 m_start_pos;								//!<始点
		CCount* m_pCreateCnt;									//!<生成するまでのカウント
	};

	/** @brief 描いてる状態通常クラス */
	class CWriteCursol_Normal : public CWriteCursol
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CWriteCursol_Normal();

		/**
		* @brief デストラクタ
		*/
		~CWriteCursol_Normal() override;

		/**
		* @brief 描く
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief カーソルの軌跡生成
		 * @param [in]マウスカーソルのポインタ
		 */
		void CreateTrailPos(CGameMouseCursor* mouse) override;

		/**
		 * @brief 線形補間し途切れないように生成
		 * @param [in][out]軌跡の位置
		 */
		void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) override;
	private:
	};

	/** @brief 描いてる状態必殺技クラス */
	class CWriteCursol_Special : public CWriteCursol
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CWriteCursol_Special();

		/**
		* @brief デストラクタ
		*/
		~CWriteCursol_Special() override;

		/**
		* @brief 描く
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief カーソルの軌跡生成
		 * @param [in]マウスカーソルのポインタ
		 */
		void CreateTrailPos(CGameMouseCursor* mouse) override;

		/**
		 * @brief 線形補間し途切れないように生成
		 * @param [in][out]軌跡の位置
		 */
		void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) override;
	private:
		static const int TRAIL_CREATE_NUM =5;									//一回で何回生成するか
		static const int SPECIAL_AMONT = 400;										//総量
		static const D3DXVECTOR3 TRAIL_CREATE_MIN_POS;
		static const D3DXVECTOR3 TRAIL_CREATE_MAX_POS;

		std::vector<CMouseTrail*> m_pTrail;
	};

	/** @brief 描き終わった状態クラス */
	class CWrittenCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CWrittenCursol();

		/**
		* @brief デストラクタ
		*/
		~CWrittenCursol() override;

		/**
		* @brief 描き終わった
		* @param [in]マウスカーソルのポインタ
		*/
		virtual void Written(CGameMouseCursor* mouse) override;
	private:
		CCount* m_pTrailCreateCnt;								//!<軌跡生成するまでのカウント

		/**
		 * @brief プレイヤーを軌跡の場所へ
		 * @param [in][out]到達したか
		 */
		void PlayerSetPos(CMouseTrailPoint* point, bool& retflag);
	};

	/** @brief ポーズ状態クラス */
	class CPauseCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CPauseCursol();

		/**
		* @brief デストラクタ
		*/
		~CPauseCursol() override;

		/**
		* @brief ポーズ処理
		* @param [in]マウスカーソルポインタ
		*/
		virtual void Pause(CGameMouseCursor* mouse)override;
	private:
	}; 
}
#endif // !_MOUSE_CURSOR_STATE_H
