#include "stdafx.h"
#include "Game.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "Player.h"
//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
Game* g_game = nullptr;

Game::Game()
{

	g_game = this;
	
	for (int i = 0; i < 4; i++)
	{
		m_stoneManager.SetInstance(&m_player[i],i/*&m_minotaur[i],i &m_goblin, &m_orc*/);
	}

	m_gameCamera[0].InitViewport(640, 360, 0, 0);
	m_gameCamera[0].SetPlayer(&m_player[0]);
	m_gameCamera[0].Seti(0);
	m_player[0].SetPosition({ 250.0f,0.0f,0.0f });

	m_gameCamera[1].InitViewport(640, 360, 640, 0);
	m_gameCamera[1].SetPlayer(&m_player[1]);
	m_gameCamera[1].Seti(1);
	m_player[1].SetPosition({ -250.0f,0.0f,0.0f });


	m_gameCamera[2].InitViewport(640, 360, 0, 360);
	m_gameCamera[2].SetPlayer(&m_player[2]);
	m_gameCamera[2].Seti(2);
	m_player[2].SetPosition({ 0.0f,0.0f,250.0f });

	
	m_gameCamera[3].InitViewport(640, 360, 640, 360);
	m_gameCamera[3].SetPlayer(&m_player[3]);
	m_gameCamera[3].Seti(3);
	m_player[3].SetPosition({ 0.0f,0.0f,-250.0f });

	g_shadowMap.InitShadowMap();
}


Game::~Game()
{
	g_game = nullptr;
}

void Game::Update()
{//�V���h�E�}�b�v���X�V�B
	g_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f,0.0f,0.0f }
	);
	//�v���C���[�̍X�V�B
	/*m_goblin.Update();
	m_orc.Update();*/
	for (int i = 0; i < 4; i++)
	{
		m_player[i].Update(g_camera3D[i],i);
		m_gameCamera[i].Update();	
	}
	m_bg.Update();
	m_stoneManager.Update();
	
}

void Game::Draw()
{
	
	for (int i = 0; i < 4; i++) {
		m_gameCamera[i].StartRender();
		DrawShadowMap(i);
		for (int j = 0; j < 4; j++)
		{
			m_player[j].Draw(g_camera3D[i], i, j);
		}
		/*m_goblin.Draw(g_camera3D[i]);
		m_orc.Draw(g_camera3D[i]);*/
		//�w�i�̕`��
		m_bg.Draw(g_camera3D[i]);
		m_stoneManager.Draw(g_camera3D[i]);
		m_sky.Draw(g_camera3D[i]);
	}
}

void Game::DrawShadowMap(int i)
{
	///////////////////////////////////////////////
	//�V���h�E�}�b�v�Ƀ����_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//�V���h�E�}�b�v�Ƀ����_�����O
	g_shadowMap.RenderToShadowMap();

	//���ɖ߂��B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
}