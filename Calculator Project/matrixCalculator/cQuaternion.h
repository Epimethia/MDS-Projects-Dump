#pragma once

#include "cMatrix.h"

class cQuaternion {
public:
	cQuaternion();
	~cQuaternion();
	void SetQuatW(float _fW) { m_fW = _fW; };
	void SetQuatX(float _fX) { m_fX = _fX; };
	void SetQuatY(float _fY) { m_fY = _fY; };
	void SetQuatZ(float _fZ) { m_fZ = _fZ; };
	float GetQuatW() { return m_fW; };
	float GetQuatX() { return m_fX; };
	float GetQuatY() { return m_fY; };
	float GetQuatZ() { return m_fZ; };
	static void Add(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuant);
	static void Subtract(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat);
	static void Multiply(cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat);
	static void Multiply(cQuaternion* _QuatA, float _fScalar, cQuaternion* _ResultQuat);
	static void ComplexConjugate(cQuaternion* _QuatA, cQuaternion* _ResultQuat);
	static float Magnitude(cQuaternion* _QuatA);
	static void Normalize(cQuaternion* _QuatA);
	static void Inverse(cQuaternion* _QuatA, cQuaternion* _ResultQuat);
	static float DotProduct(cQuaternion* _QuatA, cQuaternion* _QuatB);
	static void Slerp(cQuaternion* _QuatA, cQuaternion* _QuatB, float _fScalar, cQuaternion* _ResultQuat);
	static void QuatToRotMatrix(cQuaternion* _QuatA, cMatrix* _Matrix);
private:
	float m_fW;
	float m_fX;
	float m_fY;
	float m_fZ;
};
