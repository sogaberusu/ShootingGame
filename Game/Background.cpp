#include "stdafx.h"
#include "Background.h"


Background::Background()
{
	m_model.Init(L"Assets/modelData/Background.cmo");

	m_phyStaticObject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());

}


Background::~Background()
{
}

void Background::Draw(Camera& camera)
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
}