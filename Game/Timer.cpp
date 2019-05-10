#include "stdafx.h"
#include "Timer.h"
#include "Game.h"


Timer::Timer()
{	
	m_font = new Font;
}

Timer::~Timer()
{
}

void Timer::Draw()
{
	float restTime = g_game->GetRestTime();

	wchar_t time[256];
	
	swprintf(time, L"Žc‚èŽžŠÔ %.f•b",restTime);

	m_font->BeginDraw();
	
	m_font->Draw(time, { -640.0f, 360.0f }, { 0.0f,0.0f,0.0f,1.0f }, 0.0f, 0.5f);

	m_font->EndDraw();
}