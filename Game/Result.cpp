#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"

Result::Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
	float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime)
{
	m_gameMode = gameMode;

	ID3D11ShaderResourceView* result = nullptr;
	ID3D11ShaderResourceView * Crown1 = nullptr;
	ID3D11ShaderResourceView * Crown2 = nullptr;
	ID3D11ShaderResourceView * Crown3 = nullptr;
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Result.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &result);
	
	m_background.Init(result, 1280.0, 720.0);
	m_background.SetTexture(*result);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/1stCrown.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &Crown1);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/2ndCrown.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &Crown2);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/3rdCrown.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &Crown3);

	for (int i = 0; i < 4; i++)
	{
		m_1stCrown[i].Init(Crown1, 46.0, 32.0);
		m_1stCrown[i].SetTexture(*Crown1);

		m_2ndCrown[i].Init(Crown2, 46.0, 32.0);
		m_2ndCrown[i].SetTexture(*Crown2);

		m_3rdCrown[i].Init(Crown3, 46.0, 32.0);
		m_3rdCrown[i].SetTexture(*Crown3);
	}
	
	m_playerkills[0] = Player1Kills;
	m_playerkills[1] = Player2Kills;
	m_playerkills[2] = Player3Kills;
	m_playerkills[3] = Player4Kills;
	
	std::array<int, 4> kill{ Player1Kills,Player2Kills,Player3Kills, Player4Kills };
	std::sort(kill.begin(), kill.end(), [](int a, int b) {return a > b;});
	auto Kills = kill.begin();
	m_1stKills = (*Kills);
	Kills++;
	m_2ndKills = (*Kills);
	Kills++;
	m_3rdKills = (*Kills);


	m_playerCaptureTime[0] = Player1CaptureTime;
	m_playerCaptureTime[1] = Player2CaptureTime;
	m_playerCaptureTime[2] = Player3CaptureTime;
	m_playerCaptureTime[3] = Player4CaptureTime;

	std::array<float, 4>time{ Player1CaptureTime, Player2CaptureTime, Player3CaptureTime,Player4CaptureTime };
	std::sort(time.begin(), time.end(), [](float a, float b) {return a > b;});
	auto Time = time.begin();
	m_1stTime = (*Time);
	Time++;
	m_2ndTime = (*Time);
	Time++;
	m_3rdTime = (*Time);
}


Result::~Result()
{
}

void Result::Update()
{
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	for (int i = 0; i < 4; i++)
	{
		m_1stCrown[i].Update(CVector3{ -200.0f,200.0f - (i * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());
		m_2ndCrown[i].Update(CVector3{ -200.0f,200.0f - (i * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());
		m_3rdCrown[i].Update(CVector3{ -200.0f,200.0f - (i * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());

		if (m_gameMode == enGame_DM && m_1stKills == m_playerkills[i])
		{
			m_1stCrownDrawFlag[i] = true;
		}
		if (m_gameMode == enGame_DM && m_2ndKills == m_playerkills[i])
		{
			m_2ndCrownDrawFlag[i] = true;
		}
		if (m_gameMode == enGame_DM && m_3rdKills == m_playerkills[i])
		{
			m_3rdCrownDrawFlag[i] = true;
		}
		if (m_gameMode == enGame_CTF && m_1stTime == m_playerCaptureTime[i])
		{
			m_1stCrownDrawFlag[i] = true;
		}
		if (m_gameMode == enGame_CTF && m_2ndTime == m_playerCaptureTime[i])
		{
			m_2ndCrownDrawFlag[i] = true;
		}
		if (m_gameMode == enGame_CTF && m_3rdTime == m_playerCaptureTime[i])
		{
			m_3rdCrownDrawFlag[i] = true;
		}

	}


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
		//ƒQ[ƒ€ƒV[ƒ“‚ðì¬‚µ‚ÄAŽ©•ª‚ÍŽ€‚ÊB
		g_currentScene = new Title;
		delete this;
	}
}

void Result::Draw()
{
	m_background.Draw(0);
	
	wchar_t Player1Kills[256], Player2Kills[256], Player3Kills[256], Player4Kills[256],
		P1CaptureTime[256], P2CaptureTime[256], P3CaptureTime[256], P4CaptureTime[256];
	swprintf(Player1Kills, L"Player1 %dƒLƒ‹", m_playerkills[0]);
	swprintf(Player2Kills, L"Player2 %dƒLƒ‹", m_playerkills[1]);
	swprintf(Player3Kills, L"Player3 %dƒLƒ‹", m_playerkills[2]);
	swprintf(Player4Kills, L"Player4 %dƒLƒ‹", m_playerkills[3]);
	swprintf(P1CaptureTime, L"Player1:%.2f•b", m_playerCaptureTime[0]);
	swprintf(P2CaptureTime, L"Player2:%.2f•b", m_playerCaptureTime[1]);
	swprintf(P3CaptureTime, L"Player3:%.2f•b", m_playerCaptureTime[2]);
	swprintf(P4CaptureTime, L"Player4:%.2f•b", m_playerCaptureTime[3]);

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
	
	for (int i = 0; i < 4; i++)
	{
		if (m_3rdCrownDrawFlag[i] == true)
		{
			m_3rdCrown[i].Draw(0);
		}
		if (m_2ndCrownDrawFlag[i] == true)
		{
			m_2ndCrown[i].Draw(0);
		}
		if (m_1stCrownDrawFlag[i] == true)
		{
			m_1stCrown[i].Draw(0);
		}
	}
	
	m_font.EndDraw();
	
}