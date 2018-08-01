#include "shape.h"

IShape::IShape() {

}

void IShape::SetStartX(int _iStartX) {
	m_iStartX = _iStartX;
}

void IShape::SetStartY(int _iStartY) {
	m_iStartX = _iStartY;
}

void IShape::SetEndX(int _iEndX) {
	m_iEndX = _iEndX;
}

void IShape::SetEndY(int _iEndY) {
	m_iEndY = _iEndY;
}
