#include "stdafx.h"
#include "Minotaur.h"
#include "GameCamera.h"
#include "Game.h"
#include "Stone.h"

Minotaur::Minotaur()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Minotaur.cmo");

	InitAnimation();

	m_position.y =100.00f;
	m_charaCon.Init(10.0f, 50.0f, m_position);

	
}

void Minotaur::InitAnimation()
{
	//tkaファイルの読み込み。
	m_animationClips[enAnimation_Idle].Load(L"Assets/animData/Minotaur_Idle.tka");
	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_walk].Load(L"Assets/animData/Minotaur_Walk.tka");
	m_animationClips[enAnimation_walk].SetLoopFlag(true);

	m_animationClips[enAnimation_Jump].Load(L"Assets/animData/Minotaur_Jump.tka");
	m_animationClips[enAnimation_Jump].SetLoopFlag(false);

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enAnimation_Num		//アニメーションクリップの数。
	);
}

Minotaur::~Minotaur()
{
}

void Minotaur::Update()
{
	//移動処理
	Move();

	//回転処理
	Turn();

	switch (m_state)
	{
	case Minotaur::enState_Idle:
		m_animation.Play(enAnimation_Idle, 0.3);
		break;
	case Minotaur::enState_walk:
		m_animation.Play(enAnimation_walk, 0.3);
		break;
	case Minotaur::enState_Jump:
		m_animation.Play(enAnimation_Jump, 0.3);
		break;
	}
	
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Minotaur::Move()
{
	//XZ平面の移動速度はパッドの入力から引っ張ってくる。
	m_lStickX = g_pad[0].GetLStickXF();
	m_lStickY = g_pad[0].GetLStickYF();
	//パッドの入力を使ってカメラを回す。
	m_rStickX = g_pad[0].GetRStickXF();
	m_rStickY = g_pad[0].GetRStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f *( 1.0f / 60.0f);
	m_moveSpeed += cameraForward * m_lStickY * 200.0f;		//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight   * m_lStickX * 200.0f;		//右方向への移動速度を加算。
	if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0) {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_Idle;
	}
	else {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_walk;
	}

	if (g_pad[0].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		m_moveSpeed.y += 500.0f;
		m_state = enState_Jump;
	}
	
	if (g_pad[0].IsTrigger(enButtonRB2) == true)
	{
		Stone* stone = g_game->GetStoneManager().NewStone();
		CVector3 target = g_camera3D.GetTarget() - g_camera3D.GetPosition();
		target.Normalize();
		stone->SetMoveSpeed(target * 10);
		stone->SetPosition(m_position += {0.0, 50.0, 0.0});
	}

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	CMatrix rotMatrix = m_model.GetRotationMatrix();
		m_forward.x = rotMatrix.m[2][0];
		m_forward.y = rotMatrix.m[2][1];
		m_forward.z = rotMatrix.m[2][2];
		m_forward.Normalize();
		m_right.x = rotMatrix.m[0][0];
		m_right.y = rotMatrix.m[0][1];
		m_right.z = rotMatrix.m[0][2];
		m_right.Normalize();
}

void Minotaur::Turn()
{
	if (g_pad[0].IsPress(enButtonLB2) == true)
	{
		SetCameraType(EnCameraType::enType_FPS);
		////ワールド座標系での前方向
		//CVector3 front = CVector3::Front();
		////回転させるための軸
		//CVector3 axisY;
		////かめらの前方向
		//CVector3 cameraDir = m_cameraDirection;
		////角度を保存する変数
		//float radY = 0.0f;
		////カメラの前方向を正規化
		//cameraDir.Normalize();
		////カメラの前方向とfrontの内積をとる(この時に正規化していなければacosで非数が返ってくる
		//float angle = cameraDir.Dot(front);
		////カメラの前方向とfrontの外積をとる
		//axisY.Cross(cameraDir,front);
		////外積をとった後正規化する。(quaternionに使う軸は正規化されたベクトルでなければいけない
		//axisY.Normalize();
		////内積の結果からでた三角関数の値をラジアン(角度に直す、使う関数はacos
		//radY = acosf(angle);
		////m_rotation.SetRotation(axisY,radY);
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));
	}
	else
	{
		SetCameraType(EnCameraType::enType_TPS);

		//向きも変える。
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));
		
		//if (fabsf(m_moveSpeed.x) > 0.1f || fabsf(m_moveSpeed.z) > 0.1f)
		//{
		//	m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
		//}
	}
}
void Minotaur::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}