//=============================================
//
//メッシュ3Dオブジェクト[object3D_mesh.h]
//Author Matsuda Towa
//
//=============================================
#include "object3D_mesh.h"

My::CObject3D_Mesh::CObject3D_Mesh(int nPriority):CObject3D(nPriority)
{
}

My::CObject3D_Mesh::~CObject3D_Mesh()
{
}

HRESULT My::CObject3D_Mesh::Init()
{
	return S_OK;
}

void My::CObject3D_Mesh::Uninit()
{
}

void My::CObject3D_Mesh::Update()
{
}

void My::CObject3D_Mesh::Draw()
{
}

void My::CObject3D_Mesh::SetVtx(D3DXVECTOR3 nor)
{
}
