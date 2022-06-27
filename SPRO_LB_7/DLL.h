#pragma once

#include <windows.h>

#define Import __declspec(dllimport) 



	Import void Graphic(HDC hDc, int x, int y, float* Arr, unsigned short sect);
	Import void RoundDiagram(HDC hDc, int x, int y, float* Arr, unsigned short sect);
