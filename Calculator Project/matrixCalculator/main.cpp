// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Complete Calculator - James Devenport
// Description	: Complete calculator project for BSE GD1MO2
// Author		: James Devenport
// Mail			: james.dev7362@mediadesign.school.nz


#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <string>
#include "utils.h"

#include "resource.h"
#include "cQuaternion.h"
#include "cGaussian.h"
#include "cSlerp.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

#pragma region
//Matrix Variables
cMatrix* pMatrixA = new cMatrix;
cMatrix* pMatrixB = new cMatrix;
cMatrix* pMatrixR = new cMatrix;

//Quaternion Variables
cQuaternion* pQuatA = new cQuaternion;
cQuaternion* pQuatB = new cQuaternion;
cQuaternion* pQuatR = new cQuaternion;

//Gaussian Variables
cGaussian* pGauss = new cGaussian;

//SLERP Variables
cQuaternion* pSlerpQuatA = new cQuaternion;
cQuaternion* pSlerpQuatB = new cQuaternion;
cQuaternion* pSlerpQuatResult = new cQuaternion;
cMatrix* pSlerpMatrix = new cMatrix;

//Transformation Variables
cMatrix* pTransformationMatrix = new cMatrix;
cMatrix* pTranslationMatrix = new cMatrix;
cMatrix* pScaleMatrix = new cMatrix;
cMatrix* pRotateMatrix = new cMatrix;
cMatrix* pProjectionMatrix = new cMatrix;
#pragma endregion Global variables, matrices and quaternion classes

