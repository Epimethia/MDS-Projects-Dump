#include "Debug.h"
#include "game.h"
#include "backbuffer.h"
#include <Windows.h>

CDebug* CDebug::s_pDebug = 0;

CDebug::CDebug()
{
}


CDebug::~CDebug()
{
}

CDebug & CDebug::GetInstance()
{
	if (s_pDebug == 0)
	{
		s_pDebug = new CDebug();
	}

	return (*s_pDebug);
}

void CDebug::DestroyInstance()
{
	delete s_pDebug;
	s_pDebug = 0;
}

void CDebug::Draw()
{
	SetBkMode(CGame::GetInstance().GetBackBuffer()->GetBFDC(), TRANSPARENT);
	SetTextColor(CGame::GetInstance().GetBackBuffer()->GetBFDC(), RGB(255, 255, 255));
	int distanceFromBottom = static_cast<int>(Stringtext.size() * 20);
	int line = 0;
	for (std::vector<std::string>::iterator it = Stringtext.begin(); it != Stringtext.end(); ++it)
	{
		TextOutA(CGame::GetInstance().GetBackBuffer()->GetBFDC(), 10, 550 - distanceFromBottom + line * 20, Stringtext[line].c_str(), static_cast<int>(Stringtext[line].size()));
		line++;
	}
}

void CDebug::SetDebugText(int Line, std::string _text)
{
	while (Stringtext.size() < Line + 1)
	{
		Stringtext.push_back(" ");
	}
	Stringtext[Line] = _text;
}