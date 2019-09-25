#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Player.h"
#include "Title.h"
#include "Result.h"
#include "WeaponAttr.h"
#include "Flag.h"
#include "Timer.h"
#include "GrenadeManager.h"
#include "BulletManager.h"
#include "HUD.h"

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
Game* g_game = nullptr;

Game::Game(int gameMode,int mapNo)
{
	g_game = this;

	m_gameMode = gameMode;
	m_flag = new Flag();
	m_timer = new Timer();
	m_grenadeManager = new GrenadeManager();
	m_bulletManager = new BulletManager();
	m_level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"Background") == true) {
			m_background = new Background(objData.position, objData.rotation, mapNo);
		}
		else if (objData.EqualName(L"Player1") == true) {
			m_player[enPlayer1] = new Player(enPlayer1);
			m_player[enPlayer1]->SetPosition(objData.position);
			m_player[enPlayer1]->SetRotation(objData.rotation);
			m_gameCamera[enPlayer1] = new GameCamera({ -150.0f, 150.0f, 0.0f });
			m_respawn[enPlayer1].PlayerPosition = objData.position;
			m_respawn[enPlayer1].PlayerRotation = objData.rotation;
			m_respawn[enPlayer1].CameraPosition = CVector3(-150.0f, 150.0f, 0.0f);
		}
		else if (objData.EqualName(L"Player2") == true) {
			m_player[enPlayer2] = new Player(enPlayer2);
			m_player[enPlayer2]->SetPosition(objData.position);
			m_player[enPlayer2]->SetRotation(objData.rotation);
			m_gameCamera[enPlayer2] = new GameCamera({ 150.0f, 150.0f, 0.0f });
			m_respawn[enPlayer2].PlayerPosition = objData.position;
			m_respawn[enPlayer2].PlayerRotation = objData.rotation;
			m_respawn[enPlayer2].CameraPosition = CVector3(150.0f, 150.0f, 0.0f);
		}
		else if (objData.EqualName(L"Player3") == true) {
			if (PLAYERS >= enPlayer4)
			{
				m_player[enPlayer3] = new Player(enPlayer3);
				m_player[enPlayer3]->SetPosition(objData.position);
				m_player[enPlayer3]->SetRotation(objData.rotation);
				m_gameCamera[enPlayer3] = new GameCamera({ 0.0f, 150.0f, -150.0f });
			}
				m_respawn[enPlayer3].PlayerPosition = objData.position;
				m_respawn[enPlayer3].PlayerRotation = objData.rotation;
				m_respawn[enPlayer3].CameraPosition = CVector3(0.0f, 150.0f, -150.0f);
		}
		else if (objData.EqualName(L"Player4") == true) {
			if (PLAYERS >= enPlayerNum)
			{
				m_player[enPlayer4] = new Player(enPlayer4);
				m_player[enPlayer4]->SetPosition(objData.position);
				m_player[enPlayer4]->SetRotation(objData.rotation);
				m_gameCamera[enPlayer4] = new GameCamera({ 0.0f, 150.0f, 150.0f });
			}
				m_respawn[enPlayer4].PlayerPosition = objData.position;
				m_respawn[enPlayer4].PlayerRotation = objData.rotation;
				m_respawn[enPlayer4].CameraPosition = CVector3(0.0f, 150.0f, 150.0f);
		}
		return true;
	});
	
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		m_hud[PlayerNo] = new HUD();
		m_bulletManager->SetInstance(m_player[PlayerNo], PlayerNo);
		m_grenadeManager->SetInstance(m_player[PlayerNo], PlayerNo);
		m_flag->SetInstance(m_player[PlayerNo], PlayerNo);
		m_timer->SetPlayer(m_player[PlayerNo], PlayerNo);
		m_muzzleflasheffect[PlayerNo].Init(L"Assets/effect/MuzzleFlash.efk");
		m_explosioneffect[PlayerNo].Init(L"Assets/effect/Explosion.efk");
		m_m4a1[PlayerNo].SetInstance(m_player[PlayerNo]);
		m_mp5[PlayerNo].SetInstance(m_player[PlayerNo]);
		m_benelliM4[PlayerNo].SetInstance(m_player[PlayerNo]);
		m_m110[PlayerNo].SetInstance(m_player[PlayerNo]);
		m_player[PlayerNo]->SetWeaponInstance(&m_m4a1[PlayerNo], &m_mp5[PlayerNo],&m_benelliM4[PlayerNo],&m_m110[PlayerNo]);
		for (int People = 0; People < PLAYERS; People++)
		{
			m_hud[PlayerNo]->SetInstance(m_player[People], People);
		}
		m_hud[PlayerNo]->SetPlayerNo(PlayerNo);
		m_hud[PlayerNo]->SetGameMode(gameMode);
	}

	if (PLAYERS != enPlayer3)
	{
		m_gameCamera[enPlayer1]->InitViewport(640, 360, 0, 0);
		m_gameCamera[enPlayer1]->SetPlayer(m_player[enPlayer1]);
		m_gameCamera[enPlayer1]->SetPlayerNo(enPlayer1);

		m_gameCamera[enPlayer2]->InitViewport(640, 360, 640, 0);
		m_gameCamera[enPlayer2]->SetPlayer(m_player[enPlayer2]);
		m_gameCamera[enPlayer2]->SetPlayerNo(enPlayer2);
	}
	else
	{
		m_gameCamera[enPlayer1]->InitViewport(640, 720, 0, 0);
		m_gameCamera[enPlayer1]->SetPlayer(m_player[enPlayer1]);
		m_gameCamera[enPlayer1]->SetPlayerNo(enPlayer1);

		m_gameCamera[enPlayer2]->InitViewport(640, 720, 640, 0);
		m_gameCamera[enPlayer2]->SetPlayer(m_player[enPlayer2]);
		m_gameCamera[enPlayer2]->SetPlayerNo(enPlayer2);
	}
	if (PLAYERS >= enPlayer4)
	{
		m_gameCamera[enPlayer3]->InitViewport(640, 360, 0, 360);
		m_gameCamera[enPlayer3]->SetPlayer(m_player[enPlayer3]);
		m_gameCamera[enPlayer3]->SetPlayerNo(enPlayer3);
	}
	if (PLAYERS >= enPlayerNum)
	{
		m_gameCamera[enPlayer4]->InitViewport(640, 360, 640, 360);
		m_gameCamera[enPlayer4]->SetPlayer(m_player[enPlayer4]);
		m_gameCamera[enPlayer4]->SetPlayerNo(enPlayer4);
	}

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
	//�����V���b�g�Đ���SE
	m_startSound.Init(L"Assets/sound/Start.wav");
	m_endSound.Init(L"Assets/sound/End.wav");
	Update();
	m_waitflag = false;
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		m_player[PlayerNo]->SetWeapon(enWeapon_Num);
	}
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
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		delete m_player[PlayerNo];
		delete m_gameCamera[PlayerNo];
		delete m_hud[PlayerNo];
	}
	delete m_background;
	delete m_flag;
}