#pragma region
//Matrix Calculator Functions
void MatrixToUIA(HWND _hwnd, cMatrix* _pMatrix) {
	WriteToEditBox(_hwnd, IDC_EDIT_A11, _pMatrix->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A12, _pMatrix->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A13, _pMatrix->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A14, _pMatrix->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A21, _pMatrix->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A22, _pMatrix->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A23, _pMatrix->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A24, _pMatrix->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A31, _pMatrix->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A32, _pMatrix->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A33, _pMatrix->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A34, _pMatrix->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A41, _pMatrix->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A42, _pMatrix->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A43, _pMatrix->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A44, _pMatrix->GetElement(3, 3));
}
void MatrixToUIB(HWND _hwnd, cMatrix* _pMatrix) {
	WriteToEditBox(_hwnd, IDC_EDIT_B11, _pMatrix->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B12, _pMatrix->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B13, _pMatrix->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B14, _pMatrix->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B21, _pMatrix->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B22, _pMatrix->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B23, _pMatrix->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B24, _pMatrix->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B31, _pMatrix->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B32, _pMatrix->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B33, _pMatrix->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B34, _pMatrix->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B41, _pMatrix->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B42, _pMatrix->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B43, _pMatrix->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B44, _pMatrix->GetElement(3, 3));
}
void MatrixToUIR(HWND _hwnd, cMatrix* _pMatrix) {
	WriteToEditBox(_hwnd, IDC_EDIT_R11, _pMatrix->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R12, _pMatrix->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R13, _pMatrix->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R14, _pMatrix->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R21, _pMatrix->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R22, _pMatrix->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R23, _pMatrix->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R24, _pMatrix->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R31, _pMatrix->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R32, _pMatrix->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R33, _pMatrix->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R34, _pMatrix->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_R41, _pMatrix->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_R42, _pMatrix->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_R43, _pMatrix->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_R44, _pMatrix->GetElement(3, 3));
}
void UIToMatrixA(HWND _hwnd) {
	pMatrixA->SetElement(0, 0, ReadFromEditBox(_hwnd, IDC_EDIT_A11));
	pMatrixA->SetElement(0, 1, ReadFromEditBox(_hwnd, IDC_EDIT_A12));
	pMatrixA->SetElement(0, 2, ReadFromEditBox(_hwnd, IDC_EDIT_A13));
	pMatrixA->SetElement(0, 3, ReadFromEditBox(_hwnd, IDC_EDIT_A14));
	pMatrixA->SetElement(1, 0, ReadFromEditBox(_hwnd, IDC_EDIT_A21));
	pMatrixA->SetElement(1, 1, ReadFromEditBox(_hwnd, IDC_EDIT_A22));
	pMatrixA->SetElement(1, 2, ReadFromEditBox(_hwnd, IDC_EDIT_A23));
	pMatrixA->SetElement(1, 3, ReadFromEditBox(_hwnd, IDC_EDIT_A24));
	pMatrixA->SetElement(2, 0, ReadFromEditBox(_hwnd, IDC_EDIT_A31));
	pMatrixA->SetElement(2, 1, ReadFromEditBox(_hwnd, IDC_EDIT_A32));
	pMatrixA->SetElement(2, 2, ReadFromEditBox(_hwnd, IDC_EDIT_A33));
	pMatrixA->SetElement(2, 3, ReadFromEditBox(_hwnd, IDC_EDIT_A34));
	pMatrixA->SetElement(3, 0, ReadFromEditBox(_hwnd, IDC_EDIT_A41));
	pMatrixA->SetElement(3, 1, ReadFromEditBox(_hwnd, IDC_EDIT_A42));
	pMatrixA->SetElement(3, 2, ReadFromEditBox(_hwnd, IDC_EDIT_A43));
	pMatrixA->SetElement(3, 3, ReadFromEditBox(_hwnd, IDC_EDIT_A44));
}
void UIToMatrixB(HWND _hwnd) {
	pMatrixB->SetElement(0, 0, ReadFromEditBox(_hwnd, IDC_EDIT_B11));
	pMatrixB->SetElement(0, 1, ReadFromEditBox(_hwnd, IDC_EDIT_B12));
	pMatrixB->SetElement(0, 2, ReadFromEditBox(_hwnd, IDC_EDIT_B13));
	pMatrixB->SetElement(0, 3, ReadFromEditBox(_hwnd, IDC_EDIT_B14));
	pMatrixB->SetElement(1, 0, ReadFromEditBox(_hwnd, IDC_EDIT_B21));
	pMatrixB->SetElement(1, 1, ReadFromEditBox(_hwnd, IDC_EDIT_B22));
	pMatrixB->SetElement(1, 2, ReadFromEditBox(_hwnd, IDC_EDIT_B23));
	pMatrixB->SetElement(1, 3, ReadFromEditBox(_hwnd, IDC_EDIT_B24));
	pMatrixB->SetElement(2, 0, ReadFromEditBox(_hwnd, IDC_EDIT_B31));
	pMatrixB->SetElement(2, 1, ReadFromEditBox(_hwnd, IDC_EDIT_B32));
	pMatrixB->SetElement(2, 2, ReadFromEditBox(_hwnd, IDC_EDIT_B33));
	pMatrixB->SetElement(2, 3, ReadFromEditBox(_hwnd, IDC_EDIT_B34));
	pMatrixB->SetElement(3, 0, ReadFromEditBox(_hwnd, IDC_EDIT_B41));
	pMatrixB->SetElement(3, 1, ReadFromEditBox(_hwnd, IDC_EDIT_B42));
	pMatrixB->SetElement(3, 2, ReadFromEditBox(_hwnd, IDC_EDIT_B43));
	pMatrixB->SetElement(3, 3, ReadFromEditBox(_hwnd, IDC_EDIT_B44));
}

//Quaternion Functions
void QuatToUI(HWND _hwnd, cQuaternion* _pQuat) {
	WriteToEditBox(_hwnd, IDC_EDIT10, _pQuat->GetQuatX());
	WriteToEditBox(_hwnd, IDC_EDIT11, _pQuat->GetQuatY());
	WriteToEditBox(_hwnd, IDC_EDIT12, _pQuat->GetQuatZ());
	WriteToEditBox(_hwnd, IDC_EDIT13, _pQuat->GetQuatW());
}

