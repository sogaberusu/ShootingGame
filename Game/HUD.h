#pragma once
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include "Game.h"
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
	void Draw(int cameraNo,int Ammo,int hitPoint, int grenades, bool AttackFlag,bool KillFlag,int weapon,bool cameraflag);
	void SetEnemyPosition(CVector3 enemypos)
	{
		m_enemyPosition = enemypos;
	}
	void SetDamageFlag(bool damage)
	{
		m_damegeflag = damage;
	}
	void SetDamageFlagCount(int time)
	{
		m_damegeflagcount = time;
	}
	void SetInstance(Player *player, int PlayerNumber)
	{
		m_player[PlayerNumber] = player;
	}
	void SetPlayerNo(int No)
	{ 
		m_playerNo = No;
	}
	void SetGameMode(int mode)
	{
		m_gameMode = mode;
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
	Sprite m_damage;
	Sprite m_hudgrenade;
	Sprite m_dangergrenade;
	Sprite m_eotech;
	Sprite m_m4a1ironsight;
	Sprite m_mp5ironsight;
	Sprite m_benelli_m4ironsight;
	Font m_font;									//フォント
	CVector3 m_enemyPosition = CVector3::Zero();	//攻撃してきた敵の座標
	bool m_damegeflag = false;						//ダメージをくらうと赤く表示する
	int m_damegeflagcount;							//ダメージを表示する時間
	Player *m_player[PLAYERS];						//プレイヤーのインスタンス
	int m_playerNo;									//プレイヤーの番号
	int m_gameMode;									//現在のゲームモード
};

