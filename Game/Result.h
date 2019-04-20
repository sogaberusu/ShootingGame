#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "IScene.h"
class Result:public IScene
{
public:
	Result(int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills);
	~Result();
	//アップデート
	void Update();
	//ドロー
	void Draw();
	/*void SetPlayerKills(int kills,int playerNo)
	{
		m_playerkills[playerNo] = kills;
	}*/
private:
	Sprite m_sprite;
	ID3D11ShaderResourceView* m_result = nullptr;
	Font m_font;
	int m_playerkills[4];
	wchar_t Player1Kills[256], Player2Kills[256], Player3Kills[256], Player4Kills[256];
};