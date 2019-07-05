#include "stdafx.h"
#include "Title.h"
#include "GameSelect.h"

Title::Title()
{
	m_model.Init(L"Assets/modelData/Player.cmo");

	m_animationClips[0].Load(L"Assets/animData/Player_Salute.tka");
	m_animationClips[0].SetLoopFlag(false);

	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		1					//アニメーションクリップの数。
	);

	g_camera3D[0].SetPosition({ 0.0f, 80.0f, 100.0f });
	g_camera3D[0].SetTarget(CVector3{0.0f,60.0f,0.0f});
	g_camera3D[0].Update();

	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Title.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_background);

	m_sprite.Init(m_background, 1280.0, 720.0);
	m_sprite.SetTexture(*m_background);

	m_rotation.SetRotationDeg(CVector3::AxisY(), -30.0f);
}


Title::~Title()
{
	m_background->Release();
}
void Title::Update()
{
	m_model.UpdateWorldMatrix(CVector3{80.0f,0.0f,-20.0f }, m_rotation, CVector3::One());
	m_animation.Play(0);
	m_animation.Update(1.0f / 30.0f);
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

	m_model.Draw(g_camera3D[0].GetViewMatrix(), g_camera3D[0].GetProjectionMatrix(), 0);

	m_font.BeginDraw();

	m_font.Draw(L"アームド・コンフリクト", { -350.0f,200.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, 0.0f, 1.5f);

	m_font.Draw(L"スタートボタンで始める", { -250.0f,-100.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }, 0.0f, 1.0f);

	m_font.EndDraw();
}