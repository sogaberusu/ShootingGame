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
		//m_stoneManager.SetInstance(&m_player[i], i/*&m_minotaur[i],i &m_goblin, &m_orc*/);
		m_bulletManager.SetInstance(&m_player[i],i);
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

	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();

	g_shadowMap.InitShadowMap();

	//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	g_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_copyMainRtToFrameBufferSprite.Init(
		g_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
}


Game::~Game()
{
	g_game = nullptr;

	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
}

void Game::Update()
{
	//�V���h�E�}�b�v���X�V�B
	g_shadowMap.UpdateFromLightTarget(
		{1000.0f,1000.0f,1000.0f},
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
	//m_stoneManager.Update();
	m_bulletManager.Update();
	
	//�|�X�g�G�t�F�N�g�̍X�V�B
	m_postEffect.Update();
}

void Game::Draw()
{
	DrawShadowMap();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto smSRV = g_shadowMap.GetShadowMapSRV();
	deviceContext->PSSetShaderResources(3, 1, &smSRV);
	auto rtSRV = g_mainRenderTarget.GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &rtSRV);
	for (int i = 0; i < 4; i++) {
		m_gameCamera[i].StartRender();
		
		for (int j = 0; j < 4; j++)
		{
			m_player[j].Draw(g_camera3D[i], i, j);
		}
		/*m_goblin.Draw(g_camera3D[i]);
		m_orc.Draw(g_camera3D[i]);*/
		//�w�i�̕`��
		m_bg.Draw(g_camera3D[i]);
		//m_stoneManager.Draw(g_camera3D[i]);
		m_bulletManager.Draw(g_camera3D[i]);
		m_sky.Draw(g_camera3D[i]);
	}
}

void Game::DrawShadowMap()
{
	
	///////////////////////////////////////////////
	//�V���h�E�}�b�v�Ƀ����_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	/*ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);*/
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//�V���h�E�}�b�v�Ƀ����_�����O
	g_shadowMap.RenderToShadowMap();

	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	g_graphicsEngine->ChangeRenderTarget(&g_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_mainRenderTarget.ClearRenderTarget(clearColor);

	//�|�X�g�G�t�F�N�g�̕`��B
	m_postEffect.Draw();

	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	g_graphicsEngine->ChangeRenderTarget(
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//�h���h��
	m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

	////���ɖ߂��B
	//d3dDeviceContext->OMSetRenderTargets(
	//	1,
	//	&oldRenderTargetView,
	//	oldDepthStencilView
	//);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	/*oldRenderTargetView->Release();
	oldDepthStencilView->Release();*/
}