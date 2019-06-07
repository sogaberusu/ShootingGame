#include "stdafx.h"
#include "Background.h"


Background::Background(CVector3 pos, CQuaternion rot)
{
	m_model.Init(L"Assets/modelData/Background.cmo");

	m_phyStaticObject.CreateMeshObject(m_model, pos, rot);
	m_position = pos;
	m_rotation = rot;
	//�n�ʂ��V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);
}


Background::~Background()
{
}

void Background::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//�V���h�E�L���X�^�[��o�^�B
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	
}

void Background::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(),0);
}