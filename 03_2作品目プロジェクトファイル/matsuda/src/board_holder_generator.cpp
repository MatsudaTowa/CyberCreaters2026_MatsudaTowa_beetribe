//=============================================
//
//板持ち生成[board_holder_generator.cpp]
//Auther matsuda towa
//
//=============================================
#include "board_holder_generator.h"
#include "field.h"
#include "game_manager.h"
#include "json.h"
#include "game.h"

//=============================================
//ポインター
//=============================================
namespace MyPointer
{
	My::CField* pField; //フィールドのポインター
}

//乱数に関するネームスペース
namespace MyRandomBoard_Generator
{
	auto seed = chrono::system_clock::now().time_since_epoch().count(); //現在時刻をシード値として使用
	mt19937 gen((unsigned)seed);                                        // メルセンヌ・ツイスターの32ビット版
}

//=============================================
// 乱数の生成処理
//=============================================
int My::CBoardHolderGenerator::Random(int Low, int Hight)
{
	uniform_int_distribution<> dist(Low, Hight);                        //指定された範囲の値が等確率で発生するよう離散分布するクラスで設定
	return dist(MyRandomBoard_Generator::gen);                          //乱数を返す
}

//========================================
// 登録
//========================================
void My::CBoardHolderGenerator::Regist(CBoardHolder* board_holder)
{
	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_pBoardHolderList)
	{
		if (itr == board_holder)
		{
			bRegisted = true;
			break;
		}
	}

	//登録されているなら抜ける
	if (bRegisted)
	{
		return;
	}

	//板持ちの情報を登録
	m_pBoardHolderList.push_back(board_holder);
}

//========================================
// 削除
//========================================
void My::CBoardHolderGenerator::Delete(CBoardHolder* board_holder, D3DXVECTOR3 pos)
{
	//サイズが0なら抜ける
	if (m_pBoardHolderList.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_pBoardHolderList)
	{
		if (itr == board_holder)
		{
			bRegisted = true;
			break;
		}
	}

	//登録されていないなら抜ける
	if (!bRegisted)
	{
		return;
	}

	//板持ちの情報を削除
	m_pBoardHolderList.remove(board_holder);

	//保存した位置を消す（消した空手オブジェクトの位置）
	int size = m_savepos.size();

	for (int nCount = 0; nCount < size; nCount++)
	{
		if (size > 0)
		{
			//Y軸に少数以下の微ずれな為、XとZ軸で判定
			if (pos.x == m_savepos[nCount].x && pos.z == m_savepos[nCount].z)
			{
				m_savepos.erase(m_savepos.begin() + nCount);
				break;
			}
		}
	}
}

//=============================================
// 初期化
//=============================================
HRESULT My::CBoardHolderGenerator::Init()
{
	CGameManager::GetInstance()->SetGenerator(this);
	return S_OK;
}

