#pragma once

#include "Minotaur.h"
#include "Goblin.h"
#include "Orc.h"
#include "Player.h"
#include "Background.h"

//石マネージャー
class Stone;

class StoneManager
{
public:
	StoneManager();
	~StoneManager();
	Stone* NewStone(int i);
	void Update();
	void Draw(Camera& camera);
	void HitCheck(int i);
	void SetInstance(Player *player,int i/*Minotaur *minotaur,int i, Goblin *goblin, Orc *orc*/)
	{
		m_player[i] = player;
		//m_minotaur[i] = minotaur;
		/*m_goblin = goblin;
		m_orc = orc;*/
	}
private:
	std::vector<Stone*> m_stones[4];	//弾丸の可変長配列。
	Player *m_player[4];
	//Background m_background;
	/*Minotaur *m_minotaur[4];
	Goblin *m_goblin = nullptr;
	Orc *m_orc = nullptr;*/
};

