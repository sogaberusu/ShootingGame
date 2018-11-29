#pragma once

#include "Minotaur.h"
#include "Goblin.h"
#include "Orc.h"

//石マネージャー
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
	std::vector<Stone*> m_stones;	//弾丸の可変長配列。
	Minotaur *m_minotaur = nullptr;
	Goblin *m_goblin = nullptr;
	Orc *m_orc = nullptr;
};

