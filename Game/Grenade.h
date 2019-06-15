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
	void Draw(Camera& camera);
	bool IsDead()
	{
		return m_isDead;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SpriteDrawFlag(bool draw)
	{
		m_spriteDrawflag = draw;
	}
	bool GetSpriteDrawFlag()
	{
		return m_spriteDrawflag;
	}
	int GetThrowPlayer()
	{
		return m_throwplayer;
	}
private:
	GrenadeController m_grenadeController;				//�O���l�[�h�R���g���[���[
	SkinModel m_model;									//���f��
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_target = CVector3::Zero();
	int m_life = 100;									//�����܂ł̎���		
	bool m_isDead = false;								//�������Ă��邩
	bool m_spriteDrawflag = false;
	int m_throwplayer;										//�N���������̂��L�^���Ă���
};