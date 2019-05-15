#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Target.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_target);
	m_sprite.Init(m_target, 64.0, 64.0);
	m_sprite.SetTexture(*m_target);
}


HUD::~HUD()
{
	m_target->Release();
}

void HUD::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}

void HUD::Update()
{
	m_sprite.Update({0.0f,0.0f,0.0f}, CQuaternion::Identity(), CVector3::One());
}

void HUD::Draw(int cameraNo)
{
	m_sprite.Draw(cameraNo);
}