void Game::Update()
{

	if (m_waitflag == true && m_endflag == false)
	{

		m_restTimer = max(0.0f, m_restTimer - 1.0f / 30.0f);

		
		for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
		{
			//�v���C���[�̍X�V�B
			m_player[PlayerNo]->Update(g_camera3D[PlayerNo], PlayerNo);
			//�Q�[���J�����̍X�V
			m_gameCamera[PlayerNo]->Update();
			//�e�̍X�V
			switch (m_player[PlayerNo]->GetWeapon())
			{
			case enWeapon_M4A1:
				m_m4a1[PlayerNo].Update();
				break;
			case enWeapon_MP5:
				m_mp5[PlayerNo].Update();
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4[PlayerNo].Update();
				break;
			case enWeapon_M110:
				m_m110[PlayerNo].Update();
			}
			//hud�̍X�V
			m_hud[PlayerNo]->Update(PlayerNo);
		}
		//bulletmanager�̍X�V
		m_bulletManager->Update();
		//grenademanager�̍X�V
		m_grenadeManager->Update();
		//���݂̃Q�[�����[�h���L���v�`���[�U�t���b�O�Ȃ�
		if (m_gameMode == enGame_CTF)
		{
			//�t���b�O�̍X�V
			m_flag->Update();
		}
	}
	//�}�b�v�̍X�V
	m_background->Update();

	if (m_restTimer == 0.0f)
	{
		m_endflag = true;

		if (m_transitionflag == true)
		{
			//�v���C���[�̐���2�l�Ȃ�
			if (PLAYERS == enPlayer3)
			{
				g_currentScene = new Result(
					m_gameMode,
					m_player[enPlayer1]->GetKills(),
					m_player[enPlayer2]->GetKills(),
					m_player[enPlayer1]->GetStatus().CaptureTime,
					m_player[enPlayer2]->GetStatus().CaptureTime);
			}
			//�v���C���[�̐���3�l�Ȃ�
			if (PLAYERS == enPlayer4)
			{
				g_currentScene = new Result(
					m_gameMode,
					m_player[enPlayer1]->GetKills(),
					m_player[enPlayer2]->GetKills(),
					m_player[enPlayer3]->GetKills(),
					m_player[enPlayer1]->GetStatus().CaptureTime,
					m_player[enPlayer2]->GetStatus().CaptureTime,
					m_player[enPlayer3]->GetStatus().CaptureTime);
			}
			//�v���C���[�̐���4�l�Ȃ�
			if (PLAYERS == enPlayerNum)
			{
				g_currentScene = new Result(
					m_gameMode,
					m_player[enPlayer1]->GetKills(),
					m_player[enPlayer2]->GetKills(),
					m_player[enPlayer3]->GetKills(),
					m_player[enPlayer4]->GetKills(),
					m_player[enPlayer1]->GetStatus().CaptureTime,
					m_player[enPlayer2]->GetStatus().CaptureTime,
					m_player[enPlayer3]->GetStatus().CaptureTime,
					m_player[enPlayer4]->GetStatus().CaptureTime);
			}
			delete this;
		}
	}
}

