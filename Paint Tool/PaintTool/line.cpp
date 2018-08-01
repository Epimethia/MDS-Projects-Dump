#include "line.h"

CLine::CLine(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY) {
	//if the user specifies parameters
	m_iStyle = _iStyle;
	m_iWidth = _iWidth;
	m_Color = _newColor;
	m_iStartX = _iStartX;
	m_iStartY = _iStartY;
}

CLine::CLine() {

}

void CLine::SetWidth(int _iNewWidth) {
	m_iWidth = _iNewWidth;
}

void CLine::Draw(HDC _hdc) {
	HPEN new_pen = CreatePen(m_iStyle, m_iWidth, m_Color);
	SelectObject(_hdc, new_pen);
	MoveToEx(_hdc, m_iStartX, m_iStartY, NULL);
	LineTo(_hdc, m_iEndX, m_iEndY);
	//Deleting pens to avoid breaking the program.
	DeleteObject(new_pen);
}