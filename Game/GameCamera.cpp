#include "stdafx.h"
#include "GameCamera.h"
#include "Minotaur.h"
#include "Game.h"

GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 200.0f, 200.0f });
	g_camera3D.SetTarget({ 0.0f, 150.0f, 50.0f });
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(10000.0f);
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(g_camera3D.GetTarget() - g_camera3D.GetPosition());
	//m_toCameraTarget.Set(-6961039.00,-97635792.0,741125760.);
	//m_toCameraTarget.Set(0, 0, 1);
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{
	//パッドの入力を使ってカメラを回す。
	m_rStickX = m_minotaur->GetRStickX();
	m_rStickY = m_minotaur->GetRStickY();

	if (m_minotaurCameraTypeLastFrame != m_minotaur->GetCameraType()) {
		//カメラが変わった
		m_minotaurCameraTypeLastFrame = m_minotaur->GetCameraType();
	}
	if (m_minotaur->GetCameraType() == EnCameraType::enType_FPS)
	{
		g_game->DrowSetFalse();

		m_minoforward = m_minotaur->GetForward();
		
		m_minopos = m_minotaur->GetPosition();
		m_minopos.y += 100.0f;
		
		CVector3 target = m_minopos + m_minoforward;
		
		
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
		CVector3 newTarget = target + m_toCameraTarget;

		m_minotaur->SetCameraDirection(newTarget);
		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(m_minopos);
		g_camera3D.Update();
	}
	else
	{
		g_game->DrowSetTrue();
		//新しい注視点を求める。
		auto newTarget = m_minotaur->GetPosition();
		//Y方向にちょっと上げる。
		newTarget.y += 50.0f;
		CVector3 toCameraPosOld = m_toCameraPos;

		//Y軸周りの回転
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 2.0 * m_rStickX);
		qRot.Multiply(m_toCameraPos);
		////X軸周りの回転。
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 2.0f * m_rStickY);
		qRot.Multiply(m_toCameraPos);
		//視野角
		CVector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.9f) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		//新しい視点を計算する。
		auto newPosition = newTarget + m_toCameraPos;

		auto direction = newTarget - newPosition;
		direction.Normalize();
		m_minotaur->SetCameraDirection(direction);

		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPosition);
		g_camera3D.Update();
	}
}