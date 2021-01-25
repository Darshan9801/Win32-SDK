#include<windows.h>
#define MYTIMER 101

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("My Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return (msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static RECT rc, temp;
	static int iPaintFlag = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;
	case WM_TIMER:
		KillTimer(hwnd,MYTIMER);
		iPaintFlag++;
		
		if (iPaintFlag >8)
		{
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		SetTimer(hwnd, MYTIMER, 1000, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		temp.top = rc.top;
		temp.bottom = rc.bottom;
		hdc = BeginPaint(hwnd, &ps);
		switch (iPaintFlag)
		{
		case 8:

			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Saya
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Megento Or Purpal
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Yellow
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Orange
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 128, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//White
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;

		case 7:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Saya
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Megento Or Purpal
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Yellow
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Orange
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 128, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;

		case 6:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Saya
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Megento Or Purpal
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Yellow
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;

		case 5:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Saya
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Megento Or Purpal
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;

		case 4:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Saya
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;
		
		case 3:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//Blue
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;
		
		case 2:
			//Red
	
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);

			//green
			temp.left = temp.right;
			temp.right = temp.left + rc.right / 8;
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;
		case 1:
			//Red
			temp.left = rc.left;
			temp.right = rc.right / 8;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hbrush);
			FillRect(hdc, &temp, hbrush);
			break;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

