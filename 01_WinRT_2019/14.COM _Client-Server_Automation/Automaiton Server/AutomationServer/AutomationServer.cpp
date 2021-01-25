#include<windows.h>
#include<stdio.h>
#include"AutomationServer.h"

class CMyMath : public IMyMath//2
{
private:	
	long m_cRef;
	ITypeInfo *m_pITypeInfo;//3
public:
	CMyMath(void);
	~CMyMath(void);
	
	//IUnknown specific method
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//IDispatch specific Method
	HRESULT __stdcall GetTypeInfoCount(UINT*);//4(A)
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
					  
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

	HRESULT InitInstance(void);// 4(B)
};

class CMyMathClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CMyMathClassFactory(void);
	~CMyMathClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};
HRESULT hr;
//HMODULE ghModule = NULL;
long glNumberOfActiveComponents = 0;
long glNumberOfActiveServers = 0;
void ComErrorDescriptionString(HWND, HRESULT);//5
// {6DB90A1B-7805-4D79-A3A4-9B4F77D31158}
const GUID LIBID_AutomationServer = {0x6db90a1b, 0x7805, 0x4d79, 0xa3, 0xa4, 0x9b, 0x4f, 0x77, 0xd3, 0x11, 0x58 };
TCHAR str1[255];
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

CMyMath::CMyMath(void)
{
	m_cRef = 1;
	m_pITypeInfo = NULL;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
CMyMath::~CMyMath(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}



HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath *>(this);//6 Ask Anything you will Get only IMyMath
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath *>(this);//6
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath *>(this);//6
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CMyMath::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);

}

ULONG CMyMath::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		//as an alternative it should be in destructor (To AVoid Memory Lick)
		m_pITypeInfo->Release();// 7
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);

}
//locane LCID's "L"
HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)// 9
{
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
	{
		return(DISP_E_BADINDEX);
	}
	//before giving interface pointer to others it must be AddRef
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);

}


HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo)// 8
{
	*pCountTypeInfo = 1;
	return(S_OK);

}
//*rgszName == functions chya navancha array
//*rgDispId == functions chya navancha id array bharun de 
//CName = array size of *rgszNames
//DispGetIDsOfNames ha win32 cha function aahe
//riid = is by default IID_INULL aahe
HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT CNames, LCID lcid, DISPID *rgDispId) // 10
{

	hr = DispGetIDsOfNames(m_pITypeInfo, rgszNames, CNames, rgDispId);
	if (FAILED(hr))
	{
		ComErrorDescriptionString(NULL, hr);
		MessageBox(NULL, TEXT("Can Not Get ID from Sum Of Two Integers()"), TEXT("ERROR"), MB_OK | MB_ICONERROR | MB_TOPMOST);
	
	}
	return(hr);
}
//dispIdNumber = sumofTwoIntegers chi ID Ji GetIDsOfNames ha Function Deto
//


HRESULT CMyMath::Invoke(DISPID dispIdNumber, REFIID riid, LCID lcid, WORD wFlag, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) // 11
{
	HRESULT hr;
	hr = DispInvoke(this, m_pITypeInfo, dispIdNumber, wFlag, pDispParams, pVarResult, pExcepInfo, puArgErr);
	return(hr);
}

HRESULT CMyMath::SumOfTwoIntegers(int Num1, int Num2, int *pSum)
{
		
	swprintf_s(str1, TEXT("we just came with values %d and %d.\n"),Num1,Num2);
	MessageBox(NULL, str1, TEXT("COM ERROR"), MB_OK);
	*pSum = Num1 + Num2;
	return(S_OK);
}
HRESULT CMyMath::SubtractionOfTwoIntegers(int Num1, int Num2, int *pSubtract)
{
	*pSubtract = Num1 - Num2;
	return(S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	HRESULT hr;
	ITypeLib *pITypeLib = NULL;

	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}

///////////////////////////////////////////////////////////////////////////////////////////////////Implementation Of CMyMathClassFactory's Contructor

CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1;
}

CMyMathClassFactory::~CMyMathClassFactory(void)
{
	//Code
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CMyMath *pCMyMath = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCMyMath = new CMyMath;
	if (pCMyMath == NULL)
		return(E_OUTOFMEMORY);
	pCMyMath->InitInstance();
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL flock)
{
	if (flock)
		InterlockedIncrement(&glNumberOfActiveServers);
	else
		InterlockedDecrement(&glNumberOfActiveServers);
	return(S_OK);
}


extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMyMathClassFactory *pCMyMathClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MyMath)
		return (CLASS_E_CLASSNOTAVAILABLE);
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfActiveServers == 0))
		return(S_OK);
	else
	{
		return(S_FALSE);
	}
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




