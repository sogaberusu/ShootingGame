#include "stdafx.h"
#include "Stone.h"


Stone::Stone()
{
	m_model.Init(L"Assets/modelData/Stone.cmo");
}


Stone::~Stone()
{
}

void Stone::Update()
{
	m_pos += m_moveSpeed;
	//CVector4 posInScreen(m_pos);
	////�J�����s��
	//CMatrix mView = g_camera3D.GetViewMatrix();
	////�v���W�F�N�V�����s��
	//CMatrix mProj = g_camera3D.GetProjectionMatrix();
	////�J������Ԃ̍��W���v�Z����
	//mView.Mul(posInScreen);
	////�X�N���[�����?�ɕϊ�����
	//mProj.Mul(posInScreen);
	////w�ŏ��Z����Ɛ��K�����W�n(-1.0�`1.0)�ɂȂ�
	//posInScreen.x /= posInScreen.w;
	//posInScreen.y /= posInScreen.w;
	//posInScreen.z /= posInScreen.w;

	//if (posInScreen.x > 1.0 || posInScreen.x < -1.0 ||
	//	posInScreen.y > 1.0 || posInScreen.y < -1.0 ||
	//	posInScreen.z>1.0 || posInScreen.z < -1.0)
	//{
	//	m_isDead = true;
	//}
	if (m_pos.x > 1000 || m_pos.x < -1000 ||
		m_pos.y > 1000 || m_pos.y < -1000 ||
		m_pos.z > 1000|| m_pos.z < -1000)
	{
		m_isDead = true;
	}

	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());

}
void Stone::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
}