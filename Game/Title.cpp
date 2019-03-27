#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/box.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_mikyan);
	if (FAILED(hr))
	{
		int i = 0;
	}
	/*MessageBox(nullptr, "最初の画面はタイトルシーン！Aボタンを押すとゲームが始まるよ！", "通知", MB_OK);*/
	m_sprite.Init(m_mikyan,1280.0,720.0);
	m_sprite.SetTexture(*m_mikyan);
}


Title::~Title()
{
}
void Title::Update()
{
	

	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	if (g_pad[0].IsPress(enButtonA) == true) {
		//ゲームシーンを作成して、自分は死ぬ。
		g_currentScene = new Game;
		delete this;
	}
}
void Title::Draw()
{
	m_sprite.Draw();
}