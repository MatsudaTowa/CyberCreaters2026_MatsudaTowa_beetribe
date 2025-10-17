//=============================================
//
//板持ち生成[board_holder_generator.h]
//Auther matsuda towa
//
//=============================================

#ifndef _BOARD_HOLDER_GENERATOR_H_
#define _BOARD_HOLDER_GENERATOR_H_

#include "board_holder.h"
#include "field.h"

#include <vector>
using namespace std;

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 板持ち生成クラス
	 */
	class CBoardHolderGenerator
	{
	public:
		static const int NUM_GENERATE_POINT = 4;

		/**
		 * @brief コンストラクタ
		 */
		CBoardHolderGenerator() :m_num_holder(0), m_numTrap(0), m_numKawara(0){ m_savepos.clear(); m_pBoardHolderList.clear(); }

		/**
		 * @brief デストラクタ
		 */
		virtual ~CBoardHolderGenerator()
		{
			m_num_holder = 0;
			m_numKawara = 0;
			m_numTrap = 0;
			m_pBoardHolderList.clear();
			m_savepos.clear();
		};

		/**
		 * @brief 初期化
		 * @return 成功したか
		 */
		HRESULT Init();

		/**
		 * @brief 生成
		 */
		void Generate();

		/**
		 * @brief スポーン位置算出
		 * @param [in]床のポインタ
		 * @param [in][out]スポーン位置
		 */
		void GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos);

		/**
		 * @brief 多く生成(必殺用) bool型
		 * @param [in]床のポインタ
		 */
		bool ManyCreate(CField* pField);

		/**
		 * @brief 生成位置の範囲決め bool型
		 * @param [in]床のポインタ,生成位置,保管位置
		 */
		bool RangePos(CField* pField, D3DXVECTOR3& spawn_pos, vector<D3DXVECTOR3>savepos);

		/**
		 * @brief生成させない処理（プレイヤー） bool型
		 * @param [in]生成位置,プレイヤーのX軸,プレイヤーのZ軸
		 */
		bool NotSpwan(D3DXVECTOR3& spawn_pos, float PlayerPosX, float PlayerPosZ);

		/**
		 * @brief生成位置の最終チェック処理 bool型
		 * @param [in]床のポインタ,生成位置,保管位置
		 */
		bool CretaePosCheck(D3DXVECTOR3 field_size, D3DXVECTOR3& spawn_pos);

		/**
		 * @brief 乱数生成
		 */
		int Random(int Low, int Hight);

		/**
		 * @brief 減少
		 */
		void SubHolder()
		{
			if (0 >= m_num_holder)
			{
				return;
			}

			--m_num_holder;
		}

		/**
		 * @brief 減少
		 */
		void SubKawara()
		{
			if (0 >= m_numKawara)
			{
				return;
			}

			--m_numKawara;
		}

		/**
		 * @brief 減少
		 */
		void SubTrap()
		{
			if (0 >= m_numTrap)
			{
				return;
			}

			--m_numTrap;
		}

		/**
		 * @brief 板持ちの数取得
		 * @return 板持ちの数
		 */
		inline int GetNumHolder()
		{
			return m_num_holder;
		}

		/**
		 * @brief 板持ちの数取得
		 * @return 板持ちの数
		 */
		inline int GetNumkawara()
		{
			return m_numKawara;
		}

		/**
		 * @brief 板持ちの数取得
		 * @return 板持ちの数
		 */
		inline int GetNumTrap()
		{
			return m_numTrap;
		}

		/**
		 * @brief 登録
		 * @param [in]板持ち
		 */
		void Regist(CBoardHolder* board_holder);

		/**
		 * @brief 削除
		 * @param [in]板持ち
		 */
		void Delete(CBoardHolder* board_holder, D3DXVECTOR3 pos);

		std::list<CBoardHolder*> GetBoardHolderList()
		{
			return m_pBoardHolderList;
		}

	private:
		int m_num_holder;	//!何体いるか
		int m_numKawara;	//瓦数
		int m_numTrap;		//罠持ちの数

		D3DXVECTOR3 m_generate_point[NUM_GENERATE_POINT];
		std::list<CBoardHolder*> m_pBoardHolderList;

		vector<D3DXVECTOR3>m_savepos;  //位置を保存する為の変数

		bool m_boneflag = false;       //必殺用生成フラグ（debug用）

		//===========================
		//マクロ定義
		static constexpr float CREATE_X_POS = 50.0f;             //Ｘ軸の生成位置の範囲
		static constexpr float CREATE_Z_POS = 50.0f;             //Ｚ軸の生成位置の範囲

		static constexpr int SP_CREATE_BOARDER_NUMBER = 50;      //必殺技時の板持の生成数
		static constexpr float NOT_SPAWN_PLAYER = 80.0f;         //プレイヤーの生成位置されない範囲

		//乱数用
		static constexpr int RANDOM_SCREEN_X = 120;
		static constexpr int RANDOM_SCREEN_Y = 80;
	};
}

#endif