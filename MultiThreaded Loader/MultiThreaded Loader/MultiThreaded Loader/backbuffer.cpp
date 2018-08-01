#include "backbuffer.h"



CBackBuffer::CBackBuffer() {
}


CBackBuffer::~CBackBuffer() {
}

bool CBackBuffer::Initialize(HWND _hwnd, int _iWidth, int _iHeight) {
	m_hwnd = _hwnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	HDC hWindowDC = ::GetDC(m_hwnd);
	m_BufferDC = CreateCompatibleDC(hWindowDC);
	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);
	ReleaseDC(m_hwnd, hWindowDC);

	m_OldBuffer = static_cast<HBITMAP>(SelectObject(m_BufferDC, m_hSurface));
	HBRUSH BrushBlack = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_BufferDC, BrushBlack));
	Rectangle(m_BufferDC, 0, 0, m_iWidth, m_iHeight);
	SelectObject(m_BufferDC, oldBrush);
	return true;
}

void CBackBuffer::ClearBuffer() {
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_BufferDC, GetStockObject(BLACK_BRUSH)));		//Creates a black brush 
	HPEN EmptyPen = static_cast<HPEN>(GetStockObject(NULL_BRUSH));
	SelectObject(m_BufferDC, EmptyPen);
	Rectangle(m_BufferDC, 0, 0, m_iWidth, m_iHeight);													//paints the entire backbuffer with the black brush
	SelectObject(m_BufferDC, hOldBrush);																//Reselects the brush
}

void CBackBuffer::PresentBuffer() {
	HDC hWndDC = ::GetDC(m_hwnd);												//gets the device context of the main window
	BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_BufferDC, 0, 0, SRCCOPY);		//BitBlts the buffer onto the main window
	ReleaseDC(m_hwnd, hWndDC);													//releases the main window
}
