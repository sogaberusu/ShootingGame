#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Player.h"
#include "Title.h"
#include "Result.h"


//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
Game* g_game = nullptr;

Game::Game()
{
	g_game = this;

	

	m_level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"Background") == true) {
			m_background = new Background(objData.position, objData.rotation);
		}
		else if (objData.EqualName(L"Player1") == true) {
			m_player[0] = new Player(0);
			m_player[0]->SetPosition(objData.position);
			m_player[0]->SetRotation(objData.rotation);
			m_gameCamera[0] = new GameCamera({ -150.0f, 150.0f, 0.0f });
			m_respawn[0].PlayerPosition = objData.position;
			m_respawn[0].PlayerRotation = objData.rotation;
			m_respawn[0].CameraPosition = CVector3(-150.0f, 150.0f, 0.0f);
		}
		else if (objData.EqualName(L"Player2") == true) {
			m_player[1] = new Player(1);
			m_player[1]->SetPosition(objData.position);
			m_player[1]->SetRotation(objData.rotation);
			m_gameCamera[1] = new GameCamera({ 0.0f, 150.0f, 150.0f });
			m_respawn[1].PlayerPosition = objData.position;
			m_respawn[1].PlayerRotation = objData.rotation;
			m_respawn[1].CameraPosition = CVector3(0.0f, 150.0f, 150.0f);
		}
		else if (objData.EqualName(L"Player3") == true) {
			m_player[2] = new Player(2);
			m_player[2]->SetPosition(objData.position);
			m_player[2]->SetRotation(objData.rotation);
			m_gameCamera[2] = new GameCamera({ 0.0f, 150.0f, -150.0f });
			m_respawn[2].PlayerPosition = objData.position;
			m_respawn[2].PlayerRotation = objData.rotation;
			m_respawn[2].CameraPosition = CVector3(0.0f, 150.0f, -150.0f);
		}
		else if (objData.EqualName(L"Player4") == true) {
			m_player[3] = new Player(3);
			m_player[3]->SetPosition(objData.position);
			m_player[3]->SetRotation(objData.rotation);
			m_gameCamera[3] = new GameCamera({ 150.0f, 150.0f, 0.0f });
			m_respawn[3].PlayerPosition = objData.position;
			m_respawn[3].PlayerRotation = objData.rotation;
			m_respawn[3].CameraPosition = CVector3(150.0f, 150.0f, 0.0f);
		}
		return true;
	});
	
	for (int i = 0; i < 4; i++)
	{
		m_bulletManager.SetInstance(m_player[i], i);
		m_timer.SetPlayer(m_player[i], i);
		m_effect[i].Init(L"Assets/effect/MuzzleFlash.efk");
		m_m4a1[i].SetInstance(m_player[i]);
	}

	m_gameCamera[0]->InitViewport(640, 360, 0, 0);
	m_gameCamera[0]->SetPlayer(m_player[0]);
	m_gameCamera[0]->Seti(0);

	m_gameCamera[1]->InitViewport(640, 360, 640, 0);
	m_gameCamera[1]->SetPlayer(m_player[1]);
	m_gameCamera[1]->Seti(1);

	m_gameCamera[2]->InitViewport(640, 360, 0, 360);
	m_gameCamera[2]->SetPlayer(m_player[2]);
	m_gameCamera[2]->Seti(2);
	
	m_gameCamera[3]->InitViewport(640, 360, 640, 360);
	m_gameCamera[3]->SetPlayer(m_player[3]);
	m_gameCamera[3]->Seti(3);

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

	//�V���h�E�}�b�v�Ƀ����_�����O
	g_graphicsEngine->GetShadowMap()->ResetShadowCasters();
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
	for (int i = 0; i < 4; i++)
	{
		delete m_player[i];
		delete m_gameCamera[i];
	}
	delete m_background;
}

void Game::Update()
{
	
	m_restTimer = max(0.0f, m_restTimer - 1.0f / 30.0f);
	

	//�v���C���[�̍X�V�B
	for (int i = 0; i < 4; i++)
	{
		m_player[i]->Update(g_camera3D[i],i);
		m_gameCamera[i]->Update();
		m_m4a1[i].Update(m_player[i]->GetHandPos());
		m_hud[i].Update();
	}
	m_background->Update();
	m_bulletManager.Update();
	//�|�X�g�G�t�F�N�g�̍X�V�B
	m_postEffect.Update();
	if (m_restTimer == 0.0f)
	{
		g_currentScene = new Result(m_player[0]->GetKills(),
									m_player[1]->GetKills(),
									m_player[2]->GetKills(),
									m_player[3]->GetKills());
		delete this;
	}
}

void Game::Draw()
{

	DrawShadowMap();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto smSRV = g_graphicsEngine->GetShadowMap()->GetShadowMapSRV();
	deviceContext->PSSetShaderResources(3, 1, &smSRV);
	auto rtSRV = g_mainRenderTarget.GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &rtSRV);
	for (int i = 0; i < 4; i++) {
		m_gameCamera[i]->StartRender();
		for (int j = 0; j < 4; j++)
		{
			m_player[j]->Draw(g_camera3D[i], i, j);
			m_m4a1[j].Draw(g_camera3D[i], i, j);
		}
		//�w�i�̕`��
		m_background->Draw(g_camera3D[i]);
		m_bulletManager.Draw(g_camera3D[i]);
		m_sky.Draw(g_camera3D[i]);
		m_timer.Draw();
		for (int j = 0; j < 4; j++)
		{
			m_effect[j].Draw(i);
			
		}
		m_hud[i].Draw(i,m_player[i]->GetAmmo());
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
	g_graphicsEngine->GetShadowMap()->RenderToShadowMap();

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
	m_copyMainRtToFrameBufferSprite.Draw(0);

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