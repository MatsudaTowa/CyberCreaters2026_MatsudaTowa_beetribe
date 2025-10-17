//=============================================
//
//�I�u�W�F�N�g[object.cpp]
//Author Matsuda Towa
//
//=============================================
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include  "manager.h"

//����������
int My::CObject::m_nNumAll = 0;

//�I�u�W�F�N�g�|�C���^������
My::CObject* My::CObject::m_apObject[CObject::PRI_MAX][CObject::MAX_OBJECT] = {};

/**
 * @brief �R���X�g���N�^
 * @param [in]�v���C�I���e�B
 */
My::CObject::CObject(int nPriority):
	m_isDelete(false),
	m_isStop(false),
	m_isDraw(true)
{
	m_nPriority = nPriority; //�`��D��x�ݒ�

	for (int nCnt = INT_ZERO; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{
			m_apObject[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt; //ID���
			m_type = OBJECT_TYPE_NONE;
			m_nNumAll++; //��������
			break;
		}
	}
}

/**
 * @brief �f�X�g���N�^
 */
My::CObject::~CObject()
{
	m_nNumAll--;
}

/**
 * @brief �S�č폜
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
				{//�}�l�[�W���[�ŏ�������
					//�I������
					m_apObject[nCntPri][nCntObj]->Uninit();
					m_apObject[nCntPri][nCntObj] = nullptr;
				}
			}
		}
	}
}

/**
 * @brief �S�čX�V
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
				//�X�V����
				m_apObject[nCntPri][nCntObj]->Update();
			}
		}
	}
}

/**
 * @brief �S�ĕ`��
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
			{//�`�悷����̂�
				//�`�揈��
				m_apObject[nCntPri][nCntObj]->Draw();
			}

			
		}
	}
}


/**
 * @brief �������g�̍폜
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
 * @brief �I�u�W�F�N�g�擾
 * @param [in]�v���C�I���e�B
 * @param [in]�C���f�b�N�X
 * @return �I�u�W�F�N�g�|�C���^
 */
My::CObject* My::CObject::Getobject(int nPri, int nIdx)
{
	return m_apObject[nPri][nIdx];
}