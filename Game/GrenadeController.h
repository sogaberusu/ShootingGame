/*!
* @brief	�L�����N�^�R���g���[���[�B
*/

#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"


/*!
* @brief	�L�����N�^�R���g���[���[�B
*/
class GrenadeController {
public:
	GrenadeController() {

	}
	~GrenadeController()
	{
		RemoveRigidBoby();
	}
	/*!
		* @brief	�������B
		*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
		*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
		*@param[in]	position	�����ʒu�B
		*/
	void Init(float radius, float height, const CVector3& position, CVector3& moveSpeed);
	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const CVector3& Execute(float deltaTime);
	/*!
		* @brief	���W���擾�B
		*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	���W��ݒ�B
		*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
private:
	CVector3 			m_position = CVector3::Zero();	//���W�B
	CapsuleCollider		m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;
	float				m_height = 0.0f;
	RigidBody			m_rigidBody;					//���́B
	CVector3			m_moveSpeed = CVector3::Zero();
};