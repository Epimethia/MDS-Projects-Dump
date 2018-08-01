#include "cMatrix.h"

#define PI 3.1415926
cMatrix::cMatrix() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_fMatrix[i][j] = 0;		
		};
	};
};
cMatrix::~cMatrix() {
	//Destructor
}; 
float cMatrix::Determinant(cMatrix* _rA) {
	//Floats for the determinant
	float Det = 1.0f;
	float Multiple = 1.0f;
	float OldArray[4];
	float NewArray[4];

	for (int x = 0; x < 4; ++x) {
		if (Multiple == 0) {
			Det = 0.0f;
			return Det;
		}

		//Setting the multiplier as the leading value of the row
		Multiple = _rA->GetElement(x, x);

		//Storing original row to OldArray
		for (int i = 0; i < 4; ++i) {
			OldArray[i] = _rA->GetElement(x, i);
		}

		if (x == 3) {
			Det = _rA->GetElement(0, 0) * _rA->GetElement(1, 1) * _rA->GetElement(2, 2) * _rA->GetElement(3, 3);
			return Det;
		}

		//Making the leading element of the row 1 by looping through all remaining values of the row and dividing by the multiplier
		//Resetting the array
		for (int i = 0; i < 4; ++i) {
			NewArray[i] = 0;
		}
		for (int i = 0; i < 4; ++i) {
			_rA->SetElement(x, i, _rA->GetElement(x, i) / Multiple);

			//Storing the row into an array for later use
			NewArray[i] = _rA->GetElement(x, i);
		}

		//For loop to iterate through every row under the root row
		for (int j = 1 + x; j < 4; ++j) {

			//First Step, multiply the entire root row by the leading value of the row under
			for (int i = 0; i < 4; i++) {
				_rA->SetElement(x, i, _rA->GetElement(x, i) * _rA->GetElement(j, x));
			}

			//Subtracting the root row from the row underneath
			for (int i = 0; i < 4; ++i) {
				_rA->SetElement(j, i, _rA->GetElement(j, i) - _rA->GetElement(x, i));
			}

			//Resetting the leading row back to its original form
			for (int i = 0; i < 4; ++i) {
				_rA->SetElement(x, i, NewArray[i]);
			}
		}
		for (int i = 0; i < 4; ++i) {
			_rA->SetElement(x, i, OldArray[i]);
		}
	}
	return (0);
}
float cMatrix::GetElement(int _iX, int _iY) const {
	return (m_fMatrix[_iX][_iY]);
}
bool cMatrix::Equals(cMatrix* _rA, cMatrix* _rB) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (_rA->GetElement(x, y) != _rB->GetElement(x, y)) {
				return false;
			}
		};
	};
	return true;
}
void cMatrix::SetElement(int _iX, int _iY, float _fValue) {
	m_fMatrix[_iX][_iY] = _fValue;
};
void cMatrix::Zero(cMatrix * _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			_rResult->SetElement(y, x, 0);
		};
	};
};
void cMatrix::Identity(cMatrix * _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (y != x) {
				_rResult->SetElement(y, x, 0);
			}
			else {
				_rResult->SetElement(y, x, 1);
			}
		};
	};
};
void cMatrix::Add(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			_rResult->SetElement(x, y, (_rA->GetElement(x, y) + _rB->GetElement(x, y)));
		};
	};
}
void cMatrix::Subtract(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			_rResult->SetElement(x, y, (_rA->GetElement(x, y) - _rB->GetElement(x, y)));
		};
	};
}
void cMatrix::Multiply(float _fScalar, cMatrix* _rA, cMatrix* _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			_rResult->SetElement(x, y, (_fScalar * _rA->GetElement(x, y)));
		};
	};
}
void cMatrix::Multiply(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult) {
	float fTemp = 0.0f;
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			for (int q = 0; q < 4; ++q) {
				fTemp += _rA->GetElement(y, q) * _rB->GetElement(q, x);
			};
			_rResult->SetElement(y, x, fTemp);
			fTemp = 0;
		};
	};
}
void cMatrix::Transpose(cMatrix* _rA, cMatrix* _rResult) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			_rResult->SetElement(x, y, _rA->GetElement(y, x));
		}
	};
}
void cMatrix::Inverse(cMatrix* _rA, cMatrix* _rResult) {

	float Multiple = 1.0f;
	float NewArray[8];

	//Creating a new 8x4 array to hold both the inverse matrix and the identity
	float AugMatrix[4][8] = { { 0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f },
	{ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f }
	};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			AugMatrix[i][j] = _rA->GetElement(i, j);
		}
	}

	for (int x = 0; x < 4; ++x) {

		//Setting the multiplier as the leading value of the row
		Multiple = AugMatrix[x][x];

		//Making the leading element of the row 1 by
		//looping through all remaining values of the row and dividing by the multiplier
		//Resetting the array
		for (int i = 0; i < 8; ++i) {
			NewArray[i] = 0;
		}
		for (int i = 0; i < 8; ++i) {
			AugMatrix[x][i] = AugMatrix[x][i] / Multiple;
			//Storing the row into an array for later use
			NewArray[i] = AugMatrix[x][i];
		}

		//For loop to iterate through every row under the root row
		for (int j = 0; j < 4; ++j) {

			//First Step, multiply the entire root row by the leading value of the row under
			for (int i = 0; i < 8; i++) {
				AugMatrix[x][i] = AugMatrix[x][i] * AugMatrix[j][x];
			}

			//Subtracting the root row from the row underneath
			for (int i = 0; i < 8; ++i) {
				AugMatrix[j][i] = AugMatrix[j][i] - AugMatrix[x][i];
			}

			//Resetting the leading row back to its original form
			for (int i = 0; i < 8; ++i) {
				AugMatrix[x][i] = NewArray[i];
			}
		}
	}

	//Setting the inverse matrix into the return matrix
	for (int i = 0; i < 4; ++i) {
		for (int j = 4; j < 8; ++j) {
			float temp = AugMatrix[i][j];
			_rResult->SetElement(i, j - 4, AugMatrix[i][j]);
		}
	}
}
void cMatrix::Scale(float _fX, float _fY, float _fZ, cMatrix* _rResult) {
	_rResult->SetElement(0, 0, _fX);
	_rResult->SetElement(1, 1, _fY);
	_rResult->SetElement(2, 2, _fZ);
}
void cMatrix::Translation(float _fX, float _fY, float _fZ, cMatrix * _rResult) {
	_rResult->SetElement(0, 3, _fX);
	_rResult->SetElement(1, 3, _fY);
	_rResult->SetElement(2, 3, _fZ);
}
void cMatrix::Rotate(float _fX, float _fY, float _fZ, float _Theta, cMatrix * _rResult) {
	float Mag = sqrt(pow(_fX, 2.0f) + pow(_fY, 2.0f) + pow(_fZ, 2.0f));
	float x = _fX / Mag;
	float y = _fY / Mag;
	float z = _fZ / Mag;
	float Theta = _Theta * PI / 180;

	float A00 = (x * x * (1.0f - cos(Theta))) + cos(Theta);
	float A01 = (x * y * (1.0f - cos(Theta))) - (z * sin(Theta));
	float A02 = ((x * z) * (1.0f - cos(Theta))) + (y * sin(Theta));
	float A10 = ((x * x) * (1.0f - cos(Theta))) + (z * sin(Theta));
	float A11 = (y * y * (1.0f - cos(Theta))) + cos(Theta);
	float A12 = (y * z * (1.0f - cos(Theta))) - (x * sin(Theta));
	float A20 = ((x * z) * (1.0f - cos(Theta))) - (y * sin(Theta));
	float A21 = ((y * z) * (1.0f - cos(Theta))) + (x * sin(Theta));
	float A22 = (z * z * (1.0f - cos(Theta))) + cos(Theta);
	
	_rResult->SetElement(0, 0, A00);
	_rResult->SetElement(0, 1, A01);
	_rResult->SetElement(0, 2, A02);
	_rResult->SetElement(1, 0, A10);
	_rResult->SetElement(1, 1, A11);
	_rResult->SetElement(1, 2, A12);
	_rResult->SetElement(2, 0, A20);
	_rResult->SetElement(2, 1, A21);
	_rResult->SetElement(2, 2, A22);
}
void cMatrix::Project(int _Proj, float _Distance, cMatrix * _rResult) {
	float ProjDist = 1.0f / _Distance;
	switch (_Proj) {
	case 0:
		_rResult->SetElement(3, 0, ProjDist);
		break;
	case 1:
		_rResult->SetElement(3, 1, ProjDist);
		break;
	case 2:
		_rResult->SetElement(3, 2, ProjDist);
		break;
	default: break;
	}
	_rResult->SetElement(3, 3, 0);
}
void cMatrix::Copy(cMatrix* _MatrixA, cMatrix* _MatrixB) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float f = _MatrixA->GetElement(i, j);
			_MatrixB->SetElement(i, j, f);
		}
	}
}

