#pragma once

#include "IScene.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"

class GameSelect : public IScene
{
public:
	GameSelect();
	~GameSelect();
	void Update() override;
	void Draw() override;
	
private:
	Sprite m_background;
	Sprite m_rightselect;
	Sprite m_leftselect;
	Sprite m_startButton;
	Font m_font;
	CVector2 m_fontDMPos = { -100.0f,100.0f };
	CVector2 m_fontCTFPos = { 1000.0f,100.0f };
	wchar_t m_gameSelect[256];
	bool m_leftMoveflag = false;
	bool m_rightMoveflag = false;
	enum EnGameType {
		enGame_DM,
		enGame_CTF
	};
	EnGameType m_gametype = enGame_DM;
	CVector4 Black = { 0.0f,0.0f,0.0f,1.0f };
	CVector4 Red = { 256.0f,0.0f,0.0f,1.0f };
	CVector4 m_gameTypeFontColor = Black;
	CVector4 m_stageFontColor = Black;
	CVector4 m_gameStartFontColor = Black;
	enum EnState {
		enState_GameType,
		enState_GameMap,
		enState_GameStart,
	};
	EnState m_state = enState_GameType;
};