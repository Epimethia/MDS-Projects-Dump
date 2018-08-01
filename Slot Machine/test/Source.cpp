/*#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

string	sInput ("a");
int main()
{
	//Asks to enter a string
	cout << "please enter a string: ";
	cin >> sInput;
	cout << endl;

	//Prints out the string
	cout << sInput;
	cout << endl << endl;
	//Getting string length
	int length;
	length = sInput.length();
	cout << length << endl;

	//Iterating through every char
	for (int i = 0; i < length; ++i)
	{
		cout << sInput[i];
		if (sInput[i] > 48 && sInput[i] < 57)
		{
			cout << "		This is a number!" << endl;
		}
		else
		{
			cout << "		This is not a number!" << endl;
		}
	}
	_getch();
}*/
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

string	sInput("a");
int main()
{
	//Asks to enter a string
	cout << "please enter a string: ";
	cin >> sInput;
	cout << endl;

	//Prints out the string
	cout << sInput;
	cout << endl << endl;
	//Getting string length
	cout << sInput.length() << endl;
	int myNum = 0;
	bool isNum = true;
	//Iterating through every char
	for (int i = 0; i < sInput.length(); ++i)
	{
		cout << sInput[i];
		if (sInput[i] > 48 && sInput[i] < 57)
		{
			//If the character is a number
			cout << "		This is a number!" << endl;
		}
		else
		{
			//If the character is not a number
			cout << "		This is not a number!" << endl;
			isNum = false;
		}
	}

	if (isNum)
	{
		myNum = stoi(sInput);
	}

	cout << endl << "successful? " << myNum;
	_getch();
}