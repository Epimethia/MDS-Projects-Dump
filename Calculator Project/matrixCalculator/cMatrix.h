#pragma once

#include <cmath>

class cMatrix {
private:
	float m_fMatrix[4][4];
public:
	cMatrix();
	~cMatrix();
	bool Equals(cMatrix* _rA, cMatrix* _rB);
	float GetElement(int _iX, int _iY) const;
	void SetElement(int _iX, int _iY, float _fValue);
	static float Determinant(cMatrix* _rA);
	static void Zero(cMatrix* _rResult);
	static void Identity(cMatrix* _rResult);
	static void Add(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static void Subtract(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static void Multiply(float _fScalar, cMatrix* _rA, cMatrix* _rResult);
	static void Multiply(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static void Transpose(cMatrix* _rA, cMatrix* _rResult);
	static void Inverse(cMatrix* _rA, cMatrix* _rResult);
	static void Scale(float _fX, float _fY, float _fZ, cMatrix* _rResult);
	static void Translation(float _fX, float _fY, float _fZ, cMatrix* _rResult);
	static void Rotate(float _fX, float _fY, float _fZ, float Theta, cMatrix* _rResult);
	static void Project(int _Proj,float _Distance, cMatrix* _rResult);
	static void Copy(cMatrix* _MatrixA, cMatrix* _MatrixB);
};
