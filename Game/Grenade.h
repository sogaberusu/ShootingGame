#pragma once
class Grenade
{
public:
	Grenade(CVector3 pos,CVector3 forward);
	~Grenade();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
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
private:
	SkinModel m_model;									//���f��
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_forward = CVector3::Zero();
	int m_life = 100;									//�����܂ł̎���		
	bool m_isDead = false;								//�������Ă��邩
	bool m_spriteDrawflag = false;
};

