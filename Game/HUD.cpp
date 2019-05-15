#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
	ID3D11ShaderResourceView* target = nullptr;
	ID3D11ShaderResourceView* xbutton = nullptr;
	ID3D11ShaderResourceView* life = nullptr;
	ID3D11ShaderResourceView* hitmarker = nullptr;
	ID3D11ShaderResourceView* killmarker = nullptr;
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Target.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &target);
	m_crosshair.Init(target, 64.0, 64.0);
	m_crosshair.SetTexture(*target);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Xbutton.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &xbutton);
	m_xbutton.Init(xbutton, 64.0, 64.0);
	m_xbutton.SetTexture(*xbutton);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/life.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &life);
	m_life.Init(life, 64.0, 64.0);
	m_life.SetTexture(*life);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Hitmarker.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &hitmarker);
	m_hitmarker.Init(hitmarker, 64.0, 64.0);
	m_hitmarker.SetTexture(*hitmarker);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Killmarker.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &killmarker);
	m_killmarker.Init(killmarker, 64.0, 64.0);
	m_killmarker.SetTexture(*killmarker);

}


HUD::~HUD()
{
}

void HUD::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}

void HUD::Update()
{
	m_crosshair.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_hitmarker.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_killmarker.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_xbutton.Update({400.0f,-220.0f,0.0f}, CQuaternion::Identity(), CVector3::One());
	m_life.Update({ -600.0,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
}

void HUD::Draw(int cameraNo,int Ammo,int hitPoint,bool AttackFlag,bool KillFlag)
{
	//スプライトのDraw
	if (Ammo < 10)
	{
		m_xbutton.Draw(cameraNo);
	}

	m_crosshair.Draw(cameraNo);

	if (AttackFlag == true)
	{
		m_hitmarker.Draw(cameraNo);
	}
	if (KillFlag == true)
	{
		m_killmarker.Draw(cameraNo);
	}
	m_life.Draw(cameraNo);

	//フォントのDraw
	wchar_t bullet[256],HP[256];

	swprintf(bullet, L"残弾%d", Ammo);
	swprintf(HP, L"%d", hitPoint);

	m_bullet.BeginDraw();

	if (Ammo < 10)
	{
		m_reload.Draw(L"リロード",{ -100.0f, 80.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
	}
	
	m_bullet.Draw(bullet, { -140.0f,40.0f}, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);

	m_hp.Draw(HP, { -610.0f,40.0f }, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);

	m_bullet.EndDraw();
}