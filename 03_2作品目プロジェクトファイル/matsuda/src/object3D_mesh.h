//=============================================
//
//メッシュ3Dオブジェクト[object3D_mesh.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_MESH_H_ //これが定義されてないとき

#define _OBJECT3D_MESH_H_
#include "main.h"
#include "object3D.h"
#include "manager.h"

/** @brief My 名前空間 */
namespace My
{
	/** @brief メッシュ3Dオブジェクト */
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

		//頂点座標の代入
		void SetVtx(D3DXVECTOR3 nor);

		//それぞれの分割数計算
		inline void SetSplit(SPLIT_3D split)
		{
			m_Split.s_x = split.s_x;
			m_Split.s_y = split.s_y;
		}

		//分割数計算
		inline void SetSplitDiff(SPLIT_3D split)
		{
			m_SplitDiff = split.s_x - split.s_y;
		}

		//インデックス数計算
		inline void SetNumIdx(SPLIT_3D split)
		{
			m_NumIdx = (2 * (split.s_x + 1) * split.s_y + (split.s_y - 1) * 2);
		}

		//プリミティブ数計算
		inline void SetNumPri(int idx)
		{
			m_NumPri = m_NumIdx - 2;
		}

		//頂点数計算
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
		int m_SplitDiff;	//分割数の差
		int m_NumIdx;		//インデックス数
		int m_NumPri;		//プリミティブ数
		int m_NumVtx;		//頂点数

		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //インデックスバッファのポインタ
	};
}

#endif