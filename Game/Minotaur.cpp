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

void Minotaur::Update(Camera& camera,int i)
{
	//移動処理
	Move(camera, i);

	//回転処理
	Turn(i);

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
void Minotaur::Move(Camera& camera, int i)
{
	
	//XZ平面の移動速度はパッドの入力から引っ張ってくる。
	m_lStickX = g_pad[i].GetLStickXF();
	m_lStickY = g_pad[i].GetLStickYF();
	//パッドの入力を使ってカメラを回す。
	m_rStickX = g_pad[i].GetRStickXF();
	m_rStickY = g_pad[i].GetRStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = camera.GetForward();
	CVector3 cameraRight = camera.GetRight();
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

	if (g_pad[i].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		m_moveSpeed.y += 500.0f;
		m_state = enState_Jump;
	}
	
	if (g_pad[i].IsTrigger(enButtonRB2) == true)
	{
		Stone* stone = g_game->GetStoneManager().NewStone();
		CVector3 target = camera.GetTarget() - camera.GetPosition();
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

void Minotaur::Turn(int i)
{
	if (g_pad[i].IsPress(enButtonLB2) == true)
	{
		SetCameraType(EnCameraType::enType_FPS);
		
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));
	}
	else
	{
		SetCameraType(EnCameraType::enType_TPS);

		//向きも変える。
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));

	}
}
void Minotaur::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	if (m_drawflag == true ||ViewportNumber !=PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			camera,
			0
		);
	}
}