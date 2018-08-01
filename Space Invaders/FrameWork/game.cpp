//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes
#include <ctime>

// Local Includes
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"
#include "sprite.h"
#include "Debug.h"



// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

//Creating the player ship
// Static Function Prototypes

// Implementation

CGame::CGame()
	: m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
	, m_pPlayer(0)
	, m_pBullet(0)
	, m_pFPSCounter(0)
	, m_pAlien(0)
{

}

CGame::~CGame() {
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBullet;
	m_pBullet = nullptr;

	delete m_pAlienBullet;
	m_pAlienBullet = nullptr;

	delete m_pFPSCounter;
	m_pFPSCounter = nullptr;

}

bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight) {
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	srand(unsigned int(time(NULL)));

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pPlayer = new CSprite();
	VALIDATE(m_pPlayer->Initialise(IDB_BITMAP1, IDB_BITMAP2));
	m_pPlayer->SetXPos(426);
	m_pPlayer->SetYPos(690);
	
	m_pAlienBullet = nullptr;
	LoadAlienColumns();
	RightMostColumn = 10;
	LeftMostColumn = 0;
	CDebug::GetInstance();

	m_pFPSCounter = new CFPSCounter;
	VALIDATE(m_pFPSCounter->Initialise());

	ShowCursor(true);//Change to false
	return (true);
}

void CGame::TranslateDown() {
	for (int i = 0; i < 11; ++i) {
		if (!AlienColumns[i].empty()) {
			for (std::vector<CSprite*>::iterator it = AlienColumns[i].begin(); it != AlienColumns[i].end(); ++it) {
				(*it)->SetYPos((*it)->GetY() + 32.0f);
			}
		}
	}

}

void CGame::CheckMovement() {
	if (MoveDown) {
		MoveDown = false;
		return;
	}
	if ((AlienColumns[LeftMostColumn].back()->GetX() <= 64) || (AlienColumns[RightMostColumn].back()->GetX() >= 792)) {
		AlienMoveSpeed *= -1;
		MoveDown = true;
	}
}

void CGame::ProcessAlienMovement(float _fDeltaTick) {
	if (MoveDelay >= MoveDelayLimit) {
		if (MoveDown) {
			TranslateDown();
		}
		else {
			for (int i = 0; i < 11; ++i) {
				if (!AlienColumns[i].empty()) {
					for (std::vector<CSprite*>::iterator it = AlienColumns[i].begin(); it != AlienColumns[i].end(); ++it) {
						(*it)->SetXPos((*it)->GetX() + AlienMoveSpeed);
					}
				}
			}
		}
		CheckMovement();
		MoveDelay = 0.0f;
	}
	else {
		MoveDelay += _fDeltaTick;
	}
}

void CGame::CheckColumns() {
	//Running a check for the left most valid column
	for (int i = 0; i < 10; ++i) {
		if (AlienColumns[i].empty()) {
			LeftMostColumn = i + 1;
		}
		else {
			break;
		}
	}
	for (int i = 10; i > 0; --i) {
		if (AlienColumns[i].empty()) {
			RightMostColumn = i - 1;
		}
		else {
			break;
		}
	}

}

void CGame::LoadAlienColumns() {
	int HSeparation = 48;
	int VSeparation = 40;
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 5; ++j) {
			m_pAlien = new CSprite();
			m_pAlien->Initialise(IDB_BITMAP5, IDB_BITMAP6);
			m_pAlien->SetXPos((HSeparation * i) + m_pAlien->GetWidth() / 2 + 96.0f);
			m_pAlien->SetYPos((VSeparation * j) + m_pAlien->GetHeight() / 2 + 48.0f);
			AlienColumns[i].push_back(m_pAlien);
			m_pAlien = nullptr;
		}
	}
}

void CGame::DrawAlienColumn() {
	for (int i = 0; i < 11; ++i) {
		for (std::vector<CSprite*>::iterator it = AlienColumns[i].begin(); it != AlienColumns[i].end(); ++it) {
			if (*it != nullptr) {
				(*it)->Draw();
			}
			
		}
	}
	
}

void CGame::Draw() {
	m_pBackBuffer->Clear();
	m_pPlayer->Draw();
	if (m_pBullet != nullptr){
		m_pBullet->Draw();
	}
	if (m_pAlienBullet != nullptr) {
		m_pAlienBullet->Draw();
	}

	DrawAlienColumn();

	//Debug Text
	CDebug::GetInstance().Draw();
	DrawFPS();
    m_pBackBuffer->Present();
}

