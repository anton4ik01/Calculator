#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") // манифест
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include "resourse.h"
#include <cmath>
#include <string>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateButton(HWND); // функция создания кнопок
HFONT hFont1 =    CreateFont(35, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Calibri"));//шрифты
HFONT hFont2 =	  CreateFont(25, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Calibri"));
HFONT hFontMode = CreateFont(55, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Calibri"));
TCHAR s_ModeN[] = "Обычный";
TCHAR s_ModeE[] = "Инженерный";
TCHAR s_ModeP[] = "Программист";
TCHAR szClassName[] = "My Class";

char* FirstOperand  = new char[32];
char* SecondOperand = new char[32];
int Sign = 0; // действие
int activemodeprogrammist = 0; // 0 - HEX, 1 - DEX, 2 - OCT, 3 - BIN
int activewindowmode = 0; // Для определения режима 0 = обычный , 1 = инженерный , 2 - программист

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbWndExtra =    0;
	wc.cbClsExtra =    0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor =       LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon =         LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm =       LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance =     hInstance;
	wc.lpfnWndProc =   WndProc;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName =  nullptr;
	wc.style =         CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wc)) return EXIT_FAILURE; // Регистрация класса
	if (hwnd = CreateWindow(wc.lpszClassName, "Calculator", WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN) / 4,GetSystemMetrics(SM_CYSCREEN) / 4, 336, 539, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, nullptr, 0, 0)) 
	{ 
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		
		CreateButton(hWnd);
		hmenu1 = CreateMenu();
		hPopupMenu1 = CreatePopupMenu();
		AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu1, "&Режим");
		{
			AppendMenu(hPopupMenu1, MF_STRING, ID_regular, "Обычный");
			AppendMenu(hPopupMenu1, MF_STRING, ID_engineer, "Инженерный");
			AppendMenu(hPopupMenu1, MF_STRING, ID_programmer, "Программист");
			AppendMenu(hPopupMenu1, MF_SEPARATOR, 1000, "");
			AppendMenu(hPopupMenu1, MF_STRING, ID_EXITALL, "Выход");
		}
		SetMenu(hWnd, hmenu1);
		FirstOperand[0] = 0;
		SecondOperand[0] = 0;
	}
	return 0;
	case WM_GETMINMAXINFO: //Получили сообщение от Винды
	{
		MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
		POINT Min = { 336, 539 };
		POINT  Max = { 1920, 1080 };
		pInfo->ptMinTrackSize = Min; // Установили минимальный размер
		pInfo->ptMaxTrackSize = Max; // Установили максимальный размер
		return 0;
	}
	case WM_SIZE:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (activewindowmode == 0)
		{
			SetWindowPos(Edit, nullptr, rc.right * 0, rc.bottom /8 *1, rc.right, rc.bottom / 3.65, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(EditMode, nullptr, rc.right * 0, rc.bottom * 0, rc.right, rc.bottom / 8, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_NEG, nullptr, rc.right * 0, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Zero, nullptr, rc.right * 0.25, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Point, nullptr, rc.right * 0.5, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Equally, nullptr, rc.right * 0.75, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_1, nullptr, rc.right * 0, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_2, nullptr, rc.right * 0.25, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_3, nullptr, rc.right * 0.5, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Plus, nullptr, rc.right * 0.75, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_4, nullptr, rc.right * 0, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_5, nullptr, rc.right * 0.25, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_6, nullptr, rc.right * 0.5, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Minus, nullptr, rc.right * 0.75, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_7, nullptr, rc.right * 0, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_8, nullptr, rc.right * 0.25, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_9, nullptr, rc.right * 0.5, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Multiply, nullptr, rc.right * 0.75, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Clear_active, nullptr, rc.right * 0, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_C, nullptr, rc.right * 0.25, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_CE, nullptr, rc.right * 0.5, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Divided, nullptr, rc.right * 0.75, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Percent, nullptr, rc.right * 0, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Square, nullptr, rc.right * 0.25, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Square2, nullptr, rc.right * 0.5, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_OneDividedToX, nullptr, rc.right * 0.75, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		else if(activewindowmode == 1)
		{
			SetWindowPos(Edit, nullptr, (double)rc.right * 0, (double)rc.bottom * 0.125, rc.right, rc.bottom / 3.43, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(EditMode, nullptr, (double)rc.right * 0, (double)rc.bottom * 0, rc.right, rc.bottom / 8, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Equally, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Point, nullptr,( double)rc.right * 0.6, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Zero, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Ln, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_xsquare3, nullptr, rc.right * 0, (double)rc.bottom /12*11, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Plus, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_3, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_2, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_1, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_NEG, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Minus, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_6, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_5, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_4, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Fact, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Multiply, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_9, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_8, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_7, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Pi, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Divided, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_CE, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_C, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Clear_active, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_OneDividedToX, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Mod, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Exp, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Log, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_10square, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Square, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Tan, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Cos, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Sin, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_xsquarey, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Square2, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		else if (activewindowmode == 2)
		{
			SetWindowPos(EditMode, nullptr, (double)rc.right * 0, (double)rc.bottom * 0, rc.right, rc.bottom / 12*1.5, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(Edit, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 1.5, rc.right, rc.bottom / 12 * 1.5, SWP_NOZORDER | SWP_NOOWNERZORDER);
			
			SetWindowPos(button_Equally, nullptr, (double)rc.right /6 * 5, (double)rc.bottom / 12 * 11, rc.right/6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Plus, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Minus, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Multiply, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Divided, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Point, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_3, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_6, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_9, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_CE, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_Zero, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_2, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_5, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_8, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_C, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_NEG, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_1, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_4, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_7, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Clear_active, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_F, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_D, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_B, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Mod, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Xor, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_E, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(buttonC, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_A, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_And, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Not, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(button_BIN, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 6, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_OCT, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 5, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_DEC, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 4, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_HEX, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 3, rc.right / 6, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);

			SetWindowPos(EditBin, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 6, rc.right / 6*5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(EditOct, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 5, rc.right / 6*5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(EditDec, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 4, rc.right / 6*5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(EditHex, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 3, rc.right / 6*5, rc.bottom / 12, SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
	}return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_regular:
		{
			FirstOperand[0] = 0;
			SecondOperand[0] = 0;
			activewindowmode = 0;
			EnableWindow(button_Point, true);
			RECT rc;
		GetClientRect(hWnd, &rc);
			SetWindowText(EditMode, s_ModeN); //Изменить текст в EditMode
			SetWindowText(Edit, "0");
			SetWindowPos(Edit, nullptr, rc.right * 0, rc.bottom / 8 * 1, rc.right, rc.bottom / 3.65, SWP_SHOWWINDOW);
			SetWindowPos(EditMode, nullptr, rc.right * 0, rc.bottom * 0, rc.right, rc.bottom / 8, SWP_SHOWWINDOW);
			SetWindowPos(button_Equally, nullptr, rc.right * 0.75, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Plus, nullptr, rc.right * 0.75, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Minus, nullptr, rc.right * 0.75, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Multiply, nullptr, rc.right * 0.75, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Divided, nullptr, rc.right * 0.75, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_OneDividedToX, nullptr, rc.right * 0.75, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Point, nullptr, rc.right * 0.5, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_3, nullptr, rc.right * 0.5, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_6, nullptr, rc.right * 0.5, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_9, nullptr, rc.right * 0.5, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_CE, nullptr, rc.right * 0.5, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Square, nullptr, rc.right * 0.5, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Zero, nullptr, rc.right * 0.25, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_2, nullptr, rc.right * 0.25, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_5, nullptr, rc.right * 0.25, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_8, nullptr, rc.right * 0.25, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_C, nullptr, rc.right * 0.25, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Square2, nullptr, rc.right * 0.25, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_NEG, nullptr, rc.right * 0, rc.bottom * 0.9, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_1, nullptr, rc.right * 0, rc.bottom * 0.8, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_4, nullptr, rc.right * 0, rc.bottom * 0.7, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_7, nullptr, rc.right * 0, rc.bottom * 0.6, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Clear_active, nullptr, rc.right * 0, rc.bottom * 0.5, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			SetWindowPos(button_Percent, nullptr, rc.right * 0, rc.bottom * 0.4, rc.right / 4, rc.bottom / 10, SWP_SHOWWINDOW);
			ShowWindow(button_Pi, 0);
			ShowWindow(button_Fact, 0);
			ShowWindow(button_Cos, 0);
			ShowWindow(button_Log, 0);
			ShowWindow(button_Tan, 0);
			ShowWindow(button_Sin, 0);
			ShowWindow(button_Ln, 0);
			ShowWindow(button_xsquare3, 0);
			ShowWindow(button_10square, 0);
			ShowWindow(button_Mod, 0);
			ShowWindow(button_Exp, 0);
			ShowWindow(button_xsquarey, 0);
			ShowWindow(button_And, 0);
			ShowWindow(button_A, 0);
			ShowWindow(button_B, 0);
			ShowWindow(buttonC, 0);
			ShowWindow(button_D, 0);
			ShowWindow(button_E, 0);
			ShowWindow(button_F, 0);
			ShowWindow(button_Not, 0);
			ShowWindow(button_Xor, 0);
			ShowWindow(EditHex, 0);
			ShowWindow(EditDec, 0);
			ShowWindow(EditOct, 0);
			ShowWindow(EditBin, 0);
			ShowWindow(button_HEX, 0);
			ShowWindow(button_DEC, 0);
			ShowWindow(button_OCT, 0);
			ShowWindow(button_BIN, 0);
			SendMessage(button_NEG, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_1, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_2, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_3, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_4, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_5, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_6, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_7, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_8, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_9, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Zero, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Point, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Plus, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Equally, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Minus, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Multiply, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Divided, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_C, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_CE, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Clear_active, WM_SETFONT, (WPARAM)hFont1, NULL);
			break;
		}
		case ID_engineer:
		{
			FirstOperand[0] = 0;
			SecondOperand[0] = 0;
			activewindowmode = 1;
			EnableWindow(button_Point, true);
			SetWindowText(Edit, "0");
			RECT rc;
			GetClientRect(hWnd, &rc);
			SetWindowText(EditMode, s_ModeE); //Изменить текст в EditMode
			SetWindowPos(Edit, nullptr, (double)rc.right * 0, (double)rc.bottom * 0.125, rc.right, rc.bottom / 3.43, SWP_SHOWWINDOW);
			SetWindowPos(EditMode, nullptr, (double)rc.right * 0, (double)rc.bottom * 0, rc.right, rc.bottom / 8, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(button_Equally, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Plus, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Minus, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Multiply, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Divided, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Tan, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_OneDividedToX, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Point, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_3, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_6, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_9, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_CE, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Exp, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Cos, nullptr, (double)rc.right * 0.6, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);				
			SetWindowPos(button_Zero, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Ln, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_xsquare3, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 11, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_2, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_5, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_8, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_C, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Log, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Sin, nullptr, (double)rc.right * 0.4, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_Ln, 1);
			EnableWindow(button_Ln, TRUE);
			SetWindowPos(button_1, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_4, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_7, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Clear_active, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 7, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_10square, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_xsquarey, nullptr, (double)rc.right * 0.2, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);				
			ShowWindow(button_xsquare3, 1);
			EnableWindow(button_xsquare3, TRUE);
			SetWindowPos(button_NEG, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 10, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_Fact, 1);
			EnableWindow(button_Fact, TRUE);
			SetWindowPos(button_Fact, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 9, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Pi, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 8, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_Pi, 1);
			EnableWindow(button_Pi, TRUE);
			SetWindowPos(button_Square, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 6, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Square2, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 5, rc.right / 5, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_Percent, 0);
			ShowWindow(button_10square, 1);
			EnableWindow(button_10square, TRUE);
			ShowWindow(button_Log, 1);
			EnableWindow(button_Log, TRUE);
			ShowWindow(button_Exp, 1);
			EnableWindow(button_Exp, TRUE);
			ShowWindow(button_Mod, 1);
			EnableWindow(button_Mod, TRUE);
			ShowWindow(button_xsquarey, 1);
			EnableWindow(button_xsquarey, TRUE);
			ShowWindow(button_Sin, 1);
			EnableWindow(button_Sin, TRUE);
			ShowWindow(button_Cos, 1);
			EnableWindow(button_Cos, TRUE);
			ShowWindow(button_Tan, 1);
			EnableWindow(button_Tan, TRUE);
			ShowWindow(button_And, 0);
			ShowWindow(button_A, 0);
			ShowWindow(button_B, 0);
			ShowWindow(buttonC, 0);
			ShowWindow(button_D, 0);
			ShowWindow(button_E, 0);
			ShowWindow(button_F, 0);
			ShowWindow(button_Not, 0);
			ShowWindow(button_Xor, 0);
			ShowWindow(EditHex, 0);
			ShowWindow(EditDec, 0);
			ShowWindow(EditOct, 0);
			ShowWindow(EditBin, 0);
			ShowWindow(button_HEX, 0);
			ShowWindow(button_DEC, 0);
			ShowWindow(button_OCT, 0);
			ShowWindow(button_BIN, 0);
			SetWindowPos(button_Mod, nullptr, (double)rc.right * 0.8, (double)rc.bottom / 12 * 6, (double)rc.right / 5, (double)rc.bottom / 12, SWP_SHOWWINDOW);
			SendMessage(button_NEG, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_1, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_2, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_3, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_4, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_5, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_6, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_7, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_8, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_9, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Zero, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Point, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Plus, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Equally, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Minus, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Multiply, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Divided, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_C, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_CE, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Clear_active, WM_SETFONT, (WPARAM)hFont1, NULL);
			SendMessage(button_Mod, WM_SETFONT, (WPARAM)hFont1, NULL);			
			break;
		}	
		case ID_programmer:
		{
			FirstOperand[0] = 0;
			SecondOperand[0] = 0;
			activewindowmode = 2;
			EnableWindow(button_Point, false);
			SetWindowText(EditMode, s_ModeP); //Изменить текст в EditMode
			RECT rc;
			GetClientRect(hWnd, &rc);
			SetWindowText(Edit, "0");
			ShowWindow(button_Tan, 0);
			ShowWindow(button_Cos, 0);
			ShowWindow(button_Sin, 0);
			ShowWindow(button_Exp, 0);
			ShowWindow(button_Log, 0);
			ShowWindow(button_Ln, 0);
			ShowWindow(button_OneDividedToX, 0);
			ShowWindow(button_Square, 0);
			ShowWindow(button_Square2, 0);
			ShowWindow(button_Percent, 0);
			ShowWindow(button_10square, 0);
			ShowWindow(button_Fact, 0);
			ShowWindow(button_xsquarey, 0);
			ShowWindow(button_xsquare3, 0);
			ShowWindow(button_Pi, 0);
			ShowWindow(EditHex, 1);
			ShowWindow(EditDec, 1);
			ShowWindow(EditOct, 1);
			ShowWindow(EditBin, 1);
			SetWindowPos(EditMode, nullptr, (double)rc.right * 0, (double)rc.bottom * 0, rc.right, rc.bottom / 12 * 1.5, SWP_NOZORDER | SWP_NOOWNERZORDER);
			SetWindowPos(Edit, nullptr, (double)rc.right * 0, (double)rc.bottom / 12 * 1.5, rc.right, rc.bottom / 12 * 1.5, SWP_SHOWWINDOW);
			SetWindowPos(EditBin, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 6, rc.right / 6 * 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(EditOct, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 5, rc.right / 6 * 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(EditDec, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 4, rc.right / 6 * 5, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(EditHex, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 3, rc.right / 6 * 5, rc.bottom / 12, SWP_SHOWWINDOW);
			EnableWindow(button_Mod, TRUE);
			SetWindowPos(button_Mod, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Equally, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Plus, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Minus, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Multiply, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Divided, nullptr, (double)rc.right / 6 * 5, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Point, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_3, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_6, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_9, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_CE, nullptr, (double)rc.right / 6 * 4, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Zero, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_2, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_5, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_8, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_C, nullptr, (double)rc.right / 6 * 3, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_NEG, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_1, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_4, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_7, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SetWindowPos(button_Clear_active, nullptr, (double)rc.right / 6 * 2, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_F, 1);
			EnableWindow(button_F, TRUE);
			SetWindowPos(button_F, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_E, 1);
			EnableWindow(button_E, TRUE);
			SetWindowPos(button_E, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 11, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_D, 1);
			EnableWindow(button_D, TRUE);
			SetWindowPos(button_D, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(buttonC, 1);
			EnableWindow(buttonC, TRUE);
			SetWindowPos(buttonC, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 10, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_B, 1);
			EnableWindow(button_B, TRUE);
			SetWindowPos(button_B, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_A, 1);
			EnableWindow(button_A, TRUE);
			SetWindowPos(button_A, nullptr, (double)rc.right / 6 * 00, (double)rc.bottom / 12 * 9, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_And, 1);
			EnableWindow(button_And, TRUE);
			SetWindowPos(button_And, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 8, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW); ShowWindow(button_A, 1);
			ShowWindow(button_Not, 1);
			EnableWindow(button_Not, TRUE);
			SetWindowPos(button_Not, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW); ShowWindow(button_A, 1);
			ShowWindow(button_Xor, 1);
			EnableWindow(button_Xor, TRUE);
			SetWindowPos(button_Xor, nullptr, (double)rc.right / 6 * 1, (double)rc.bottom / 12 * 7, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_HEX, 1);
			EnableWindow(button_HEX, TRUE);
			SetWindowPos(button_HEX, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 3, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_DEC, 1);
			EnableWindow(button_DEC, TRUE);
			SetWindowPos(button_DEC, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 4, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_OCT, 1);
			EnableWindow(button_OCT, TRUE);
			SetWindowPos(button_OCT, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 5, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			ShowWindow(button_BIN, 1);
			EnableWindow(button_BIN, TRUE);
			SetWindowPos(button_BIN, nullptr, (double)rc.right / 6 * 0, (double)rc.bottom / 12 * 6, rc.right / 6, rc.bottom / 12, SWP_SHOWWINDOW);
			SendMessage(button_And, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Not, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Xor, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_NEG, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_1, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_2, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_3, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_4, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_5, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_6, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_7, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_8, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_9, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Zero, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Point, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Plus, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Equally, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Minus, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Multiply, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Divided, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_C, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_CE, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Mod, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_A, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_B, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(buttonC, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_D, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_F, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_E, WM_SETFONT, (WPARAM)hFont2, NULL);
			SendMessage(button_Clear_active, WM_SETFONT, (WPARAM)hFont2, NULL);
			break;
		}
		case 1: {
			strcat(FirstOperand, "1");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case 2: {
			strcat(FirstOperand, "2");
			SetWindowText(Edit, FirstOperand);
			if(activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case 3: {
			strcat(FirstOperand, "3");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case 4: {
			strcat(FirstOperand, "4");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
		}
		case 5: {
			strcat(FirstOperand, "5");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
		}
		case 6: {
			strcat(FirstOperand, "6");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
		}
		case 7: {
			strcat(FirstOperand, "7");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
		}
		case 8: {
			strcat(FirstOperand, "8");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand,activemodeprogrammist);
			}
			break;
		}
		case 9: {
			strcat(FirstOperand, "9");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case Zero: {
				strcat(FirstOperand, "0");
				SetWindowText(Edit, FirstOperand);
				if (activewindowmode == 2)
				{
					system_of_calculation(FirstOperand, activemodeprogrammist);
				}
			break;
		}
		case A:
		{
			strcat(FirstOperand, "A");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case B:
		{
			strcat(FirstOperand, "B");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
		}
		case C:
		{
			strcat(FirstOperand, "C");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case D:
		{
			strcat(FirstOperand, "D");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case E:
		{
			strcat(FirstOperand, "E");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case F:
		{
			strcat(FirstOperand, "F");
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case Negative:{
			double _FirstOperand = atof(FirstOperand);
			double _SecondOperand = 0;
			double FirstOperandDouble = _SecondOperand - _FirstOperand;
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Point:{
			if (FirstOperand[0] == '\0')
			{

				if (strstr(FirstOperand, ".") == 0)
					strcat(FirstOperand, "0.");
				SetWindowText(Edit, FirstOperand);
			}
			else
			{
				if (strstr(FirstOperand, ".") == 0)
					strcat(FirstOperand, ".");
				SetWindowText(Edit, FirstOperand);
			}
			break;
		}
		case Plus:{
			Sign = Plus;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
		
			SetWindowText(Edit, "");
			break;
		}
		case Equally: {
			double _FirstOperand = atof(FirstOperand);
			double _SecondOperand = atof(SecondOperand);
			if (_FirstOperand == 0 && Sign == Divided) {
				MessageBox(NULL, "Деление на ноль", "ERROR", MB_ICONERROR);
				FirstOperand[0] = 0;
				SecondOperand[0] = 0;
				break;
			}
			//FirstOperand[0] = 0;
			//SecondOperand[0] = 0;
			if (Sign == Plus) {
				double FirstOperandDouble = _SecondOperand + _FirstOperand;
				sprintf(FirstOperand, "%lf", FirstOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			}
			if (Sign == Mod)
			{
				double FirstOperandDouble = fmod(_SecondOperand, _FirstOperand);
				sprintf(FirstOperand, "%4lf", FirstOperandDouble);
			}
			if (Sign == xsquarey)
			{
				double FirstOperandDouble = pow(_SecondOperand, _FirstOperand);

				sprintf(FirstOperand, "%lf", FirstOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			}
			if (Sign == Minus) {
			    double FirstOperandDouble = _SecondOperand - _FirstOperand;
				sprintf(FirstOperand, "%lf", FirstOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			}
			if (Sign == Multiply) {
				double FirstOperandDouble = _SecondOperand * _FirstOperand;
				sprintf(FirstOperand, "%lf", FirstOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			}
			if (Sign == Divided) {
				double FirstOperandDouble = _SecondOperand / _FirstOperand;
				sprintf(FirstOperand, "%lf", FirstOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			
			}
			if (Sign == Xor)
			{
				int a = _SecondOperand;
				int b = _FirstOperand;
				if (&a != &b)
				{
					a ^= b;
					a ^= b;
					a ^= b;

				}
				sprintf(FirstOperand, "%d", a);				
			}				
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
		//	FirstOperand[0] = 0;
			SecondOperand[0] = 0;
			break;
		}
		case Divided: {
			Sign = Divided;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			break;
		}
		case Minus: {
			Sign = Minus;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			break;
		}
		case Multiply: {
			Sign = Multiply;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			break;
		}
		case Mod:
		{
			Sign = Mod;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);
			}
			break;
		}
		case xsquarey:
		{
			Sign = xsquarey;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			break;
		}
		case ClearLast: {
			FirstOperand[0] = 0;
			SetWindowText(Edit, "0");
			if (activewindowmode == 2)
			{
				SetWindowText(EditHex, "0");
				SetWindowText(EditOct, "0");
				SetWindowText(EditBin, "0");
				SetWindowText(EditDec, "0");
			}
			break;
		}
		case ClearActive:
			{
			int lenght_str = strlen(FirstOperand);
			FirstOperand[strlen(FirstOperand) - 1] = '\0';
			SetWindowText(Edit, FirstOperand);
			if (activewindowmode == 2)
			{
				system_of_calculation(FirstOperand, activemodeprogrammist);

			}
			break;
			}
		case ClearAll: {
			FirstOperand[0] = 0;
			SecondOperand[0] = 0;
			SetWindowText(Edit, "0");
			if (activewindowmode == 2)
			{
				SetWindowText(EditHex, "0");
				SetWindowText(EditDec, "0");
				SetWindowText(EditOct, "0");
				SetWindowText(EditBin, "0");
			}
			break;
		}
		case OneDividetX:{
			double _FirstOperand = atof(FirstOperand);
			double FirstOperandDouble = 1 / _FirstOperand;
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Square_2:
		{
			double _FirstOperand = atof(FirstOperand);
			double FirstOperandDouble = pow(_FirstOperand,2);
			sprintf(FirstOperand, "%lf", FirstOperandDouble);

			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			
			
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Square:
		{
			double _FirstOperand = atof(FirstOperand);
			double FirstOperandDouble = sqrt(_FirstOperand);
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Percent:
		{
			double _FirstOperand = atof(FirstOperand);
			double _SecondOperand = atof(SecondOperand);
			if (_SecondOperand == 0) {
				SetWindowText(Edit, "0");
				FirstOperand[0] = 0;
			}
			else {
				double _SecondOperandDouble = _FirstOperand * _SecondOperand / 100;
				sprintf(FirstOperand, "%lf", _SecondOperandDouble);
				int dlin = strlen(FirstOperand);
				for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
				{
					if (FirstOperand[k] == '0')
					{
						FirstOperand[k] = '\0';
					}
				}
				dlin = strlen(FirstOperand);
				if (FirstOperand[dlin - 1] == '.')
				{
					FirstOperand[dlin - 1] = '\0';
				}
			}
			break;
		}	
		case Pi:
		{
			double FirstOperandDouble = 3.141592653589793238462633832795;
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Factorial:
		{
			double _FirstOperand = atoi(FirstOperand);
			sprintf(FirstOperand, "%lf", factfunc(_FirstOperand));
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Square10:
		{
			double _FirstOperand = atof(FirstOperand);
			double FirstOperandDouble = pow(10,_FirstOperand);
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Sin:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = sin(_FirstOperand* 3.141592653589793238462633832795 / 180);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Cos:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = cos(_FirstOperand * 3.141592653589793238462633832795 / 180);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Exp:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = exp(_FirstOperand);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Log:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = log10(_FirstOperand);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Tan:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = tan(_FirstOperand* 3.141592653589793238462633832795/180);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case Ln:
		{
			double _FirstOperand = atof(FirstOperand);
			_FirstOperand = log(_FirstOperand);
			sprintf(FirstOperand, "%lf", _FirstOperand);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case xsquare3:
		{
			double _FirstOperand = atof(FirstOperand);
			double FirstOperandDouble = pow(_FirstOperand, 3);
			sprintf(FirstOperand, "%lf", FirstOperandDouble);
			int dlin = strlen(FirstOperand);
			for (int k = dlin - 1; FirstOperand[k] == '0'; k--)
			{
				if (FirstOperand[k] == '0')
				{
					FirstOperand[k] = '\0';
				}
			}
			dlin = strlen(FirstOperand);
			if (FirstOperand[dlin - 1] == '.')
			{
				FirstOperand[dlin - 1] = '\0';
			}
			SetWindowText(Edit, FirstOperand);
			break;
		}
		case HEX:
		{
			activemodeprogrammist = 0;
			EnableWindow(button_A, true);
			EnableWindow(button_B, true);
			EnableWindow(buttonC, true);
			EnableWindow(button_D, true);
			EnableWindow(button_F, true);
			EnableWindow(button_E, true);
			EnableWindow(button_9, true);
			EnableWindow(button_8, true);
			EnableWindow(button_7, true);
			EnableWindow(button_6, true);
			EnableWindow(button_5, true);
			EnableWindow(button_4, true);
			EnableWindow(button_3, true);
			EnableWindow(button_2, true);
			break;
		}
		case DEC:
		{
			activemodeprogrammist = 1;
			EnableWindow(button_A, false);
			EnableWindow(button_B, false);
			EnableWindow(buttonC, false);
			EnableWindow(button_D, false);
			EnableWindow(button_F, false);
			EnableWindow(button_E, false);
			EnableWindow(button_9, true);
			EnableWindow(button_8, true);
			EnableWindow(button_7, true);
			EnableWindow(button_6, true);
			EnableWindow(button_5, true);
			EnableWindow(button_4, true);
			EnableWindow(button_3, true);
			EnableWindow(button_2, true);
			break;
		}
		case OCT:
		{
			activemodeprogrammist = 2;
			EnableWindow(button_A, false);
			EnableWindow(button_B, false);
			EnableWindow(buttonC, false);
			EnableWindow(button_D, false);
			EnableWindow(button_F, false);
			EnableWindow(button_E, false);
			EnableWindow(button_9, false);
			EnableWindow(button_8, false);
			EnableWindow(button_7, true);
			EnableWindow(button_6, true);
			EnableWindow(button_5, true);
			EnableWindow(button_4, true);
			EnableWindow(button_3, true);
			EnableWindow(button_2, true);
			break;
		}
		case BIN:
		{
			activemodeprogrammist = 3;
			EnableWindow(button_A, false);
			EnableWindow(button_B, false);
			EnableWindow(buttonC, false);
			EnableWindow(button_D, false);
			EnableWindow(button_F, false);
			EnableWindow(button_E, false);
			EnableWindow(button_9, false);
			EnableWindow(button_8, false);
			EnableWindow(button_7, false);
			EnableWindow(button_6, false);
			EnableWindow(button_5, false);
			EnableWindow(button_4, false);
			EnableWindow(button_3, false);
			EnableWindow(button_2, false);
			break;
		}
		case ID_EXITALL: {
			PostQuitMessage(EXIT_SUCCESS);
			break;
		}
		case Xor:
			{
			Sign = Xor;
			for (int i = 0; i <= strlen(FirstOperand); i++)
				SecondOperand[i] = FirstOperand[i];
			FirstOperand[0] = 0;
			SetWindowText(Edit, "");
			break;
			}
		} break;
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(EXIT_SUCCESS);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void CreateButton(HWND hWnd)
{	
	RECT rc;
	GetClientRect(hWnd, &rc);

	EditMode = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", s_ModeN, WS_VISIBLE|WS_DISABLED | WS_CHILD | ES_MULTILINE  | ES_CENTER | ES_READONLY, 0, 0, rc.right, 60, hWnd, NULL, nullptr, NULL);
	SendMessage(EditMode, WM_SETFONT, (WPARAM)hFontMode, NULL);
//	EditStatus = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "", WS_VISIBLE | WS_DISABLED | WS_CHILD | ES_MULTILINE | ES_RIGHT | ES_READONLY, 0, 60, rc.right, 50, hWnd, NULL, nullptr, NULL);
	Edit = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "0", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER  | ES_RIGHT | ES_READONLY,0,60, rc.right,110,hWnd, HMENU(editwind),nullptr,NULL);
	button_Equally = CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 420, 80, 50, hWnd, HMENU(Equally), nullptr, nullptr);
	button_Plus = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 370, 80, 50, hWnd, HMENU(Plus), nullptr, nullptr);
	button_Minus = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 320, 80, 50, hWnd, HMENU(Minus), nullptr, nullptr);
	button_Multiply = CreateWindow("button","х", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 270, 80, 50, hWnd, HMENU(Multiply), nullptr, nullptr);
	button_Divided = CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 220, 80, 50, hWnd, HMENU(Divided), nullptr, nullptr);
	button_OneDividedToX = CreateWindow("button", "1/x", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 240, 170, 80, 50, hWnd, HMENU(OneDividetX), nullptr, nullptr);
	button_Point = CreateWindow("button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 160, 420, 80, 50, hWnd, HMENU(Point), nullptr, nullptr);
	button_3 = CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 160, 370, 80, 50, hWnd, HMENU(3), nullptr, nullptr);
	button_6 = CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 160, 320, 80, 50, hWnd, HMENU(6), nullptr, nullptr);
	button_9 = CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 160, 270, 80, 50, hWnd, HMENU(9), nullptr, nullptr);
	button_CE = CreateWindow("button", "B", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER | BS_BITMAP , 160, 220, 80, 50, hWnd, HMENU(ClearActive), nullptr, nullptr);
	SendMessage(button_CE, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	button_Square2 = CreateWindow("button", "x^2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 160, 170, 80, 50, hWnd, HMENU(Square_2), nullptr, nullptr);
	button_Zero = CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 420, 80, 50, hWnd, HMENU(Zero), nullptr, nullptr);
	button_2 = CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 370, 80, 50, hWnd, HMENU(2), nullptr, nullptr);
	button_5 = CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 320, 80, 50, hWnd, HMENU(5), nullptr, nullptr);
	button_8 = CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 270, 80, 50, hWnd, HMENU(8), nullptr, nullptr);
	button_C = CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 220, 80, 50, hWnd, HMENU(ClearAll), nullptr, nullptr);
	button_Square = CreateWindow("button", "sqrt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 80, 170, 80, 50, hWnd, HMENU(Square), nullptr, nullptr);
	button_NEG = CreateWindow("button", "-/+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 420, 80, 50, hWnd, HMENU(Negative), nullptr, nullptr);
	button_1 = CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 370, 80, 50, hWnd, HMENU(1), nullptr, nullptr);
	button_4 = CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 320, 80, 50, hWnd, HMENU(4), nullptr, nullptr);
	button_7 = CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 270, 80, 50, hWnd, HMENU(7), nullptr, nullptr);
	button_Clear_active = CreateWindow("button", "CE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 220, 80, 50, hWnd, HMENU(ClearLast), nullptr, nullptr);
	button_Percent = CreateWindow("button", "%", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_BORDER, 0, 170, 80, 50, hWnd, HMENU(Percent), nullptr, nullptr);
	button_Ln = CreateWindow("button", "ln", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, rc.right * 0.2, rc.bottom / 12.5 * 11, rc.right / 5, rc.bottom / 12.5, hWnd, HMENU(Ln), nullptr, nullptr);
	SendMessage(button_Ln, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_xsquare3 = CreateWindow("button", "x^3", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, rc.right * 0, rc.bottom / 12.5 * 11, rc.right / 5, rc.bottom / 12.5, hWnd, HMENU(xsquare3), nullptr, nullptr);
	SendMessage(button_xsquare3, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Fact = CreateWindow("button", "n!", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 0, 350, 64, 40, hWnd, HMENU(Factorial), nullptr, nullptr);
	SendMessage(button_Fact, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Pi = CreateWindow("button", "pi", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 0, 310, 64, 40, hWnd, HMENU(Pi), nullptr, nullptr);
	SendMessage(button_Pi, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_10square = CreateWindow("button", "10^x", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 64, 230, 64, 40, hWnd, HMENU(Square10), nullptr, nullptr);
	SendMessage(button_10square, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Log = CreateWindow("button", "log", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 128, 230, 64, 40, hWnd, HMENU(Log), nullptr, nullptr);
	SendMessage(button_Log, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Exp = CreateWindow("button", "Exp", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 192, 230, 64, 40, hWnd, HMENU(Exp), nullptr, nullptr);
	SendMessage(button_Exp, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Mod = CreateWindow("button", "Mod", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 230, 64, 40, hWnd, HMENU(Mod), nullptr, nullptr);
	SendMessage(button_Mod, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_xsquarey = CreateWindow("button", "x^y", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 64, 190, 64, 40, hWnd, HMENU(xsquarey), nullptr, nullptr);
	SendMessage(button_xsquarey, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Sin = CreateWindow("button", "sin", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 128, 190, 64, 40, hWnd, HMENU(Sin), nullptr, nullptr);
	SendMessage(button_Sin, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Cos = CreateWindow("button", "cos", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 192, 190, 64, 40, hWnd, HMENU(Cos), nullptr, nullptr);
	SendMessage(button_Cos, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_Tan = CreateWindow("button", "tan", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 190, 64, 40, hWnd, HMENU(Tan), nullptr, nullptr);
	SendMessage(button_Tan, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(Edit, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_NEG, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_1, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_4, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_7, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Clear_active, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Percent, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_CE, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Zero, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_2, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_5, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_8, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_C, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Square, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_3, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_6, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_9, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Equally, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Plus, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Minus, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Multiply, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Divided, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_OneDividedToX, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Point, WM_SETFONT, (WPARAM)hFont1, NULL);
	SendMessage(button_Square2, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_A = CreateWindow("button", "A", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 64, 190, 64, 40, hWnd, HMENU(A), nullptr, nullptr);
	SendMessage(button_A, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_B = CreateWindow("button", "B", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 128, 190, 64, 40, hWnd, HMENU(B), nullptr, nullptr);
	SendMessage(button_B, WM_SETFONT, (WPARAM)hFont1, NULL);
	buttonC = CreateWindow("button", "C", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 192, 190, 64, 40, hWnd, HMENU(C), nullptr, nullptr);
	SendMessage(buttonC, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_D = CreateWindow("button", "D", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 190, 64, 40, hWnd, HMENU(D), nullptr, nullptr);
	SendMessage(button_D, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_E = CreateWindow("button", "E", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 192, 190, 64, 40, hWnd, HMENU(E), nullptr, nullptr);
	SendMessage(button_E, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_F = CreateWindow("button", "F", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 190, 64, 40, hWnd, HMENU(F), nullptr, nullptr);
	SendMessage(button_F, WM_SETFONT, (WPARAM)hFont1, NULL);
	button_And = CreateWindow("button", "And", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 190, 64, 40, hWnd, HMENU(And), nullptr, nullptr);
	button_Not = CreateWindow("button", "Not", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 192, 190, 64, 40, hWnd, HMENU(Not), nullptr, nullptr);
	button_Xor = CreateWindow("button", "Xor", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON | WS_BORDER, 256, 190, 64, 40, hWnd, HMENU(Xor), nullptr, nullptr);
	button_BIN = CreateWindow("button", "BIN", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON, 5, 130, 60, 40, hWnd, HMENU(BIN), nullptr, nullptr);
	button_OCT = CreateWindow("button", "OCT", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON, 5, 130, 60, 40, hWnd, HMENU(OCT), nullptr, nullptr);
	button_DEC = CreateWindow("button", "DEC", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON, 5, 130, 60, 40, hWnd, HMENU(DEC), nullptr, nullptr);
	button_HEX = CreateWindow("button", "HEX", WS_CHILD | WS_DISABLED | BS_PUSHBUTTON , 5, 130, 60, 40, hWnd, HMENU(HEX), nullptr, nullptr);
	EditHex = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "0",  WS_CHILD | ES_MULTILINE | ES_LEFT | ES_READONLY, 55, 110, rc.right-55, 40, hWnd, (HMENU)998, nullptr, NULL);
	EditDec = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "0",  WS_CHILD | ES_MULTILINE | ES_LEFT | ES_READONLY, 55, 150, rc.right-55, 40, hWnd, (HMENU)997, nullptr, NULL);
	EditOct = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "0",  WS_CHILD | ES_MULTILINE | ES_LEFT | ES_READONLY, 55, 190, rc.right-55, 40, hWnd, (HMENU)996, nullptr, NULL);
	EditBin = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "0",  WS_CHILD | ES_MULTILINE | ES_LEFT | ES_READONLY, 55, 230, rc.right-55, 40, hWnd, (HMENU)995, nullptr, NULL);
}
