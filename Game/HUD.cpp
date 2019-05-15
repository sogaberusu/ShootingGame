#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Target.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_target);
	m_crosshair.Init(m_target, 64.0, 64.0);
	m_crosshair.SetTexture(*m_target);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Xbutton.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_button);
	m_xbutton.Init(m_button, 64.0, 64.0);
	m_xbutton.SetTexture(*m_button);

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
	m_crosshair.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_xbutton.Update({400.0f,-220.0f,0.0f}, CQuaternion::Identity(), CVector3::One());
}

void HUD::Draw(int cameraNo,int Ammo)
{
	if (Ammo < 10)
	{
		m_xbutton.Draw(cameraNo);
	}

	m_crosshair.Draw(cameraNo);

	wchar_t bullet[256];

	swprintf(bullet, L"Žc’e%d",Ammo);

	m_bullet.BeginDraw();

	if (Ammo < 10)
	{
		m_reload.Draw(L"ƒŠƒ[ƒh",{ -100.0f, 80.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
	}
	
	m_bullet.Draw(bullet, { -140.0f,50.0}, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 1.0f);

	m_bullet.EndDraw();
}