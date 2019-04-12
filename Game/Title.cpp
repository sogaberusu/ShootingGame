#include "stdafx.h"
#include "Title.h"
#include "Game.h"

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
	/*MessageBox(nullptr, "�ŏ��̉�ʂ̓^�C�g���V�[���IA�{�^���������ƃQ�[�����n�܂��I", "�ʒm", MB_OK);*/
	m_sprite.Init(m_title,1280.0,720.0);
	m_sprite.SetTexture(*m_title);
}


Title::~Title()
{
	m_title->Release();
}
void Title::Update()
{
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	m_font.Begin();
	
	wchar_t fps[256];
	swprintf_s(fps, L"FPS = %.2f", 1);
	float w = FRAME_BUFFER_W;
	float h = FRAME_BUFFER_H;
	m_font.Draw(
		fps,
		{ 0.0f,h*0.5f },
		{ 1.0f,1.0f,1.0f,1.0f },
		0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
		2.0f,
		{ 0.0f, 1.0f }
	);
	wchar_t Seconds[256];
	swprintf_s(Seconds, L"�b�@�� %.2f", 1);
	m_font.Draw(
		Seconds,
		{ w*0.5f,h*0.5f },
		{ 1.0f,0.0f,0.0f,1.0f },
		0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
		2.0f,
		{ 1.0f, 1.0f }
	);

	m_font.End();
	
	if (g_pad[0].IsPress(enButtonStart) == true) {
		//�Q�[���V�[�����쐬���āA�����͎��ʁB
		g_currentScene = new Game;
		delete this;
	}
}
void Title::Draw()
{
	m_sprite.Draw();
}