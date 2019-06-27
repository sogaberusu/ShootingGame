#include "stdafx.h"
#include "GameSelect.h"
#include "Game.h"

GameSelect::GameSelect()
{
	ID3D11ShaderResourceView* background = nullptr;
	ID3D11ShaderResourceView* select = nullptr;
	ID3D11ShaderResourceView* startbutton = nullptr;

	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/GameMode.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &background);
	m_background.Init(background, 1280.0, 720.0);
	m_background.SetTexture(*background);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Select.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &select);
	m_rightselect.Init(select, 64.0, 64.0);
	m_rightselect.SetTexture(*select);

	m_leftselect.Init(select, 64.0, 64.0);
	m_leftselect.SetTexture(*select);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/StartButton.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &startbutton);
	m_startButton.Init(startbutton, 64.0, 64.0);
	m_startButton.SetTexture(*startbutton);
}


GameSelect::~GameSelect()
{
}
void GameSelect::Update()
{
	bool transitionflag = false;
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_background.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	if (m_state == enState_GameType)
	{
		m_leftselect.Update(CVector3{ -500.0f,78.0f,0.0f }, rot, CVector3::One());
		m_rightselect.Update(CVector3{ 500.0f,78.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	}
	if (m_state == enState_GameMap)
	{
		m_leftselect.Update(CVector3{ -500.0f,-190.0f,0.0f }, rot, CVector3::One());
		m_rightselect.Update(CVector3{ 500.0f,-190.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	}
	
	m_startButton.Update(CVector3{ -300.0f,-300.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	for (int PlayerNo = 0; PlayerNo < 4; PlayerNo++)
	{
		if (g_pad[PlayerNo].IsTrigger(enButtonRight) == true) {
			if (m_gametype == enGame_DM && m_state == enState_GameType)
			{
				m_leftMoveflag = true;
				m_rightMoveflag = false;
				m_gametype = enGame_CTF;
			}
			if (m_maptype == enMap_Container && m_state == enState_GameMap)
			{
				m_leftMoveflag = true;
				m_rightMoveflag = false;
				m_maptype = enMap_Test;
			}
		}
		if (g_pad[PlayerNo].IsTrigger(enButtonLeft) == true) {
			if (m_gametype == enGame_CTF && m_state == enState_GameType)
			{
				m_leftMoveflag = false;
				m_rightMoveflag = true;
				m_gametype = enGame_DM;
			}
			if (m_maptype == enMap_Test && m_state == enState_GameMap)
			{
				m_leftMoveflag = false;
				m_rightMoveflag = true;
				m_maptype = enMap_Container;
			}
		}
		if (g_pad[PlayerNo].IsTrigger(enButtonUp) == true && m_leftMoveflag == false && m_rightMoveflag == false) {
			if (m_state == enState_GameType)
			{
				m_state = enState_GameStart;
			}
			else {
				m_state = static_cast<EnState>(m_state - 1);
			}
		}
		if (g_pad[PlayerNo].IsTrigger(enButtonDown) == true && m_leftMoveflag == false && m_rightMoveflag == false)
		{
			if (m_state == enState_GameStart)
			{
				m_state = enState_GameType;
			}
			else {
				m_state = static_cast<EnState>(m_state + 1);
			}
		}
		if (g_pad[PlayerNo].IsPress(enButtonStart) == true && m_state == enState_GameStart) {
			transitionflag = true;
			
		}
	}
	if (transitionflag == true)
	{
		//ゲームシーンを作成して、自分は死ぬ。
			g_currentScene = new Game(m_gametype, m_maptype);
			delete this;
	}
	if (m_leftMoveflag == true)
	{
		if (m_state == enState_GameType)
		{
			if (m_fontCTFPos.x <= -180.0f)
			{
				m_leftMoveflag = false;
			}
			m_fontDMPos.x = m_fontDMPos.x - 100.0f;
			m_fontCTFPos.x = m_fontCTFPos.x - 100.0f;
		}
		if (m_state == enState_GameMap)
		{
			if (m_fontTestMapPos.x <= 0.0f)
			{
				m_leftMoveflag = false;
			}
			m_fontContainerPos.x = m_fontContainerPos.x - 100.0f;
			m_fontTestMapPos.x = m_fontTestMapPos.x - 100.0f;
		}
	}
	if (m_rightMoveflag == true)
	{
		if (m_state == enState_GameType)
		{
			if (m_fontDMPos.x >= -250.0f)
			{
				m_rightMoveflag = false;
			}
			m_fontDMPos.x = m_fontDMPos.x + 100.0f;
			m_fontCTFPos.x = m_fontCTFPos.x + 100.0f;
		}
		if (m_state == enState_GameMap)
		{
			if (m_fontContainerPos.x >= -250.0f)
			{
				m_rightMoveflag = false;
			}
			m_fontContainerPos.x = m_fontContainerPos.x + 100.0f;
			m_fontTestMapPos.x = m_fontTestMapPos.x + 100.0f;
		}
	}
	//文字の色を変える
	switch (m_state)
	{
	case enState_GameType:
		m_gameTypeFontColor = Red;
		m_stageFontColor = Black;
		m_gameStartFontColor = Black;
		break;
	case enState_GameMap:
		m_gameTypeFontColor = Black;
		m_stageFontColor = Red;
		m_gameStartFontColor = Black;
		break;
	case enState_GameStart:
			m_gameTypeFontColor = Black;
			m_stageFontColor = Black;
			m_gameStartFontColor = Red;
			break;
		}
}
void GameSelect::Draw()
{
	m_background.Draw(0);
	if (m_leftMoveflag == false && m_rightMoveflag == false && m_state == enState_GameType)
	{
		if (m_gametype == enGame_DM )
		{
			m_rightselect.Draw(0);
		}
		if (m_gametype == enGame_CTF)
		{
			m_leftselect.Draw(0);
		}
	}
	if (m_leftMoveflag == false && m_rightMoveflag == false && m_state == enState_GameMap)
	{
		if (m_maptype == enMap_Container)
		{
			m_rightselect.Draw(0);
		}
		if (m_maptype == enMap_Test)
		{
			m_leftselect.Draw(0);
		}
	}

	if (m_state == enState_GameStart)
	{
		m_startButton.Draw(0);
	}

	m_font.BeginDraw();

	m_font.Draw(L"デスマッチ", m_fontDMPos, m_gameTypeFontColor, 0.0f, 1.0f);

	m_font.Draw(L"キャプチャー・ザ・フラッグ", m_fontCTFPos, m_gameTypeFontColor, 0.0f, 1.0f);

	m_font.Draw(L"ステージ", {-100.0f,-20.0f} ,{ 0.0f, 0.0f, 0.0f, 1.0f }, 0.0f, 1.5f);

	m_font.Draw(L"コンテナ置き場", m_fontContainerPos, m_stageFontColor, 0.0f, 1.0f);

	m_font.Draw(L"テストマップ", m_fontTestMapPos, m_stageFontColor, 0.0f, 1.0f);

	m_font.Draw(L"ゲームスタート", { -100.0f, -280.0f }, m_gameStartFontColor, 0.0f, 1.0f);

	m_font.EndDraw();
}