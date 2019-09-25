#pragma once
#include "Player.h"
#include "Game.h"
class Flag
{
public:
	Flag();
	~Flag();
	//�`��
	void Draw(Camera& camera);
	//�X�V
	void Update();
	//�v���C���[�̃C���X�^���X��ݒ肷��
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
private:
	SkinModel m_model;										//���f��
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	Player* m_player[PLANES];								//�v���C���[�̃C���X�^���X
	int m_playerNo = enPlayer1;								//�v���C���[�ԍ�		
};