//=============================================
// 生成
//=============================================
void My::CBoardHolderGenerator::Generate()
{
	int UpperBoard = (int)(CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->GetUpperLimitNumber() * 0.7);     //板持上限数の取得
	int UpperKawara = (int)ceil(CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->GetUpperLimitNumber() * 0.1);     //瓦の上限数の取得
	int UpperTrap = (int)ceil(CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->GetUpperLimitNumber() * 0.2);   //罠の上限数の取得
	int AllUpper = UpperBoard + UpperTrap + UpperKawara;                                                             //上限数の総数

	int AllCreateCount = 0;
	for (int i = 0; i < CJson::MAX_KARATEOBJ; ++i)
	{
		AllCreateCount += CJson::GetJson()->GetKarate(i)->GetcreateCount(); //各空手オブジェクトの保管数の取得
	}

	//空手オブジェクトの数(処理の順番の関係上ローカル)
	int nBoardCount = AllUpper - AllCreateCount;

	//生成数が上限に行った時
	if (m_num_holder >= UpperBoard && m_numTrap >= UpperTrap)
	{
		return;
	}

	D3DXVECTOR3 spawn_pos = VEC3_RESET_ZERO;

	//板持の数分回す
	for (int i = 0; i < nBoardCount; i++)
	{
		CField* pField = CGameManager::GetInstance()->GetField();

		MyPointer::pField = pField;

		My::CCamera* pCamera = GET_CAMERA(CGame::CAMERA_TYPE::BOARD_GENERATE_CAMERA);

		//HACK:マトリックスに値が入ってないときに無理やり関数を閉じる用
		if (pCamera->GetPosR() == VEC3_RESET_ZERO)
		{
			return;
		}
		if (pCamera->GetPosV() == VEC3_RESET_ZERO)
		{
			return;
		}

		//スポーン位置算出
		GeneratePosCalculation(pField, spawn_pos);

		{
			D3DXVECTOR3 generate_pos;							//生成位置用変数

			generate_pos = spawn_pos;

			//=======================================
			//各空手オブジェクトの生成処理 //MEMO 各空手オブジェクトの上限数分、生成処理＋生成数を増やす
			//========================================
			if (m_num_holder < UpperBoard)
			{//板持ち
				CBoardHolder::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CBoardHolderInfo); //生成処理（位置を乱数と同期）
				++m_num_holder;

				m_savepos.push_back(generate_pos);
			}
			//else if (m_numKawara < UpperKawara)
			//{//瓦
			//	CKawaraInfo::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CKawaraInfo);      //生成処理
			//	++m_numKawara;

			//	m_savepos.push_back(generate_pos);
			//}
			else if (m_numTrap < UpperTrap)
			{//罠持ち

				//規定値分上限数回数を向かえたら //MEMO 例、２の場合、上限数に達した回数
				if (CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->GetCount() >= 2)
				{
					CTrapHolderInfo::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CTrapHolderInfo);  //生成処理（位置を乱数と同期）
					++m_numTrap;

					m_savepos.push_back(generate_pos);
				}
			}
		}
	}

	////多く出す処理
	//if (m_boneflag == false)
	//{
	//	ManyCreate(MyPointer::pField);

	//	m_boneflag = true;
	//}
}

////========================================
//// スポーン位置算出
////========================================
//void My::CBoardHolderGenerator::GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos)
//{
//	D3DXVECTOR3 field_size = pField->GetSize();
//
//	while (1)
//	{
//		float x = Rundom(0, SCREEN_WIDTH);
//		float y = Rundom(0, SCREEN_HEIGHT);
//		spawn_pos = ConvertToWorldPoint({ x,y,0.0f }, pField->GetPos());
//
//		if (spawn_pos.x > -field_size.x && spawn_pos.x < field_size.x
//			&& spawn_pos.z > -field_size.z && spawn_pos.z < field_size.z)
//		{
//			break;
//		}
//	}
//}

//========================================
// スポーン位置算出
//========================================
void My::CBoardHolderGenerator::GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos)
{
	D3DXVECTOR3 field_size = pField->GetSize();

	//生成位置がフィールド内に収まっているかの判定
	while (1)
	{
		//補完した生成位置と今の生成位置がかぶっているかどうかの判定+プレイヤーの位置判別
		while (1)
		{
			//生成位置の範囲条件が満たされているかどうか
			if (RangePos(pField, spawn_pos, m_savepos) == true)
			{
				break;
			}
		}

		//最終チェック
		if (CretaePosCheck(field_size, spawn_pos) == true)
		{
			break;
		}

		spawn_pos = VEC3_RESET_ZERO;
	}
}

//========================================
// 多く生成する処理(板持のみ)
//========================================
bool My::CBoardHolderGenerator::ManyCreate(CField* pField)
{
	D3DXVECTOR3 field_size = pField->GetSize();                             //フィールドの大きさ

	vector<D3DXVECTOR3>savepos;                                             //生成位置を補完する用変数

	if (!m_boneflag)
	{
		m_boneflag = true;
		CGameManager::GetInstance()->GetPlayer()->SetPos(VEC3_RESET_ZERO);
		return false;
	}

	//板持の生成数
	for (int nCount = 0; nCount < SP_CREATE_BOARDER_NUMBER; nCount++)
	{
		D3DXVECTOR3 spawn_pos = VEC3_RESET_ZERO;

		//生成位置がフィールド内に収まっているかの判定
		while (1)
		{
			//補完した生成位置と今の生成位置がかぶっているかどうかの判定+プレイヤーの位置判別
			while (1)
			{
				//生成位置の範囲条件が満たされているかどうか
				if (RangePos(pField, spawn_pos, savepos) == true)
				{
					break;
				}
			}

			//最終チェック
			if (CretaePosCheck(field_size, spawn_pos) == true)
			{
				break;
			}
		}

		CBoardHolder::Create(D3DXVECTOR3(spawn_pos.x, 0.0f, spawn_pos.z), new CBoardHolderInfo); //生成処理（位置を乱数と同期）
		++m_num_holder;

		savepos.push_back(spawn_pos);
	}

	savepos.clear(); //念のため空に

	return true;
}