void CGame::ProcessPlayer(float _fDeltaTick) {
	if (GetAsyncKeyState(VK_SPACE) && m_pBullet == nullptr) {
		//If Spacebar is pressed, create a new bullet
		m_pBullet = new CSprite;
		m_pBullet->Initialise(IDB_BITMAP3, IDB_BITMAP4);
		m_pBullet->SetYPos(m_pPlayer->GetY() - 10.0f);
		m_pBullet->SetXPos(m_pPlayer->GetX());
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		//If Moving left
		if (m_pPlayer->GetX() < 50) {
			m_pPlayer->SetXPos(50);
		}
		else {
			m_pPlayer->SetXPos(m_pPlayer->GetX() - (PlayerMoveSpeed * _fDeltaTick));
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		//If Moving right
		if (m_pPlayer->GetX() > 850) {
			m_pPlayer->SetXPos(850);
		}
		else {
			m_pPlayer->SetXPos(m_pPlayer->GetX() + (PlayerMoveSpeed * _fDeltaTick));
		}
	}
}

bool CGame::CheckAlienCollision(int _iColumn) {
	if (AlienColumns[_iColumn].empty()) {
		return false;
	}
	if (m_pBullet == nullptr || AlienColumns[_iColumn].empty()) {	//If there is no bullet or the column being checked is empty
		return false;	//Returns no collision
	}
	else {
		for (std::vector<CSprite*>::iterator it = AlienColumns[_iColumn].begin(); it != AlienColumns[_iColumn].end();it++) {
			int iBottom = static_cast<int>((*it)->GetY() + (*it)->GetHeight() / 2);
			int iLeft = static_cast<int>((*it)->GetX() - (*it)->GetWidth() / 2);
			int iRight = static_cast<int>(iLeft + (*it)->GetWidth());
			int iBulletXPos = static_cast<int>(m_pBullet->GetX());
			int iBulletYPos = static_cast<int>(m_pBullet->GetY());

			if ((*it) != nullptr && iBulletYPos <= iBottom && iBulletXPos >= iLeft && iBulletXPos <= iRight) {
				AlienColumns[_iColumn].erase(it);
				delete m_pBullet;
				m_pBullet = nullptr;
				return true;
			}
		}
	}
	return false;
}

void CGame::ProcessBullet(float _fDeltaTick) {
	for (int i = 0; i < 11; ++i) {
		//Checks through every column for a collision
		if (CheckAlienCollision(i)) {
			//If there is a collision, return
			return;
		}
	}

	if (m_pBullet != nullptr && (m_pBullet->GetY() < 20)) {
		delete m_pBullet;
		m_pBullet = nullptr;
		return;
	}

	else if (m_pBullet != nullptr) {
		m_pBullet->SetYPos(m_pBullet->GetY() - PlayerBulletSpeed * _fDeltaTick);
		return;
	}

}

void CGame::ProcessAlienShoot() {
	if (m_pAlienBullet != nullptr) {
		return;
	}
	int ShootCol = rand() % 11;
	if (AlienColumns[ShootCol].empty()) {
		return;
	}
	int Shoot = rand() % 10;
	if (Shoot == 2) {
		m_pAlienBullet = new CSprite;
		m_pAlienBullet->Initialise(IDB_BITMAP3, IDB_BITMAP4);
		if (!AlienColumns[ShootCol].empty()) {
			m_pAlienBullet->SetXPos(AlienColumns[ShootCol].back()->GetX());
			m_pAlienBullet->SetYPos(AlienColumns[ShootCol].back()->GetY() + 24.0f);
		}
	}
}

void CGame::ProcessAlienBullet(float _fDeltaTick) {
	if (m_pAlienBullet == nullptr) {
		return;
	}
	if ((m_pAlienBullet->GetX() >= m_pPlayer->GetX() - 24) && m_pAlienBullet->GetX() <= m_pPlayer->GetX() + 24 && m_pAlienBullet->GetY() >= m_pPlayer->GetY()) {
		delete m_pAlienBullet;
		m_pAlienBullet = nullptr;
		--PlayerHealth;

	}
	else if ((m_pAlienBullet->GetY() > 790)) {
		delete m_pAlienBullet;
		m_pAlienBullet = nullptr;
		return;
	}

	else {
		m_pAlienBullet->SetYPos(m_pAlienBullet->GetY() + PlayerBulletSpeed * _fDeltaTick);
		return;
	}

}

bool CGame::CheckLose() {
	for (int i = 0; i < 11; ++i) {
		for (std::vector<CSprite*>::iterator it = AlienColumns[i].begin(); it != AlienColumns[i].end(); ++it) {
			if ((*it) != nullptr && (*it)->GetY() >= 600){
				return true;
			}
		}
	}
	/*if (PlayerHealth <= 0) {
		return true;
	}*/
	return false;
}

void CGame::Process(float _fDeltaTick) {
	if (!CheckLose()) {
		//Process Player Movement
		ProcessPlayer(_fDeltaTick);
		ProcessAlienMovement(_fDeltaTick);
		ProcessAlienShoot();
		//Process Bullet Movement
		ProcessBullet(_fDeltaTick);
		ProcessAlienBullet(_fDeltaTick);
		CheckColumns();
		m_pFPSCounter->CountFramesPerSecond(_fDeltaTick);
	}
	else {
		//end game
	}
	
}

void CGame::ExecuteOneFrame() {
    float fDT = m_pClock->GetDeltaTick();
    Process(fDT);
	m_pClock->Process();
	m_pFPSCounter->CountFramesPerSecond(fDT);
    Draw();
}

CGame& CGame::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}

void CGame::DestroyInstance() {
    delete s_pGame;
    s_pGame = 0;
}

CBackBuffer* CGame::GetBackBuffer() {
    return (m_pBackBuffer);
}

HINSTANCE CGame::GetAppInstance() {
    return (m_hApplicationInstance);
}

HWND CGame::GetWindow() {
    return (m_hMainWindow);
}

void CGame::DrawFPS() {
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	SetTextColor(hdc, RGB(255, 255, 255));
	m_pFPSCounter->DrawFPSText(hdc, 0, 0); 
}