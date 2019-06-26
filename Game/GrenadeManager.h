#pragma once
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Grenade;
class GrenadeManager
{
public:
	GrenadeManager();
	~GrenadeManager();
	Grenade* NewGrenade(CVector3 pos, int PlayerNumber, CVector3 target);
	void Update();
	void Draw(Camera& camera);
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
	Player* GetPlayer(int PlayerNumber)
	{
		return m_player[PlayerNumber];
	}
private:
	std::vector<Grenade*> m_grenade[4];					//グレネードの可変長配列。
	Player *m_player[4];								//プレイヤーのインスタンス
	bool m_spriteDrawflag = false;
	CSoundSource m_explosion;							//SE
};