void Game::Draw()
{

	m_startTimer = max(0.0f, m_startTimer - 1.0f / 30.0f);
	wchar_t time[256];

	swprintf(time, L"%.f", m_startTimer);

	DrawShadowMap();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto smSRV = g_graphicsEngine->GetShadowMap()->GetShadowMapSRV();
	deviceContext->PSSetShaderResources(3, 1, &smSRV);
	auto rtSRV = g_mainRenderTarget.GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &rtSRV);
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++) {
		m_gameCamera[PlayerNo]->StartRender();
		if (m_waitflag == true)
		{
			for (int People = 0; People < PLAYERS; People++)
			{	
				switch (m_player[People]->GetWeapon())
				{
				case enWeapon_M4A1:
					m_m4a1[People].Draw(g_camera3D[PlayerNo], PlayerNo, People);
					break;
				case enWeapon_MP5:
					m_mp5[People].Draw(g_camera3D[PlayerNo], PlayerNo, People);
					break;
				case enWeapon_Benelli_M4:
					m_benelliM4[People].Draw(g_camera3D[PlayerNo], PlayerNo, People);
					break;
				case enWeapon_M110:
					m_m110[People].Draw(g_camera3D[PlayerNo], PlayerNo, People);
					break;
				}
			}
		}
		//�w�i�̕`��
		m_background->Draw(g_camera3D[PlayerNo]);
		//�e�̕`��
		m_bulletManager->Draw(g_camera3D[PlayerNo]);
		//�O���l�[�h�̕`��
		m_grenadeManager->Draw(g_camera3D[PlayerNo]);
		//��̕`��
		m_sky.Draw(g_camera3D[PlayerNo]);
		if (m_waitflag == true)
		{
			for (int People = 0;People < PLAYERS;People++)
			{
				//���݂̃Q�[�����[�h���L���v�`���[�U�t���b�O�Ȃ�
				if (m_gameMode == enGame_CTF)
				{
					//�����m�ۂ��Ă���v���C���[�̃V���G�b�g��`�悷��
					m_player[People]->SilhouetteDrwa(g_camera3D[PlayerNo], PlayerNo, People);
				}
				//�v���C���[�̕`��
				m_player[People]->Draw(g_camera3D[PlayerNo], PlayerNo, People);
			}
			//���݂̃Q�[�����[�h���L���v�`���[�U�t���b�O�Ȃ�
			if (m_gameMode == enGame_CTF)
			{
				//�t���b�O�̕`��
				m_flag->Draw(g_camera3D[PlayerNo]);
			}
		}
		//�v���C���[�̑������Ă��镐����擾���������Ă��镐��̉摜��\������
		switch (m_player[PlayerNo]->GetWeapon())
		{
		case enWeapon_M4A1:
			m_hud[PlayerNo]->Draw(PlayerNo, m_m4a1[PlayerNo].GetAmmo(), m_player[PlayerNo]->GetHitPoint(), m_player[PlayerNo]->GetGrenade(), m_player[PlayerNo]->GetAttackFlag(), m_player[PlayerNo]->GetKillFlag(), m_player[PlayerNo]->GetWeapon(), m_player[PlayerNo]->GetCameraType());
			break;
		case enWeapon_MP5:
			m_hud[PlayerNo]->Draw(PlayerNo, m_mp5[PlayerNo].GetAmmo(), m_player[PlayerNo]->GetHitPoint(), m_player[PlayerNo]->GetGrenade(), m_player[PlayerNo]->GetAttackFlag(), m_player[PlayerNo]->GetKillFlag(), m_player[PlayerNo]->GetWeapon(), m_player[PlayerNo]->GetCameraType());
			break;
		case enWeapon_Benelli_M4:
			m_hud[PlayerNo]->Draw(PlayerNo, m_benelliM4[PlayerNo].GetAmmo(), m_player[PlayerNo]->GetHitPoint(), m_player[PlayerNo]->GetGrenade(), m_player[PlayerNo]->GetAttackFlag(), m_player[PlayerNo]->GetKillFlag(), m_player[PlayerNo]->GetWeapon(), m_player[PlayerNo]->GetCameraType());
			break;
		case enWeapon_M110:
			m_hud[PlayerNo]->Draw(PlayerNo, m_m110[PlayerNo].GetAmmo(), m_player[PlayerNo]->GetHitPoint(), m_player[PlayerNo]->GetGrenade(), m_player[PlayerNo]->GetAttackFlag(), m_player[PlayerNo]->GetKillFlag(), m_player[PlayerNo]->GetWeapon(), m_player[PlayerNo]->GetCameraType());
		}
		for (int People = 0; People < PLAYERS; People++)
		{
			if (m_waitflag == false)
			{
				m_font.BeginDraw();

				if (m_gameMode == enGame_DM)
				{
					//�v���C���[����l�����ł͂Ȃ��Ȃ�
					if (PLAYERS != enPlayer3)
					{
						m_font.Draw(L"�f�X�}�b�`", { -400.0f,250.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
					}
					else
					{
						//�v���C���[����l�����̎��̓t�H���g�̏o���ʒu��ύX
						m_font.Draw(L"�f�X�}�b�`", { -400.0f,0.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
					}
				}
				if (m_gameMode == enGame_CTF)
				{
					//�v���C���[����l�����ł͂Ȃ��Ȃ�
					if (PLAYERS != enPlayer3)
					{
						m_font.Draw(L"�L���v�`���[�U�t���b�O", { -550.0f,250.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
					}
					else
					{
						//�v���C���[����l�����̎��̓t�H���g�̏o���ʒu��ύX
						m_font.Draw(L"�L���v�`���[�U�t���b�O", { -550.0f,0.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
					}
				}
				//�v���C���[����l�����ł͂Ȃ��Ȃ�
				if (PLAYERS != enPlayer3)
				{
					m_font.Draw(time, { -320.0f,200.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
				}
				else
				{
					//�v���C���[����l�����̎��̓t�H���g�̏o���ʒu��ύX
					m_font.Draw(time, { -320.0f,-50.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
				}
				m_font.EndDraw();
			}
			if (m_endflag == true)
			{
				m_font.BeginDraw();
				//�v���C���[����l�����ł͂Ȃ��Ȃ�
				if (PLAYERS != enPlayer3)
				{
					m_font.Draw(L"�I��", { -360.0f,200.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
				}
				else
				{
					//�v���C���[����l�����̎��̓t�H���g�̏o���ʒu��ύX
					m_font.Draw(L"�I��", { -360.0f,0.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
				}
				if (m_endSoundflag == true)
				{
					m_endSound.Play(false);
					m_endSoundflag = false;
				}
				if (m_endSound.IsPlaying() == false)
				{
					m_transitionflag = true;
				}

				m_font.EndDraw();
			}
			if (m_player[PlayerNo]->GetCameraType() == Player::EnCameraType::enType_TPS || PlayerNo != People)
			{
				//�e�̐悩��o��G�t�F�N�g��`��
				m_muzzleflasheffect[People].Draw(PlayerNo);
			}
			//�O���l�[�h�̔����̃G�t�F�N�g��`��
			m_explosioneffect[People].Draw(PlayerNo);
		}
		if (m_waitflag == true)
		{
			//�Q�[���̎c�莞�Ԃ�`��
			m_timer->Draw();
		}
		m_player[PlayerNo]->SetAttackFalse();
		m_player[PlayerNo]->SetKillFalse();
		
	}
	if (m_startTimer <= 0.0f)
	{
		m_waitflag = true;
		if (m_weaponflag == true)
		{
			SetPlayerWeapon();

			m_weaponflag = false;

			m_startSound.Play(false);
		}
	}
}

void Game::DrawShadowMap()
{
	
	///////////////////////////////////////////////
	//�V���h�E�}�b�v�Ƀ����_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���ɖ߂��B
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
	
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	g_graphicsEngine->ChangeRenderTarget(
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//�h���h��
	m_copyMainRtToFrameBufferSprite.Draw(0);

	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
}