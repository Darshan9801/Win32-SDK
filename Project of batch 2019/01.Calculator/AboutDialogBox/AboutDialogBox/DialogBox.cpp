#include<Windows.h>
#include "Header.h"
#include<math.h>
#include"MyMath.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

static HINSTANCE hgblInstance;
int num1 , num2 , ans,numd;
static int iCalflag = 0;

static TCHAR Checker[255] = TEXT(""), Current[255] = TEXT(""), Writer[255] = TEXT("");
static int iChecker = 0;

HINSTANCE hDll = NULL;
typedef int(*fnMakeAddition)(int,int);
fnMakeAddition fnA = NULL;
typedef int(*fnMakeSubstraction)(int,int);
fnMakeSubstraction fnSub = NULL;
typedef int(*fnMakeMultiplication)(int,int);
fnMakeMultiplication fnM = NULL;
typedef int(*fnMakeDivision)(int, int);
fnMakeDivision fnD = NULL;
typedef int(*fnMakeSquer)(int);
fnMakeSquer fnS = NULL;
typedef int(*fnMakeReminder)(int, int);
fnMakeReminder fnR = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Hello World");
	hgblInstance = hInstance;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("MY APPLICATION"),
		WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}
LRESULT WINAPI WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[255] = TEXT("BHOPADIKE AB TO THODA HASS DE..!");
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	int i, j;
	i = j = 0;
	TCHAR st8[266];
	switch (iMsg)
	{
	case WM_PAINT:
		SendMessage(hwnd, WM_DESTROY, 0, 0);
		/*GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);*/
		break;
	case WM_KEYDOWN:
		DestroyWindow(hwnd);
		break;
	case WM_CREATE:

		hDll = LoadLibrary(TEXT("MyMath.dll"));
		if (hDll == NULL)
		{
			MessageBox(hwnd, TEXT("ERROR while Loading The Dll."), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		DialogBox(hgblInstance, TEXT("AboutDialogBox"), hwnd, AboutDlgProc);
		break;
	case WM_LBUTTONDOWN:
		//MessageBox(hwnd, TEXT("About Dialog Box"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
		
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND one_hwnd;
	//const wchar_t a[255] = TEXT("5");
	static TCHAR str[25];

	switch (message)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rc;
		HBRUSH hbrush;

	case WM_INITDIALOG:
		one_hwnd = GetDlgItem(hDlg, IDOK_ONE);
		return false;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case WM_KEYDOWN:
			MessageBox(hDlg, TEXT("Hello you pressed a key on dlgbox....!"), TEXT("Message Box..!"), MB_OK);
			break;
		case IDOK_ONE:
			switch (HIWORD(wParam))
			{
			case BN_SETFOCUS:
				//7410111516
				//Sagar mishra
				/*GetClientRect(one_hwnd, &rc);
				hdc = BeginPaint(one_hwnd, &ps);
				hbrush = CreateSolidBrush(RGB(255, 0, 0));
				SelectObject(hdc, hbrush);
				FillRect(hdc, &rc, hbrush);
				*/
				break;

			case BN_CLICKED:

				GetDlgItemText(hDlg, TEXT_ID_ANS, Checker, 255);
				//GetDlgItemText(hDlg, IDOK_ONE, Current, 255);

				wsprintf(Writer, TEXT("D---"), Checker);
				iChecker = _wtoi(Checker);
				//wsprintf(Writer,TEXT("Previous value is :%d "),iChecker);


				if (iChecker == 1 || iChecker == 2 || iChecker == 3 || iChecker == 4 || iChecker == 5 || iChecker == 6 || iChecker == 7 || iChecker == 8 || iChecker == 9 || iChecker == 0)
				{



					MessageBox(hDlg, Writer, TEXT("This is Dialog Box..!"), MB_OK);
				}

				GetDlgItemText(hDlg, IDOK_ONE, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, Writer);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_TWO:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_TWO, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_THREE:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_THREE, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_FOUR:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_FOUR, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;

		case IDOK_FIVE:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_FIVE, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;

		case IDOK_SIX:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_SIX, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_SEVEN:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_SEVEN, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_EIGHT:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_EIGHT, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_NINE:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_NINE, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;
		case IDOK_ZERO:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:

				GetDlgItemText(hDlg, IDOK_ZERO, str, 255);
				if (str == NULL)
				{
					MessageBox(hDlg, TEXT("STR IS NULL!"), TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				}
				else
				{
					//wsprintf(str2, TEXT("The text :"),str);
					SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OK);
				}
			}

			break;

		case IDOK_PLS:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("+"));
				//assign value as one for Addition
				iCalflag = 1;
				break;
			}
			
			break;
		case IDOK_MINUS:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("-"));
				//assign value as one for Addition
				iCalflag = 2;
				break;
			}
			break;
		case IDOK_MULT:
			//Multiplication
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("*"));
				//assign value as one for Addition
				iCalflag = 3;
				break;
			}
			break;
		case IDOK_DIVIDE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("/"));
				//assign value as one for Addition
				iCalflag = 4;
				break;
			}
			break;
		case IDOK_REMINDER:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("%"));
				//assign value as one for Addition
				iCalflag = 5;
				break;
			}
			break;
		case IDOK_SQU:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num1 = _wtoi(str);
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("X^2"));
				//assign value as one for Addition
				iCalflag = 6;
				break;
			}
			break;
		case IDOK_SQU_ROOT:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				numd = _wtof(str);
				//sqrt(num1);
				wsprintf(str, TEXT("%ld"), sqrt(numd));
				SetDlgItemText(hDlg, TEXT_ID_ANS, str);

				num1 = num2 = 0;
				//assign value as one for Addition
				//iCalflag = 7;
				break;
			}
			break;
		case IDOK_EQL:

			switch (HIWORD(wParam))
			{

			case BN_CLICKED:
				GetDlgItemText(hDlg, TEXT_ID_ANS, str, 255);
				num2 = _wtoi(str);

				if ((num1 == 0) || (num2 == 0))
				{
					MessageBox(hDlg, TEXT("One oF the value is not given."), TEXT("Error"), MB_OK);
					SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("0"));
					num1 = num2 = 0;
					break;
				}

				//wsprintf(str, TEXT("NO :%d"), iCalflag);
				//MessageBox(hDlg, str, TEXT("This is Dialog Box..!"), MB_OKCANCEL);
				switch (iCalflag)
				{
				case 1:

					fnA = (fnMakeAddition)GetProcAddress(hDll, "MakeAddition");
					if (fnA != NULL)
					{
						ans = fnA(num1, num2);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					//Addition

					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 2:
					//Substracion
					fnSub = (fnMakeSubstraction)GetProcAddress(hDll, "MakeSubstraction");
					if (fnSub != NULL)
					{
						ans = fnSub(num1, num2);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 3:
					//Multiplication
					fnM = (fnMakeMultiplication)GetProcAddress(hDll, "MakeMultiplication");
					if (fnM != NULL)
					{
						ans = fnM(num1, num2);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 4:
					//Division
					fnD = (fnMakeDivision)GetProcAddress(hDll, "MakeDivision");
					if (fnD != NULL)
					{
						ans = fnD(num1, num2);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 5:
					//reminder
					//ans = modf(num1, num2);
					fnR = (fnMakeReminder)GetProcAddress(hDll, "MakeReminder");
					if (fnR != NULL)
					{
						ans = fnR(num1, num2);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 6:
					//Squer 
					fnS = (fnMakeSquer)GetProcAddress(hDll, "MakeSquer");
					if (fnS != NULL)
					{
						ans = fnS(num1);
						wsprintf(str, TEXT("%d"), ans);
						SetDlgItemText(hDlg, TEXT_ID_ANS, str);
					}
					iCalflag = 0;
					num1 = num2 = 0;
					break;
				case 7:
					//squer Root
					iCalflag = 0;
					num1 = num2 = 0;
					break;

				}

				break;

			}
			break;
		case IDOK_C:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:
				SetDlgItemText(hDlg, TEXT_ID_ANS, TEXT("0"));
				break;
			}
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE; 
}

