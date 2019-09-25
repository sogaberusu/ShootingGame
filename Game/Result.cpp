#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"

Result::Result(int gameMode, int Player1Kills, int Player2Kills,
	float Player1CaptureTime, float Player2CaptureTime)
{
	m_gameMode = gameMode;

	Init();

	m_playerkills[enPlayer1] = Player1Kills;
	m_playerkills[enPlayer2] = Player2Kills;

	std::array<int, 2> kill{ Player1Kills,Player2Kills };
	std::sort(kill.begin(), kill.end(), [](int a, int b) {return a > b;});
	auto Kills = kill.begin();
	m_1stKills = (*Kills);
	Kills++;
	m_2ndKills = (*Kills);

	m_playerCaptureTime[enPlayer1] = Player1CaptureTime;
	m_playerCaptureTime[enPlayer2] = Player2CaptureTime;

	std::array<float, 2>time{ Player1CaptureTime, Player2CaptureTime };
	std::sort(time.begin(), time.end(), [](float a, float b) {return a > b;});
	auto Time = time.begin();
	m_1stTime = (*Time);
	Time++;
	m_2ndTime = (*Time);
}

Result::Result(int gameMode, int Player1Kills, int Player2Kills, int Player3Kills,
	float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime)
{
	m_gameMode = gameMode;

	Init();

	m_playerkills[enPlayer1] = Player1Kills;
	m_playerkills[enPlayer2] = Player2Kills;
	m_playerkills[enPlayer3] = Player3Kills;

	std::array<int, 3> kill{ Player1Kills,Player2Kills,Player3Kills };
	std::sort(kill.begin(), kill.end(), [](int a, int b) {return a > b;});
	auto Kills = kill.begin();
	m_1stKills = (*Kills);
	Kills++;
	m_2ndKills = (*Kills);
	Kills++;
	m_3rdKills = (*Kills);

	m_playerCaptureTime[enPlayer1] = Player1CaptureTime;
	m_playerCaptureTime[enPlayer2] = Player2CaptureTime;
	m_playerCaptureTime[enPlayer3] = Player3CaptureTime;

	std::array<float, 3>time{ Player1CaptureTime, Player2CaptureTime, Player3CaptureTime };
	std::sort(time.begin(), time.end(), [](float a, float b) {return a > b;});
	auto Time = time.begin();
	m_1stTime = (*Time);
	Time++;
	m_2ndTime = (*Time);
	Time++;
	m_3rdTime = (*Time);
}
Result::Result(int gameMode,int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills,
	float Player1CaptureTime, float Player2CaptureTime, float Player3CaptureTime, float Player4CaptureTime)
{
	m_gameMode = gameMode;
	
	Init();

	m_playerkills[enPlayer1] = Player1Kills;
	m_playerkills[enPlayer2] = Player2Kills;
	m_playerkills[enPlayer3] = Player3Kills;
	m_playerkills[enPlayer4] = Player4Kills;
	
	std::array<int, 4> kill{ Player1Kills,Player2Kills,Player3Kills, Player4Kills };
	std::sort(kill.begin(), kill.end(), [](int a, int b) {return a > b;});
	auto Kills = kill.begin();
	m_1stKills = (*Kills);
	Kills++;
	m_2ndKills = (*Kills);
	Kills++;
	m_3rdKills = (*Kills);

	m_playerCaptureTime[enPlayer1] = Player1CaptureTime;
	m_playerCaptureTime[enPlayer2] = Player2CaptureTime;
	m_playerCaptureTime[enPlayer3] = Player3CaptureTime;
	m_playerCaptureTime[enPlayer4] = Player4CaptureTime;

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
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		m_1stCrown[PlayerNo].Update(CVector3{ -200.0f,200.0f - (PlayerNo * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());
		m_2ndCrown[PlayerNo].Update(CVector3{ -200.0f,200.0f - (PlayerNo * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());
		m_3rdCrown[PlayerNo].Update(CVector3{ -200.0f,200.0f - (PlayerNo * 100.0f),0.0f }, CQuaternion::Identity(), CVector3::One());

		if (m_gameMode == enGame_DM && m_1stKills == m_playerkills[PlayerNo])
		{
			m_1stCrownDrawFlag[PlayerNo] = true;
		}
		if (m_gameMode == enGame_DM && m_2ndKills == m_playerkills[PlayerNo])
		{
			m_2ndCrownDrawFlag[PlayerNo] = true;
		}
		if (m_gameMode == enGame_DM && m_3rdKills == m_playerkills[PlayerNo])
		{
			m_3rdCrownDrawFlag[PlayerNo] = true;
		}
		if (m_gameMode == enGame_CTF && m_1stTime == m_playerCaptureTime[PlayerNo])
		{
			m_1stCrownDrawFlag[PlayerNo] = true;
		}
		if (m_gameMode == enGame_CTF && m_2ndTime == m_playerCaptureTime[PlayerNo])
		{
			m_2ndCrownDrawFlag[PlayerNo] = true;
		}
		if (m_gameMode == enGame_CTF && m_3rdTime == m_playerCaptureTime[PlayerNo])
		{
			m_3rdCrownDrawFlag[PlayerNo] = true;
		}
	}

	bool newflag = false;

	if (g_pad[enPlayer1].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[enPlayer2].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[enPlayer3].IsPress(enButtonA) == true) {
		newflag = true;
	}
	if (g_pad[enPlayer4].IsPress(enButtonA) == true) {
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
	swprintf(Player1Kills, L"Player1 %dƒLƒ‹", m_playerkills[enPlayer1]);
	swprintf(Player2Kills, L"Player2 %dƒLƒ‹", m_playerkills[enPlayer2]);
	if (PLAYERS >= enPlayer4)
	{
		swprintf(Player3Kills, L"Player3 %dƒLƒ‹", m_playerkills[enPlayer3]);
	}
	if (PLAYERS >= enPlayerNum)
	{
		swprintf(Player4Kills, L"Player4 %dƒLƒ‹", m_playerkills[enPlayer4]);
	}
	swprintf(P1CaptureTime, L"Player1:%.2f•b", m_playerCaptureTime[enPlayer1]);
	swprintf(P2CaptureTime, L"Player2:%.2f•b", m_playerCaptureTime[enPlayer2]);
	if (PLAYERS >= enPlayer4)
	{
		swprintf(P3CaptureTime, L"Player3:%.2f•b", m_playerCaptureTime[enPlayer3]);
	}
	if (PLAYERS >= enPlayerNum)
	{
		swprintf(P4CaptureTime, L"Player4:%.2f•b", m_playerCaptureTime[enPlayer4]);
	}

	m_font.BeginDraw();
	switch (m_gameMode)
	{
	case enGame_DM:
		m_font.Draw(Player1Kills, { -100.0f, 200.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(Player2Kills, { -100.0f, 100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		if (PLAYERS >= enPlayer4)
		{
			m_font.Draw(Player3Kills, { -100.0f, 0.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		}
		if (PLAYERS >= enPlayerNum)
		{
			m_font.Draw(Player4Kills, { -100.0f, -100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		}
		break;
	case enGame_CTF:
		m_font.Draw(P1CaptureTime, { -100.0f, 200.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		m_font.Draw(P2CaptureTime, { -100.0f, 100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		if (PLAYERS >= enPlayer4)
		{
			m_font.Draw(P3CaptureTime, { -100.0f, 0.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		}
		if (PLAYERS >= enPlayerNum)
		{
			m_font.Draw(P4CaptureTime, { -100.0f, -100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
		}
		break;
	}
	
	for (int PlayerNo = 0; PlayerNo < PLAYERS; PlayerNo++)
	{
		if (m_3rdCrownDrawFlag[PlayerNo] == true)
		{
			m_3rdCrown[PlayerNo].Draw(0);
		}
		if (m_2ndCrownDrawFlag[PlayerNo] == true)
		{
			m_2ndCrown[PlayerNo].Draw(0);
		}
		if (m_1stCrownDrawFlag[PlayerNo] == true)
		{
			m_1stCrown[PlayerNo].Draw(0);
		}
	}
	
	m_font.EndDraw();
	
}

void Result::Init()
{
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

	for (int PlayeNo = 0; PlayeNo < PLAYERS; PlayeNo++)
	{
		m_1stCrown[PlayeNo].Init(Crown1, 46.0, 32.0);
		m_1stCrown[PlayeNo].SetTexture(*Crown1);
		m_2ndCrown[PlayeNo].Init(Crown2, 46.0, 32.0);
		m_2ndCrown[PlayeNo].SetTexture(*Crown2);
		m_3rdCrown[PlayeNo].Init(Crown3, 46.0, 32.0);
		m_3rdCrown[PlayeNo].SetTexture(*Crown3);
	}
}