#include "stdafx.h"
#include "MP5.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

MP5::MP5()
{
	//�����V���b�g�Đ���SE
	m_gunshot.Init(L"Assets/sound/MP5_Shot.wav");

	m_model.Init(L"Assets/modelData/MP5.cmo");

}


MP5::~MP5()
{
}
void MP5::Update()
{
	m_position = m_player->GetHandPos();

	m_rotation = m_player->GetRotation();

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

	//�V���h�E�L���X�^�[��o�^�B
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}
void MP5::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	if (m_player->GetDrawFlag() == true || ViewportNumber != PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			0
		);
	}
	if (m_player->GetDrawFlag() == false || ViewportNumber != PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			0
		);
	}
}

void MP5::Shot(CVector3 target, int PlayerNumber)
{
	if (m_gunStatus.Ammo > 0)
	{

		m_shootIntervalNow += 0.1f;

		if (m_shootIntervalNow > m_gunStatus.SHOTINTERVAL)
		{
			//�G�t�F�N�g���Đ�
			g_game->GetEffect(PlayerNumber).Play(m_position, CVector3::One(), m_rotation);

			if (m_gunshot.IsPlaying())
			{
				m_gunshot.Stop();
			}
			m_gunshot.Play(false);

			Bullet* bullet = g_game->GetBulletManager().NewBullet(m_player->GetHandPos(),PlayerNumber, m_gunStatus.Attack);
			bullet->SetMoveSpeed(target * 2000);
			m_gunStatus.Ammo--;

			m_shootIntervalNow = 0.0f;
		}
	}
}