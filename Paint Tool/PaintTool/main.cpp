
//#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.

#include "resource.h"
#include "shape.h"
#include "line.h"
#include "canvas.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "stamp.h"
#include "backBuffer.h"
#include <string>

#define WINDOW_CLASS_NAME L"WINCLASS1"
//Global variables
HINSTANCE g_hInstance;
CCanvas* g_pCanvas;
IShape* g_pShape = 0;
HMENU g_hMenu;
int g_iCurrentShape = 0;

//Enum to decalre the type of tool supported by the application.
enum ESHAPE
{
	FREEHAND = 0,
	LINESHAPE,
	RECTANGLESHAPE,
	ELLIPSESHAPE,
	POLYGONSHAPE,
	STAMP
};

LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

	
	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.
		g_pCanvas = new CCanvas;
		// Return Success.
		return (0);
	}

	break;

	case WM_PAINT:
	{
		hdc = BeginPaint(_hwnd, &ps);

		g_pCanvas->Draw(hdc);	

		EndPaint(_hwnd, &ps);
		// Return success.
		return (0);
	}
	break;

	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case ID_FILE_EXIT: {
			PostQuitMessage(0);
			break;
		}
		case ID_HELP_ABOUT:	{
			MessageBox(_hwnd, L"This paint tool was developed by .............", L"Author Information", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case ID_SHAPE_LINE: {
			g_iCurrentShape = LINESHAPE;
			break;
		}
		case ID_SHAPE_R: {
			g_iCurrentShape = RECTANGLESHAPE;
			break;
		}
		case ID_SHAPE_ELLIPSE: {
			g_iCurrentShape = ELLIPSESHAPE;
			break;
		}
		case ID_SHAPE_POLYGON: {
			g_iCurrentShape = POLYGONSHAPE;
			break;
		}

		default:break;
		}
		return(0);
	}
	break;

	case WM_MOUSEMOVE: {
		//Getting mouse xpos/ypos
		int iMouseX = static_cast<int>(LOWORD(_lparam));
		int iMouseY = static_cast<int>(HIWORD(_lparam));

		if (g_pShape != 0) {
			g_pShape->SetEndX(iMouseX);
			g_pShape->SetEndY(iMouseY);
		}

		//Invalidating the rectangle
		InvalidateRect(_hwnd, NULL, TRUE);
		return(0);
	}
	break;

	case WM_LBUTTONDOWN: {
		//Getting mouse xpos/ypos
		int iMouseX = static_cast<int>(LOWORD(_lparam));
		int iMouseY = static_cast<int>(HIWORD(_lparam));
		switch (g_iCurrentShape) {
		case LINESHAPE: {
			g_pShape = new CLine(PS_SOLID, 7, RGB(0, 0, 0), iMouseX, iMouseY);
			g_pShape->SetEndX(iMouseX);
			g_pShape->SetEndY(iMouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case RECTANGLESHAPE: {
			g_pShape = new CRectangle(SOLID, HS_CROSS, RGB(150, 150, 150), PS_SOLID, RGB(0, 0, 0), iMouseX, iMouseY);
			g_pShape->SetEndX(iMouseX);
			g_pShape->SetEndY(iMouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case ELLIPSESHAPE: {
			g_pShape = new CEllipse(RGB(150, 150, 150), iMouseX, iMouseY);
			g_pShape->SetEndX(iMouseX);
			g_pShape->SetEndY(iMouseY);
			g_pCanvas->AddShape(g_pShape);
			break;
		}
		case POLYGONSHAPE: {
			if (g_pShape == 0) {
				//Creating the polygon if there is none created
				g_pShape = new CPolygon(HS_CROSS, RGB(150, 150, 150), PS_SOLID, RGB(0, 0, 0), 10);
				g_pCanvas->AddShape(g_pShape);
			}

			CPolygon* Poly = static_cast<CPolygon*>(g_pShape);
			POINT NewPoint;
			NewPoint.x = iMouseX;
			NewPoint.y = iMouseY;
	
			if (Poly->IsComplete()) {
				g_pShape = 0;
				break;
			}
			Poly->AddPoint(NewPoint);

			break;
		}
		default:break;	
		}


		return(0);
	}
	break;

	case WM_LBUTTONUP: {
		if (g_iCurrentShape == POLYGONSHAPE) {
			return (0);
		}
		g_pShape = 0;
		return(0);
	}
	break;

	case WM_DESTROY: {
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

		default:break;
	} // End switch.

	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

	g_hInstance = _hInstance;
	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Asma's Paint Tool",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,                    // Initial x,y.
		1500, 800,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}



	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}

		// Main game processing goes here.

	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}
