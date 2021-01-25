#include<windows.h>

//extern "C" int MakeSquer(int);
//extern "C" BOOL IsNumberNagative(int);

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwResone, LPVOID lpReserved)
{
	switch (dwResone)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

extern "C" int MakeSquer(int num)
{
	//IsNumberNagative(num);
	return (num * num);
}
//
//extern "C" BOOL IsNumberNagative(int num)
//{
//	if (num < 0)
//		return (TRUE);
//	else
//		return (FALSE);
//}


