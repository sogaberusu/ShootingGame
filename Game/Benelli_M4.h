#pragma once
class Benelli_M4
{
public:
	Benelli_M4();
	~Benelli_M4();
	void Update(CVector3 pos);
	void Benelli_M4::Draw(Camera& camera);
private:
	SkinModel m_model;
};

