// ShapeApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ShapeApp.h"
#include "Shape.h"
#include "Point.h"
#include "Ellipse.h"
#include "Rect.h"
#include "Poly.h"
#include <windowsx.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTiULe[MAX_LOADSTRING];					// The tiULe bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

												// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTiULe, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SHAPEAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHAPEAPP));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHAPEAPP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_SHAPEAPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTiULe, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static CShape* aS[][7] =
	{
		{ new CEllipse(280, 250, 200, 100), new CCircle(270, 260, 150), new CTriangle(241, 542, 444, 542, 120, 145), new CRect(180, 440, 320, 200), new CSquare(190, 500, 200), new CSemiCircle(170, 370, 160) },
		{ new CRect(650, 450, 100, 300), new CSemiCircle(470, 370, 200), new CCircle(740, 330, 190), new CSquare(550, 480, 300), new CEllipse(700, 350, 130, 220), new CTriangle(531, 422, 744, 366, 620, 135) },
		{ new CTriangle(1131, 630, 1014, 490, 880, 570), new CEllipse(990, 480, 310, 170), new CSemiCircle(970, 470, 200), new CSquare(880, 580, 210), new CCircle(1090, 430, 150), new CRect(1050, 550, 200, 350) }
	};
	static Point* aP[] = { new Point(290, 390), new Point(150, 450), new Point(250, 300), new Point(250, 550), new Point(300, 150), new Point(550, 230) };
	static CPLine* numOfLine[3];
	WCHAR tb[][80] = { L"Không cắt hình nào", L"Cắt 1 hình", L"Cắt 2 hình", L"Cắt 3 hình" };

	static int flag_control_aS = 0, columnOfaS, nPL = 3;
	for (columnOfaS = 0; aS[0][columnOfaS] != NULL; columnOfaS++);
	static int nS = sizeof(aS) / sizeof(aS[0]);
	static int nP = sizeof(aP) / sizeof(aP[0]);
	static int ptMouse = -1;
	static int tmp[] = { 2, 0, 0 };
	static int flag[] = { 2, 0, 0 };
	static int shapeOrder[] = { 0, 0, 0 };

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CHAR:
		switch (TCHAR(wParam))
		{
		case '\t':
			if (++shapeOrder[flag_control_aS] == columnOfaS) shapeOrder[flag_control_aS] = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case '+':
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->scale(1.2);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case '-':
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->scale(1 / 1.2);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case '1':
			if (++flag_control_aS == nS) flag_control_aS = 0;

			for (int i = 0; i < nS; i++)
			{
				if (i == flag_control_aS)
					tmp[i] = 2;
				else tmp[i] = 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->move(-10, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->move(10, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP:
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->move(0, -10);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			aS[flag_control_aS][shapeOrder[flag_control_aS]]->move(0, 10);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

	case WM_LBUTTONDOWN:
	{
		SetCapture(hWnd);
		int xpos = GET_X_LPARAM(lParam);
		int ypos = GET_Y_LPARAM(lParam);
		if (ptMouse == -1)
		{
			for (int a = 0; a < nP; a++)
			{
				if (abs(aP[a]->getX() - xpos) < 10)
				{
					if (abs(aP[a]->getY() - ypos) < 10)
					{
						ptMouse = a;
						break;
					}
				}
			}
		}
		else
		{
			aP[ptMouse]->set(xpos, ypos);
			ptMouse = -1;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < nS; i++)//0 to 2
			flag[i] = tmp[i];//flag (2 0 0) thay doi theo tmp

		numOfLine[0] = new StraightLine(*aP[0], *aP[1]);
		numOfLine[1] = new Curve(aP);
		numOfLine[2] = new StraightLine(*aP[4], *aP[5]);

		for (int i = 0; i < nPL; i++)
		{
			numOfLine[i]->pointOnLine(aS, flag, shapeOrder, nS);
			if (totalBalance(flag, nS) == nS) break;
		}


		//Draw Shape
		for (int i = 0; i < nS; i++)
		{
			if (i != flag_control_aS)
				fill(aS[i][shapeOrder[i]], hdc, flag[i]);
		}
		fill(aS[flag_control_aS][shapeOrder[flag_control_aS]], hdc, flag[flag_control_aS]);
		//Draw PolyLine
		for (int i = 0; i < nPL; i++)
			numOfLine[i]->draw(hdc);

		//Draw Point
		for (int i = 0; i < nP; i++)
			aP[i]->draw(hdc);

		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, tb[totalBalance(flag, nS)], lstrlen(tb[totalBalance(flag, nS)]), &rt, DT_CENTER);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY://xoa
		for (int i = 0; i < nS; i++)
			for(int j = 0; j < columnOfaS; j++)
				delete aS[i][j];
		for (int i = 0; i < nPL; i++)
			delete numOfLine[i];
		for (int i = 0; i < nP; i++)
			delete aP[i];
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
