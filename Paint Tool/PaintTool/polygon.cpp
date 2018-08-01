#include "polygon.h"

CPolygon::CPolygon(int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, COLORREF _PenColor, int _iPenWidth) {
	m_iFillStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenColor = _PenColor;
	m_iPenWidth = _iPenWidth;
	PolyComplete = false;
	m_nPoints = 2;
	m_pPointList = new POINT[2];
	m_pPointList[0] = { 0, 0 };
	m_pPointList[1] = { 0, 0 };
}

CPolygon::CPolygon() {

}

CPolygon::~CPolygon() {

}

void CPolygon::Draw(HDC _hdc) {
	if (m_nPoints > 1) {
		HPEN new_pen = CreatePen(m_iPenStyle, 7, RGB(0,0,0));
		HBRUSH new_brush = CreateSolidBrush(RGB(100,100,100));
		SelectObject(_hdc, new_pen);
		SelectObject(_hdc, new_brush);
		Polygon(_hdc, m_pPointList, m_nPoints);
		DeleteObject(new_pen);
		DeleteObject(new_brush);
	}
}

void CPolygon::SetFillColor(COLORREF _newColor) {
	m_iFillColor = _newColor;
}

void CPolygon::SetPenColor(COLORREF _newColor) {
	m_iPenColor = _newColor;
}

void CPolygon::AddPoint(POINT _p) {
	if (IsComplete()) return;

	//First click moves both initial points
	if (m_pPointList[0].x == (m_pPointList[1].x && 0) && m_pPointList[0].y == (m_pPointList[1].y && 0)) {
		m_pPointList[0] = _p;
		m_pPointList[1] = _p;
		return;
	}

	//Second click moves the second point;
	if (m_nPoints < 3) {
		// If the points are the same (but not 0) so needs to set second point
		if ((m_pPointList[1].x == m_pPointList[0].x && m_pPointList[0].y == m_pPointList[1].y))
		{
			m_pPointList[1] = _p;
			return;
		}
	}

	// FOR LINE DRAWING POLYGON METHOD
	if (abs(m_pPointList[0].x - _p.x) < 30 && abs(m_pPointList[0].y - _p.y) < 30) // If the point placing is at (near) the start point
	{
		PolyComplete = true;
		return;
	}

	// Adds to 'number of points' array
	m_nPoints++;
	POINT* TempArray = new POINT[m_nPoints]; // Creates new temp array to copy over values
	for (int i = 0; i < m_nPoints - 1; i++) // copy values to temp array
	{
		TempArray[i] = m_pPointList[i];
	}

	delete m_pPointList; // Delete point list array

						 // Sets point list array to the duplicated temp array (of 1 size bigger)
	m_pPointList = TempArray;
	m_pPointList[m_nPoints - 1] = _p; // Sets the unset last value of the array to the new point
}
