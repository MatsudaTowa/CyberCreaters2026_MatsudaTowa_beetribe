//===============================================================
//
// ライブラリ(test_text.cpp)
// Author : Haruki Chiba
//
//===============================================================

#include "json.h"
#include <fstream>
#include <cmath>
#include "game.h"

//random_device rd;             //乱数生成エンジン
//default_random_engine  gen;   //乱数ジェネレータ

My::CJson* My::CJson::m_pJson = nullptr;


//ファイルに関する情報
namespace MyFile
{
	//エラーメッセージ表示
	void ErrorMessage(const char* FileName) { cerr << "File open error: " << FileName << "\n"; }

	//読み書き時
	template <typename T, typename C = const char*>
	void Error(T& Writing_File, C Message)
	{
		//ファイルが開けない時									              
		if (!Writing_File)
		{
			ErrorMessage(Message);                                      //エラーメッセージ表示
			quick_exit(0);                                              //後処理なしで終了
		}
	}
}

//名前空間（テキスト編）
namespace My
{
	//=============================
	//コンストラクタ
	//=============================
	CJson::CJson() : m_json{}
	{
		pKarateObject[0] = new CBoardObj();
		pKarateObject[1] = new CKawaraObj();
		pKarateObject[2] = new CTrapObj();
	}

	//=============================
	//デストラクタ
	//=============================
	CJson::~CJson()
	{
		for (int nCount = 0; nCount < MAX_KARATEOBJ; nCount++)
		{
			if (pKarateObject[nCount] != nullptr)
			{
				delete pKarateObject[nCount];
				pKarateObject[nCount] = nullptr;
			}
		}
	}

	//========================================
	//ジェイソンファイルを読み込む処理(乱数)
	//========================================
	void CJson::JysonRandLoad()
	{
		string filename = CJsonName::jsonFileName;                            //ファイルパスを設定

		//ファイルを読み込んで内容を画面に表示する			                  
		//読み込みに失敗した場合はエラーを表示する			                  
		ifstream ifs(filename.c_str());

		json json;                                                            //ジェイソンデータ格納用

		//空												               
		if (ifs.good())
		{
			//ループ
			while (1)
			{
				//ifs>>で情報が無い時は下のcatchに以移行する
				try
				{
					ifs >> json;                                              //読み込んだファイル情報と同期させる
				}
				//tryが終了次第移行
				catch (const exception&)
				{
					break;
				}
			}

			DeleteJson();                                                     //ファイル内の情報を削除

			ifs.close();
		}
		else
		{
			MyFile::Error(ifs, CJsonName::jsonFileName);                      //エラー処理
		}
	}

	//========================================
	//ジェイソンファイルに書き込む処理
	//========================================
	void CJson::JysonWrite()
	{
		//作成したファイルに内容を書き込む					                  
		ofstream writing_file;
		writing_file.open(CJsonName::jsonFileName, ios::out | ios::app);      //ファイルに追加書き込み

		//ファイルが開けない時								                  
		MyFile::Error(writing_file, CJsonName::jsonFileName);

		writing_file << m_json.dump() << endl;                                //データ構造をジェイソンに変換+書き込み

		writing_file.close();
	}

	//========================================
	//ジェイソンファイルに書き込む処理(情報削除)
	//========================================
	void CJson::DeleteJson()
	{
		//作成したファイルに内容を書き込む					                  
		ofstream writing_file;
		writing_file.open(CJsonName::jsonFileName, ios::out);                 //ファイルに書き込み

		//ファイルが開けない時									              
		MyFile::Error(writing_file, CJsonName::jsonFileName);

		writing_file << endl;                                                 //無を書き込み

		writing_file.close();
	}

	//========================================
	//ジェイソン情報の設定
	//========================================
	void CJson::SetJson()
	{
		m_json[CJsonName::TYPE] = 0;  //種類の設定
		JysonWrite();                 //ファイルに書く処理
	}


	//==================================================================================================================================
	//空手オブジェクトの情報のクラス処理
	//==================================================================================================================================
	void CKarateObject::Createobj()
	{
		//空手オブジェクトが破棄された時 //TODO これを追加するとジェネレータ処理の、上限数が古い方の取得になってしまう
		//if (m_nkarateObjCount >= 1)

		UpperLimitRatio();
	}

	//==================================
	//上限数から割合を出す処理
	//==================================
	void CKarateObject::UpperLimitRatio()
	{
		int nUpper = m_nupperLimitNumber-4;                                               //ゲージの規定値の最大数

		//ゲージが規定値以上に達した時							         
		if (m_ngage >= nUpper)
		{
			//上限数が規定値より小さい時＝上限数の最大値が規定値になる
			if (m_nupperLimitNumber < 20)
			{
				//各種類の割合を出す。
				m_nupperLimitNumber = m_nupperLimitNumber += UPPER_LIMIT_NUMBER_PLUS;  //上限数の引き上げ

				m_ncount++; //カウントを進める
			}

			m_nkarateObjCount = (int)(m_nupperLimitNumber)-m_ncreateCount;             //上限数のRatio割り分ー現在生成されている数=生成したい数

			m_ngage = 0;                                                               //ゲージリセット
		}
	}
}