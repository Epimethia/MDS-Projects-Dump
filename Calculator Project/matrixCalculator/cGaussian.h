#pragma once

class cGaussian {
public:
	cGaussian();
	~cGaussian();
	float GetValue(int _iIndexX, int _iIndexY) { return m_fGaussianArray[_iIndexX][_iIndexY]; };
	void SetValue(int _iIndexX, int _iIndexY, float _iValue) { m_fGaussianArray[_iIndexX][_iIndexY] = _iValue; };
	void Multiply(int _GaussRowA, float _fScalar);
	void Swap(int _GaussRowA, int _GaussRowB);
	void AddMulti(int _GaussRowA, int _GaussRowB, float _fScalar);
private:
	float m_fGaussianArray[3][4];
};

