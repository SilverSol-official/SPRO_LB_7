//Кожен варіант лабораторної роботи передбачає створення 2 - х динамічно приєднуваних бібліотек.
//Одна з них повинна бути приєднана явно, інша неявно.Використати створені DLL в іншій програмі.
//Варіант 6
//Перша бібліотека має функції пошуку мінімуму, максимуму, середнього значення серед елементів певних 
//відрізків масиву цілих чисел(в функцію передається покажчик на масив, число елементів масиву, 
//кількість відрізків, на які слід розділити масив).Друга бібліотека містить функції побудови діаграм, 
//що ілюструють залежність середніх значень від номеру відрізку.


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include <windows.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#pragma comment(lib,"Dll2.lib")
#include "C:\Users\Dimchik\source\repos\SPRO_LB_7\DLL2.h";

HDC hdc;
HWND hWnd;
HINSTANCE hInst;
int Arr[] = { 60, 36, 56, 12, 116, 9, 30, 22, 9, 15 };
double* Avg_Result;
int* Min_Result, * Max_Result;
HMODULE hDll;
typedef double* (*Avg)(int*, int, unsigned short);
typedef int* (*Min)(int*, int, unsigned short);
typedef int* (*Max)(int*, int, unsigned short);
Avg AvgDLL;
Min MinDLL;
Max MaxDLL;

static TCHAR szWindowClass[] = L"win32app";
static TCHAR szTitle[] = L"Лабораторна робота 7";
char buf[256];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Главная часть программы-------------------------------------------------------------------------------------
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
	wcex.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Помилка реєстрації класу!", L"Лабораторна робота 7", NULL);
		return 0;
	}
	// ------------------------------------------------------------------------------------------------------------

	// Создаём окно---------------------------------------------------------------------------------------
	hInst = hInstance;

	int width = 800, height = 500; //Для размещения окна по центру экрана

	HWND hWnd = CreateWindow(
		szWindowClass,                // Имя класса                   
		szTitle, // Текст заголовка
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,        // Стиль окна                                             
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,                  // Позиция левого верхнего угла  
		width, height,                  // Ширина и высота окна    
		(HWND)NULL,                // Указатель на родительское окно NULL    
		(HMENU)NULL,               // Используется меню класса окна              
		(HINSTANCE)hInstance,       // Указатель на текущее приложение
		NULL);                  // Передается в качестве lParam в событие WM_CREATE

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
		hDll = LoadLibrary(L"..\\Dll1.dll");
		if (hDll != 0)
		{
			MinDLL = (Min)GetProcAddress(hDll, "Min");
			MaxDLL = (Max)GetProcAddress(hDll, "Max");	
			AvgDLL = (Avg)GetProcAddress(hDll, "Avg");
			Min_Result = MinDLL(Arr, 10, 4);
			Max_Result = MaxDLL(Arr, 10, 3);
			Avg_Result = AvgDLL(Arr, 10, 5);
			FreeLibrary(hDll);
		}
		else
		{
			FreeLibrary(hDll);
			MessageBox(hWnd, L"Dll не було знайдено!",L"Помилка", MB_OK);
			PostQuitMessage(0);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			
		default:
			return ERROR;
		}
		break;
	case WM_PAINT:
	{
		WCHAR tmp[256];
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 20, L"Елементи масиву:", 16);
		for (int i = 0; i < 10; i++)
		{
			TextOut(hdc, 150 + i * 40, 20, tmp, swprintf_s(tmp, 256, L"%i;", Arr[i]));
		}
		TextOut(hdc, 10, 50, L"Середнє значення у відрізках:", 29);
		for (int i = 0; i < 5; i++)
		{
			TextOut(hdc, 260 + i * 60, 50, tmp, swprintf_s(tmp, 256, L"%.2f;", Avg_Result[i]));
		}
		TextOut(hdc, 10, 80, L"Мінімальне значення у відрізках:", 32);
		for (int i = 0; i < 4; i++)
		{
			TextOut(hdc, 260 + i * 40, 80, tmp, swprintf_s(tmp, 256, L"%i;", Min_Result[i]));
		}
		TextOut(hdc, 10, 110, L"Максимальне значення у відрізках:", 33);
		for (int i = 0; i < 3; i++)
		{
			TextOut(hdc, 260 + i * 40, 110, tmp, swprintf_s(tmp, 256, L"%i;", Max_Result[i]));
		}
		RoundDiagram(hdc, 150, 250, Avg_Result, 5);
		Graphic(hdc, 320, 250, Avg_Result, 5);
		EndPaint(hWnd, &ps);
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