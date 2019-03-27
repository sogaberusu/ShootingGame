#include "stdafx.h"
#include "Benelli_M4.h"


Benelli_M4::Benelli_M4()
{
	m_model.Init(L"Assets/modelData/Benelli M4.cmo");

	m_model.SetShadowReciever(true);
}


Benelli_M4::~Benelli_M4()
{
}

void Benelli_M4::Update(CVector3 pos)
{
	m_model.UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}

void Benelli_M4::Draw(Camera& camera)
{
	

	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}