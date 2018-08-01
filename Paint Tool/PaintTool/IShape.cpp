#include "shape.h"

IShape::IShape() {
	m_iStartX = 0;
	m_iEndX = 0;
	m_iStartY = 0;
	m_iEndY = 0;
}

void IShape::Draw(HDC _hdc) {
	MoveToEx(_hdc, m_iStartX, m_iStartY, NULL);
	LineTo(_hdc, m_iEndX, m_iEndY);
}

void IShape::SetStartX(int _iStartX) {
	m_iStartX = _iStartX;
}

void IShape::SetEndX(int _iEndX) {
	m_iEndX = _iEndX;
}

void IShape::SetStartY(int _iStartY) {
	m_iStartY = _iStartY;
}

void IShape::SetEndY(int _iEndY) {
	m_iEndY = _iEndY;
}
