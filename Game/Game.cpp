#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Background.h"
#include "Player.h"
#include "Title.h"
#include "Result.h"
#include "WeaponAttr.h"


//グローバルなアクセスポイントをグローバル変数として提供する。
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
		m_grenadeManager.SetInstance(m_player[i], i);
		m_timer.SetPlayer(m_player[i], i);
		m_effect[i].Init(L"Assets/effect/MuzzleFlash.efk");
		m_m4a1[i].SetInstance(m_player[i]);
		m_mp5[i].SetInstance(m_player[i]);
		m_benelliM4[i].SetInstance(m_player[i]);
		m_m110[i].SetInstance(m_player[i]);
		m_player[i]->SetWeaponInstance(&m_m4a1[i], &m_mp5[i],&m_benelliM4[i],&m_m110[i]);
		m_hud[i].SetInstance(m_player[i]);
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

	//シャドウマップにレンダリング
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
	

	//プレイヤーの更新。
	for (int i = 0; i < 4; i++)
	{
		m_player[i]->Update(g_camera3D[i],i);
		m_gameCamera[i]->Update();
		switch (m_player[i]->GetWeapon())
		{
		case enWeapon_M4A1:
			m_m4a1[i].Update();
			break;
		case enWeapon_MP5:
			m_mp5[i].Update();
			break;
		case enWeapon_Benelli_M4:
			m_benelliM4[i].Update();
			break;
		case enWeapon_M110:
			m_m110[i].Update();
		}
		m_hud[i].Update(i);
	}
	m_background->Update();
	m_bulletManager.Update();
	m_grenadeManager.Update();
	//ポストエフェクトの更新。
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
			switch (m_player[j]->GetWeapon())
			{
			case enWeapon_M4A1:
				m_m4a1[j].Draw(g_camera3D[i], i, j);
				break;
			case enWeapon_MP5:
				m_mp5[j].Draw(g_camera3D[i], i, j);
				break;
			case enWeapon_Benelli_M4:
				m_benelliM4[j].Draw(g_camera3D[i], i, j);
				break;
			case enWeapon_M110:
				m_m110[j].Draw(g_camera3D[i], i, j);
				break;
			}
		}
		//背景の描画
		m_background->Draw(g_camera3D[i]);
		m_bulletManager.Draw(g_camera3D[i]);
		m_grenadeManager.Draw(g_camera3D[i]);
		m_sky.Draw(g_camera3D[i]);
		m_timer.Draw();
		for (int j = 0; j < 4; j++)
		{
			m_effect[j].Draw(i);
			
		}
		switch (m_player[i]->GetWeapon())
		{
		case enWeapon_M4A1:
			m_hud[i].Draw(i,m_m4a1[i].GetAmmo(),m_player[i]->GetHitPoint(),m_player[i]->GetAttackFlag(),m_player[i]->GetKillFlag(), m_player[i]->GetWeapon(),m_player[i]->GetCameraType());
			break;
		case enWeapon_MP5:
			m_hud[i].Draw(i, m_mp5[i].GetAmmo(), m_player[i]->GetHitPoint(), m_player[i]->GetAttackFlag(), m_player[i]->GetKillFlag(), m_player[i]->GetWeapon(), m_player[i]->GetCameraType());
			break;
		case enWeapon_Benelli_M4:
			m_hud[i].Draw(i, m_benelliM4[i].GetAmmo(), m_player[i]->GetHitPoint(), m_player[i]->GetAttackFlag(), m_player[i]->GetKillFlag(), m_player[i]->GetWeapon(), m_player[i]->GetCameraType());
			break;
		case enWeapon_M110:
			m_hud[i].Draw(i, m_m110[i].GetAmmo(), m_player[i]->GetHitPoint(), m_player[i]->GetAttackFlag(), m_player[i]->GetKillFlag(), m_player[i]->GetWeapon(), m_player[i]->GetCameraType());
		}
		
		m_player[i]->SetAttackFalse();
		m_player[i]->SetKillFalse();
		if (m_player[i]->GetDrawFlag() == false && m_player[i]->GetWeapon() == enWeapon_M110)
		{
			g_camera3D[i].SetViewAngle(CMath::DegToRad(10.0f));
		}
		else {
			g_camera3D[i].SetViewAngle(CMath::DegToRad(60.0f));

		}
	}
	
}

void Game::DrawShadowMap()
{
	
	///////////////////////////////////////////////
	//シャドウマップにレンダリング
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//元に戻す。
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
	g_graphicsEngine->GetShadowMap()->RenderToShadowMap();

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
	m_copyMainRtToFrameBufferSprite.Draw(0);

	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
}