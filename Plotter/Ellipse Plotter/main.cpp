#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

void DisplayEllipse(float _fHorizontalAxis, float _fVerticlaAxis, float _fAngleCount, int _iCentreX, int _iCentreY);
void DisplayPoint(int _iX, int _iY);

int main()
{
	int iX;
	int iY;
	float iHRadius;
	float iVRadius;
	int iAngleCount = 360;

	cout << "Please enter the coordinates of the centre" << endl;
	
	cout << "Please enter the X coordinate:";
	cin >> iX;

	cout << "Please enter the Y coordinate:";
	cin >> iY;

	cout << "Please enter the horizontal radius of the ellipse:";
	cin >> iHRadius;

	cout << "Please enter the vertical radius of the ellipse";
	cin >> iVRadius;

	DisplayEllipse(iHRadius, iVRadius, iAngleCount, iX, iY);

	getch();

}


void DisplayEllipse(float _fHorizontalAxis, float _fVerticalAxis, float _fAngleCount, int _iCentreX, int _iCentreY)
{
	for (float fAngle = 0.017453f; fAngle < (2.0 * 3.14596f); fAngle += (2.0 * 3.14596f) / _fAngleCount)
	{
		float fX = _fHorizontalAxis *cos(fAngle);
		float fY = _fVerticalAxis * sin(fAngle);
		DisplayPoint(fX + _iCentreX, fY + _iCentreY);
		cout << '#';
	}
}

void DisplayPoint(int _iX, int _iY)
{
	COORD point;
	point.X = _iX;
	point.Y = _iY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}