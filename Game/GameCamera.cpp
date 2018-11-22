#include "stdafx.h"
#include "GameCamera.h"
#include "Minotaur.h"
#include "Game.h"

GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D[i].SetPosition({0.0f, 150.0f, 250.0f });
	g_camera3D[i].SetTarget({ 0.0f, 150.0f, 50.0f });
	g_camera3D[i].SetNear(1.0f);
	g_camera3D[i].SetFar(10000.0f);
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(g_camera3D[i].GetTarget() - g_camera3D[i].GetPosition());
	//視点から注視点までのベクトルを設定。
	m_toCameraTarget.Set(g_camera3D[i].GetPosition() - g_camera3D[i].GetTarget());

}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{

	//パッドの入力を使ってカメラを回す。
	m_rStickX = m_minotaur->GetRStickX();
	m_rStickY = m_minotaur->GetRStickY();	
	//キャラクターの移動に合わせてカメラを回す。
	m_lStickX = m_minotaur->GetLStickX();
	m_lStickY = m_minotaur->GetLStickY();
//////////////////////////////////////////////////////////////////////////////////
//	FPS視点の計算
//////////////////////////////////////////////////////////////////////////////////
	CVector3 minoforward = m_minotaur->GetForward();
		
	CVector3 minopos = m_minotaur->GetPosition();
	minopos.y += 100.0f;

	CVector3 target = minopos + minoforward;
		
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
///////////////////////////////////////////////////////////////////////////////////////
//	TPS視点の計算
///////////////////////////////////////////////////////////////////////////////////////
		
	////新しい視点を求める。
	//auto newPosition = m_minotaur->GetPosition();
	////Y方向にちょっと上げる。
	//newPosition.y += 50.0f;
	////X方向にちょっとずらす
	//newPosition.z -= 150.0f;
	//newPosition.x += 50.0f;
	////新しい注視点を求める。
	//auto newTPSTarget = m_minotaur->GetPosition();
	////Y方向にちょっと上げる。
	//newTPSTarget.y += 50.0f;
	//newTPSTarget.x += 50.0f;
	//auto direction = newTPSTarget - newPosition;
	//direction.Normalize();

	
	
	//新しい注視点を求める。
	auto newTPSTarget = m_minotaur->GetPosition();
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


	if (m_minotaur->GetCameraType() == EnCameraType::enType_FPS)
	{
		g_game->DrowSetFalse();
		m_minotaur->SetCameraDirection(newFPSTarget);
		g_camera3D[i].SetTarget(newFPSTarget);
		g_camera3D[i].SetPosition(minopos);
		g_camera3D[i].Update();
	}
	else
	{
		g_game->DrowSetTrue();
		m_minotaur->SetCameraDirection(direction);
		g_camera3D[i].SetTarget(newTPSTarget);
		g_camera3D[i].SetPosition(newPosition);
		g_camera3D[i].Update();
	}
}

void GameCamera::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);

}