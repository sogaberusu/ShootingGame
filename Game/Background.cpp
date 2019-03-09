#include "stdafx.h"
#include "Background.h"


Background::Background()
{
	m_model.Init(L"Assets/modelData/Background.cmo");

	m_phyStaticObject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());

	//�n�ʂ��V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);
}


Background::~Background()
{
}

void Background::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//�V���h�E�L���X�^�[��o�^�B
	g_shadowMap.RegistShadowCaster(&m_model);
	
}

void Background::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(),0);
}