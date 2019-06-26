#pragma once
#include "Player.h"
class Flag
{
public:
	Flag();
	~Flag();
	void Draw(Camera& camera);
	void Update();
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
private:
	SkinModel m_model;									//���f��
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	Player* m_player[4];								//�v���C���[�̃C���X�^���X
	int m_playerNo = 0;
};