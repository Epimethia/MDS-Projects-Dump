#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "Tableau.h"

#define WINDOW_CLASS_NAME L"WINDOW"

CTableau* g_pTableau;

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	PAINTSTRUCT PaintStruct;
	HDC hdc;

	switch (_msg) {
	case WM_CREATE: {

		return 0;
	}
					break;
	case WM_PAINT: {
		hdc = BeginPaint(_hwnd, &PaintStruct);
		g_pTableau->Draw(hdc);
		EndPaint(_hwnd, &PaintStruct);
		return 0;
	}
				   break;
	case WM_COMMAND: {

		return 0;
	}
					 break;
	case WM_DESTROY: {

		PostQuitMessage(0);
		return 0;
	}
					 break;

	default: break;
	}
	return(DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow) {
	WNDCLASSEX Winclass;
	HWND hwnd;
	MSG msg;

	// First fill in the window class structure.
	Winclass.cbSize = sizeof(WNDCLASSEX);
	Winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	Winclass.lpfnWndProc = WindowProc;
	Winclass.cbClsExtra = 0;
	Winclass.cbWndExtra = 0;
	Winclass.hInstance = _hInstance;
	Winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	Winclass.lpszMenuName = NULL;
	Winclass.lpszClassName = WINDOW_CLASS_NAME;
	Winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&Winclass)) {
		return (0);
	}


	// create the window
	hwnd = CreateWindowEx(NULL,				// Extended style.
		WINDOW_CLASS_NAME,					// Class.
		L"Your Basic Window",				// Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// Other Window settings
		0, 0,								// Initial x,y.
		800, 600,							// Initial width, height.
		NULL,								// Handle to parent.
		NULL,								// Handle to menu.
		_hInstance,							// Instance of this application.
		NULL);								// Extra creation parameters.

	if (!(hwnd)) {
		return (0);
	}

	// Enter main event loop
	while (true) {
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Test if this is a quit.
			if (msg.message == WM_QUIT) {
				break;
			}
			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}
	}

	delete g_pTableau;
	DestroyWindow(hwnd);
	return (static_cast<int>(msg.wParam));
};
