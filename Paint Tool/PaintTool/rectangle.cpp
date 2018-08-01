#include "rectangle.h"

CRectangle::CRectangle(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor, int _X, int _Y) {
	m_iBrushStyle = _iBrushStyle;
	m_iHatchStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenColor = _PenColor;
	m_iStartX = _X;
	m_iStartY = _Y;
}

CRectangle::CRectangle() {

}

CRectangle::~CRectangle() {

}

void CRectangle::Draw(HDC _hdc) {
	//Creating a pen for the outline
	HPEN new_pen = CreatePen(m_iPenStyle, 5, m_Color);
	HBRUSH new_brush = CreateSolidBrush(m_iFillColor);
	SelectObject(_hdc, new_pen);
	SelectObject(_hdc, new_brush);
	Rectangle(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);
	DeleteObject(new_pen);
	DeleteObject(new_brush);
}

void CRectangle::SetBrushStyle(EBRUSHSTYLE _brushStyle) {
	m_iBrushStyle = _brushStyle;
}

void CRectangle::SetFillColor(COLORREF _newColor) {
	m_iFillColor = _newColor;
}

void CRectangle::SetPenStyle(int _iPenStyle) {
	m_iPenStyle = _iPenStyle;
}

void CRectangle::SetPenColor(COLORREF _newColor) {
	m_iPenColor = _newColor;
}

void CRectangle::SetHatchStyle(int _iHatchStyle) {
	m_iHatchStyle = _iHatchStyle;
}
