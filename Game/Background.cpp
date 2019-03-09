#include "stdafx.h"
#include "Background.h"


Background::Background()
{
	m_model.Init(L"Assets/modelData/Background.cmo");

	m_phyStaticObject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());

	//地面をシャドウレシーバーにする。
	m_model.SetShadowReciever(true);
}


Background::~Background()
{
}

void Background::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//シャドウキャスターを登録。
	g_shadowMap.RegistShadowCaster(&m_model);
	
}

void Background::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(),0);
}