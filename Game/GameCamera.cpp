#include "stdafx.h"
#include "GameCamera.h"
#include "Game.h"
#include "Player.h"

GameCamera::GameCamera(CVector3 camerapos)
{	
	g_camera3D[m_playerNo].SetPosition(camerapos);
	g_camera3D[m_playerNo].SetTarget({ 0.0f, 200.0f, 0.0f });
	g_camera3D[m_playerNo].SetNear(1.0f);
	g_camera3D[m_playerNo].SetFar(10000.0f);
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(g_camera3D[m_playerNo].GetTarget() - g_camera3D[m_playerNo].GetPosition());
	//視点から注視点までのベクトルを設定。
	m_toCameraTarget.Set(g_camera3D[m_playerNo].GetPosition() - g_camera3D[m_playerNo].GetTarget());
	
}


GameCamera::~GameCamera()
{
	EndRender();
}
void GameCamera::Update()
{	
	//パッドの入力を使ってカメラを回す。
	m_rStickX = m_player->GetRStickX();
	m_rStickY = m_player->GetRStickY();
	//キャラクターの移動に合わせてカメラを回す。
	m_lStickX = m_player->GetLStickX();
	m_lStickY = m_player->GetLStickY();
//////////////////////////////////////////////////////////////////////////////////
//	FPS視点の計算
//////////////////////////////////////////////////////////////////////////////////
	CVector3 playerforward = m_player->GetForward();
		
	CVector3 playerpos = m_player->GetPosition();
	if (m_player->GetCrouch() == false)
	{
		playerpos.y += 85.0f;
	}
	if (m_player->GetCrouch() == true)
	{
		playerpos.y += 60.0f;
	}

	CVector3 target = playerpos + playerforward;
		
	CVector3 toCameraTargetOld = m_toCameraTarget;
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(),2.0f * m_rStickX);
	qRot.Multiply(m_toCameraTarget);
	//X軸周りの回転。
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
		//カメラが下向きすぎ。
		m_toCameraTarget = toCameraTargetOld;
	}
	else if (toTargetDir.y > 0.7f) {
		//カメラが上向きすぎ。
		m_toCameraTarget = toCameraTargetOld;
	}


	if (m_player->GetCameraType() == EnCameraType::enType_FPS)		//FPS
	{
		m_player->DrawSetFalse();
		m_player->SetCameraDirection(newFPSTarget);
		g_camera3D[m_playerNo].SetTarget(newFPSTarget);
		g_camera3D[m_playerNo].SetPosition(playerpos);
		g_camera3D[m_playerNo].Update();
	}
///////////////////////////////////////////////////////////////////////////////////////
//	TPS視点の計算
///////////////////////////////////////////////////////////////////////////////////////
	
	//新しい注視点を求める。
	auto newTPSTarget = m_player->GetPosition();
	//Y方向にちょっと上げる。
	newTPSTarget.y += 100.0f;
	CVector3 toCameraPosOld = m_toCameraPos;

	//Y軸周りの回転
	//CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0 * m_rStickX);
	qRot.Multiply(m_toCameraPos);
	////X軸周りの回転。
	//CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * m_rStickY);
	qRot.Multiply(m_toCameraPos);
	//視野角
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.7f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	//新しい視点を計算する。
	auto newPosition = newTPSTarget + m_toCameraPos;
	auto direction = newTPSTarget - newPosition;
	direction.Normalize();


	
	if (m_player->GetCameraType() == EnCameraType::enType_TPS)			//TPS
	{
		m_player->DrawSetTrue();
		m_player->SetCameraDirection(direction);
		g_camera3D[m_playerNo].SetTarget(newTPSTarget);
		g_camera3D[m_playerNo].SetPosition(newPosition);
		g_camera3D[m_playerNo].Update();
	}
}

void GameCamera::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}

void GameCamera::EndRender()
{
	g_graphicsEngine->SetViewport(1280, 740, 0, 0);
}