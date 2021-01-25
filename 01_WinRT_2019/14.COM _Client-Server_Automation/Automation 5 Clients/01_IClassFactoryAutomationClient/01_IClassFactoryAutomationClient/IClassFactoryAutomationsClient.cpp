#include<Windows.h>
#include<stdio.h>
#include"AutomationServer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
IMyMath *pIMyMath = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Com Client");
	HRESULT hr;
	//Com Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library can not be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

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
		TEXT("Client Of Dll Server."),
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
	CoUninitialize();
	return ((int)msg.wParam);

}

LRESULT WINAPI WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;
	int iNum1, iNum2, iSum,iSubtract;
	TCHAR str[255];
	
	//Function Declarations
	void ComErrorDescriptionString(HWND, HRESULT);
	void SafeInterfaceRelease(void);

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void **)&pIMyMath);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}
		iNum1 = 50;
		iNum2 = 49;
		pIMyMath->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		iNum1 = 50;
		iNum2 = 49;
		pIMyMath->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, &iSubtract);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;


	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));


}


void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("[could not find a description for error # %#x.]\n"), hr);
	}
	MessageBox(hwnd, str, TEXT("COM ERROR"), MB_OK);
}

void SafeInterfaceRelease(void)
{
	if (pIMyMath)
	{
		pIMyMath->Release();
		pIMyMath = NULL;
	}
	
}
