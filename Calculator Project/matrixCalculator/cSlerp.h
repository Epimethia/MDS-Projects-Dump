#pragma once
#include <cmath>

#include "cQuaternion.h"
#include "cMatrix.h"
class cSlerp {
public:
	cSlerp();
	~cSlerp();
	static cQuaternion* Slerp(float _InterpolateT, cQuaternion* _QuatA, cQuaternion* _QuatB, cQuaternion* _ResultQuat);
	cMatrix* QuatToMatrix(cQuaternion* _QuatA, cMatrix* _ReturnMatrix);
private:
	cQuaternion* m_pSlerpQuatA;
	cQuaternion* m_pSlerpQuatB;
};

