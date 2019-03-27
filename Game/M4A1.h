#pragma once
class M4A1
{
public:
	M4A1();
	~M4A1();
	void Update(CVector3 pos);
	void Draw(Camera& camera);
private:
	SkinModel m_model;
};

