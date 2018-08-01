#include <cmath>

#include "cQuaternion.h"

cQuaternion::cQuaternion() {
	m_fW = 0.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fZ = 0.0f;
}
cQuaternion::~cQuaternion() {

}
float cQuaternion::DotProduct(cQuaternion* _QuatA, cQuaternion* _QuatB) {
	float fDotProd = (_QuatA->m_fW * _QuatB->m_fW) +
		(_QuatA->m_fX * _QuatB->m_fX) +
		(_QuatA->m_fY * _QuatB->m_fY) +
		(_QuatA->m_fZ * _QuatB->m_fZ);
	return fDotProd;
}
float cQuaternion::Magnitude(cQuaternion* _QuatA) {
	float fMagnitude = sqrt(pow(_QuatA->m_fW, 2.0f) +
		pow(_QuatA->m_fX, 2.0f) +
		pow(_QuatA->m_fY, 2.0f) +
		pow(_QuatA->m_fZ, 2.0f));
	return fMagnitude;
}
void cQuaternion::Add(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fW = _QuatA->m_fW + _QuatB->m_fW;
	_ResultQuat->m_fX = _QuatA->m_fX + _QuatB->m_fX;
	_ResultQuat->m_fY = _QuatA->m_fY + _QuatB->m_fY;
	_ResultQuat->m_fZ = _QuatA->m_fZ + _QuatB->m_fZ;
}
void cQuaternion::Subtract(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fW = _QuatA->m_fW - _QuatB->m_fW;
	_ResultQuat->m_fX = _QuatA->m_fX - _QuatB->m_fX;
	_ResultQuat->m_fY = _QuatA->m_fY - _QuatB->m_fY;
	_ResultQuat->m_fZ = _QuatA->m_fZ - _QuatB->m_fZ;
}
void cQuaternion::Multiply(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fW = (_QuatA->m_fW * _QuatB->m_fW) -
						(_QuatA->m_fX * _QuatB->m_fX) -
						(_QuatA->m_fY * _QuatB->m_fY) -
						(_QuatA->m_fZ * _QuatB->m_fZ);

	_ResultQuat->m_fX = (_QuatA->m_fW * _QuatB->m_fX) +
						(_QuatA->m_fX * _QuatB->m_fW) +
						(_QuatA->m_fY * _QuatB->m_fZ) -
						(_QuatA->m_fZ * _QuatB->m_fY);

	_ResultQuat->m_fY = (_QuatA->m_fW * _QuatB->m_fY) -
						(_QuatA->m_fX * _QuatB->m_fZ) +
						(_QuatA->m_fY * _QuatB->m_fW) +
						(_QuatA->m_fZ * _QuatB->m_fX);

	_ResultQuat->m_fZ = (_QuatA->m_fW * _QuatB->m_fZ) +
						(_QuatA->m_fX * _QuatB->m_fY) -
						(_QuatA->m_fY * _QuatB->m_fX) +
						(_QuatA->m_fZ * _QuatB->m_fW);
}
void cQuaternion::Multiply(cQuaternion* _QuatA, float _fScalar, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fW = _QuatA->m_fW * _fScalar;
	_ResultQuat->m_fX = _QuatA->m_fX * _fScalar;
	_ResultQuat->m_fY = _QuatA->m_fY * _fScalar;
	_ResultQuat->m_fZ = _QuatA->m_fZ * _fScalar;
}
void cQuaternion::ComplexConjugate(cQuaternion* _QuatA, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fX = -1 * _QuatA->m_fX;
	_ResultQuat->m_fY = -1 * _QuatA->m_fY;
	_ResultQuat->m_fZ = -1 * _QuatA->m_fZ;
	_ResultQuat->m_fW = _QuatA->m_fW;
}
void cQuaternion::Normalize(cQuaternion* _QuatA) {
	float Mag = cQuaternion::Magnitude(_QuatA);
	_QuatA->SetQuatX(_QuatA->GetQuatX() / Mag);
	_QuatA->SetQuatY(_QuatA->GetQuatY() / Mag);
	_QuatA->SetQuatZ(_QuatA->GetQuatZ() / Mag);
	_QuatA->SetQuatW(_QuatA->GetQuatW() / Mag);
}
void cQuaternion::Inverse(cQuaternion* _QuatA, cQuaternion* _ResultQuat) {
	_ResultQuat->m_fW = _QuatA->m_fW / pow(Magnitude(_QuatA), 2.0f);
	_ResultQuat->m_fX = _QuatA->m_fX / pow(Magnitude(_QuatA), 2.0f);
	_ResultQuat->m_fY = _QuatA->m_fY / pow(Magnitude(_QuatA), 2.0f);
	_ResultQuat->m_fZ = _QuatA->m_fZ / pow(Magnitude(_QuatA), 2.0f);
}
void cQuaternion::Slerp(cQuaternion* _QuatA, cQuaternion* _QuatB, float _fInterpolateT, cQuaternion* _ResultQuat) {
	//Copying the two Quaternions to temp Quaternions to avoid changing the original Quaternions
	cQuaternion* TempQuatA = new cQuaternion;
	cQuaternion* TempQuatB = new cQuaternion;
	
	TempQuatA->SetQuatW(_QuatA->GetQuatW());
	TempQuatA->SetQuatX(_QuatA->GetQuatX());
	TempQuatA->SetQuatY(_QuatA->GetQuatY());
	TempQuatA->SetQuatZ(_QuatA->GetQuatZ());
	TempQuatB->SetQuatW(_QuatB->GetQuatW());
	TempQuatB->SetQuatX(_QuatB->GetQuatX());
	TempQuatB->SetQuatY(_QuatB->GetQuatY());
	TempQuatB->SetQuatZ(_QuatB->GetQuatZ());

	cQuaternion::Normalize(TempQuatA);
	cQuaternion::Normalize(TempQuatB);

	//Computing the cosine of the angle via the dotprod
	float CosTheta = cQuaternion::DotProduct(TempQuatA, TempQuatB);

	//Testing for a negative DotProd, to determine if there is a shorter SLERP arc
	if (CosTheta < 0.0f) {
		TempQuatB->SetQuatW(_QuatB->GetQuatW() * -1.0f);
		TempQuatB->SetQuatX(_QuatB->GetQuatX() * -1.0f);
		TempQuatB->SetQuatY(_QuatB->GetQuatY() * -1.0f);
		TempQuatB->SetQuatZ(_QuatB->GetQuatZ() * -1.0f);
		CosTheta = -CosTheta;
	}

	//Interpolation parameters
	float k0 = 0.0f;
	float k1 = 0.0f;

	//Protecting against divide by zero
	if (CosTheta > 0.9999f) {
		//If small angle approximation is available
		k0 = 1.0f - _fInterpolateT;
		k1 = _fInterpolateT;
	}
	else {
		//Computing sine of the angle
		float SinTheta = sqrt(1.0f - pow(CosTheta, 2.0f));

		//Compute angle from the sine and cosine
		float Theta = atan2(SinTheta, CosTheta);

		//Computing the inverse of the denominator
		float InverseSinTheta = 1.0f / SinTheta;

		//Computing Interpolation parameters
		k0 = sin((1.0f - _fInterpolateT) * Theta) * InverseSinTheta;
		k1 = sin(_fInterpolateT * Theta) * InverseSinTheta;
	}

	//Interpolating
	_ResultQuat->SetQuatW((TempQuatA->GetQuatW() * k0) + (TempQuatB->GetQuatW() * k1));
	_ResultQuat->SetQuatX((TempQuatA->GetQuatX() * k0) + (TempQuatB->GetQuatX() * k1));
	_ResultQuat->SetQuatY((TempQuatA->GetQuatY() * k0) + (TempQuatB->GetQuatY() * k1));
	_ResultQuat->SetQuatZ((TempQuatA->GetQuatZ() * k0) + (TempQuatB->GetQuatZ() * k1));

	//Clearing up memory
	delete TempQuatA;
	delete TempQuatB;
	TempQuatA = nullptr;
	TempQuatB = nullptr;
}
void cQuaternion::QuatToRotMatrix(cQuaternion* _QuatA, cMatrix* _Matrix) {
	Normalize(_QuatA);
	float A00 = 1 - (2 * (pow(_QuatA->GetQuatY(), 2.0f) + pow(_QuatA->GetQuatZ(), 2.0f)));
	float A01 = (2 * _QuatA->GetQuatX() * _QuatA->GetQuatY()) + (2 * _QuatA->GetQuatW() * _QuatA->GetQuatZ());
	float A02 = (2 * _QuatA->GetQuatX() * _QuatA->GetQuatZ()) - (2 * _QuatA->GetQuatW() * _QuatA->GetQuatY());
	float A03 = 0;

	float A10 = (2 * _QuatA->GetQuatX() * _QuatA->GetQuatY()) - (2 * _QuatA->GetQuatW() * _QuatA->GetQuatZ());
	float A11 = 1 - (2 * pow(_QuatA->GetQuatX(), 2.0f)) - (2 * pow(_QuatA->GetQuatZ(), 2.0f));
	float A12 = (2 * _QuatA->GetQuatY() * _QuatA->GetQuatZ()) + (2 * _QuatA->GetQuatW() * _QuatA->GetQuatX());
	float A13 = 0;

	float A20 = (2 * _QuatA->GetQuatX() * _QuatA->GetQuatZ()) + (2 * _QuatA->GetQuatW() * _QuatA->GetQuatY());
	float A21 = (2 * _QuatA->GetQuatY() * _QuatA->GetQuatZ()) - (2 * _QuatA->GetQuatW() * _QuatA->GetQuatX());
	float A22 = 1 - (2 * pow(_QuatA->GetQuatX(), 2.0f)) - (2 * pow(_QuatA->GetQuatY(), 2.0f));
	float A23 = 0;

	float A30 = 0;
	float A31 = 0;
	float A32 = 0;
	float A33 = 1;

	_Matrix->SetElement(0, 0, A00);
	_Matrix->SetElement(0, 1, A01);
	_Matrix->SetElement(0, 2, A02);
	_Matrix->SetElement(0, 3, A03);
	_Matrix->SetElement(1, 0, A10);
	_Matrix->SetElement(1, 1, A11);
	_Matrix->SetElement(1, 2, A12);
	_Matrix->SetElement(1, 3, A13);
	_Matrix->SetElement(2, 0, A20);
	_Matrix->SetElement(2, 1, A21);
	_Matrix->SetElement(2, 2, A22);
	_Matrix->SetElement(2, 3, A23);
	_Matrix->SetElement(3, 0, A30);
	_Matrix->SetElement(3, 1, A31);
	_Matrix->SetElement(3, 2, A32);
	_Matrix->SetElement(3, 3, A33);

}
