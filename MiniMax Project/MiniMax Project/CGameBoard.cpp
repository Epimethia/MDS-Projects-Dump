#include "CGameBoard.h"

/*
Parameters:		None
Return Type:	None
Description:	CGameBoard Constructor. Fills the cBoard array with empty spaces
*/
CGameBoard::CGameBoard() {
	for (int i = 0; i < 9; ++i) cBoard[i] = ' ';
}

/*
Parameters:		None
Return Type:	None
Description:	CGameBoard Destructor
*/
CGameBoard::~CGameBoard() {
	//Destructor
}

/*
Parameters:		None
Return Type:	None
Description:	Prints the cBoard array into a tic-tac-toe format
*/
void CGameBoard::PrintBoard() {
	//draw board code
	std::cout << "  -----------" << std::endl;
	for (int i = 0; i < 9; ++i) {
		std::cout << " | " << cBoard[i];
		if (i == 2 || i == 5 || i == 8) {
			std::cout << " |" << std::endl;
			std::cout << "  -----------" << std::endl;
		}
	}
}

/*
Parameters:		int _Index, char _CurrentPlayer
Return Type:	Bool
Description:	Inserts the given _CurrentPLayer into the cBoard array at the given _Index.
				Returns true if a valid move is made. Returns false (and does not insert) if invalid.
*/
bool CGameBoard::InsertBoard(int _Index, char _CurrentPlayer) {
	//If the current index is not taken up, place the player
	if (cBoard[_Index - 1] == ' ') {
		cBoard[_Index - 1] = _CurrentPlayer;
		return true;
	} else return false;
}

/*
Parameters:		int _Index, char _Player
Return Type:	Bool
Description:	Inserts an AI move into the cBoard array. different from player input due to _getch() interactions
				Returns true if valid move is made. Returns false (and does not insert) if invalid
*/
bool CGameBoard::AiInsertBoard(int _Index, char _Player) {
	//If the current index is not taken up, place the player
	if (cBoard[_Index] == ' ') {
		cBoard[_Index] = _Player;
		return true;
	} else return false;
}

/*
Parameters:		int _Index
Return Type:	Bool
Description:	Resets the index to empty (' ')
				Returns true if successful. 
*/
bool CGameBoard::ResetBoardVal(int _Index) {
	if (cBoard[_Index] != ' ') {
		cBoard[_Index] = ' ';
		return true;
	} else return false;
}


/*
Parameters:		char _Player
Return Type:	Bool
Description:	Checks if the given _Player has won the game
				Returns true if a winning condition is reached, false if not.
*/
const bool CGameBoard::CheckWin(char _Player) {
	struct Row {
		char A;
		char B;
		char C;
	};

	//Horizontal win conditions
	std::vector<Row> WinningRows;
	Row Row0 = { cBoard[0], cBoard[1], cBoard[2] };
	WinningRows.push_back(Row0);
	Row Row1 = { cBoard[3], cBoard[4], cBoard[5] };
	WinningRows.push_back(Row1);
	Row Row2 = { cBoard[6], cBoard[7], cBoard[8] };
	WinningRows.push_back(Row2);

	//Vertical win conditions
	Row Row3 = { cBoard[0], cBoard[3], cBoard[6] };
	WinningRows.push_back(Row3);
	Row Row4 = { cBoard[1], cBoard[4], cBoard[7] };
	WinningRows.push_back(Row4);
	Row Row5 = { cBoard[2], cBoard[5], cBoard[8] };
	WinningRows.push_back(Row5);

	//Diagonal win conditions
	Row Row6 = { cBoard[0], cBoard[4], cBoard[8] };
	WinningRows.push_back(Row6);
	Row Row7 = { cBoard[2], cBoard[4], cBoard[6] };
	WinningRows.push_back(Row7);

	for (auto it = WinningRows.begin(); it != WinningRows.end(); ++it) {
		//If all 3 values match and are the specified player's value, return a win
		if ((it->A == it->B) && (it->B == it->C) && it->C == _Player) return true;
	} return false;
}

/*
Parameters:		None
Return Type:	Bool
Description:	Checks if the entire cBoard array is filled (and thus, there is a tie)
				Returns false if an empty spot is found. Otherwise returns true.
*/
const bool CGameBoard::CheckTie() {
	//Iterate through entire board
	for (int i = 0; i < 9; ++i) {
		//If any slot on the board is empty
		if (cBoard[i] == ' ') return false;
	}
	//If the for loop runs through that means the board is full and there is a tie
	return true;
}


