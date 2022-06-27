#pragma once
#include <windows.h>
extern "C" _declspec(dllexport) void Graphic(HDC hDc, int x, int y, double* Arr, unsigned short sect);
extern "C" _declspec(dllexport) void RoundDiagram(HDC hDc, int x, int y, double* Arr, unsigned short sect);