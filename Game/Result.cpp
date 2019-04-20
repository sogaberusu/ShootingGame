#include "stdafx.h"
#include "Result.h"
#include "Title.h"

Result::Result(int Player1Kills, int Player2Kills, int Player3Kills, int Player4Kills)
{
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
}


Result::~Result()
{
	m_result->Release();
}

void Result::Update()
{
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	if (g_pad[0].IsPress(enButtonStart) == true) {
		//ゲームシーンを作成して、自分は死ぬ。
		g_currentScene = new Title;
		delete this;
	}

	

	
}

void Result::Draw()
{
	m_sprite.Draw(0);
	swprintf(Player1Kills, L"Player1 %dキル", m_playerkills[0]);
	swprintf(Player2Kills, L"Player2 %dキル", m_playerkills[1]);
	swprintf(Player3Kills, L"Player3 %dキル", m_playerkills[2]);
	swprintf(Player4Kills, L"Player4 %dキル", m_playerkills[3]);

	m_font.BeginDraw();

	m_font.Draw(Player1Kills, { 0.0f, 200.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
	m_font.Draw(Player2Kills, { 0.0f, 100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
	m_font.Draw(Player3Kills, { 0.0f, 0.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);
	m_font.Draw(Player4Kills, { 0.0f, -100.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);

	m_font.EndDraw();
	
}