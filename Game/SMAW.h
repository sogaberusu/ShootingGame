#pragma once
class SMAW
{
public:
	SMAW();
	~SMAW();
	void Update(CVector3 pos);
	void SMAW::Draw(Camera& camera);
private:
	SkinModel m_model;
};

