#include "stdafx.h"
#include "Goblin.h"
#include "StoneManager.h"

Goblin::Goblin()
{
	m_model.Init(L"Assets/modelData/Goblin.cmo");

	InitAnimation();

	m_position.y = 100.0f;
	m_position.x = 300.0f;
	m_charaCon.Init(10.0f, 50.0f, m_position);
}

void Goblin::InitAnimation()
{
	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[enAnimation_Idle].Load(L"Assets/animData/Goblin_Idle.tka");
	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_walk].Load(L"Assets/animData/Goblin_Walk.tka");
	m_animationClips[enAnimation_walk].SetLoopFlag(true);

	m_animationClips[enAnimation_Jump].Load(L"Assets/animData/Goblin_Jump.tka");
	m_animationClips[enAnimation_Jump].SetLoopFlag(false);

	//�A�j���[�V�����̏������B
	m_animation.Init(
		m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
		enState_Num					//�A�j���[�V�����N���b�v�̐��B
	);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	//�ړ�����
	Move();

	switch (m_state)
	{
	case Goblin::enState_Idle:
		m_animation.Play(enAnimation_Idle, 0.3);
		break;
	case Goblin::enState_walk:
		m_animation.Play(enAnimation_walk, 0.3);
		break;
	case Goblin::enState_Jump:
		m_animation.Play(enAnimation_Jump, 0.3);
		break;
	}

	
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Goblin::Move()
{
	//XZ���ʂ̈ړ����x�̓p�b�h�̓��͂�����������Ă���B
	m_moveSpeed.x = g_pad[1].GetLStickXF() * -300.0f;
	m_moveSpeed.z = g_pad[1].GetLStickYF() * -300.0f;
	if (m_moveSpeed.x == 0 && m_moveSpeed.z == 0) {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_Idle;
	}
	else {
		if (m_charaCon.IsOnGround() == true)
			m_state = enState_walk;
	}

	if (g_pad[1].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		m_moveSpeed.y += 500.0f;
		m_state = enState_Jump;
	}

	//Y�����̈ړ����x�͏d�͉������s���B
	m_moveSpeed.y -= 980.0f * (1.0f / 60.0f);

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//�������ς���B
	if (fabsf(m_moveSpeed.x) > 0.1f || fabsf(m_moveSpeed.z) > 0.1f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	}

}
void Goblin::Draw(Camera& camera)
{
	m_model.Draw(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		0
	);
}