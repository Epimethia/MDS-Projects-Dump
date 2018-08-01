#include "backBuffer.h"

CBackBuffer::CBackBuffer() {
	m_hWnd = 0;				//The window handle
	m_BFDC = 0;				//The buffer device handle
	m_hBFBitmap = 0;		//Backbuffer bitmap
	m_hOldBitmap = 0;		//Backbuffer old bitmap
	m_iWidth = 0;			//Backbuffer x/y size
	m_iHeight = 0;
}

CBackBuffer::~CBackBuffer() {

}

bool CBackBuffer::Initialise(HWND _hWnd) {
	//Initializing the window properties
	//Getting the window handle for the main window
	m_hWnd = _hWnd;

	//Creating a new handle for the backbuffer
	RECT window;
	
	//Setting window rect as the entire desktop



	return false;
}

HDC CBackBuffer::GetBFDC() const {
	//Gets and returns the backbuffer device handle
	return HDC(m_BFDC);
}

int CBackBuffer::GetHeight() const {
	//Gets and returns the height of the backbuffer
	return m_iHeight;
}

int CBackBuffer::GetWidth() const {
	//Gets and returns the width of the backbuffer
	return m_iWidth;
}

void CBackBuffer::Clear() {
	//Clears the Backbuffer to a clean white background

	//Creating a white background brush
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_BFDC, GetStockObject(WHITE_BRUSH)));

	//Creating a rect to select the editable region in the window
	RECT _rRect;

	//Setting and filling the window Rect with the brush we created
	GetClientRect(m_hWnd, &_rRect);
	FillRect(m_BFDC, &_rRect, hOldBrush);

	//Reselecting the brush and placing it in the device context
	SelectObject(m_BFDC, hOldBrush);
}

void CBackBuffer::Present() {
	//Prints the backbuffer to the screen

}

