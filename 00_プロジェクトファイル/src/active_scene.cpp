//=============================================
//
//遊べるシーン[active_scene.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_scene.h"

//=============================================
// コンストラクタ
//=============================================
CActiveScene::CActiveScene():m_pState(nullptr)
{
}

//=============================================
// デストラクタ
//=============================================
CActiveScene::~CActiveScene()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CActiveScene::Init()
{
	if (m_pState == nullptr)
	{
		m_pState = new CNormal;
	}
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CActiveScene::Uninit()
{
}

//=============================================
// 更新
//=============================================
void CActiveScene::Update()
{
	if (m_nPauseCnt <= PAUSE_POSSIBLE_FLAME)
	{
		++m_nPauseCnt;
	}
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Pause(this);
		m_pState->Setting(this);
	}
}

//=============================================
// 描画
//=============================================
void CActiveScene::Draw()
{
}

//=============================================
// 更新を止めるか
//=============================================
void CActiveScene::UpdateObjectDecision(bool isActive)
{
	for (int i = 0; i < CObject::PRI_MAX; ++i)
	{
		for (int j = 0; j < CObject::MAX_OBJECT; ++j)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(i, j);	//先頭取得

			if (pObj == nullptr)
			{
				continue;
			}

			if (pObj->GetisActive() != isActive)
			{
				pObj->SetisActive(isActive);
			}
		}
	}
}

//=============================================
// 更新を止めるか
//=============================================
void CActiveScene::LoadBlock(const std::string& pFileName)
{
	//ファイルの読み込み
	std::ifstream File(pFileName, std::ios::binary);

	//ファイルが開かなかったら関数を抜ける
	if (!File.is_open())
	{
		return;
	}

	//生成するブロック数読み込み用
	int NumBlock = 0;

	File.read(reinterpret_cast<char*>(&NumBlock), sizeof(int));

	if (NumBlock > 0)
	{
		//生成するブロックの情報を持つ変数
		std::vector<LOAD_BLOCK> info(NumBlock);

		//ファイルから読み込んだデータを格納
		File.read(reinterpret_cast<char*>(info.data()), sizeof(LOAD_BLOCK) * NumBlock);

		//イテレータで回して生成
		for (auto& itr : info)
		{
			CBlock::Create(itr.type, itr.pos, itr.rot);
		}
	}

	File.close();
}

//=============================================
// ステート状態
//=============================================
void CActiveScene::ChangeState(CActiveSceneState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
	else if (m_pState == nullptr)
	{
		delete state;
	}
}
