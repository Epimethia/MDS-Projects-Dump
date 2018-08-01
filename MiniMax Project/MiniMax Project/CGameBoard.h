#pragma once
/*
Name:			CGameBoard.h
Author:			James Devenport
Description:	User defined CGameBoard object and related
*/
#include <iostream>
#include <conio.h>
#include <vector>

/*

*/
class CGameBoard {
public:
	CGameBoard();
	~CGameBoard();
	void PrintBoard();
	bool InsertBoard(int _Index, char _Player);
	bool AiInsertBoard(int _Index, char _Player);
	bool ResetBoardVal(int _Index);
	const char GetBoardVal(int _Index) { return cBoard[_Index]; };
	const bool CheckWin(char _Player);
	const bool CheckTie();

private:
	//A character array to represent the board
	char cBoard[9];
};