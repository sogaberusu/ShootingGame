#pragma once
class Player;
class M4A1
{
public:
	M4A1();
	~M4A1();
	void Update(CVector3 pos);
	void Draw(Camera& camera, int ViewportNumber, int PlayerNumber);
	void SetInstance(Player *player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	Player *m_player;
	CVector3 m_position;
	CQuaternion m_rotation = CQuaternion::Identity();
	
};