//Gaussian Functions
void GaussToUi(HWND _hwnd, cGaussian* _pGauss) {
	WriteToEditBox(_hwnd, IDC_EDIT1, _pGauss->GetValue(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT2, _pGauss->GetValue(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT3, _pGauss->GetValue(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT4, _pGauss->GetValue(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT5, _pGauss->GetValue(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT6, _pGauss->GetValue(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT7, _pGauss->GetValue(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT8, _pGauss->GetValue(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT9, _pGauss->GetValue(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT10, _pGauss->GetValue(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT11, _pGauss->GetValue(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT12, _pGauss->GetValue(2, 3));
}
bool bCheckEchelon(cGaussian* _pGauss) {
	int i, j, k;
	for (i = 0; i < 4; ++i) {
		if (_pGauss->GetValue(0, i) != 0) {
			if (_pGauss->GetValue(0, i) == 1) {
				break;
			}
			else {
				return false;
			}
		}
	}
	for (j = 0; j < 4; ++j) {
		if (_pGauss->GetValue(1, j) != 0) {
			if (_pGauss->GetValue(1, j) == 1) {
				break;
			}
			else {
				return false;
			}
		}
	}
	for (k = 0; k < 4; ++k) {
		if (_pGauss->GetValue(2, k) != 0) {
			if (_pGauss->GetValue(2, k) == 1) {
				break;
			}
			else {
				return false;
			}
		}
	}
	
	if (k == 4) { k = 5; }
	
	if (j > i && k > j) {
		return true;
	}
	return true;
}
void bCheckRowEchelon(cGaussian* _pGauss) {
	if (bCheckEchelon(_pGauss) == false) {
		return;
	}
	int i = 0;
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < 4; ++k) {
			if (_pGauss->GetValue(j, k) != 0) {
				++i;
			}
		}
	}
	if (i >= 4) {
		MessageBox(NULL, L"This is in row echelon form", L"REF/RREF CHECKER", MB_OK);
		return;
	}
	else {
		MessageBox(NULL, L"This is in reduced row echelon form", L"REF/RREF CHECKER", MB_OK);
		return;
	}
}

//SLERP Functions
void SlerpQuatToUI(HWND _hwnd, cQuaternion* _pQuat) {
	WriteToEditBox(_hwnd, IDC_EDIT10, _pQuat->GetQuatX());
	WriteToEditBox(_hwnd, IDC_EDIT11, _pQuat->GetQuatY());
	WriteToEditBox(_hwnd, IDC_EDIT12, _pQuat->GetQuatZ());
	WriteToEditBox(_hwnd, IDC_EDIT13, _pQuat->GetQuatW());
}
void UIQuatAToSlerpQuat(HWND _hwnd) {
	pSlerpQuatA->SetQuatX(ReadFromEditBox(_hwnd, IDC_EDIT1));
	pSlerpQuatA->SetQuatY(ReadFromEditBox(_hwnd, IDC_EDIT2));
	pSlerpQuatA->SetQuatZ(ReadFromEditBox(_hwnd, IDC_EDIT3));
	pSlerpQuatA->SetQuatW(ReadFromEditBox(_hwnd, IDC_EDIT4));
}
void UIQuatBToSlerpQuat(HWND _hwnd) {
	pSlerpQuatB->SetQuatX(ReadFromEditBox(_hwnd, IDC_EDIT5));
	pSlerpQuatB->SetQuatY(ReadFromEditBox(_hwnd, IDC_EDIT6));
	pSlerpQuatB->SetQuatZ(ReadFromEditBox(_hwnd, IDC_EDIT7));
	pSlerpQuatB->SetQuatW(ReadFromEditBox(_hwnd, IDC_EDIT8));
}
void MatrixToSlerpUI(HWND _hwnd, cMatrix* _pMatrix) {
	WriteToEditBox(_hwnd, IDC_EDIT34, _pMatrix->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT35, _pMatrix->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT36, _pMatrix->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT37, _pMatrix->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT38, _pMatrix->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT39, _pMatrix->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT40, _pMatrix->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT41, _pMatrix->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT42, _pMatrix->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT43, _pMatrix->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT44, _pMatrix->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT45, _pMatrix->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT46, _pMatrix->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT47, _pMatrix->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT48, _pMatrix->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT49, _pMatrix->GetElement(3, 3));
}

//Transformation Functions
void ToUiA(HWND _hwnd, cMatrix* _pMatrix) {
	WriteToEditBox(_hwnd, IDC_EDIT_A00, _pMatrix->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A01, _pMatrix->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A02, _pMatrix->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A03, _pMatrix->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A10, _pMatrix->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A11, _pMatrix->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A12, _pMatrix->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A13, _pMatrix->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A20, _pMatrix->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A21, _pMatrix->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A22, _pMatrix->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A23, _pMatrix->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_A30, _pMatrix->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_A31, _pMatrix->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_A32, _pMatrix->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_A33, _pMatrix->GetElement(3, 3));
}
void ToUiB(HWND _hwnd, cMatrix* _pMatrix) {
	cMatrix* pTemp = new cMatrix;
	cMatrix::Transpose(_pMatrix, pTemp);
	WriteToEditBox(_hwnd, IDC_EDIT_B00, pTemp->GetElement(0, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B01, pTemp->GetElement(0, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B02, pTemp->GetElement(0, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B03, pTemp->GetElement(0, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B10, pTemp->GetElement(1, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B11, pTemp->GetElement(1, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B12, pTemp->GetElement(1, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B13, pTemp->GetElement(1, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B20, pTemp->GetElement(2, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B21, pTemp->GetElement(2, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B22, pTemp->GetElement(2, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B23, pTemp->GetElement(2, 3));
	WriteToEditBox(_hwnd, IDC_EDIT_B30, pTemp->GetElement(3, 0));
	WriteToEditBox(_hwnd, IDC_EDIT_B31, pTemp->GetElement(3, 1));
	WriteToEditBox(_hwnd, IDC_EDIT_B32, pTemp->GetElement(3, 2));
	WriteToEditBox(_hwnd, IDC_EDIT_B33, pTemp->GetElement(3, 3));
	delete pTemp;
	pTemp = nullptr;
}
#pragma endregion UI Input/ Output functions

//Window Procedure
LRESULT CALLBACK WindowProc(HWND _hwnd,	UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

	// What is the message?
	switch (_msg) {
	case WM_CREATE:	{
		// Do initialization stuff here.

		// Return Success.
		return (0);
	}
	break;
	case WM_PAINT: {
		// Simply validate the window.
		hdc = BeginPaint(_hwnd, &ps);

		// You would do all your painting here...

		EndPaint(_hwnd, &ps);

		// Return Success.
		return (0);
	}
	break;
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case ID_EXIT: {
			PostQuitMessage(0);
			break;
		}
		case ID_CALCULATOR_MATRIX: {
			ShowWindow(g_hDlgMatrix, SW_SHOWNORMAL);
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION: {
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			break;

		}
			//open the matrix dialog
		case ID_CALCULATOR_GAUSSIAN: {
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			break;
		}
			//open the gaussian dialog
		case ID_CALCULATOR_QUATERNION: {
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			break;
		}
			//open the quaternion dialog
		case ID_CALCULATOR_SLERP: {
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
			break;
		}
		default: break;
		}
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

#pragma region
BOOL CALLBACK MatrixDlgProc(HWND _hwnd,	UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	switch (_msg) {
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case ID_IDENTITY_A: {
			UIToMatrixA(_hwnd);
			pMatrixA->Identity(pMatrixA);
			MatrixToUIA(_hwnd, pMatrixA);
			break;
		}
		case ID_DET_A: {
			UIToMatrixA(_hwnd);
			pMatrixA->Transpose(pMatrixA, pMatrixR);
			pMatrixA->Determinant(pMatrixR);
			WriteToEditBox(_hwnd, IDC_EDIT_DetA, pMatrixA->Determinant(pMatrixA));
			break;
		}
		case ID_TRANSPOSE_A: {
			UIToMatrixA(_hwnd);
			pMatrixA->Transpose(pMatrixA, pMatrixR);
			MatrixToUIA(_hwnd, pMatrixR);
			break;
		}
		case ID_INVERSE_A: {
			UIToMatrixA(_hwnd);
			pMatrixA->Inverse(pMatrixA, pMatrixR);
			MatrixToUIA(_hwnd, pMatrixR);
			break;
		}
		case ID_S_MULTI_A: {
			UIToMatrixA(_hwnd);
			pMatrixA->Multiply(ReadFromEditBox(_hwnd, IDC_EDIT_AScaled), pMatrixA, pMatrixR);
			MatrixToUIA(_hwnd, pMatrixR);
			break;
		}
		case ID_IDENTITY_B: {
			UIToMatrixB(_hwnd);
			pMatrixB->Identity(pMatrixB);
			MatrixToUIB(_hwnd, pMatrixB);
			break;
		}
		case ID_DET_B: {
			UIToMatrixB(_hwnd);
			pMatrixB->Transpose(pMatrixB, pMatrixR);
			pMatrixB->Determinant(pMatrixR);
			WriteToEditBox(_hwnd, IDC_EDIT_DetB, pMatrixB->Determinant(pMatrixB));
			break;
		}
		case ID_TRANSPOSE_B: {
			UIToMatrixB(_hwnd);
			pMatrixB->Transpose(pMatrixB, pMatrixR);
			MatrixToUIB(_hwnd, pMatrixR);
			break;
		}
		case ID_INVERSE_B: {
			UIToMatrixB(_hwnd);
			pMatrixB->Inverse(pMatrixB, pMatrixR);
			MatrixToUIB(_hwnd, pMatrixR);
			break;
		}
		case ID_S_MULTI_B: {
			UIToMatrixB(_hwnd);
			pMatrixB->Multiply(ReadFromEditBox(_hwnd, IDC_EDIT_BScaled), pMatrixB, pMatrixR);
			MatrixToUIB(_hwnd, pMatrixR);
			break;
		}
		case ID_ADD: {
			UIToMatrixA(_hwnd);
			UIToMatrixB(_hwnd);
			cMatrix::Add(pMatrixA, pMatrixB, pMatrixR);
			MatrixToUIR(_hwnd, pMatrixR);
			break;
		}
		case ID_A_SUB_B: {
			UIToMatrixA(_hwnd);
			UIToMatrixB(_hwnd);
			cMatrix::Subtract(pMatrixA, pMatrixB, pMatrixR);
			MatrixToUIR(_hwnd, pMatrixR);
			break;
		}
		case ID_A_MULTI_B: {
			UIToMatrixA(_hwnd);
			UIToMatrixB(_hwnd);
			cMatrix::Multiply(pMatrixA, pMatrixB, pMatrixR);
			MatrixToUIR(_hwnd, pMatrixR);
			break;
		}
		case ID_B_MULTI_A: {
			UIToMatrixA(_hwnd);
			UIToMatrixB(_hwnd);
			cMatrix::Multiply(pMatrixB, pMatrixA, pMatrixR);
			MatrixToUIR(_hwnd, pMatrixR);
			break;
		}
		default: break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE: {
		ShowWindow(_hwnd, SW_HIDE);
		cMatrix::Zero(pMatrixA);
		cMatrix::Zero(pMatrixB);
		cMatrix::Zero(pMatrixR);
		return TRUE;
		break;
	}
	default: break;
	}
	return FALSE;
}
BOOL CALLBACK GaussianDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	switch (_msg) {
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case IDC_EDIT1: {
			pGauss->SetValue(0, 0, ReadFromEditBox(_hwnd, IDC_EDIT1));
			break;
		}
		case IDC_EDIT2: {
			pGauss->SetValue(0, 1, ReadFromEditBox(_hwnd, IDC_EDIT2));
			break;
		}
		case IDC_EDIT3: {
			pGauss->SetValue(0, 2, ReadFromEditBox(_hwnd, IDC_EDIT3));
			break;
		}
		case IDC_EDIT4: {
			pGauss->SetValue(0, 3, ReadFromEditBox(_hwnd, IDC_EDIT4));
			break;
		}
		case IDC_EDIT5: {
			pGauss->SetValue(1, 0, ReadFromEditBox(_hwnd, IDC_EDIT5));
			break;
		}
		case IDC_EDIT6: {
			pGauss->SetValue(1, 1, ReadFromEditBox(_hwnd, IDC_EDIT6));
			break;
		}
		case IDC_EDIT7: {
			pGauss->SetValue(1, 2, ReadFromEditBox(_hwnd, IDC_EDIT7));
			break;
		}
		case IDC_EDIT8: {
			pGauss->SetValue(1, 3, ReadFromEditBox(_hwnd, IDC_EDIT8));
			break;
		}
		case IDC_EDIT9: {
			pGauss->SetValue(2, 0, ReadFromEditBox(_hwnd, IDC_EDIT9));
			break;
		}
		case IDC_EDIT10: {
			pGauss->SetValue(2, 1, ReadFromEditBox(_hwnd, IDC_EDIT10));
			break;
		}
		case IDC_EDIT11: {
			pGauss->SetValue(2, 2, ReadFromEditBox(_hwnd, IDC_EDIT11));
			break;
		}
		case IDC_EDIT12: {
			pGauss->SetValue(2, 3, ReadFromEditBox(_hwnd, IDC_EDIT12));
			break;
		}
		case IDC_BUTTON1: {
			pGauss->Multiply(ReadFromEditBox(_hwnd, IDC_EDIT13), ReadFromEditBox(_hwnd, IDC_EDIT14));
			GaussToUi(_hwnd, pGauss);
			bCheckRowEchelon(pGauss);
			break;
		}
		case IDC_BUTTON2: {
			pGauss->Swap(ReadFromEditBox(_hwnd, IDC_EDIT16), ReadFromEditBox(_hwnd, IDC_EDIT17));
			GaussToUi(_hwnd, pGauss);
			bCheckRowEchelon(pGauss);
			break;
		}
		case IDC_BUTTON3: {
			pGauss->AddMulti(ReadFromEditBox(_hwnd, IDC_EDIT20), ReadFromEditBox(_hwnd, IDC_EDIT22), ReadFromEditBox(_hwnd, IDC_EDIT19));
			GaussToUi(_hwnd, pGauss);
			bCheckRowEchelon(pGauss);
			break;
		}
		default: break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE: {
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default: break;
	}
	return FALSE;
}
BOOL CALLBACK QuaternionDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	switch (_msg) {
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case IDC_EDIT1: {
			pQuatA->SetQuatX(ReadFromEditBox(_hwnd, IDC_EDIT1));
			break;
		}
		case IDC_EDIT2: {
			pQuatA->SetQuatY(ReadFromEditBox(_hwnd, IDC_EDIT2));
			break;
		}
		case IDC_EDIT3: {
			pQuatA->SetQuatZ(ReadFromEditBox(_hwnd, IDC_EDIT3));
			break;
		}
		case IDC_EDIT4: {
			pQuatA->SetQuatW(ReadFromEditBox(_hwnd, IDC_EDIT4));
			break;
		}
		case IDC_EDIT5: {
			pQuatB->SetQuatX(ReadFromEditBox(_hwnd, IDC_EDIT5));
			break;
		}
		case IDC_EDIT6: {
			pQuatB->SetQuatY(ReadFromEditBox(_hwnd, IDC_EDIT6));
			break;
		}
		case IDC_EDIT7: {
			pQuatB->SetQuatZ(ReadFromEditBox(_hwnd, IDC_EDIT7));
			break;
		}
		case IDC_EDIT8: {
			pQuatB->SetQuatW(ReadFromEditBox(_hwnd, IDC_EDIT8));
			break;
		}
		case IDC_BUTTON1: {
			cQuaternion::Add(pQuatA, pQuatB, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON5: {
			cQuaternion::Subtract(pQuatA, pQuatB, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON6: {
			cQuaternion::Subtract(pQuatB, pQuatA, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON2: {
			cQuaternion::Multiply(pQuatA, pQuatB, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON7: {
			cQuaternion::Multiply(pQuatB, pQuatA, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON3: {
			cQuaternion::ComplexConjugate(pQuatA, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON9: {
			cQuaternion::ComplexConjugate(pQuatB, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON10: {
			WriteToEditBox(_hwnd, IDC_EDIT14, cQuaternion::Magnitude(pQuatA));
			break;
		}
		case IDC_BUTTON11: {
			WriteToEditBox(_hwnd, IDC_EDIT14, cQuaternion::Magnitude(pQuatB));
			break;
		}
		case IDC_BUTTON12: {
			cQuaternion::Inverse(pQuatA, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON13: {
			cQuaternion::Inverse(pQuatB, pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON14: {
			cQuaternion::Multiply(pQuatA, ReadFromEditBox(_hwnd, IDC_EDIT9), pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON15: {
			cQuaternion::Multiply(pQuatB, ReadFromEditBox(_hwnd, IDC_EDIT9), pQuatR);
			QuatToUI(_hwnd, pQuatR);
			break;
		}
		case IDC_BUTTON8: {
			WriteToEditBox(_hwnd, IDC_EDIT14, cQuaternion::DotProduct(pQuatA, pQuatB));
			break;
		}
		}
		return TRUE;
		break;
	}
	case WM_CLOSE: {
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:break;
	}
	return FALSE;
}
BOOL CALLBACK SLERPDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	switch (_msg) {
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case IDC_BUTTON1: {
			float fScalar = ReadFromEditBox(_hwnd, IDC_EDIT9);
			UIQuatAToSlerpQuat(_hwnd);
			UIQuatBToSlerpQuat(_hwnd);
			cQuaternion::Slerp(pSlerpQuatA, pSlerpQuatB, fScalar, pSlerpQuatResult);
			SlerpQuatToUI(_hwnd, pSlerpQuatResult);
			cQuaternion::QuatToRotMatrix(pSlerpQuatResult, pSlerpMatrix);
			MatrixToSlerpUI(_hwnd, pSlerpMatrix);
			break;
		}
		case IDC_BUTTON2: {
			cQuaternion::QuatToRotMatrix(pSlerpQuatA, pSlerpMatrix);
			MatrixToSlerpUI(_hwnd, pSlerpMatrix);
			break;
		}
		case IDC_BUTTON3: {
			cQuaternion::QuatToRotMatrix(pSlerpQuatB, pSlerpMatrix);
			MatrixToSlerpUI(_hwnd, pSlerpMatrix);
			break;
		}
		case IDC_BUTTON4: {
			cQuaternion::QuatToRotMatrix(pSlerpQuatResult, pSlerpMatrix);
			MatrixToSlerpUI(_hwnd, pSlerpMatrix);
			break;
		}

			return TRUE;
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE: {
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default: break;
	}
	return FALSE;
}
BOOL CALLBACK TransformationDlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {
	HWND hTransformBox = GetDlgItem(_hwnd, IDC_COMBO1);
	HWND hProjBox = GetDlgItem(_hwnd, IDC_COMBO2);
	int iIndex = 0;
	int iOpt;
	switch (_msg) {
	case WM_INITDIALOG: {
		//Sending the initial matrices to the UI
		ToUiA(_hwnd, pTransformationMatrix);

		//Setting Transformation Option Box values
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Reset to Identity Matrix"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Generate Scale Matrix"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Generate Translate Matrix"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Generate Rotate Matrix"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Generate Projection Matrix"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Concatenate Rotation with Previous"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Concatenate Scale with Previous"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Concatenate Translation with Previous"));
		SendMessage(hTransformBox, CB_ADDSTRING, 0, (LPARAM)(L"Concatenate Projection with Previous"));
		//Setting the default option to index 0 ("Choose...")
		SendMessage(hTransformBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

		//Setting Projection Option Box Values
		SendMessage(hProjBox, CB_ADDSTRING, 0, (LPARAM)(L"X Axis Projection"));
		SendMessage(hProjBox, CB_ADDSTRING, 0, (LPARAM)(L"Y Axis Projection"));
		SendMessage(hProjBox, CB_ADDSTRING, 0, (LPARAM)(L"Z Axis Projection"));
		//Setting the default option to index 0 ("X Axis Projection")
		SendMessage(hProjBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
		return TRUE;
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(_wparam)) {
		case IDC_BUTTON4: {
			iIndex = SendMessage(hTransformBox, CB_GETCURSEL, 0, 0);
			switch (iIndex) {
			case 0: {
				//Reset Matrices back to identity
				cMatrix::Identity(pTransformationMatrix);
				cMatrix::Identity(pTranslationMatrix);
				cMatrix::Identity(pScaleMatrix);
				cMatrix::Identity(pRotateMatrix);
				cMatrix::Identity(pProjectionMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 1: {
				//Generating Scale Matrix
				cMatrix::Identity(pScaleMatrix);
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT1);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT2);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT3);
				cMatrix::Scale(fX, fY, fZ, pScaleMatrix);
				cMatrix::Copy(pScaleMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 2: {
				//Generating Translation Matrix
				cMatrix::Identity(pTranslationMatrix);
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT4);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT5);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT6);
				cMatrix::Translation(fX, fY, fZ, pTranslationMatrix);
				cMatrix::Copy(pTranslationMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 3: {
				//Generating Rotate Matrix
				cMatrix::Identity(pRotateMatrix);
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT7);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT8);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT9);
				float fTheta = ReadFromEditBox(_hwnd, IDC_EDIT10);
				cMatrix::Rotate(fX, fY, fZ, fTheta, pRotateMatrix);
				cMatrix::Copy(pRotateMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 4: {
				//Generating Projection Matrix
				cMatrix::Identity(pProjectionMatrix);
				iOpt = SendMessage(hProjBox, CB_GETCURSEL, 0, 0);
				cMatrix::Project(iOpt, ReadFromEditBox(_hwnd, IDC_EDIT14), pProjectionMatrix);
				cMatrix::Copy(pProjectionMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 5: {
				//Concatenation with Rotation Matrix
				//Generating the Rotation matrix
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT7);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT8);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT9);
				float fTheta = ReadFromEditBox(_hwnd, IDC_EDIT10);
				cMatrix::Rotate(fX, fY, fZ, fTheta, pRotateMatrix);
				cMatrix::Multiply(pTransformationMatrix, pRotateMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 6: {
				//Concatenation with Scale Matrix
				//Generating the Scale Matrix
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT1);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT2);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT3);
				cMatrix::Scale(fX, fY, fZ, pScaleMatrix);
				cMatrix::Multiply(pTransformationMatrix, pScaleMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 7: {
				//Concatenation with Translate Matrix
				float fX = ReadFromEditBox(_hwnd, IDC_EDIT4);
				float fY = ReadFromEditBox(_hwnd, IDC_EDIT5);
				float fZ = ReadFromEditBox(_hwnd, IDC_EDIT6);
				cMatrix::Translation(fX, fY, fZ, pTranslationMatrix);
				cMatrix::Multiply(pTransformationMatrix, pTranslationMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			case 8: {
				//Generating Projection Matrix
				cMatrix::Identity(pProjectionMatrix);
				iOpt = SendMessage(hProjBox, CB_GETCURSEL, 0, 0);
				cMatrix::Project(iOpt, ReadFromEditBox(_hwnd, IDC_EDIT14), pProjectionMatrix);
				cMatrix::Multiply(pTransformationMatrix, pProjectionMatrix, pTransformationMatrix);
				ToUiA(_hwnd, pTransformationMatrix);
				ToUiB(_hwnd, pTransformationMatrix);
				break;
			}
			default: break;
			}
			break;
		}
		default: break;
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE: {
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default: break;
	}
	return FALSE;
}
#pragma endregion Calculator Dialogue Procedures


int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow) {
	WNDCLASSEX winclass;		// This will hold the class we create.
	HWND hwnd;					// Generic window handle.
	MSG msg;					// Generic message.

	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass)) {
		return (0);
	}

	//Load the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

	// create the window
	hwnd = CreateWindowEx(NULL,				// Extended style.
		WINDOW_CLASS_NAME,					// Class.
		L"Your Basic Window",				// Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// Other Window settings
		50, 50,								// Initial x,y.
		300, 300,							// Initial width, height.
		NULL,								// Handle to parent.
		g_hMenu,							// Handle to menu.
		_hInstance,							// Instance of this application.
		NULL);								// Extra creation parameters.

	if (!(hwnd)) {
		return (0);
	}

	//Create the modeless dialog boxes for the calculators
	g_hDlgMatrix = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogMatrix), hwnd, MatrixDlgProc);
	g_hDlgTransformation = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogTransformations), hwnd, TransformationDlgProc);
	g_hDlgGaussian = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogGaussian), hwnd, GaussianDlgProc);
	g_hDlgQuaternion = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogQuaternion), hwnd, QuaternionDlgProc);
	g_hDlgSLERP = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogSLERP), hwnd, SLERPDlgProc);

	// Enter main event loop
	while (true) {
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Test if this is a quit.
			if (msg.message == WM_QUIT) {
				break;
			}

			if ((g_hDlgMatrix == 0 && g_hDlgTransformation == 0 && g_hDlgGaussian == 0 && g_hDlgQuaternion == 0 && g_hDlgSLERP == 0) ||
				(!IsDialogMessage(g_hDlgMatrix, &msg) && !IsDialogMessage(g_hDlgTransformation, &msg) && !IsDialogMessage(g_hDlgGaussian, &msg) && !IsDialogMessage(g_hDlgQuaternion, &msg) && !IsDialogMessage(g_hDlgSLERP, &msg))) {
				// Translate any accelerator keys.
				TranslateMessage(&msg);
				// Send the message to the window proc.
				DispatchMessage(&msg);
			}
		}
	}

	//Clearing up memory
	delete pMatrixA;
	delete pMatrixB;
	delete pMatrixR;
	delete pQuatA;
	delete pQuatB;
	delete pQuatR;
	delete pGauss;
	delete pSlerpQuatA;
	delete pSlerpQuatB;
	delete pSlerpQuatResult;
	delete pTransformationMatrix;
	delete pTranslationMatrix;
	delete pScaleMatrix;
	delete pRotateMatrix;
	delete pProjectionMatrix;

	//Redirecting pointers
	pMatrixA = nullptr;
	pMatrixB = nullptr;
	pMatrixR = nullptr;
	pQuatA = nullptr;
	pQuatB = nullptr;
	pQuatR = nullptr;
	pGauss = nullptr;
	pSlerpQuatA = nullptr;
	pSlerpQuatB = nullptr;
	pSlerpQuatResult = nullptr;
	pTransformationMatrix = nullptr;
	pTranslationMatrix = nullptr;
	pScaleMatrix = nullptr;
	pRotateMatrix = nullptr;
	pProjectionMatrix = nullptr;


	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}


