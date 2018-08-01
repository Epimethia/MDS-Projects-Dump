#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

//Functions
void GoToXY(int _iX, int _iY);
void DisplayCircle(float _fRadius, int _fAngleCount, int _iCentreX, int _iCentreY);

int main()
{
	int iX;
	int iY;
	int iRadius;
	int iAngleCount = 360;
	
	//Asking for the Centre Coordinate
	cout << "Please enter the coordinates of the centre." << endl;
	cout << "Please enter the x coordinate:";
	cin >> iX;
	cout << "Please enter the y coordinate:";
	cin >> iY;
	

	//Asking for the radii
	cout << "Please enter the radii of the circle:" << endl;
	cin >> iRadius;

	DisplayCircle(iRadius, iAngleCount, iX, iY);

	getch();
}

//Displaying the circle (placing X on the radius)
void DisplayCircle(float _fRadius, int _fAngleCount, int _iCentreX, int _iCentreY)
{
	for (float fAngle = 0.017453f;
		fAngle < (2.0f * 3.14596f);
		fAngle += (2.0f * 3.14596f) / _fAngleCount)
	{
		float fX = _fRadius * cosf(fAngle); 
		float fY = _fRadius * sinf(fAngle);
		GoToXY(fX + _iCentreX, fY + _iCentreY);
		cout << "X";
	}
}

//Centering the circle (placing the cursor at the centre of the screen, where
//it can then draw the circle around itself.
void GoToXY(int _iX, int _iY)
{
	COORD point;
	point.X = _iX;
	point.Y = _iY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}