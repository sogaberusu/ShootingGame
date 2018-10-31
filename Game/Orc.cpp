#include "stdafx.h"
#include "Orc.h"


Orc::Orc()
{
	m_model.Init(L"Assets/modelData/Orc.cmo");

	InitAnimation();

	m_position.y = 100.0f;
	m_position.z = 300.0f;
	m_charaCon.Init(50.0f, 100.0f, m_position);
}


Orc::~Orc()
{
}
void Orc::InitAnimation()
{
	//tkaファイルの読み込み。
	m_animationClips[enAnimation_Idle].Load(L"Assets/animData/Orc_Idle.tka");
	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_walk].Load(L"Assets/animData/Orc_Walk.tka");
	m_animationClips[enAnimation_walk].SetLoopFlag(true);

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enState_Num			//アニメーションクリップの数。
	);
}
void Orc::Update()
{
	//移動処理
	Move();
	
	switch (m_state)
	{
	case Orc::enState_Idle:
		m_animation.Play(enAnimation_Idle, 0.3);
		break;
	case Orc::enState_walk:
		m_animation.Play(enAnimation_walk, 0.3);
		break;
	}

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Orc::Move()
{
	//XZ平面の移動速度はパッドの入力から引っ張ってくる。
	m_moveSpeed.x = g_pad[2].GetLStickXF() * -300.0f;
	m_moveSpeed.z = g_pad[2].GetLStickYF() * -300.0f;
	if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0) {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_Idle;
	}
	else {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_walk;
	}

	//Y方向の移動速度は重力加速を行う。
	m_moveSpeed.y -= 980.0f * (1.0f / 60.0f);

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//向きも変える。
	if (fabsf(m_moveSpeed.x) > 0.1f || fabsf(m_moveSpeed.z) > 0.1f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	}

}
void Orc::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}