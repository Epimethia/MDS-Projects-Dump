#include "Tableau.h"



CTableau::CTableau() {

}


CTableau::~CTableau() {

}

bool CTableau::Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iWidth, int _iHeight) {
	//Creating a new backbuffer and initializing it
	m_pBackBuffer = new CBackBuffer;
	m_pBackBuffer->Initialise(_hwnd, _iWidth, _iHeight);

	return true;
}

CTableau& CTableau::GetInstance() {
	/*if (s_pTableau == 0) {
		s_pTableau = new CTableau;
	}*/
	return(*s_pTableau);
}

void CTableau::Draw(HDC _hdc) {
	m_pBackBuffer->Clear();	//Clears the backbuffer
	//Drawing the first column
}
