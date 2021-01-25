#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);

DWORD WINAPI ThreadProcTwo(LPVOID);
HWND ghwnd;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Hie Thread");

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
		WS_OVERLAPPEDWINDOW,
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
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	ghwnd = hwnd;
	
	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		if (hThreadTwo == NULL)
		{
			MessageBox(hwnd, TEXT("Thread Error..!"), TEXT("My Thread"), MB_OK);
		}
		//MessageBox(hwnd, TEXT("My Thread"), TEXT("Thread Is Created....!"),MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left Button Pressed..!"), TEXT("My Thread"), MB_OK|MB_ICONINFORMATION);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	for (i = 0; i < 4294967295; i++)
	{
		wsprintf(str, TEXT("ThreadOne->Increasing Order:%ld"),i);
		TextOut(hdc, 5,5, str, wcslen(str));
	}
	
	ReleaseDC((HWND)param, hdc);
	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];
	

	hdc = GetDC((HWND)param);
	//MessageBox((HWND)param, TEXT("Thread is checked..!"), TEXT("My Thread"), MB_OK);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	for (i = 429496729; i > 0; i--)
	{
		wsprintf(str, TEXT("ThreadTwo->Decreasing Order:%ld"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return (0);
}




