#include "stdafx.h"
#include "Game.h"
#include "Minotaur.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Goblin.h"
#include "Orc.h"
#include "Player.h"

//グローバルなアクセスポイントをグローバル変数として提供する。
Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	
	for (int i = 0; i < 4; i++)
	{
		//m_stoneManager.SetInstance(&m_player[i], i/*&m_minotaur[i],i &m_goblin, &m_orc*/);
		m_bulletManager.SetInstance(&m_player[i],i);
	}
	
	m_level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"Background") == true) {
			m_bg = new Background(objData.position, objData.rotation);
		}
		else if (objData.EqualName(L"Player1") == true) {
			m_player[0].SetPosition(objData.position);
			m_player[0].SetRotation(objData.rotation);
			m_gameCamera[0] = new GameCamera({ -200.0f, 150.0f, 0.0f });
			m_respawn[0].PlayerPosition = objData.position;
			m_respawn[0].PlayerRotation = objData.rotation;
			m_respawn[0].CameraPosition = CVector3(-200.0f, 150.0f, 0.0f);
		}
		else if (objData.EqualName(L"Player2") == true) {
			m_player[1].SetPosition(objData.position);
			m_player[1].SetRotation(objData.rotation);
			m_gameCamera[1] = new GameCamera({ 0.0f, 150.0f, 200.0f });
			m_respawn[1].PlayerPosition = objData.position;
			m_respawn[1].PlayerRotation = objData.rotation;
			m_respawn[1].CameraPosition = CVector3(0.0f, 150.0f, 200.0f);
		}
		else if (objData.EqualName(L"Player3") == true) {
			m_player[2].SetPosition(objData.position);
			m_player[2].SetRotation(objData.rotation);
			m_gameCamera[2] = new GameCamera({ 0.0f, 150.0f, -200.0f });
			m_respawn[2].PlayerPosition = objData.position;
			m_respawn[2].PlayerRotation = objData.rotation;
			m_respawn[2].CameraPosition = CVector3(0.0f, 150.0f, -200.0f);
		}
		else if (objData.EqualName(L"Player4") == true) {
			m_player[3].SetPosition(objData.position);
			m_player[3].SetRotation(objData.rotation);
			m_gameCamera[3] = new GameCamera({ 200.0f, 150.0f, 0.0f });
			m_respawn[3].PlayerPosition = objData.position;
			m_respawn[3].PlayerRotation = objData.rotation;
			m_respawn[3].CameraPosition = CVector3(200.0f, 150.0f, 0.0f);
		}
		return true;
	});
	
	m_gameCamera[0]->InitViewport(640, 360, 0, 0);
	m_viewport[0].Width = 640;
	m_viewport[0].Height = 360;
	m_viewport[0].TopLeftX = 0;
	m_viewport[0].TopLeftY = 0;
	m_gameCamera[0]->SetPlayer(&m_player[0]);
	m_gameCamera[0]->Seti(0);
	//m_player[0].SetPosition({ 1087.0f,0.0f,-1017.20f });
	

	m_gameCamera[1]->InitViewport(640, 360, 640, 0);
	m_viewport[1].Width = 640;
	m_viewport[1].Height = 360;
	m_viewport[1].TopLeftX = 640;
	m_viewport[1].TopLeftY = 0;
	m_gameCamera[1]->SetPlayer(&m_player[1]);
	m_gameCamera[1]->Seti(1);
	//m_player[1].SetPosition({ 1048.0f,0.0f,1003.8f });

	m_gameCamera[2]->InitViewport(640, 360, 0, 360);
	m_viewport[2].Width = 640;
	m_viewport[2].Height = 360;
	m_viewport[2].TopLeftX = 0;
	m_viewport[2].TopLeftY = 360;
	m_gameCamera[2]->SetPlayer(&m_player[2]);
	m_gameCamera[2]->Seti(2);
	//m_player[2].SetPosition({ -1192.6f,0.0f,1029.3f });
	

	m_gameCamera[3]->InitViewport(640, 360, 640, 360);
	m_viewport[0].Width = 640;
	m_viewport[0].Height = 360;
	m_viewport[0].TopLeftX = 640;
	m_viewport[0].TopLeftY = 360;
	m_gameCamera[3]->SetPlayer(&m_player[3]);
	m_gameCamera[3]->Seti(3);
	//m_player[3].SetPosition({ -1191.1f,0.0f,-991.5f });


	g_shadowMap.InitShadowMap();

	//メインとなるレンダリングターゲットを作成する。
	g_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
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
	m_restTimer = max(0.0f, m_restTimer - 1.0f / 30.0f);
	//シャドウマップを更新。
	g_shadowMap.UpdateFromLightTarget(
		{1000.0f,1000.0f,0.0f},
		{ 0.0f,0.0f,0.0f }
	);
	//プレイヤーの更新。
	/*m_goblin.Update();
	m_orc.Update();*/
	for (int i = 0; i < 4; i++)
	{
		m_player[i].Update(g_camera3D[i],i);
		m_gameCamera[i]->Update();	
	}
	m_bg->Update();
	//m_stoneManager.Update();
	m_bulletManager.Update();
	
	//ポストエフェクトの更新。
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
		m_gameCamera[i]->StartRender();
		
		for (int j = 0; j < 4; j++)
		{
			m_player[j].Draw(g_camera3D[i], i, j);
		}
		/*m_goblin.Draw(g_camera3D[i]);
		m_orc.Draw(g_camera3D[i]);*/
		//背景の描画
		m_bg->Draw(g_camera3D[i]);
		//m_stoneManager.Draw(g_camera3D[i]);
		m_bulletManager.Draw(g_camera3D[i]);
		m_sky.Draw(g_camera3D[i]);
		m_timer.Draw();
	}
}

void Game::DrawShadowMap()
{
	
	///////////////////////////////////////////////
	//シャドウマップにレンダリング
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
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
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//シャドウマップにレンダリング
	g_shadowMap.RenderToShadowMap();

	//レンダリングターゲットをメインに変更する。
	g_graphicsEngine->ChangeRenderTarget(&g_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_mainRenderTarget.ClearRenderTarget(clearColor);
	

	//ポストエフェクトの描画。
	m_postEffect.Draw();

	//レンダリングターゲットをフレームバッファに戻す。
	g_graphicsEngine->ChangeRenderTarget(
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//ドロドロ
	m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

	////元に戻す。
	//d3dDeviceContext->OMSetRenderTargets(
	//	1,
	//	&oldRenderTargetView,
	//	oldDepthStencilView
	//);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	/*oldRenderTargetView->Release();
	oldDepthStencilView->Release();*/
}