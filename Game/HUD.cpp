#include "stdafx.h"
#include "HUD.h"
#include "WeaponAttr.h"
#include "Player.h"
#include "Game.h"
#include "Grenade.h"
HUD::HUD()
{
	ID3D11ShaderResourceView* target = nullptr;
	ID3D11ShaderResourceView* xbutton = nullptr;
	ID3D11ShaderResourceView* life = nullptr;
	ID3D11ShaderResourceView* hitmarker = nullptr;
	ID3D11ShaderResourceView* killmarker = nullptr;
	ID3D11ShaderResourceView* shotguntarget = nullptr;
	ID3D11ShaderResourceView* sniperscope = nullptr;
	ID3D11ShaderResourceView* assault = nullptr;
	ID3D11ShaderResourceView* submachinegun = nullptr;
	ID3D11ShaderResourceView* shotgun = nullptr;
	ID3D11ShaderResourceView* sniper = nullptr;
	ID3D11ShaderResourceView* damage = nullptr;
	ID3D11ShaderResourceView* grenade = nullptr;
	ID3D11ShaderResourceView* sight = nullptr;
	ID3D11ShaderResourceView* m4a1ironsight = nullptr;
	ID3D11ShaderResourceView* mp5ironsight = nullptr;
	ID3D11ShaderResourceView* benelli_m4ironsight = nullptr;
	
	
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

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/ShotgunTarget.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &shotguntarget);
	m_shotguntarget.Init(shotguntarget, 96.0, 96.0);
	m_shotguntarget.SetTexture(*shotguntarget);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/SniperScope.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &sniperscope);
	m_scope.Init(sniperscope, 1280.0, 1280.0);
	m_scope.SetTexture(*sniperscope);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/M4A1.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &assault);
	m_m4a1.Init(assault, 256.0, 128.0);
	m_m4a1.SetTexture(*assault);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/MP5.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &submachinegun);
	m_mp5.Init(submachinegun, 256.0, 128.0);
	m_mp5.SetTexture(*submachinegun);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Shotgun.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &shotgun);
	m_shotgun.Init(shotgun, 256.0, 128.0);
	m_shotgun.SetTexture(*shotgun);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Sniper.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &sniper);
	m_m110.Init(sniper, 256.0, 128.0);
	m_m110.SetTexture(*sniper);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/DamageMarker.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &damage);
	m_damage.Init(damage, 64.0, 64.0);
	m_damage.SetTexture(*damage);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Grenade.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &grenade);
	m_hudgrenade.Init(grenade, 64.0, 64.0);
	m_hudgrenade.SetTexture(*grenade);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Eotech.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &sight);
	m_eotech.Init(sight, 640.0, 640.0);
	m_eotech.SetTexture(*sight);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/M4A1IronSight.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m4a1ironsight);
	m_m4a1ironsight.Init(m4a1ironsight, 1280.0, 1280.0);
	m_m4a1ironsight.SetTexture(*m4a1ironsight);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/MP5IronSight.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &mp5ironsight);
	m_mp5ironsight.Init(mp5ironsight, 1280.0, 1280.0);
	m_mp5ironsight.SetTexture(*mp5ironsight);

	hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Benelli_M4IronSight.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &benelli_m4ironsight);
	m_benelli_m4ironsight.Init(benelli_m4ironsight, 1280.0, 1280.0);
	m_benelli_m4ironsight.SetTexture(*benelli_m4ironsight);
}


HUD::~HUD()
{
}

void HUD::StartRender()
{
	g_graphicsEngine->SetViewport(m_width, m_height, m_topLeftX, m_topLeftY);
}

