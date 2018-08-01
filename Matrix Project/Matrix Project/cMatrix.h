#ifndef _C_MATRIX_H_
#define _C_MATRIX_H_


class cMatrix {
private:
	float m_fMatrix[4][4] = { { 2.0f,8.0f,4.0f,6.0f },{ 2.0f,11.0f,7.0f,9.0f },{ 5.0f,23.0f,14.0f,18.0f },{ 3.0f,14.0f,8.0f,10.0f } };
public:
	cMatrix();
	~cMatrix();
	void SetElement(int _iX, int _iY, float _fValue);
	float GetElement(int _iX, int _iY) const;
	static cMatrix* Zero(cMatrix* _rResult);
	static cMatrix* Identity(cMatrix* _rResult);
	bool Equals(cMatrix* _rA, cMatrix* _rB);
	static cMatrix* Add(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static cMatrix* Subtract(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static cMatrix* Multiply(float _fScalar, cMatrix* _rA, cMatrix* _rResult);
	static cMatrix* Multiply(cMatrix* _rA, cMatrix* _rB, cMatrix* _rResult);
	static cMatrix* Transpose(cMatrix* _rA, cMatrix* _rResult);
	static float Determinant(cMatrix* _rA);
	static cMatrix* Inverse(cMatrix* _rA, cMatrix* _rResult);
};

#endif // _C_MATRIX_H