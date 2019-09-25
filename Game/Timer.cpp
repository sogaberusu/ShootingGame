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
	wchar_t time[256];

	int in = g_game->GetRestTime();
	int m, s;

	m = in / 60;
	in %= 60;

	s = in;
	
	if (s <10)
	{
		swprintf(time,L"%d:0%d\n", m, s);
	}
	else
	{
		swprintf(time, L"%d:%d\n", m, s);
	}
	
	

	m_font->BeginDraw();
	
	m_font->Draw(time, { -340.0f, 350.0f }, m_timerColorGray, 0.0f, 0.5f);

	m_font->EndDraw();
}