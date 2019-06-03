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
	void Draw(int cameraNo,int Ammo,int hitPoint, bool AttackFlag,bool KillFlag,int weapon,bool cameraflag);
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
	Sprite m_shotguntarget;
	Sprite m_scope;
	Sprite m_m4a1;
	Sprite m_m110;
	Sprite m_shotgun;
	Sprite m_mp5;
	//Sprite m_crosskey;
	
	Font m_bullet;
	Font m_reload;
	Font m_hp;
};

