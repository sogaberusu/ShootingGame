#pragma once

#include "Minotaur.h"
#include "Goblin.h"
#include "Orc.h"

//�΃}�l�[�W���[
class Stone;

class StoneManager
{
public:
	StoneManager();
	~StoneManager();
	Stone* NewStone();
	void Update();
	void Draw(Camera& camera);
	void HitCheck();
	void SetInstance(Minotaur *minotaur/*, Goblin *goblin, Orc *orc*/)
	{
		m_minotaur = minotaur;
		/*m_goblin = goblin;
		m_orc = orc;*/
	}
private:
	std::vector<Stone*> m_stones;	//�e�ۂ̉ϒ��z��B
	Minotaur *m_minotaur = nullptr;
	Goblin *m_goblin = nullptr;
	Orc *m_orc = nullptr;
};

