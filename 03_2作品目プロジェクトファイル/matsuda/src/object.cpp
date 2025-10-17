//=============================================
//
//オブジェクト[object.cpp]
//Author Matsuda Towa
//
//=============================================
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include  "manager.h"

//総数初期化
int My::CObject::m_nNumAll = 0;

//オブジェクトポインタ初期化
My::CObject* My::CObject::m_apObject[CObject::PRI_MAX][CObject::MAX_OBJECT] = {};

/**
 * @brief コンストラクタ
 * @param [in]プライオリティ
 */
My::CObject::CObject(int nPriority):
	m_isDelete(false),
	m_isStop(false),
	m_isDraw(true)
{
	m_nPriority = nPriority; //描画優先度設定

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{
			m_apObject[m_nPriority][nCnt] = this; //自分自身を代入
			m_nID = nCnt; //ID代入
			m_type = OBJECT_TYPE_NONE;
			m_nNumAll++; //総数増加
			break;
		}
	}
}

/**
 * @brief デストラクタ
 */
My::CObject::~CObject()
{
	m_nNumAll--;
}

/**
 * @brief 全て削除
 */
void My::CObject::ReleaseAll()
{
	for (int nCntPri = INT_ZERO; nCntPri < CObject::PRI_MAX; nCntPri++)
	{
		for (int nCntObj = INT_ZERO; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				if (m_apObject[nCntPri][nCntObj]->m_type != CObject::OBJECT_TYPE::OBJECT_TYPE_FADE
					&& m_apObject[nCntPri][nCntObj]->m_type != CObject::OBJECT_TYPE::OBJECT_MOUSE_DEBUG)
				{//マネージャーで消すため
					//終了処理
					m_apObject[nCntPri][nCntObj]->Uninit();
					m_apObject[nCntPri][nCntObj] = nullptr;
				}
			}
		}
	}
}

/**
 * @brief 全て更新
 */
void My::CObject::UpdateAll()
{
	for (int nCntPri = INT_ZERO; nCntPri < CObject::PRI_MAX; nCntPri++)
	{
		for (int nCntObj = INT_ZERO; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				if (m_apObject[nCntPri][nCntObj]->m_isStop)
				{
					continue;
				}
				//更新処理
				m_apObject[nCntPri][nCntObj]->Update();
			}
		}
	}
}

/**
 * @brief 全て描画
 */
void My::CObject::DrawAll()
{
	for (int nCntPri = INT_ZERO; nCntPri < CObject::PRI_MAX; nCntPri++)
	{
		for (int nCntObj = INT_ZERO; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] == nullptr)
			{
				continue;
			}

			if (m_apObject[nCntPri][nCntObj]->GetisDraw())
			{//描画するものは
				//描画処理
				m_apObject[nCntPri][nCntObj]->Draw();
			}

			
		}
	}
}


/**
 * @brief 自分自身の削除
 */
void My::CObject::Release()
{
	int nID = m_nID;
	int nPri = m_nPriority;
	if (m_apObject[nPri][nID] != nullptr)
	{
		delete m_apObject[nPri][nID];
		m_apObject[nPri][nID] = nullptr;
	}
}

/**
 * @brief オブジェクト取得
 * @param [in]プライオリティ
 * @param [in]インデックス
 * @return オブジェクトポインタ
 */
My::CObject* My::CObject::Getobject(int nPri, int nIdx)
{
	return m_apObject[nPri][nIdx];
}