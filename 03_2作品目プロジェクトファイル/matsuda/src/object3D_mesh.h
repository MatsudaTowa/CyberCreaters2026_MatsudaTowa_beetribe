//=============================================
//
//���b�V��3D�I�u�W�F�N�g[object3D_mesh.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_MESH_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT3D_MESH_H_
#include "main.h"
#include "object3D.h"
#include "manager.h"

/** @brief My ���O��� */
namespace My
{
	/** @brief ���b�V��3D�I�u�W�F�N�g */
	class CObject3D_Mesh : public CObject3D
	{
	public:
		struct SPLIT_3D
		{
			int s_x;
			int s_y;
		};

		CObject3D_Mesh(int nPriority = 3);
		~CObject3D_Mesh()override;
		HRESULT Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;

		//���_���W�̑��
		void SetVtx(D3DXVECTOR3 nor);

		//���ꂼ��̕������v�Z
		inline void SetSplit(SPLIT_3D split)
		{
			m_Split.s_x = split.s_x;
			m_Split.s_y = split.s_y;
		}

		//�������v�Z
		inline void SetSplitDiff(SPLIT_3D split)
		{
			m_SplitDiff = split.s_x - split.s_y;
		}

		//�C���f�b�N�X���v�Z
		inline void SetNumIdx(SPLIT_3D split)
		{
			m_NumIdx = (2 * (split.s_x + 1) * split.s_y + (split.s_y - 1) * 2);
		}

		//�v���~�e�B�u���v�Z
		inline void SetNumPri(int idx)
		{
			m_NumPri = m_NumIdx - 2;
		}

		//���_���v�Z
		inline void SetNumVtx(SPLIT_3D split)
		{
			m_NumVtx = (split.s_x + 1) * (split.s_y + 1);
		}

		void SetMeshData()
		{
			SetSplit(m_Split);
			SetSplitDiff(m_Split);
			SetNumIdx(m_Split);
			SetNumPri(m_NumIdx);
			SetNumVtx(m_Split);
		}

	private:

		SPLIT_3D m_Split;
		int m_SplitDiff;	//�������̍�
		int m_NumIdx;		//�C���f�b�N�X��
		int m_NumPri;		//�v���~�e�B�u��
		int m_NumVtx;		//���_��

		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //�C���f�b�N�X�o�b�t�@�̃|�C���^
	};
}

#endif