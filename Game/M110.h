#pragma once
class M110
{
public:
	M110();
	~M110();
	void Update(CVector3 pos);
	void M110::Draw(Camera& camera);
private:
	SkinModel m_model;
};

