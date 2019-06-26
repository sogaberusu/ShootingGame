#include "stdafx.h"
#include "Title.h"
#include "GameSelect.h"

Title::Title()
{
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Title.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_title);
	if (FAILED(hr))
	{
		int i = 0;
	}
	m_sprite.Init(m_title, 1280.0, 720.0);
	m_sprite.SetTexture(*m_title);
}


Title::~Title()
{
	m_title->Release();
}
void Title::Update()
{
	bool newflag = false;

	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	
	if (g_pad[0].IsPress(enButtonStart) == true) {
		newflag = true;
	}
	if (g_pad[1].IsPress(enButtonStart) == true) {
		newflag = true;
	}
	if (g_pad[2].IsPress(enButtonStart) == true) {
		newflag = true;
	}
	if (g_pad[3].IsPress(enButtonStart) == true) {
		newflag = true;
	}
	if (newflag == true)
	{
		//ゲームシーンを作成して、自分は死ぬ。
		g_currentScene = new GameSelect;
		delete this;
	}
}
void Title::Draw()
{
	m_sprite.Draw(0);
}