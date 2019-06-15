#include "stdafx.h"
#include "GrenadeManager.h"
#include "Grenade.h"


GrenadeManager::GrenadeManager()
{
	//������
	for (int PlayerNumber = 0; PlayerNumber < 4; PlayerNumber++)
	{
		m_player[PlayerNumber] = nullptr;
	}
	m_explosion.Init(L"Assets/sound/Explosion.wav");
}


GrenadeManager::~GrenadeManager()
{
	//���
	for (int PlayerNumber = 0; PlayerNumber < 4; PlayerNumber++)
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
	for (int i = 0; i < 4; i++)
	{
		for (auto& Grenade : m_grenade[i]) {
			Grenade->Update(i);
		}

		auto it = m_grenade[i].begin();
		while (it != m_grenade[i].end()) {
			if ((*it)->IsDead() == true) {
				for (int j = 0; j < 4; j++)
				{
					CVector3 distance = (*it)->GetPosition() - m_player[j]->GetPosition();
					if (distance.Length() < 100 && m_player[j]->GetState() != 19)
					{
						m_player[j]->SetHitPoint(m_player[j]->GetHitPoint() - 100);

						if (m_player[j]->GetHitPoint() <= 0)
						{
							//�����̓������O���l�[�h�ł͂Ȃ��Ȃ�
							if (j != (*it)->GetThrowPlayer())
							{
								//�U�������v���C���[�̃L�����𑝂₷
								m_player[(*it)->GetThrowPlayer()]->SetKills(m_player[(*it)->GetThrowPlayer()]->GetStatus().Kills + 1);
							}
							//�v���C���[��HP��0�ȉ��ɂȂ�����0�ɂ���
							m_player[j]->SetHitPoint(0);
							//�v���C���[�����S��Ԃɂ���
							m_player[j]->SetDead();
							break;
						}
					}
					if (distance.Length() < 200 && m_player[j]->GetState() != 19)
					{
						m_player[j]->SetHitPoint(m_player[j]->GetHitPoint() - 50);
						//���������v���C���[�̎��R�񕜂܂ł̃C���^�[�o����ݒ肷��
						m_player[j]->SetHealTimer(300);

						if (m_player[j]->GetHitPoint() <= 0)
						{
							//�����̓������O���l�[�h�ł͂Ȃ��Ȃ�
							if (j != (*it)->GetThrowPlayer())
							{
								//�U�������v���C���[�̃L�����𑝂₷
								m_player[(*it)->GetThrowPlayer()]->SetKills(m_player[(*it)->GetThrowPlayer()]->GetStatus().Kills + 1);
							}
							//�v���C���[��HP��0�ȉ��ɂȂ�����0�ɂ���
							m_player[j]->SetHitPoint(0);
							//�v���C���[�����S��Ԃɂ���
							m_player[j]->SetDead();
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
				it = m_grenade[i].erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void GrenadeManager::Draw(Camera& camera)
{
	for (int PlayerNumber = 0; PlayerNumber < 4; PlayerNumber++)
	{
		for (auto& Grenade : m_grenade[PlayerNumber]) {
			Grenade->Draw(camera);
		}
	}
}