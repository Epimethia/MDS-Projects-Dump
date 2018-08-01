#pragma once
#include <Windows.h>
#include "Column.h"
#include "Backbuffer.h"

class CTableau {
public:
	CTableau();
	~CTableau();
	void Draw(HDC _hdc);
	bool Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iWidth, int _iHeight);

	//Singleton Methods
	static CTableau& GetInstance();
	//static void DestroyInstance();
private:
	//Singleton Instance
	static CTableau* s_pTableau;
	//BackBuffer pointer
	CBackBuffer* m_pBackBuffer;
};

