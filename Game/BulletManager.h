#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
#include "Player.h"

class Bullet;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	Bullet* NewBullet(int PlayerNumber);
	void Update();
	void Draw(Camera& camera);
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
	Player* GetPlayer(int PlayerNumber)
	{
		return m_player[PlayerNumber];
	}
	///*!
	//	* @brief	�������B
	//	*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
	//	*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
	//	*@param[in]	position	�����ʒu�B
	//	*/
	//void Init(float radius, float height, const CVector3& position);
	///*!
	//	* @brief	���s�B
	//	*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
	//	*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
	//	*@return �ړ���̃L�����N�^�[�̍��W�B
	//	*/
	//const CVector3& Execute(float deltaTime, CVector3& moveSpeed,Bullet& bullet);
	///*!
	//* @brief	���̂𕨗��G���W������폜�B�B
	//*/
	//void RemoveRigidBoby();
private:
	//CVector3 			m_position = CVector3::Zero();	//���W
	//CapsuleCollider		m_collider;						//�R���C�_�[�B
	//float				m_radius = 0.0f;				//�R���C�_�[�̔��a
	//float				m_height = 0.0f;				//�R���C�_�[�̍���
	//RigidBody			m_rigidBody;					//���́B
	std::vector<Bullet*> m_bullet[4];					//�e�ۂ̉ϒ��z��B
	Player *m_player[4];								//�v���C���[�̃C���X�^���X
};

