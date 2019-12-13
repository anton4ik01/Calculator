#pragma once
#define Zero 0
#define Plus 11
#define Minus 12
#define Multiply 13
#define Divided 14
#define Equally 100
#define Point 101
#define ClearAll 102
#define Negative 103
#define ClearLast 104
#define About 105
#define OneDividetX 15
#define Square_2 16
#define Square 17
#define ClearActive 18
#define Percent 19
#define ModeC 121
#define Ln 20
#define xsquare3 21
#define Pi 22
#define Square10 23
#define Log 24
#define Exp 25
#define Mod 26
#define xsquarey 27
#define Sin 28
#define Cos 29
#define Tan 30
#define A 50
#define B 51
#define C 52
#define D 53
#define E 54
#define F 55
#define And 56
#define Not 57
#define Xor 58
#define ID_EXITALL 3007
#define ID_regular 3001
#define ID_programmer 3002
#define ID_engineer 3003
#define Factorial 36
#define HEX 71
#define DEC 72
#define OCT 73
#define BIN 74
#define editwind 999
#include <cmath>
#include <cstdio>
#include <string.h>

HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

static HWND button_HEX;
static HWND button_DEC;
static HWND button_OCT;
static HWND button_BIN;
HBRUSH brush;
HDC hdc;
HMENU hmenu1, hPopupMenu1, hPopupMenu2;
HWND Edit,EditMode,EditStatus,EditHex,EditDec,EditOct,EditBin;
HWND Mode;
static HWND button_And;
static HWND button_Not;
static HWND button_Xor;
static HWND button_A;
static HWND button_B;
static HWND buttonC;
static HWND button_D;
static HWND button_E;
static HWND button_F;
static HWND button_Sin;
static HWND button_Cos;
static HWND button_Tan;
static HWND button_xsquarey;
static HWND button_Log;
static HWND button_Exp;
static HWND button_Mod;
static HWND button_10square;
static HWND button_Pi;
static HWND button_Fact;
static HWND button_Ln;
static HWND button_xsquare3;
static HWND button_1;
static HWND button_2;
static HWND button_3;
static HWND button_4;
static HWND button_5;
static HWND button_6;
static HWND button_7;
static HWND button_8;
static HWND button_9;
static HWND button_Zero;
static HWND button_Point;
static HWND button_Plus;
static HWND button_Minus;
static HWND button_Multiply;
static HWND button_Divided;
static HWND button_Equally;
static HWND button_C;
static HWND button_NEG;
static HWND button_CE;
static HWND button_About;
static HWND button_OneDividedToX;
static HWND button_Square2;
static HWND button_Square;
static HWND button_Clear_active;
static HWND button_Percent;
inline void system_of_calculation(char* str, int active);
long double factfunc(double N)
{
	if (N < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (N == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нуля , это 1
	else 
		return N * factfunc(N - 1); // делаем рекурсию.
}

inline char* binarybuff[100];
inline char* buffer = new char[32];
inline char* buffer_oct = new char[32];
inline char* buffer_dec_to_hex = new char[32];

void system_of_calculation(char* str, int active)
{
	if (active == 0) // Режим HEX
	{
		
		auto done = 0;
		buffer[0] = 0;
		int length_str = 0;
		for (auto i = 0; i < strlen(str); i++)
		{
			if (str[i] != '.')
			{
				length_str++;
			}
			else
			{
				break;
			}
		}
		int incumber[32];
		// перевод в числа и сохранение в incumber
		for (auto i = 0; i < length_str; i++)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				incumber[i] = str[i] - '0';
			}
			else if (str[i] == 'A')
			{
				incumber[i] = 10;
			}
			else if (str[i] == 'B')
			{
				incumber[i] = 11;
			}
			else if (str[i] == 'C')
			{
				incumber[i] = 12;
			}
			else if (str[i] == 'D')
			{
				incumber[i] = 13;
			}
			else if (str[i] == 'E')
			{
				incumber[i] = 14;
			}
			else if (str[i] == 'F')
			{
				incumber[i] = 15;
			}
		}
		auto j = length_str - 1;
		for (auto i = 0; i < length_str; i++)
		{
			done = incumber[j] * pow(16, i) + done;
			j--;
		}
		sprintf(buffer, "%d", done);
		//Из десятичной в восьмеричную
		length_str = strlen(buffer);

		auto sternum = atoi(buffer);
		int arr[16];
		j = 0;
		for (int i = sternum; i != 0; i = i / 8)
		{
			arr[j] = i % 8;
			j++;
		}
		int arr2[16];
		auto k = 0;
		for (int i = j; i != 0; i--)
		{
			arr2[k] = arr[i - 1];
			k++;
		}
		int num_A = 0;
		for (int i = 0; i < j; i++)
		{
			num_A *= 10;
			num_A += arr2[i];

		}
		sprintf(buffer_oct, "%d", num_A);

		int temp = atoi(buffer);
		char* buffer_BIN = new char[128];
		memset(buffer_BIN, '\0', 128);
		k = 0;
		int arr_BIN[128];
		while (temp > 0)
		{
			if (temp == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			else if (temp % 2 == 0)
			{
				arr_BIN[k] = 0;
				k++;
			}
			else if (temp % 2 == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			temp = temp / 2;
		}
		int arrt_BIN[128];
		int f = k;
		if (f == 1)
		{
			buffer_BIN[0] = arr_BIN[0] + '0';
		}
		else {
			for (int j = 0; j < f; j++)
			{
				buffer_BIN[j] = arr_BIN[k - 1] + '0';
				k--;
			}
		}
		SetWindowText(EditOct, buffer_oct);
		SetWindowText(EditHex, str);
		SetWindowText(EditDec, buffer);
		SetWindowText(EditBin, buffer_BIN);

	}
	else if (active == 1) //режим DEC
	{
		memset(buffer_dec_to_hex, '\0', 32);
		int arr[32];
		int i = 0;
		auto foo = atoi(str);
		if (foo / 16 == 0)
		{
			arr[i] = foo;
		}
		else {
			while (foo / 16 != 0)
			{
				arr[i] = foo % 16;
				foo = foo / 16;
				i++;
				if (foo < 16)
				{
					arr[i] = foo;
					foo = 0;
				}
			}
		}
		int k = i;
		int arrt[32];
		for (int j = 0; j <= i; j++)
		{
			arrt[j] = arr[k];
			arr[k] = 0;
			k--;
		}
		for (int j = 0; j <= i; j++)
		{
			if (arrt[j] >= 0 && arrt[j] <= 9)
			{
				buffer_dec_to_hex[j] = arrt[j] + '0';
			}
			else if (arrt[j] == 10)
			{
				buffer_dec_to_hex[j] = 'A';
			}
			else if (arrt[j] == 11)
			{
				buffer_dec_to_hex[j] = 'B';
			}
			else if (arrt[j] == 12)
			{
				buffer_dec_to_hex[j] = 'C';
			}
			else if (arrt[j] == 13)
			{
				buffer_dec_to_hex[j] = 'D';
			}
			else if (arrt[j] == 14)
			{
				buffer_dec_to_hex[j] = 'E';
			}
			else if (arrt[j] == 15)
			{
				buffer_dec_to_hex[j] = 'F';
			}
		}
		const int length_str = strlen(buffer_dec_to_hex);

		auto sternum = atoi(str);
		auto j = 0;
		for (int i = sternum; i != 0; i = i / 8)
		{
			arr[j] = i % 8;
			j++;
		}
		int arr2[16];
		k = 0;
		for (int i = j; i != 0; i--)
		{
			arr2[k] = arr[i - 1];
			k++;
		}
		int num_A = 0;
		for (int i = 0; i < j; i++)
		{
			num_A *= 10;
			num_A += arr2[i];

		}
		char* buffer_oct1 = new char[32];

		sprintf(buffer_oct1, "%d", num_A);

		// To BIN
		int temp = sternum;
		char* buffer_BIN = new char[128];
		memset(buffer_BIN, '\0', 128);
		k = 0;
		int arr_BIN[128];
		while(temp>0)
		{
			if(temp == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			else if(temp%2 == 0)
			{
				arr_BIN[k] = 0;
				k++;
			}
			else if (temp % 2 == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			temp = temp / 2;
		}
		int arrt_BIN[128];
		int f = k;
		if(f == 1)
		{
			buffer_BIN[0] = arr_BIN[0] + '0';
		}
		else {
			for (int j = 0; j < f; j++)
			{
				buffer_BIN[j] = arr_BIN[k-1] + '0';
				k--;
			}
		}

		SetWindowText(EditOct, buffer_oct1);
		SetWindowText(EditHex, buffer_dec_to_hex);
		SetWindowText(EditDec, str);
		SetWindowText(EditBin, buffer_BIN);
	}
	else if (active == 2)
	{
		auto done = 0;
		buffer[0] = 0;
		int length_str = 0;
		for (auto i = 0; i < strlen(str); i++)
		{
			if (str[i] != '.')
			{
				length_str++;
			}
			else
			{
				break;
			}
		}
		int incumber[32];
		// перевод в числа и сохранение в incumber
		for (auto i = 0; i < length_str; i++)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				incumber[i] = str[i] - '0';
			}
			else if (str[i] == 'A')
			{
				incumber[i] = 10;
			}
			else if (str[i] == 'B')
			{
				incumber[i] = 11;
			}
			else if (str[i] == 'C')
			{
				incumber[i] = 12;
			}
			else if (str[i] == 'D')
			{
				incumber[i] = 13;
			}
			else if (str[i] == 'E')
			{
				incumber[i] = 14;
			}
			else if (str[i] == 'F')
			{
				incumber[i] = 15;
			}
		}
		auto j = length_str - 1;
		for (auto i = 0; i < length_str; i++)
		{
			done = incumber[j] * pow(8, i) + done;
			j--;
		}
		sprintf(buffer, "%d", done);
		// из десятичной(buffer) в Шестнадцатиричное
		memset(buffer_dec_to_hex, '\0', 32);
		*buffer_dec_to_hex = '\0';
		int arr[32];
		int i = 0;
		auto foo = atoi(buffer);
		if (foo / 16 == 0)
		{
			arr[i] = foo;
		}
		else {
			while (foo / 16 != 0)
			{
				arr[i] = foo % 16;
				foo = foo / 16;
				i++;
				if (foo < 16)
				{
					arr[i] = foo;
					foo = 0;
				}
			}
		}
		int k = i;
		int arrt[32];
		for (int j = 0; j <= i; j++)
		{
			arrt[j] = arr[k];
			arr[k] = 0;
			k--;
		}
		for (int j = 0; j <= i; j++)
		{
			if (arrt[j] >= 0 && arrt[j] <= 9)
			{
				buffer_dec_to_hex[j] = arrt[j] + '0';
			}
			else if (arrt[j] == 10)
			{
				buffer_dec_to_hex[j] = 'A';
			}
			else if (arrt[j] == 11)
			{
				buffer_dec_to_hex[j] = 'B';
			}
			else if (arrt[j] == 12)
			{
				buffer_dec_to_hex[j] = 'C';
			}
			else if (arrt[j] == 13)
			{
				buffer_dec_to_hex[j] = 'D';
			}
			else if (arrt[j] == 14)
			{
				buffer_dec_to_hex[j] = 'E';
			}
			else if (arrt[j] == 15)
			{
				buffer_dec_to_hex[j] = 'F';
			}
		}


		int temp = atoi(buffer);
		char* buffer_BIN = new char[128];
		memset(buffer_BIN, '\0', 128);
		k = 0;
		int arr_BIN[128];
		while (temp > 0)
		{
			if (temp == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			else if (temp % 2 == 0)
			{
				arr_BIN[k] = 0;
				k++;
			}
			else if (temp % 2 == 1)
			{
				arr_BIN[k] = 1;
				k++;
			}
			temp = temp / 2;
		}
		int arrt_BIN[128];
		int f = k;
		if (f == 1)
		{
			buffer_BIN[0] = arr_BIN[0] + '0';
		}
		else {
			for (int j = 0; j < f; j++)
			{
				buffer_BIN[j] = arr_BIN[k - 1] + '0';
				k--;
			}
		}
		SetWindowText(EditHex, buffer_dec_to_hex);
		SetWindowText(EditOct, str);
		SetWindowText(EditDec, buffer);
		SetWindowText(EditBin, buffer_BIN);

	}
	else if (active == 3)
	{
		// BIN to DEC
		int i = strlen(str);
		int arr9[128];
		int arrt9[128];
		for(int j = 0;j<i;j++)
		{
			arr9[j] = str[j] - '0';
		}
		int k = i-1;
		for (int j = 0; j < i; j++)
		{
			arrt9[j] = arr9[k];
			arr9[k] = 0;
			k--;
		}
		k = 0;
		int f = 0,sum = 0;
		while(f<i)
		{
			sum+=arrt9[f] * pow(2, k);
			k++;
			f++;
		}
		
		char* bufferdex = new char[128];
		sprintf(bufferdex, "%d", sum);

		// DEC to OCT
		auto sternum = atoi(bufferdex);
		auto j = 0;
		for (int i = sternum; i != 0; i = i / 8)
		{
			arr9[j] = i % 8;
			j++;
		}
		int arr2[16];
		k = 0;
		for (int i = j; i != 0; i--)
		{
			arr2[k] = arr9[i - 1];
			k++;
		}
		int num_A = 0;
		for (int i = 0; i < j; i++)
		{
			num_A *= 10;
			num_A += arr2[i];

		}
		char* buffer_oct1 = new char[32];

		sprintf(buffer_oct1, "%d", num_A);
		// Dec to HEX

		memset(buffer_dec_to_hex, '\0', 32);
		int arr[32];
		i = 0;
		auto foo = atoi(bufferdex);
		if (foo / 16 == 0)
		{
			arr[i] = foo;
		}
		else {
			while (foo / 16 != 0)
			{
				arr[i] = foo % 16;
				foo = foo / 16;
				i++;
				if (foo < 16)
				{
					arr[i] = foo;
					foo = 0;
				}
			}
		}
		k = i;
		int arrt[32];
		for (int j = 0; j <= i; j++)
		{
			arrt[j] = arr[k];
			arr[k] = 0;
			k--;
		}
		for (int j = 0; j <= i; j++)
		{
			if (arrt[j] >= 0 && arrt[j] <= 9)
			{
				buffer_dec_to_hex[j] = arrt[j] + '0';
			}
			else if (arrt[j] == 10)
			{
				buffer_dec_to_hex[j] = 'A';
			}
			else if (arrt[j] == 11)
			{
				buffer_dec_to_hex[j] = 'B';
			}
			else if (arrt[j] == 12)
			{
				buffer_dec_to_hex[j] = 'C';
			}
			else if (arrt[j] == 13)
			{
				buffer_dec_to_hex[j] = 'D';
			}
			else if (arrt[j] == 14)
			{
				buffer_dec_to_hex[j] = 'E';
			}
			else if (arrt[j] == 15)
			{
				buffer_dec_to_hex[j] = 'F';
			}
		}
		SetWindowText(EditOct, buffer_oct1);
		SetWindowText(EditDec, bufferdex);
		SetWindowText(EditHex, buffer_dec_to_hex);
		SetWindowText(EditBin, str);
	}
}