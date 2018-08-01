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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes
#include "clock.h"
#include "FPSCounter.h"

#define Column std::vector<CSprite*>

class CBackBuffer;
class CSprite;

class CGame {
    // Member Functions
public:
    ~CGame();

    bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	void TranslateDown();

	void CheckMovement();

	void ProcessAlienMovement(float _fDeltaTick);

	void CheckColumns();

	void LoadAlienColumns();
	void DrawAlienColumn();

    void Draw();
	void ProcessPlayer(float _fDeltaTick);
	bool CheckAlienCollision(int _iColumn);
	void ProcessBullet(float _fDeltaTick);
	void ProcessAlienShoot();
	void ProcessAlienBullet(float _fDeltaTick);
	bool CheckLose();
	void Process(float _fDeltaTick);
	void DrawFPS();
	void ExecuteOneFrame();

    CBackBuffer* GetBackBuffer();
    HINSTANCE GetAppInstance();
    HWND GetWindow();

    // Singleton Methods
    static CGame& GetInstance();
    static void DestroyInstance();

private:
    CGame();
    CGame(const CGame& _kr);
    CGame& operator= (const CGame& _kr);


protected:
    CClock* m_pClock;
    CBackBuffer* m_pBackBuffer;
	CFPSCounter* m_pFPSCounter;
	
	//Player
	CSprite* m_pPlayer;
	CSprite* m_pBullet;
	int PlayerHealth = 3;
	float PlayerMoveSpeed = 100.0f;
	float PlayerBulletSpeed = 300.0f;

	//Alien
	CSprite* m_pAlien;
	CSprite* m_pAlienBullet;
	std::vector<CSprite*> AlienBulletVect;
	Column AlienColumns[11];
	bool MoveRight = true;
	bool MoveDown = false;
	int AlienMoveSpeed = 32;
	int AlienBulletSpeed = 8;
	float MoveDelay = 0.0f;
	float MoveDelayLimit = 1.0f;
	int RightMostColumn = 0;
	int LeftMostColumn = 0;


    //Application data
    HINSTANCE m_hApplicationInstance;
    HWND m_hMainWindow;

    // Singleton Instance
    static CGame* s_pGame;
	
};

#endif    // __GAME_H__


