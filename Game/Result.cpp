#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"

Result::Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
	float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime)
{
	m_gameMode = gameMode;
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Result.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_result);
	
	m_sprite.Init(m_result, 1280.0, 720.0);
	m_sprite.SetTexture(*m_result);
	m_playerkills[0] = Player1Kills;
	m_playerkills[1] = Player2Kills;
	m_playerkills[2] = Player3Kills;
	m_playerkills[3] = Player4Kills;
	m_playerCaptureTime[0] = Player1CaptureTime;
	m_playerCaptureTime[1] = Player2CaptureTime;
	m_playerCaptureTime[2] = Player3CaptureTime;
	m_playerCaptureTime[3] = Player4CaptureTime;
}


Result::~Result()
{
	m_result->Release();
}

void Result::Update()
{
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	bool newflag = false;

	if (g_pad[0].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[1].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[2].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[3].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (newflag == true)
	{
		//ゲームシーンを作成して、自分は死ぬ。
		g_currentScene = new Title;
		delete this;
	}
}

void Result::Draw()
{
	m_sprite.Draw(0);
	
	wchar_t Player1Kills[256], Player2Kills[256], Player3Kills[256], Player4Kills[256],
		P1CaptureTime[256], P2CaptureTime[256], P3CaptureTime[256], P4CaptureTime[256];
	swprintf(Player1Kills, L"Player1 %dキル", m_playerkills[0]);
	swprintf(Player2Kills, L"Player2 %dキル", m_playerkills[1]);
	swprintf(Player3Kills, L"Player3 %dキル", m_playerkills[2]);
	swprintf(Player4Kills, L"Player4 %dキル", m_playerkills[3]);
	swprintf(P1CaptureTime, L"Player1:%.2f秒", m_playerCaptureTime[0]);
	swprintf(P2CaptureTime, L"Player2:%.2f秒", m_playerCaptureTime[1]);
	swprintf(P3CaptureTime, L"Player3:%.2f秒", m_playerCaptureTime[2]);
	swprintf(P4CaptureTime, L"Player4:%.2f秒", m_playerCaptureTime[3]);

	m_font.BeginDraw();
	switch (m_gameMode)
	{
	case enGame_DM:
		m_font.Draw(Player1Kills, { -100.0f, 200.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(Player2Kills, { -100.0f, 100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(Player3Kills, { -100.0f, 0.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(Player4Kills, { -100.0f, -100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		break;
	case enGame_CTF:
		m_font.Draw(P1CaptureTime, { -100.0f, 200.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(P2CaptureTime, { -100.0f, 100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(P3CaptureTime, { -100.0f, 0.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(P4CaptureTime, { -100.0f, -100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		break;
	}
	

	

	m_font.EndDraw();
	
}