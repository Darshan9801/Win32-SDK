#include<Windows.h>
#include<stdio.h>
#include"AutomationServer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Client");

	wndclass.cbSize = sizeof(wndclass);
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
		TEXT("IDispatch Client"),
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

	void ComErrorDescriptionString(HWND, HRESULT);
	IDispatch *pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;						   
	OLECHAR *szFunctionName1 = (OLECHAR*)L"SumOfTwoIntegers";
	OLECHAR *szFunctionName2 = (OLECHAR*)L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = {vArg,0,2,NULL};
	int n1, n2;
	TCHAR str[255];


	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID from Sum Of Two Integers()"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&pIDispatch);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Componant can not be created"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}
		n1 = 75;
		n2 = 25;
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = n2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = n1;
		param.cArgs = 2;
		param.cNamedArgs = 0;
		param.rgdispidNamedArgs = NULL;
		param.rgvarg = vArg;
		VariantInit(&vRet);
		/////////////////////////////////////////IMyMath->Sum
	
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);
	
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID from Sum Of Two Integers()"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke Function."), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else
		{
			wsprintf(str, TEXT("Sum of %d And %d Is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);
		}

		/////////////////////////////////////////iMyMath->Subtraction
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Get ID from Subtraction Of Two Integers()"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(NULL, TEXT("Can Not Invoke Function."), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else
		{
			wsprintf(str, TEXT("Subtraction of %d And %d Is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);
		}
		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);

		


		break;

	case WM_DESTROY:
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






