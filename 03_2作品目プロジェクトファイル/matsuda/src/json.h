//===============================================================
//
// ライブラリ(test_text.h)
// Author : Haruki Chiba
//
//===============================================================

#pragma once

#include "json.hpp"
#include <functional>
#include <vector>

//using宣言
using json = nlohmann::json;  //ジェイソンの使用可能宣言
using namespace std;          //std省略

////===================================
//	//文字列の設定
//string u8FieldText = u8"上段"; //日本語対応


/** @brief My TextLibrary */
namespace My
{
	//==========================================
	//空手オブジェクトの基底クラス
	class CKarateObject
	{
	public:

		//種類
		enum class Type
		{
			board = 0,                             //板持
			kawara,                                //瓦
			trap                                   //罠
		};

		/**
		* @brief コンストラクタ
		*/
		CKarateObject() : m_ngage(0), m_nupperLimitNumber(UPPER_LIMIT_NUMBER), m_ncount(0),
			m_nkarateObjCount(0), m_ncreateCount(0)
		{

		}

		/**
		* @brief デストラクタ
		*/
		virtual ~CKarateObject()
		{
			
		}

		/**
		* @brief タイプ別生成処理
		*/
		virtual void Createobj();

		/**
	   * @brief 上限数から割合を出す関数
	   */
		void UpperLimitRatio();

		/**
		* @brief オブジェクト数を増やす関数
		*/
		void PlusCreateobjCount()
		{
			m_ncreateCount++;
		}

		/**
		* @brief カウントを調整する関数
		*/
		inline void AdjsutobjCount()
		{
			m_nkarateObjCount++;
			m_ncreateCount--;
		}

		/**
		* @brief 生成保管数を取得
		*/
		inline int& GetcreateCount() { return m_ncreateCount; }

		/**
		* @brief 自身のオブジェクトのカウント数の設定
		* @param[in]入れる値
		*/
		inline void SetKarateObjCount(int nkarateobjectCount) { m_nkarateObjCount = nkarateobjectCount; }

		/**
		* @brief ゲージの値の設定
		* @param[in]入れる値
		*/
		inline void SetGage(int ngage) { m_ngage = ngage; }

		/**
		* @brief ゲージの値の取得
		*/
		inline int& GetGage() { return m_ngage; }

		/**
		* @brief 上限数の取得
		*/
		inline int& GetUpperLimitNumber() { return m_nupperLimitNumber; }

		int& GetCount() { return m_ncount; }


	protected:
		//=================================
		//マクロ定義
		static constexpr int LOWESTNUMBER = 1;            //最低値
		static constexpr int RECAST_TIME = 120;           //リキャストタイムの最大数
		static constexpr int UPPER_LIMIT_NUMBER = 5;      //上限数
		static constexpr int UPPER_LIMIT_NUMBER_PLUS = 5; //上限数の加算値
		static constexpr int INIT_BOARDCOUNT = 3;         //板持の初期数
		static constexpr int INIT_KAWARACOUNT = 1;        //瓦数の初期数
		static constexpr int INIT_TRAPCOUNT = 1;          //罠の初期数

	private:
		int m_nkarateObjCount;                            //板持の数   (割られた数)
		int m_ncreateCount;                               //生成された板の数
		int m_ngage;                                      //仮ゲー
		int m_nupperLimitNumber;                          //上限数

		//NOTE 例えば,>=2の時生成処理を呼ぶなどの使い方
		int m_ncount;                                     //カウント数で生成するか決めるよう
	};

	//==========================================
	//板持の情報クラス
	class CBoardObj : public CKarateObject
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CBoardObj()
		{
			SetKarateObjCount(INIT_BOARDCOUNT);                 //オブジェクト数の設定
			//PshuObjRecastTime(INIT_BOARDCOUNT, RECAST_TIME);  //リキャストタイムの設定
		}

		/**
		* @brief デストラクタ
		*/
		~CBoardObj()override
		{

		}

		/**
		* @brief タイプ別生成処理
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}

	private:
	};

	//==========================================
	//瓦の情報クラス
	class CKawaraObj :public CKarateObject
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CKawaraObj()
		{
			SetKarateObjCount(INIT_KAWARACOUNT);               //オブジェクト数の設定
		}

		/**
		* @brief デストラクタ
		*/
		~CKawaraObj()override
		{

		}

		/**
		* @brief タイプ別生成処理
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}

	private:
	};

	//==========================================
	//罠の情報クラス
	class CTrapObj :public CKarateObject
	{
	public:
		/**
		* @brief コンストラクタ
		*/
		CTrapObj()
		{
			SetKarateObjCount(INIT_TRAPCOUNT);               //オブジェクト数の設定
		}

		/**
		* @brief デストラクタ
		*/
		~CTrapObj()override
		{

		}

		/**
		* @brief タイプ別生成処理
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}
	private:
	};

	//==========================================
	//ジェイソンクラス
	class CJson
	{
	public:
		/**
		* @brief 自身のポインター
		*/
		static CJson*& GetJson() { return m_pJson; }

		/**
		* @brief 空手オブジェクトの取得
		* * @param [in]番号(0=板,1=瓦,2=罠)
		*/
		inline CKarateObject* GetKarate(int idx) { return pKarateObject[idx]; }

		/**
		* @brief コンストラクタ
		*/
		CJson();

		/**
		* @brief デストラクタ
		*/
		~CJson();

		/**
		* @brief 終了処理
		*/
		void Uninit()
		{
			delete m_pJson;
			m_pJson = nullptr;
		}

		/**
		* @brief 生成処理
		*/
		void Create()
		{
			m_pJson = new CJson();
		}

		/**
		* @brief ジェイソンファイルの読み込み（位置を乱数で調整）
		* @param [in] X軸の位置
		*/
		void JysonRandLoad();

		/**
		* @brief ジェイソンファイルの書き込み
		* @param
		*/
		void JysonWrite();

		/**
		* @brief ジェイソンファイルの中身の情報削除
		* @param
		*/
		void DeleteJson();

		/**
		* @brief ジェイソンファイルの書き込み(情報設定)
		* @param [in]種類
		*/
		void SetJson();

		//=======================
		//マクロ定義				      
		static constexpr int RANDRANGE = 200;      //乱数値の範囲(+-の値)
		static constexpr int NOTSPOWN = 80;        //スポーンしない範囲
		static constexpr int MAX_KARATEOBJ = 3;    //空手オブジェクトの総数

		//=======================
		//各空手オブジェクトの番号（配列番号）
		static constexpr int BOARDHOLDER_NUMBER = 0;
		static constexpr int KAWARA_NUMBER = 1;
		static constexpr int TRAPHOLDER_NUMBER = 2;

	private:

		//パス用クラス
		class CJsonName
		{
		public:
			static constexpr auto POS = "POS";                                   //位置
			static constexpr auto TYPE = "TYPE";                                 //種類

			static constexpr auto  jsonFileName = "data\\json\\file.json";       //ジェイソンファイルパス
		};

		//枚数、左右の判別、段の判別,強度,殴り可能か判別
		json m_json =
		{
			{CJsonName::POS,{0.0f,0.0f,0.0f}},     //位置
			{CJsonName::TYPE,-1},                  //種類
		};

		//======================
		//ポインター
		CKarateObject* pKarateObject[MAX_KARATEOBJ];
		static  CJson* m_pJson;
	};
}