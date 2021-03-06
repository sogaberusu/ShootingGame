#include "stdafx.h"
#include "Benelli_M4.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

Benelli_M4::Benelli_M4()
{
	//ワンショット再生のSE
	m_gunshot.Init(L"Assets/sound/Shotgun_Shot.wav");

	m_model.Init(L"Assets/modelData/Benelli M4.cmo");

	srand((unsigned)time(NULL));
}


Benelli_M4::~Benelli_M4()
{
}
void Benelli_M4::Update()
{
	m_position = m_player->GetHandPos();

	m_rotation = m_player->GetRotation();

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}
void Benelli_M4::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
{
	if (m_player->GetCameraType() == Player::EnCameraType::enType_TPS || ViewportNumber != PlayerNumber)
	{
		m_model.Draw(
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			enNormalDraw
		);
	}
}

void Benelli_M4::Shot(CVector3 target, int PlayerNumber)
{
	

	if (m_gunStatus.Ammo > 0)
	{
		m_shootIntervalNow += 0.1f;

		if (m_shootIntervalNow > m_gunStatus.SHOTINTERVAL)
		{
			//エフェクトを再生
			g_game->GetMuzzleFlasheEffect(PlayerNumber).Play(m_position, m_rotation, CVector3::One());

			if (m_gunshot.IsPlaying())
			{
				m_gunshot.Stop();
			}
			m_gunshot.Play(false);

			for (int i = 0; i < m_gunStatus.SCATTER; i++)
			{
				if (m_player->GetCameraType() == Player::EnCameraType::enType_TPS) {
					Bullet* bullet = g_game->GetBulletManager().NewBullet(m_player->GetHandPos(), PlayerNumber, m_gunStatus.Attack);
					target.x += GetRandom();
					target.y += GetRandom();
					target.z += GetRandom();
					bullet->SetMoveSpeed(target * 2000);
					bullet->SetLife(m_gunStatus.BulletLife);
				}
				else {
					Bullet* bullet = g_game->GetBulletManager().NewBullet(g_camera3D[PlayerNumber].GetPosition(), PlayerNumber, m_gunStatus.Attack);
					target.x += GetRandom();
					target.y += GetRandom();
					target.z += GetRandom();
					bullet->SetMoveSpeed(target * 2000);
					bullet->SetLife(m_gunStatus.BulletLife);
				}
			}
			m_gunStatus.Ammo--;

			m_shootIntervalNow = 0.0f;
		}
	}
}