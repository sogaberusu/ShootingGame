#include "stdafx.h"
#include "Minotaur.h"
#include "GameCamera.h"
#include "Game.h"
#include "Stone.h"

Minotaur::Minotaur()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Minotaur.cmo");

	InitAnimation();

	m_position.y =100.00f;
	m_charaCon.Init(10.0f, 50.0f, m_position);

	
}

void Minotaur::InitAnimation()
{
	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[enAnimation_Idle].Load(L"Assets/animData/Minotaur_Idle.tka");
	m_animationClips[enAnimation_Idle].SetLoopFlag(true);

	m_animationClips[enAnimation_walk].Load(L"Assets/animData/Minotaur_Walk.tka");
	m_animationClips[enAnimation_walk].SetLoopFlag(true);

	m_animationClips[enAnimation_Jump].Load(L"Assets/animData/Minotaur_Jump.tka");
	m_animationClips[enAnimation_Jump].SetLoopFlag(false);

	//�A�j���[�V�����̏������B
	m_animation.Init(
		m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
		enAnimation_Num		//�A�j���[�V�����N���b�v�̐��B
	);
}

Minotaur::~Minotaur()
{
}

void Minotaur::Update()
{
	//�ړ�����
	Move();

	//��]����
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
	
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Minotaur::Move()
{
	//XZ���ʂ̈ړ����x�̓p�b�h�̓��͂�����������Ă���B
	m_lStickX = g_pad[0].GetLStickXF();
	m_lStickY = g_pad[0].GetLStickYF();
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	m_rStickX = g_pad[0].GetRStickXF();
	m_rStickY = g_pad[0].GetRStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f *( 1.0f / 60.0f);
	m_moveSpeed += cameraForward * m_lStickY * 200.0f;		//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight   * m_lStickX * 200.0f;		//�E�����ւ̈ړ����x�����Z�B
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
		////���[���h���W�n�ł̑O����
		//CVector3 front = CVector3::Front();
		////��]�����邽�߂̎�
		//CVector3 axisY;
		////���߂�̑O����
		//CVector3 cameraDir = m_cameraDirection;
		////�p�x��ۑ�����ϐ�
		//float radY = 0.0f;
		////�J�����̑O�����𐳋K��
		//cameraDir.Normalize();
		////�J�����̑O������front�̓��ς��Ƃ�(���̎��ɐ��K�����Ă��Ȃ����acos�Ŕ񐔂��Ԃ��Ă���
		//float angle = cameraDir.Dot(front);
		////�J�����̑O������front�̊O�ς��Ƃ�
		//axisY.Cross(cameraDir,front);
		////�O�ς��Ƃ����㐳�K������B(quaternion�Ɏg�����͐��K�����ꂽ�x�N�g���łȂ���΂����Ȃ�
		//axisY.Normalize();
		////���ς̌��ʂ���ł��O�p�֐��̒l�����W�A��(�p�x�ɒ����A�g���֐���acos
		//radY = acosf(angle);
		////m_rotation.SetRotation(axisY,radY);
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_cameraDirection.x, m_cameraDirection.z));
	}
	else
	{
		SetCameraType(EnCameraType::enType_TPS);

		//�������ς���B
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