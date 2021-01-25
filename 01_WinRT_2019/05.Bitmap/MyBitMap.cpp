#include<windows.h>
#include"MyBM.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP hbitmap;
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[255] = TEXT("My BItMap");
	hInst = hInstance;
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

	return((int)msg.wParam);


}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	BITMAP bitmap;
	TCHAR str[155];
	HDC hdc,myhdc;
	RECT rc;
	PAINTSTRUCT ps;
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			hbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(MYBITMAP));
			break;
		}
		break;
	
	case WM_CREATE:
		
		wsprintf(str, TEXT("Window Is Created..!"));
		MessageBox(hwnd, str, TEXT("WINDOW"),MB_OK|MB_ICONINFORMATION);
		break;
	case WM_PAINT:
		//to get changing Rect...
		GetClientRect(hwnd, &rc);
		//calling the specialist.
		hdc = BeginPaint(hwnd, &ps);
		//To select bitmap into hdc...
		myhdc = CreateCompatibleDC(NULL);
		//now select object dc
		SelectObject(myhdc, hbitmap);
		//Get the current object 
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,myhdc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
		DeleteDC(myhdc);
		
		EndPaint(hwnd, &ps);



		break;


	case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
