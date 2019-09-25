#include "stdafx.h"
#include "GrenadeManager.h"
#include "Grenade.h"


GrenadeManager::GrenadeManager()
{
	//初期化
	for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
	{
		m_player[PlayerNumber] = nullptr;
	}
	m_explosion.Init(L"Assets/sound/Explosion.wav");
}


GrenadeManager::~GrenadeManager()
{
	//解放
	for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
	{
		for (auto& Grenade : m_grenade[PlayerNumber]) {
			delete Grenade;
		}
	}
}

Grenade*GrenadeManager::NewGrenade(CVector3 pos, int PlayerNumber,CVector3 target)
{
	Grenade* newGrenade = new Grenade(pos,PlayerNumber, target);
	m_grenade[PlayerNumber].push_back(newGrenade);
	return newGrenade;
}

void GrenadeManager::Update()
{
	for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
	{
		for (auto& Grenade : m_grenade[PlayerNumber]) {
			Grenade->Update(PlayerNumber);
		}

		auto it = m_grenade[PlayerNumber].begin();
		while (it != m_grenade[PlayerNumber].end()) {
			if ((*it)->IsDead() == true) {
				for (int People = 0; People < PLAYERS; People++)
				{
					CVector3 distance = (*it)->GetPosition() - m_player[People]->GetPosition();

					if (distance.Length() < 100 && m_player[People]->GetState() != Player::enState_Death)
					{
						m_player[People]->SetHitPoint(m_player[People]->GetHitPoint() - 100);

						if (m_player[People]->GetHitPoint() <= 0)
						{
							//自分の投げたグレネードではないなら
							if (People != (*it)->GetThrowPlayer())
							{
								//攻撃したプレイヤーのキル数を増やす
								m_player[(*it)->GetThrowPlayer()]->SetKills(m_player[(*it)->GetThrowPlayer()]->GetStatus().Kills + 1);
							}
							//プレイヤーのHPが0以下になったら0にする
							m_player[People]->SetHitPoint(0);
							//プレイヤーを死亡状態にする
							m_player[People]->SetDead();
							break;
						}
					}
					if (distance.Length() < 200 && m_player[People]->GetState() != Player::enState_Death)
					{

						m_player[People]->SetHitPoint(m_player[People]->GetHitPoint() - 50);
						//当たったプレイヤーの自然回復までのインターバルを設定する
						m_player[People]->SetHealTimer(300);

						if (m_player[People]->GetHitPoint() <= 0)
						{
							//自分の投げたグレネードではないなら
							if (People != (*it)->GetThrowPlayer())
							{
								//攻撃したプレイヤーのキル数を増やす
								m_player[(*it)->GetThrowPlayer()]->SetKills(m_player[(*it)->GetThrowPlayer()]->GetStatus().Kills + 1);
							}
							//プレイヤーのHPが0以下になったら0にする
							m_player[People]->SetHitPoint(0);
							//プレイヤーを死亡状態にする
							m_player[People]->SetDead();
							break;
						}
					}
				}
				if (m_explosion.IsPlaying())
				{
					m_explosion.Stop();
				}
				m_explosion.Play(false);
				delete *it;
				it = m_grenade[PlayerNumber].erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void GrenadeManager::Draw(Camera& camera)
{
	for (int PlayerNumber = 0; PlayerNumber < PLAYERS; PlayerNumber++)
	{
		for (auto& Grenade : m_grenade[PlayerNumber]) {
			Grenade->Draw(camera);
		}
	}
}