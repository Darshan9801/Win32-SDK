#include<windows.h>

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
	LPCWSTR str[100] = { TEXT("India is my country."),TEXT("All Indians are my Brothers and Sisters."),TEXT("I love my country and I am proud of its rich and varied heritage. ") };
	LPCWSTR str1[100] = { TEXT("I shall always strive to be worthy of it."),TEXT("I shall give my parents, "),TEXT("Teachers and all elders respect and treat everyone with courtesy.") };
	LPCWSTR str2[100] = { TEXT("To my country and my people,"),TEXT("I pledge my devotion. "),TEXT("In their well being and prosperity alone, lies my happiness.") };
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	int x = 0;

	switch (iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		x = (rc.bottom / 2) - 60;
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));

		SetTextColor(hdc, RGB(0, 255, 0));
		for (int i = 0; i <= 2; i++)
		{
			TextOut(hdc, (rc.right / 2) - 65, x, str[i], wcslen(str[i]));
			x += 20;
		}
		SetTextColor(hdc, RGB(255, 255, 255));
		for (int i = 0; i <= 2; i++)
		{
			TextOut(hdc, (rc.right / 2) - 65, x, str1[i], wcslen(str1[i]));
			x += 20;
		}
		SetTextColor(hdc, RGB(255, 128, 0));
		for (int i = 0; i <= 2; i++)
		{
			TextOut(hdc, (rc.right / 2) - 65, x, str2[i], wcslen(str2[i]));
			x += 20;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}