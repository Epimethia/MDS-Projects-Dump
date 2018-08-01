#pragma once
#include <Windows.h>

class CBackBuffer {
	public:
		CBackBuffer();
		~CBackBuffer();

		bool Initialize(HWND _hWnd, int _iWidth, int _iHeight);
		HDC GetBufferDC() const { return m_BufferDC; };

		void ClearBuffer();
		void PresentBuffer();

	private :
		HWND m_hwnd;
		HDC m_BufferDC;
		HBITMAP m_hSurface;
		HBITMAP m_OldBuffer;
		int m_iWidth;
		int m_iHeight;
};