void HUD::Update(int cameraNo)
{
	m_crosshair.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_hitmarker.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_killmarker.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_xbutton.Update({ 400.0f,-220.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_life.Update({ -600.0,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_shotguntarget.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_scope.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_eotech.Update({ -25.0f,-150.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_m4a1.Update({ 410.0f,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_mp5.Update({ 410.0f,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_m110.Update({ 410.0f,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_shotgun.Update({ 410.0,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_m4a1ironsight.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_mp5ironsight.Update({ 0.0f, 50.0f, 0.0f }, CQuaternion::Identity(), CVector3::One());
	m_benelli_m4ironsight.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	if (m_damegeflag == true) {
		CVector3 spritepos = CVector3::Zero();
		spritepos = m_enemyPosition - m_player[m_playerNo]->GetPosition();
		float vectorX = spritepos.Dot(m_player[m_playerNo]->GetRight());
		float vectorZ = spritepos.Dot(m_player[m_playerNo]->GetForward());
		spritepos.x = vectorX;
		spritepos.y = 0.0f;
		spritepos.z = vectorZ;
		spritepos.Normalize();
		CQuaternion rot = CQuaternion::Identity();
		spritepos *= 200.0f;
		m_damage.Update({ spritepos.x,spritepos.z,0.0f },rot , CVector3::One());
	}
	
	m_hudgrenade.Update({ 150.0,-320.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
}

void HUD::Draw(int cameraNo,int Ammo,int hitPoint,int grenades,bool AttackFlag,bool KillFlag,int weapon,bool cameraflag)
{
	if (weapon == enWeapon_M4A1)
	{
		//スプライトのDraw
		if (Ammo < 10)
		{
			m_xbutton.Draw(cameraNo);
		}
		if (cameraflag == false) {
			m_crosshair.Draw(cameraNo);
		}
		else {
			m_m4a1ironsight.Draw(cameraNo);
		}
		m_m4a1.Draw(cameraNo);
		
	}
	if (weapon == enWeapon_MP5)
	{
		//スプライトのDraw
		if (Ammo < 10)
		{
			m_xbutton.Draw(cameraNo);
		}
		if (cameraflag == false) {
			m_crosshair.Draw(cameraNo);
		}
		else {
			m_mp5ironsight.Draw(cameraNo);
		}
		m_mp5.Draw(cameraNo);
	}
	if(weapon == enWeapon_Benelli_M4){
		if (Ammo < 4)
		{
			m_xbutton.Draw(cameraNo);
		}
		if (cameraflag == false) {
			m_shotguntarget.Draw(cameraNo);
		}
		else {
			m_benelli_m4ironsight.Draw(cameraNo);
		}
		m_shotgun.Draw(cameraNo);	
	}
	if (weapon == enWeapon_M110)
	{
		if (Ammo < 4)
		{
			m_xbutton.Draw(cameraNo);
		}
		if (cameraflag == false) {
			m_crosshair.Draw(cameraNo);
		}
		else {
			m_scope.Draw(cameraNo);
		}
		m_m110.Draw(cameraNo);
	}
	if (AttackFlag == true)
	{
		m_hitmarker.Draw(cameraNo);
	}
	if (KillFlag == true)
	{
		m_killmarker.Draw(cameraNo);
	}
	m_life.Draw(cameraNo);

	if (m_damegeflag == true)
	{
		m_damage.Draw(cameraNo);

		m_damegeflagcount--;
	}

	m_hudgrenade.Draw(cameraNo);

	//フォントのDraw
	wchar_t bullet[256], HP[256], grenade[256],
		P1Kills[256], P2Kills[256], P3Kills[256], P4Kills[256],
		P1CaptureTime[256],P2CaptureTime[256],P3CaptureTime[256],P4CaptureTime[256];

	swprintf(bullet, L"%d", Ammo);
	swprintf(HP, L"%d", hitPoint);
	swprintf(grenade, L"x%d", grenades);
	swprintf(P1Kills, L"Player1:%d", m_player[enPlayer1]->GetKills());
	swprintf(P2Kills, L"Player2:%d", m_player[enPlayer2]->GetKills());
	if (PLAYERS >= enPlayer4)
	{
		swprintf(P3Kills, L"Player3:%d", m_player[enPlayer3]->GetKills());
	}
	if (PLAYERS >= enPlayerNum)
	{
		swprintf(P4Kills, L"Player4:%d", m_player[enPlayer4]->GetKills());
	}
	swprintf(P1CaptureTime, L"Player1:%.2f", m_player[enPlayer1]->GetCaptureTime());
	swprintf(P2CaptureTime, L"Player2:%.2f", m_player[enPlayer2]->GetCaptureTime());
	if (PLAYERS >= enPlayer4)
	{
		swprintf(P3CaptureTime, L"Player3:%.2f", m_player[enPlayer3]->GetCaptureTime());
	}
	if (PLAYERS >= enPlayerNum)
	{
		swprintf(P4CaptureTime, L"Player4:%.2f", m_player[enPlayer4]->GetCaptureTime());
	}


	m_font.BeginDraw();

	if (weapon == enWeapon_M4A1 || weapon == enWeapon_MP5)
	{
		//残弾が一定以下になったらリロードしてと表示する
		if (Ammo < 10)
		{
			if (PLAYERS != enPlayer3)
			{
				m_font.Draw(L"リロード", { -100.0f, 80.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			}
			else
			{
				m_font.Draw(L"リロード", { -100.0f, -200.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			}
		}
	}
	else {
		//残弾が一定以下になったらリロードしてと表示する
		if (Ammo < 4)
		{
			if (PLAYERS != enPlayer3)
			{
				m_font.Draw(L"リロード", { -100.0f, 80.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			}
			else
			{
				m_font.Draw(L"リロード", { -100.0f, -200.0f }, { 50.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			}
		}
	}
	if (PLAYERS != enPlayer3)
	{
		//残弾数を表示する
		m_font.Draw(bullet, { -50.0f,40.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
		//プレイヤーのHPを表示する
		m_font.Draw(HP, { -610.0f,40.0f }, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
		//プレイヤーの所持グレネードの数を表示する
		m_font.Draw(grenade, { -230.0f,40.0f }, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
	}
	else {
		//残弾数を表示する
		m_font.Draw(bullet, { -50.0f,-300.0f }, { 560.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
		//プレイヤーのHPを表示する
		m_font.Draw(HP, { -610.0f,-300.0f }, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
		//プレイヤーの所持グレネードの数を表示する
		m_font.Draw(grenade, { -230.0f,-300.0f }, { 50.0f,50.0f,50.0f,1.0f }, 0.0f, 1.0f);
	}
	switch (m_gameMode)
	{
	case enGame_DM:
		switch (m_playerNo)
		{
		case 0:
			m_font.Draw(P1Kills, { -630.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			m_font.Draw(P2Kills, { -500.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3Kills, { -240.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4Kills, { -110.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			break;
		case 1:
			m_font.Draw(P1Kills, { -630.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			m_font.Draw(P2Kills, { -500.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3Kills, { -240.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4Kills, { -110.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			break;
		case 2:
			m_font.Draw(P1Kills, { -630.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			m_font.Draw(P2Kills, { -500.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3Kills, { -240.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4Kills, { -110.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			break;
		case 3:
			m_font.Draw(P1Kills, { -630.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			m_font.Draw(P2Kills, { -500.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3Kills, { -240.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4Kills, { -110.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);
			break;
		}
		break;
	case enGame_CTF:
		switch (m_playerNo)
		{
		case 0:
			m_font.Draw(P1CaptureTime, { -610.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			m_font.Draw(P2CaptureTime, { -480.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3CaptureTime, { -260.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4CaptureTime, { -130.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			break;
		case 1:
			m_font.Draw(P1CaptureTime, { -610.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			m_font.Draw(P2CaptureTime, { -480.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3CaptureTime, { -260.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4CaptureTime, { -130.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			break;
		case 2:
			m_font.Draw(P1CaptureTime, { -610.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			m_font.Draw(P2CaptureTime, { -480.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3CaptureTime, { -260.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4CaptureTime, { -130.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			break;
		case 3:
			m_font.Draw(P1CaptureTime, { -610.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			m_font.Draw(P2CaptureTime, { -480.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayer4)
			m_font.Draw(P3CaptureTime, { -260.0f,360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			if (PLAYERS >= enPlayerNum)
			m_font.Draw(P4CaptureTime, { -130.0f,360.0f }, { 255.0f,0.0f,0.0f,1.0f }, 0.0f, 0.4f);
			break;
		}
		break;
	}

	m_font.EndDraw();

	if (m_damegeflagcount <= 0)
	{
		m_damegeflag = false;
	}
}