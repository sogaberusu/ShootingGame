#include "stdafx.h"
#include "M4A1.h"


M4A1::M4A1()
{
	m_model.Init(L"Assets/modelData/M4A1.cmo");

	//m_model.SetShadowReciever(true);

}


M4A1::~M4A1()
{
}
void M4A1::Update(CVector3 pos)
{
	m_model.UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3{3.0,3.0,3.0});
}
void M4A1::Draw(Camera& camera)
{

	

	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}