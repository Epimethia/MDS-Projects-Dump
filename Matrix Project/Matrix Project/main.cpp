#include <iostream>

#include "cMatrix.h"

using namespace std;

void PrintMatrix(cMatrix* _Matrix) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			cout << "[" << _Matrix->GetElement(y, x) << "]";
		};
		cout << endl;
	};
	cout << "-----------" << endl;
	cout << endl;
}

int main() {

	cMatrix* MatrixA = new cMatrix;
	cMatrix* MatrixB = new cMatrix;

	cout << "Inverse is: " << endl;
	MatrixA->Inverse(MatrixA, MatrixB);

	PrintMatrix(MatrixB);

	int iTemp;
	cin >> iTemp;
	return 0;
}