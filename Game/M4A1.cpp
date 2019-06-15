#include "stdafx.h"
#include "M4A1.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

M4A1::M4A1()
{
	//ワンショット再生のSE
	m_gunshot.Init(L"Assets/sound/M4A1_Shot.wav");

	m_model.Init(L"Assets/modelData/M4A1.cmo");


}


M4A1::~M4A1()
{
}
void M4A1::Update()
{
	m_position = m_player->GetHandPos();
	
	m_rotation = m_player->GetRotation();

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

	//シャドウキャスターを登録。
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}
void M4A1::Draw(Camera& camera, int ViewportNumber, int PlayerNumber)
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

void M4A1::Shot(CVector3 target,int PlayerNumber)
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

			Bullet* bullet = g_game->GetBulletManager().NewBullet(m_player->GetHandPos(),PlayerNumber, m_gunStatus.Attack);
			bullet->SetMoveSpeed(target * 2000);
			m_gunStatus.Ammo--;

			m_shootIntervalNow = 0.0f;
		}
	}
}