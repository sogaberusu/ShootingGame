#include "stdafx.h"
#include "Game.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"


//グローバルなアクセスポイントをグローバル変数として提供する。
Game* g_game = nullptr;

Game::Game()
{

	g_game = this;
	
	m_stoneManager.SetInstance(&m_minotaur, &m_goblin, &m_orc);


	m_gameCamera[0].InitViewport(640, 360, 0, 0);
	m_gameCamera[0].SetPlayer(&m_minotaur);
	m_gameCamera[0].Seti(0);

	m_gameCamera[1].InitViewport(640, 360, 640, 0);
	m_gameCamera[1].SetPlayer(&m_minotaur);
	m_gameCamera[1].Seti(1);


	m_gameCamera[2].InitViewport(640, 360, 0, 360);
	m_gameCamera[2].SetPlayer(&m_minotaur);
	m_gameCamera[2].Seti(2);

	
	m_gameCamera[3].InitViewport(640, 360, 640, 360);
	m_gameCamera[3].SetPlayer(&m_minotaur);
	m_gameCamera[3].Seti(3);

}


Game::~Game()
{
	g_game = nullptr;
}

void Game::Update()
{
	//プレイヤーの更新。
	m_minotaur.Update();
	m_goblin.Update();
	m_orc.Update();
	for (int i = 0; i < 4; i++)
	{
		m_gameCamera[i].Update();
	}
	m_stoneManager.Update();
}

void Game::Draw()
{
	for (int i = 0; i < 4; i++) {
		m_gameCamera[i].StartRender();
		//プレイヤーの描画。
		if (m_dorwflag == true)
		{
			m_minotaur.Draw(g_camera3D[i]);
		}
		m_goblin.Draw(g_camera3D[i]);
		m_orc.Draw(g_camera3D[i]);
		//背景の描画
		m_bg.Draw(g_camera3D[i]);
		m_stoneManager.Draw(g_camera3D[i]);
	}
}
