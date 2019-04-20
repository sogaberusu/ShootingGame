#include "stdafx.h"
#include "SMAW.h"


SMAW::SMAW()
{
	m_model.Init(L"Assets/modelData/SMAW.cmo");

	//m_model.SetShadowReciever(true);

}


SMAW::~SMAW()
{
}
void SMAW::Update(CVector3 pos)
{
	m_model.UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}
void SMAW::Draw(Camera& camera)
{
	
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}