#include "stdafx.h"
#include "M110.h"


M110::M110()
{
	m_model.Init(L"Assets/modelData/M110.cmo");

	//m_model.SetShadowReciever(true);

}


M110::~M110()
{
}
void M110::Update(CVector3 pos)
{
	m_model.UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}
void M110::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}