#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
class Player;
class HUD
{
public:
	HUD();
	~HUD();
	void InitViewport(float Width, float Height, float TopLeftX, float TopLeftY)
	{
		m_width = Width;
		m_height = Height;
		m_topLeftX = TopLeftX;
		m_topLeftY = TopLeftY;
	}
	void StartRender();
	void Update();
	void Draw(int cameraNo,int Ammo,int hitPoint, bool AttackFlag,bool KillFlag);
private:
	float m_width = 0;
	float m_height = 0;
	float m_topLeftX = 0;
	float m_topLeftY = 0;
	Sprite m_crosshair;
	Sprite m_xbutton;
	Sprite m_life;
	Sprite m_hitmarker;
	Sprite m_killmarker;
	
	Font m_bullet;
	Font m_reload;
	Font m_hp;
};

