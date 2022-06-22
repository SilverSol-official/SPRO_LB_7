//����� ������ ����������� ������ ��������� ��������� 2 - � �������� ����������� �������.
//���� � ��� ������� ���� �������� ����, ���� ������.����������� ������� DLL � ����� �������.
//������ 6
//����� �������� �� ������� ������ ������, ���������, ���������� �������� ����� �������� ������ 
//������ ������ ����� �����(� ������� ���� - ������ �������� �� �����, ����� �������� ������, 
//������� ������, �� �� ��� �������� �����).����� �������� ������ ������� �������� ������, 
//�� ���������� ��������� ������� ������� �� ������ ������.


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#pragma warning(suppress : 4996)
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>


HDC hdc;
HWND hWnd;
HINSTANCE hInst;

static TCHAR szWindowClass[] = L"win32app";
static TCHAR szTitle[] = L"����������� ������ 7";
char buf[256];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// ������� ����� ���������-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"������� ��������� �����!", L"����������� ������ 7", NULL);
		return 0;
	}
	// ------------------------------------------------------------------------------------------------------------

	// ������ ����---------------------------------------------------------------------------------------
	hInst = hInstance;

	int width = 400, height = 250; //��� ���������� ���� �� ������ ������

	HWND hWnd = CreateWindow(
		szWindowClass,                // ��� ������                   
		szTitle, // ����� ���������
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,        // ����� ����                                             
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,                  // ������� ������ �������� ����  
		width, height,                  // ������ � ������ ����    
		(HWND)NULL,                // ��������� �� ������������ ���� NULL    
		(HMENU)NULL,               // ������������ ���� ������ ����              
		(HINSTANCE)hInstance,       // ��������� �� ������� ����������
		NULL);                  // ���������� � �������� lParam � ������� WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Win32 Guided Tour",
			0);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string temp = "";


	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		
		default:
			return ERROR;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}