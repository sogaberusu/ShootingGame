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
	Sprite m_sprite;
	ID3D11ShaderResourceView* m_result = nullptr;
	Font m_font;
	int m_playerkills[4];
	float m_playerCaptureTime[4];
	int m_gameMode;
};