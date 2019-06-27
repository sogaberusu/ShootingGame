#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "IScene.h"
class Player;
class Result:public IScene
{
public:
	Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
		float Player1CaptureTime,float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime);
	~Result();
	//アップデート
	void Update();
	//ドロー
	void Draw();
private:
	Sprite m_background;
	Sprite m_1stCrown[4];
	Sprite m_2ndCrown[4];
	Sprite m_3rdCrown[4];
	Font m_font;
	int m_playerkills[4];
	float m_playerCaptureTime[4];
	int m_gameMode;
	int m_1stKills;
	int m_2ndKills;
	int m_3rdKills;
	float m_1stTime;
	float m_2ndTime;
	float m_3rdTime;
	bool m_1stCrownDrawFlag[4] = { false,false,false,false };
	bool m_2ndCrownDrawFlag[4] = { false,false,false,false };
	bool m_3rdCrownDrawFlag[4] = { false,false,false,false };
};