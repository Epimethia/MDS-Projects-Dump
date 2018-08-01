#include "ellipse.h"

CEllipse::CEllipse(COLORREF _newColor, int _iX, int _iY) {
	m_Color = _newColor;
	m_iStartX = _iX;
	m_iStartY = _iY;
}

CEllipse::CEllipse() {

}

CEllipse::~CEllipse() {

}

void CEllipse::Draw(HDC _hdc) {
	HPEN new_pen = CreatePen(PS_SOLID, 5, RGB(0,0,0));
	HBRUSH new_brush = CreateSolidBrush(m_Color);
	SelectObject(_hdc, new_pen);
	SelectObject(_hdc, new_brush);
	Ellipse(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);
	DeleteObject(new_pen);
	DeleteObject(new_brush);
}

void CEllipse::SetColor(COLORREF _newColor) {
	m_Color = _newColor;
}
