#pragma once
#include "GrenadeController.h"
#include "physics/CollisionAttr.h"

class Grenade
{
public:
	Grenade(CVector3 pos, int PlayerNumber, CVector3 target);
	~Grenade();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update(int PlayerNumber);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�`�悵�����J�����𑗂�</param>
	void Draw(Camera& camera);
	/// <summary>
	/// �O���l�[�h�̏�Ԃ�Ԃ�
	/// </summary>
	/// <returns>treu�����@false�����҂�</returns>
	bool IsDead()
	{
		return m_isDead;
	}
	//�O���l�[�h�̍��W��Ԃ�
	CVector3 GetPosition()
	{
		return m_position;
	}
	//�N���������̂���Ԃ��B�L���������Z����̂Ɏg��
	int GetThrowPlayer()
	{
		return m_throwplayer;
	}
private:
	GrenadeController m_grenadeController;				//�O���l�[�h�R���g���[���[
	SkinModel m_model;									//���f��
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_target = CVector3::Zero();				//�O���l�[�h�𓊂������
	int m_life = 100;									//�����܂ł̎���		
	bool m_isDead = false;								//�������Ă��邩
	int m_throwplayer;									//�N���������̂��L�^���Ă���
};