#include "stdafx.h"
#include "Game.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"


//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
Game* g_game = nullptr;

Game::Game()
{

	g_game = this;
	
	m_stoneManager.SetInstance(&m_minotaur, &m_goblin, &m_orc);


	m_gameCamera.SetPlayer(&m_minotaur);
	
}


Game::~Game()
{
	g_game = nullptr;
}

void Game::Update()
{
	//�v���C���[�̍X�V�B
	m_minotaur.Update();
	m_goblin.Update();
	m_orc.Update();
	m_gameCamera.Update();
	m_stoneManager.Update();
}

void Game::Draw()
{
	//�v���C���[�̕`��B
	if (m_dorwflag == true)
	{
		m_minotaur.Draw();
	}
	
	m_goblin.Draw();
	m_orc.Draw();
	//�w�i�̕`��
	m_bg.Draw();
	m_stoneManager.Draw();
}
