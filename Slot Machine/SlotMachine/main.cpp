#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>

using namespace std;

//Setting functions
int multipliers(int _iNum1, int  _iNum2, int  _iNum3);
int checkOption(int _iCheckOption);
int checkBet(int _iCheckBet);
int title();
void winnings(int _winnings);



//Setting global variables
int iChips = 2000;
bool betValid = false;

int main() {
	while (true) {
		//Asking the player to input an option
		int iInput = title();

		//If the player presses the "1" key on the keyboard
		if (iInput == 49) {
			int iBet = 0;
			while (iBet == 0) {
				iBet = checkBet(iBet);
			}

			//Removing the chips from the player's "wallet"
			iChips -= iBet;

			//initializing the values
			srand(time(NULL));
			int iNum1;
			int iNum2;
			int iNum3;

			//Randoming values for each number
			iNum1 = rand() % 6 + 2;
			iNum2 = rand() % 6 + 2;
			iNum3 = rand() % 6 + 2;

			cout << endl;
			cout << setw(53) << "	     [" << iNum1 << "] ";
			cout << "[" << iNum2 << "] ";
			cout << "[" << iNum3 << "] ";
			cout << endl;

			//Calculating winnings
			int iWinnings;
			iWinnings = ((multipliers(iNum1, iNum2, iNum3)) * (iBet));
			winnings(iWinnings);
			iChips += iWinnings;
		}

		//If the player presses the "2" key on the keyboard
		else if (iInput == 50) {
			cout << "You have chosen to to quit the game. See you next time!" << endl;
			break;
		}

		//If the player presses the "3" key on the keyboard
		else if (iInput == 51) {
			cout << "No Credits here :'(" << endl;
			cout << endl;
		} else {
			cout << "Please enter a valid option" << endl;
		};
	};

	//Making sure the console window does not close too early
	_getch();

}

//Function for the title
int title() {
	int iTitle;
	cout.setf(ios::right);
	cout << setfill(' ') << setw(66) << "|Player's Chips: " << iChips << "|" << endl;
	cout << setfill(' ') << setw(49) << " " << setfill('-') << setw(22) << "-" << endl;
	cout << setfill(' ') << setw(71) << "|1|    Play Slots    |" << endl;
	cout << setfill(' ') << setw(49) << " " << setfill('-') << setw(22) << "-" << endl;
	cout << setfill(' ') << setw(71) << "|2| Quit Slot Machine|" << endl;
	cout << setfill(' ') << setw(49) << " " << setfill('-') << setw(22) << "-" << endl;
	cout << setfill(' ') << setw(71) << "|3|     Credits      |" << endl;
	cout << setfill(' ') << setw(49) << " " << setfill('-') << setw(22) << "-" << endl;
	iTitle = _getch();
	checkOption(iTitle);
	return(iTitle);
}

//function for checking if menu input is a valid option
int checkOption(int _iCheck) {
	//Since _getch() reads the characters entered as ASCII, this
	//function converts the recieved ASCII into a more recognizable
	//form, i.e. "1", "2", and "3"

	//If the character entered is the character "1" (49 in ASCII)
	if (_iCheck == 49) return (1);

	//If the character entered is the character "1" (49 in ASCII)
	else if (_iCheck == 50) return (2);

	//If the character entered is the character "1" (49 in ASCII)
	else if (_iCheck == 51) return (3);

	//If the character entered is not one of those specified above
	else return(4); 
}

//Function to check the player's bet is valid
int checkBet(int _iCheckBet) {
	//Asks the player how much they would like to bet
	cout << endl;
	cout << setfill(' ') << setw(76) << "   How much would you like to bet?: ";

	//Continues to prompt the player to enter
	//a valid number if a non valid number is entered
	while (!(cin >> _iCheckBet)) {
		cin.clear();
		cin.ignore(999, '\n');
		cout << setfill(' ') << setw(71) << "You haven't entered a valid number! Please try again..." << endl;
		cout << endl;
	}

	//This checks if you have bet a negative value, or 0
	if (int(_iCheckBet <= 0)) {
		cout << setfill(' ') << setw(71) << "You gotta bet more than that!" << endl;
		_iCheckBet = 0;
	}

	//This checks if you have bet more than you have
	else if (int(_iCheckBet >= iChips)) {
		cout << setfill(' ') << setw(71) << "You're betting more than you have! Bet lower!" << endl;
		_iCheckBet = 0;
	}

	//This returns the result of the checks if it passes both the negative/0 test
	//and the over-bet check
	return (_iCheckBet);
}

//Checking if the player won anything, and printing out a congratulatory message if so.
void winnings(int _winnings) {

	//If the user won something
	if (_winnings > 0) {
		cout << endl;
		cout << setfill(' ') << setw(41) << " " << "   Congratulations, you won " << _winnings << " chips!" << endl;
		cout << setfill(' ') << setw(41) << " " << " Press any key to return to the main menu" << endl;
		_getch();
		for (int i = 0; i < 3; ++i) {
			cout << setfill(' ') << setw(40) << " " << setfill('#') << setw(40) << "#" << endl;
		}
	}

	//If the user did not win anything
	else {
		cout << endl;
		cout << setfill(' ') << setw(41) << " " << "    Sorry, you didn't win anything." << endl;
		cout << setfill(' ') << setw(44) << " " << "	 Better luck next time" << endl;
		cout << setfill(' ') << setw(39) << " " << " Press any key to return to the main menu" << endl << endl;
		_getch();
		for (int i = 0; i < 3; ++i) {
			cout << setfill(' ') << setw(40) << " " << setfill('#') << setw(40) << "#" << endl;
		}
		cout << endl << endl;
	}

	//Returns from the loop
	return;
}

//Checking the player's winnings
int multipliers(int _iNum1, int  _iNum2, int  _iNum3) {
	//Declaring some local variables
	int iMultiplier;

	//If the player gets 3 7s, he wins back 10x his bet
	if ((_iNum1 == 7) && (_iNum2 == 7) && (_iNum3 == 7)) {
		iMultiplier = 10;
	}

	//If the player gets 3 of the same number, he wins back 5x his bet
	else if ((_iNum1 == _iNum2) && (_iNum1 == _iNum3)) {
		iMultiplier = 5;
	}

	//If the player gets 2 the same, he wins back 3x his bet
	else if ((_iNum1 == _iNum2) || (_iNum1 == _iNum3) || (_iNum2 == _iNum3)) {
		iMultiplier = 3;
	}

	//Otherwise he loses all that he bet, i.e. he gets no winnings
	else {
		iMultiplier = 0;
	}
	return (iMultiplier);
}