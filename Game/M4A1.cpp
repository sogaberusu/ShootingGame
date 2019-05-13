#include "stdafx.h"
#include "M4A1.h"
#include "Player.h"

M4A1::M4A1()
{
	m_model.Init(L"Assets/modelData/M4A1.cmo");
}


M4A1::~M4A1()
{
}
void M4A1::Update(CVector3 pos)
{
	m_position = m_player->GetHandPos();

	m_rotation = m_player->GetRotation();

	//CQuaternion qRot = CQuaternion::Identity();
	//qRot.SetRotationDeg(CVector3::AxisX(), m_player->GetRStickY() * -20.0f);
	////‰ñ“]‚ð‰ÁŽZ‚·‚éB
	//m_rotation.Multiply(qRot);


	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void M4A1::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	if (m_player->GetDrawFlag() == false || ViewportNumber != PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			0
		);
	}
}