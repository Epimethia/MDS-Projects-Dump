#include "CGameController.h"

/*
Parameters:		None
Return Type:	None
Description:	Initializes the game controller. Prompts user for game mode (PvP or PvAI)
*/
void CGameController::Init() {
	//Initializing the game
	CurrentPlayer = 'X';
	std::cout << "Please Choose GameMode:\n[1]Player vs Player\n[2]Player vs AI";
	
	//Getting user input using _getch()
	int input = 0;
	while (input != 1 && input != 2) {
		input = _getch() - '0';
	}

	//Initializing Game Type
	if (input == 1) State = PVP;
	else if (input == 2) State = PVE;
}

/*
Parameters:		None
Return Type:	Bool
Description:	Processes the main game logic loop
				Returns true if a win condition is reached in conjunction with CGameBoard::CheckWin()
*/
bool CGameController::GameLoop(){
	if (State == PVP) {
		//Check if a player has won
		if (Board.CheckWin(CurrentPlayer)) {
			std::cout << "Player " << CurrentPlayer << " won!\n";
			return true;
		}
		//Checking for a tie
		if (Board.CheckTie()) {
			std::cout << "Game is a tie!";
			return true;
		}
		ClearScreen();
		//Do PVP Code
		doHumanMove(CurrentPlayer);
	}

	else if (State == PVE) {
		//Do PVE Code
		//Check if the player has won
		if (Board.CheckWin('X')) {
			std::cout << "The player has won!\n";
			return true;
		}
		if (Board.CheckWin('O')) {
			std::cout << "The AI has won!\n";
			return true;
		}
		//Checking for a tie
		if (Board.CheckTie()) {
			std::cout << "Game is a tie!";
			return true;
		}


		CurrentPlayer = 'X';
		//Get the human move first
		doHumanMove(CurrentPlayer); 
		ClearScreen();
		Board.PrintBoard();

		CurrentPlayer = 'O';
		//Do the Ai Move
		doAiMove ();
		ClearScreen ();
		Board.PrintBoard ();

		
	}
	//Return false if the game has not been completed
	return false;
}

/*
Parameters:		char
Return Type:	None
Description:	Processes the logic for a human move, then swaps the player (if in PvP mode)
*/
void CGameController::doHumanMove(char _CurrentPlayer) {
	//Draw the Board
	ClearScreen();
	std::cout << "Play a move, player " << CurrentPlayer << std::endl;
	Board.PrintBoard();

	//Gets player input
	int input = 0;
	//Checks if the move is a valid one, and the space is not taken
	while (input > 9 || input < 1 || !Board.InsertBoard(input, CurrentPlayer)) {
		input = _getch() - '0';
	}

	//Inserts play into the board
	Board.InsertBoard(input, CurrentPlayer);

	//Swaps the player
	if (State == PVP) {
		if (CurrentPlayer == 'X') CurrentPlayer = 'O';
		else CurrentPlayer = 'X';
	}
}

/*
Parameters:		None
Return Type:	None
Description:	Processes the Minimax function for the AI
*/
void CGameController::doAiMove() {
	AIPlayer.PerformBestMove(Board);
}

/*
Parameters:		None
Return Type:	None
Description:	Clears the screen of all console output
*/
void CGameController::ClearScreen() {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}
