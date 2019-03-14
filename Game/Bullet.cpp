#include "stdafx.h"
#include "Bullet.h"
#include "Game.h"


Bullet::Bullet()
{
}

Bullet::Bullet(CVector3 pos)
{
	m_model.Init(L"Assets/modelData/Bullet.cmo");

	m_bulletController.Init(1.0f, 1.0f, pos);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_pos = m_bulletController.Execute(1.0f / 60.0f, m_moveSpeed);
	//m_pos += m_moveSpeed;
	//CVector4 posInScreen(m_pos);
	////カメラ行列
	//CMatrix mView = g_camera3D.GetViewMatrix();
	////プロジェクション行列
	//CMatrix mProj = g_camera3D.GetProjectionMatrix();
	////カメラ空間の座標を計算する
	//mView.Mul(posInScreen);
	////スクリーン空間?に変換する
	//mProj.Mul(posInScreen);
	////wで除算すると正規化座標系(-1.0～1.0)になる
	//posInScreen.x /= posInScreen.w;
	//posInScreen.y /= posInScreen.w;
	//posInScreen.z /= posInScreen.w;

	//if (posInScreen.x > 1.0 || posInScreen.x < -1.0 ||
	//	posInScreen.y > 1.0 || posInScreen.y < -1.0 ||
	//	posInScreen.z>1.0 || posInScreen.z < -1.0)
	//{
	//	m_isDead = true;
	//}
	m_isDead = m_bulletController.GetIsDead();
	/*if (m_pos.x > 10000 || m_pos.x < -10000 ||
		m_pos.y > 1000 || m_pos.y < -1000 ||
		m_pos.z > 10000 || m_pos.z < -10000)
	{
		m_isDead = true;
	}*/
	
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	
}
void Bullet::Draw(Camera& camera)
{
	m_model.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), 0);
}