#pragma once
#include <algorithm>
#include "CGameBoard.h"
static int numBreaks = 0;
struct sMove {
	//Move Structure
	sMove() { 
		moveIndex = 0; 
		moveScore = 0;
	};
	sMove(int Score) : moveScore(Score) {};
	int moveIndex = 0;
	int moveScore = 0;
	
};

class CAiController {
public:
	CAiController();
	~CAiController();

	void PerformBestMove(CGameBoard& _Board);

private:
	sMove MiniMaxFunc(CGameBoard& _Board, char _CurrentPlayer, int ParentAlpha, int ParentBeta);
};