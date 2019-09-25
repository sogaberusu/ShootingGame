#include "stdafx.h"
#include "Sky.h"


Sky::Sky()
{
	m_skinModel.Init(L"Assets/modelData/sky.cmo");
	m_skinModel.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), {8000.0f,8000.0f,8000.0f});

}


Sky::~Sky()
{
}

void Sky::Draw(Camera& camera)
{
	m_skinModel.Draw(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		enSkyDraw
	);
}