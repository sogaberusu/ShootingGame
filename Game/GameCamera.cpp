#include "stdafx.h"
#include "GameCamera.h"
#include "Game.h"
#include "Player.h"

GameCamera::GameCamera(CVector3 camerapos)
{	
	/*CVector3 test = pos;
	test.y = 0.0f;
	auto r = sqrt(pow(test.x, 2.0f) + pow(test.z, 2.0f));
	test.x = test.x / r * 1700;
	test.z = test.z / r * 1700;
	test.y = 100.0f;
	
	g_camera3D[i].SetPosition(test);
	g_camera3D[i].SetTarget(pos);*/
	//g_camera3D[i].Update();
	//カメラを初期化。
	//g_camera3D[i].SetPosition({-0.0f, 150.0f, 250.0f });
	//g_camera3D[i].SetTarget({ 0.0f, 150.0f, 50.0f });
	g_camera3D[i].SetPosition(camerapos);
	g_camera3D[i].SetTarget({ 0.0f, 200.0f, 0.0f });
	g_camera3D[i].SetNear(1.0f);
	g_camera3D[i].SetFar(10000.0f);
	////注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(g_camera3D[i].GetTarget() - g_camera3D[i].GetPosition());
	////視点から注視点までのベクトルを設定。
	m_toCameraTarget.Set(g_camera3D[i].GetPosition() - g_camera3D[i].GetTarget());
	
}


GameCamera::~GameCamera()
{
	EndRender();
}
void GameCamera::Update()
{	
	
//	hoge = (m_player->GetPosition() - g_camera3D[i].GetPosition());
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
		g_camera3D[i].SetTarget(newFPSTarget);
		g_camera3D[i].SetPosition(playerpos);
		g_camera3D[i].Update();
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
		g_camera3D[i].SetTarget(newTPSTarget);
		g_camera3D[i].SetPosition(newPosition);
		g_camera3D[i].Update();
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