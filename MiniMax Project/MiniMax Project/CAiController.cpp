#include "CAiController.h"

/*
Parameters:		None
Return Type:	None
Description:	Default Constructor for the AIController Object
*/
CAiController::CAiController(){
	//Constructor
}

/*
Parameters:		None
Return Type:	None
Description:	Default Destructor for the AIController Object
*/
CAiController::~CAiController() {
	//Destructor
}

/*
Parameters:		CGameBoard& _Board
Return Type:	None8
Description:	Performs the MiniMax algorithmn on the _Board reference parameter, to calculate the best possible move
*/
void CAiController::PerformBestMove(CGameBoard& _Board) {
	int alpha = -100000;
	int beta = 100000;

	sMove BestMove = MiniMaxFunc(_Board, 'O', alpha, beta);
	_Board.AiInsertBoard (BestMove.moveIndex, 'O');


}

/*
Parameters:		CGameBoard& _Board, char _CurrentPlayer, int Alpha, int Beta
Return Type:	sMove
Description:	MiniMax Algorithmn. Recursively performs Minimax on _Board, with Alpha-Beta pruning.
				Returns a user defined sMove structure that contains the best move index and a score.
*/
sMove CAiController::MiniMaxFunc (CGameBoard & _Board, char _CurrentPlayer, int Alpha, int Beta) {
	if (_Board.CheckWin ('O')) {
		return sMove (10);
	}
	//Checking for the Human win. If it does, returns an sMove structure with a score of -10
	else if (_Board.CheckWin ('X')) {
		return sMove (-10);
	}
	//Checking for a tie. Returns a score of 0
	else if (_Board.CheckTie ()) {
		return sMove (0);
	}
	//Vector to store moves
	std::vector<sMove> MovesVect;
	//Iterating through every value of the game board 
	for (int i = 0; i < 9; ++i) {
		//If the current index of the board is empty
		if (_Board.GetBoardVal (i) == ' ') {

			//Creating a move
			sMove move;
			move.moveIndex = i;
			_Board.AiInsertBoard (i, _CurrentPlayer);

			
			//Max Function
			if (_CurrentPlayer == 'O') {
				//Local Infinity value. MAX function so value is negative infinity -> Attempting to find the highest value
				int v = -100000;

				//Recursively calling the function, but the MIN version this time, for the human player
				move.moveScore = MiniMaxFunc (_Board, 'X', Alpha, Beta).moveScore;

				//Pushes the move onto the MovesVect
				MovesVect.push_back (move);
				//Resets the move that was place, to not interfere with future recursion
				_Board.ResetBoardVal (i);

				//Pruning
				//Setting the alpha value to the maximum value of its children
				v = std::max (v, move.moveScore);
				Alpha = std::max (v, Alpha);

				//if the alpha of this node is higher than the beta, which is the passed up value from its child
				//then the rest of the recursion is ignored, as any grandchild node will not surpass that of the child node
				//thus, we can cut the recursion short to save processing time
				if (Alpha >= Beta) {
					break;
				}
			}

			//Min Function
			else {
				//Local Positive infinity, as we are trying to find the smallest value
				int v = 100000;

				//Calling Max Func on AI
				move.moveScore = MiniMaxFunc (_Board, 'O', Alpha, Beta).moveScore;

				//Pushes the move onto the MovesVect
				MovesVect.push_back (move);
				//Resets the move that was place, to not interfere with future recursion
				_Board.ResetBoardVal (i);

				//Setting up the Beta to be the lowest value out of all of this node's children
				v = std::min (v, move.moveScore);
				Beta = std::min (v, Beta);

				//We are finding the minimum value of this node. However, because we know that the next node up is a max node
				//with a value of alpha (which is passed down to this node), if beta is smaller than alpha, the algorithm will
				//never return another value higher than beta (as the function finds values LOWER than beta). Thus, we can cut
				//the rest of the children/recursion and save processing time
				if (Alpha >= Beta) {
					//prune
					break;
				}
				
			}
		}
	}

	//Iterating through the moves vector to find the best move
	int MoveIndex = 0;

	//The AI player is attempting to get the best score
	if (_CurrentPlayer == 'O') {
		int bestScore = -1000000;
		for (unsigned int i = 0; i < MovesVect.size (); ++i) {
			if (MovesVect[i].moveScore > bestScore) {
				//Stores the selected move in the MoveVect
				MoveIndex = i;
				bestScore = MovesVect[i].moveScore;
			}
		}
	}

	//If the AI is simulating the Player's turn, it is trying to get the lowest score
	if (_CurrentPlayer == 'X') {
		int bestScore = 1000000;
		for (unsigned int i = 0; i < MovesVect.size (); ++i) {
			if (MovesVect[i].moveScore < bestScore) {
				//Stores the selected move in the MoveVect
				MoveIndex = i;
				bestScore = MovesVect[i].moveScore;
			}
		}
	}
	

	return MovesVect[MoveIndex];
} 

