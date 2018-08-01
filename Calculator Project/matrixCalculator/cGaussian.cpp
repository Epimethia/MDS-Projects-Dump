#include "cGaussian.h"

cGaussian::cGaussian() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_fGaussianArray[i][j] = 0.0f;
		}
	}
}
cGaussian::~cGaussian() {

}
void cGaussian::Multiply(int _GaussRow, float _fScalar) {	//Multiples Row with the Scalar
	for (int i = 0; i < 4; ++i) {
		m_fGaussianArray[_GaussRow][i] = _fScalar * m_fGaussianArray[_GaussRow][i];
	}
}
void cGaussian::Swap(int _GaussRowA, int _GaussRowB) {	//Swaps Row A with Row B
	_GaussRowA -= 1;
	_GaussRowB -= 1;
	float Temp[4];
	for (int i = 0; i < 4; ++i) {
		Temp[i] = m_fGaussianArray[_GaussRowA][i];
		m_fGaussianArray[_GaussRowA][i] = m_fGaussianArray[_GaussRowB][i];
		m_fGaussianArray[_GaussRowB][i] = Temp[i];
	}
}
void cGaussian::AddMulti(int _GaussRowA, int _GaussRowB, float _fScalar) {	//Adds Row A to Row B
	_GaussRowA -= 1;
	_GaussRowB -= 1;
	for (int i = 0; i < 4; ++i) {
		m_fGaussianArray[_GaussRowB][i] = (_fScalar * m_fGaussianArray[_GaussRowA][i]) + m_fGaussianArray[_GaussRowB][i];
	}
}
