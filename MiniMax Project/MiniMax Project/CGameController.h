#pragma once
#include <Windows.h>


#include "CAiController.h"

enum GameState {
	PVP,
	PVE
};

class CGameController {
public:
	void Init();
	bool GameLoop();
	
	//GameMode Moves
	void doHumanMove(char _CurrentPlayer);
	void doAiMove();

	//Misc
	void ClearScreen();

private:
	CGameBoard Board;
	GameState State;
	CAiController AIPlayer;
	char CurrentPlayer;
};