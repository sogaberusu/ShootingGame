#include "stdafx.h"
#include "GameCamera.h"
#include "Minotaur.h"
#include "Game.h"
#include "Player.h"

GameCamera::GameCamera()
{
	//�J�������������B
	g_camera3D[i].SetPosition({0.0f, 150.0f, 250.0f });
	g_camera3D[i].SetTarget({ 0.0f, 150.0f, 50.0f });
	g_camera3D[i].SetNear(1.0f);
	g_camera3D[i].SetFar(10000.0f);
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(g_camera3D[i].GetTarget() - g_camera3D[i].GetPosition());
	//���_���璍���_�܂ł̃x�N�g����ݒ�B
	m_toCameraTarget.Set(g_camera3D[i].GetPosition() - g_camera3D[i].GetTarget());

}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{

	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	m_rStickX = m_player->GetRStickX();
	m_rStickY = m_player->GetRStickY();
	//�L�����N�^�[�̈ړ��ɍ��킹�ăJ�������񂷁B
	m_lStickX = m_player->GetLStickX();
	m_lStickY = m_player->GetLStickY();
//////////////////////////////////////////////////////////////////////////////////
//	FPS���_�̌v�Z
//////////////////////////////////////////////////////////////////////////////////
	CVector3 playerforward = m_player->GetForward();
		
	CVector3 playerpos = m_player->GetPosition();
	playerpos.y += 85.0f;

	CVector3 target = playerpos + playerforward;
		
	CVector3 toCameraTargetOld = m_toCameraTarget;
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(),2.0f * m_rStickX);
	qRot.Multiply(m_toCameraTarget);
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraTarget);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX,2.0f * -m_rStickY );
	qRot.Multiply(m_toCameraTarget);
	CVector3 newFPSTarget = target + m_toCameraTarget;
	CVector3 toTargetDir = m_toCameraTarget;
	toTargetDir.Normalize();
	toTargetDir;
	if (toTargetDir.y < -0.9f) {
		//�J�����������������B
		m_toCameraTarget = toCameraTargetOld;
	}
	else if (toTargetDir.y > 0.7f) {
		//�J����������������B
		m_toCameraTarget = toCameraTargetOld;
	}
///////////////////////////////////////////////////////////////////////////////////////
//	TPS���_�̌v�Z
///////////////////////////////////////////////////////////////////////////////////////
	
	//�V���������_�����߂�B
	auto newTPSTarget = m_player->GetPosition();
	//Y�����ɂ�����Əグ��B
	newTPSTarget.y += 100.0f;
	CVector3 toCameraPosOld = m_toCameraPos;

	//Y������̉�]
	//CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0 * m_rStickX);
	qRot.Multiply(m_toCameraPos);
	////X������̉�]�B
	//CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * m_rStickY);
	qRot.Multiply(m_toCameraPos);
	//����p
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.7f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}
	//�V�������_���v�Z����B
	auto newPosition = newTPSTarget + m_toCameraPos;
	auto direction = newTPSTarget - newPosition;
	direction.Normalize();


	if (m_player->GetCameraType() == EnCameraType::enType_FPS)
	{
		m_player->DrawSetFalse();
		m_player->SetCameraDirection(newFPSTarget);
		g_camera3D[i].SetTarget(newFPSTarget);
		g_camera3D[i].SetPosition(playerpos);
		g_camera3D[i].Update();
	}
	else											//TPS
	{
		m_player->DrawSetTrue();
		m_player->SetCameraDirection(direction);
		g_camera3D[i].SetTarget(newTPSTarget);
		g_camera3D[i].SetPosition(newPosition);
		g_camera3D[i].Update();
	}
}

void GameCamera::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}