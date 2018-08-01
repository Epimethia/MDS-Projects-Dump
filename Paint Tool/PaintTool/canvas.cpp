#include "canvas.h"

CCanvas::CCanvas() {
}

CCanvas::~CCanvas() {

}

bool CCanvas::Initialise(HWND _hwnd, int _iWidth, int _iHeight) {

	return false;
}

CBackBuffer * CCanvas::GetBackBuffer() {

	return m_pBackBuffer;
}

bool CCanvas::Draw(HDC _hdc) {
	if (m_shapes.empty()) {
		return false;
	}
	for (std::vector<IShape*>::iterator It = m_shapes.begin(); It != m_shapes.end(); ++It) {
		(*It)->Draw(_hdc);
	}
	return true;
}

void CCanvas::Save(HWND _hwnd) {

}

void CCanvas::AddShape(IShape * _pIShape) {
	m_shapes.push_back(_pIShape);
}

void CCanvas::AddStamp(CStamp *) {

}