//========================================
// 生成位置の範囲決め
//========================================
bool My::CBoardHolderGenerator::RangePos(CField* pField, D3DXVECTOR3& spawn_pos, vector<D3DXVECTOR3>savepos)
{
	//NOTE: 画面内ギリギリを改善するには、原点０（右端、上端）から離し、終点を、離すといける
	float x = Rundom(RANDOM_SCREEN_X, SCREEN_WIDTH - RANDOM_SCREEN_X);
	float y = Rundom(RANDOM_SCREEN_Y, SCREEN_HEIGHT - RANDOM_SCREEN_Y);

	//プレイヤーの範囲決め用変数
	float fPlayerPosX = My::CGameManager::GetInstance()->GetPlayer()->GetPos().x; //プレイヤーのX軸 
	float fplayerPosZ = My::CGameManager::GetInstance()->GetPlayer()->GetPos().z; //プレイヤーのZ軸 

	spawn_pos = ConvertToWorldPoint(GET_CAMERA(CGame::BOARD_GENERATE_CAMERA), { x,y,0.0f }, pField->GetPos());

	int nsize = savepos.size();                                                   //保管数

	//sizeが無い(１人目)
	if (nsize == 0)
	{
		//プレイヤーの範囲内
		if (NotSpwan(spawn_pos, fPlayerPosX, fplayerPosZ) == true)
		{
			return false; 
		}
		return true;      
	}

	//現在の補完された位置の総数
	for (int nCount1 = 0; nCount1 < nsize; nCount1++)
	{
		//生成位置の判別
		if (spawn_pos.x > savepos[nCount1].x + CREATE_X_POS || spawn_pos.x < savepos[nCount1].x - CREATE_X_POS ||
			spawn_pos.z > savepos[nCount1].z + CREATE_Z_POS || spawn_pos.z < savepos[nCount1].z - CREATE_Z_POS)
		{
			//プレイヤーの範囲内
			if (NotSpwan(spawn_pos, fPlayerPosX, fplayerPosZ) == true)
			{
				break;
			}
		}
		else
		{
			break;       //生成位置がすでに生成された範囲内付近にかぶる＝だめです
		}

		//最後まで回した
		if (nCount1 >= nsize - 1)
		{
			return true; //完了
		}
	}

	return false;        //何かしらの条件に当てはまらない
}

//========================================
//生成させない範囲処理(プレイヤー)
//========================================
bool My::CBoardHolderGenerator::NotSpwan(D3DXVECTOR3& spawn_pos, float PlayerPosX, float PlayerPosZ)
{
	//プレイヤーの範囲判別
	if (spawn_pos.x > -NOT_SPAWN_PLAYER + PlayerPosX && spawn_pos.x < NOT_SPAWN_PLAYER + PlayerPosX &&
		spawn_pos.z > -NOT_SPAWN_PLAYER + PlayerPosZ && spawn_pos.z < NOT_SPAWN_PLAYER + PlayerPosZ)
	{
		return true;   //プレイヤーの範囲内
	}

	return false;      //プレイヤーの範囲外

}

//========================================
//生成位置の最終チェック処理
//========================================
bool My::CBoardHolderGenerator::CretaePosCheck(D3DXVECTOR3 field_size, D3DXVECTOR3& spawn_pos)
{
	//画面内判別
	if (spawn_pos.x > -field_size.x && spawn_pos.x < field_size.x
		&& spawn_pos.z > -field_size.z && spawn_pos.z < field_size.z)
	{
		return true;
	}

	return false;
}
