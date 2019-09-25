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
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="radius">
	/// �J�v�Z���R���C�_�[�̔��a�B 
	/// </param>
	/// <param name="height">
	/// �J�v�Z���R���C�_�[�̍����B	
	/// </param>
	/// <param name="position">
	/// �����ʒu�B	
	/// </param>
	/// <param name="tag">
	/// �R���C�_�[�̑���	
	/// </param>
	void Init(float radius, float height, const CVector3& position,int tag);
	/// <summary>
	///���s�B
	/// </summary>
	/// <param name="deltaTime">
	/// �o�ߎ��ԁB�P�ʂ͕b�B
	/// </param>
	/// <param name="moveSpeed">
	/// �ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
	/// </param>
	/// <param name="attack">
	/// �U����
	/// </param>
	/// <returns>
	/// �ړ���̃L�����N�^�[�̍��W�B
	/// </returns>
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, int attack);
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
	//�e�������Ă��邩��Ԃ�
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
	bool m_isDead = false;								//�e���������̃t���Otrue�ŏ�����
};