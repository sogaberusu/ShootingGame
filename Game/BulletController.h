#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"

class Bullet;

class BulletController
{
public:
	BulletController();
	~BulletController()
	{
		RemoveRigidBoby();
	}
	/*!
		* @brief	�������B
		*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
		*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
		*@param[in]	position	�����ʒu�B
		*/
	void Init(float radius, float height, const CVector3& position);
	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed);
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
	bool GetIsDead()
	{
		return m_isDead;
	}
private:
	CVector3 			m_position = CVector3::Zero();	//���W
	CapsuleCollider		m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;				//�R���C�_�[�̔��a
	float				m_height = 0.0f;				//�R���C�_�[�̍���
	RigidBody			m_rigidBody;					//���́B
	bool m_isDead = false;

};