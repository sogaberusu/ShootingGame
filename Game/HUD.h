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
	void Update(int cameraNo);
	void Draw(int cameraNo,int Ammo,int hitPoint, bool AttackFlag,bool KillFlag,int weapon,bool cameraflag);
	void SetEnemyPosition(CVector3 enemypos)
	{
		m_enemyPosition = enemypos;
	}
	void SetDamageFlag(bool damage)
	{
		m_damegeflag = damage;
	}
	void SetInstance(Player *player)
	{
		m_player = player;
	}
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
	Sprite m_damage;
	Sprite m_handgranate;
	
	Font m_bullet;
	Font m_reload;
	Font m_hp;
	CVector3 m_enemyPosition = CVector3::Zero();
	bool m_damegeflag = false;
	Player *m_player;
};

