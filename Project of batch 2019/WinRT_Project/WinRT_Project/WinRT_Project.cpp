#include<windows.h>
#include<stdio.h>
#include<string.h>
#include"BitMap.h"
#include<Winuser.h>
#include<CommCtrl.h>
#include"Database.h"
#include<io.h>
#include<mbstring.h>
#include<CommCtrl.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DataEntry(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DataRead(HWND, UINT, WPARAM, LPARAM);

HBITMAP hbitmap;
TCHAR example[6][50];


static HINSTANCE hgblInstance;
IReadRecordFile		*pIReadRecordFile = NULL;
IWriteRecordFile *pIWriteRecordFile = NULL;
HRESULT hr;
TCHAR collectionstr[6][50];
//List Box Handle
HWND hwndListMonthB,hwndListDayB,hwndListYearB;
HWND hwndListMonthJD, hwndListDayJD, hwndListYearJD;
int iIndex;
TCHAR str[20];

//Name
TCHAR Tname[50];
char strTname[50];
TCHAR TnameR[50];
char EName[50];

//Add
TCHAR Taddress[100];
char strTaddress[100];
TCHAR TaddressR[100];
char EAddress[100];

//dob
TCHAR FetchDob[15];
char strFetchDobR[15];
TCHAR FetchDobR[15];
char EDob[13];

//gender
TCHAR gender[20];
char strgender[20];
TCHAR genderR[20];
char EGender[7];

//JD
TCHAR FetchJd[13];
char strFetchJD[13];
char EJD[13];

//EID
TCHAR Enumber[10];
char strEnumber[10];
TCHAR EnumberR[10];
char ENumber[10];

//Read 
TCHAR search[10];
char search_[10];
TCHAR searchR[10];

TCHAR count[255];
TCHAR EmpId[10], EmpName[50], EmpAdd[100], EmpGen[7], EmpDOB[13], EmpJD[13];
int Name = 0, Add = 0, Gen = 0, dob = 0, jd = 0;

TCHAR DTday[3], DTmonth[4], DTyear[5];
TCHAR JDday[3], JDmonth[4], JDyear[5];
FILE *fpfile = NULL;
FILE *fpRile_T = NULL;
HWND gblHwnd;
int len,strend;
char strnormal[255];
TCHAR strnormalT[255];
TCHAR space[255] = {TEXT("                                                                                                                                      ")};
int cunt;
char strTDA[255][25], SourceB[255];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[255] = TEXT("My Project");
	HRESULT hr;
	//Com Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library can not be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

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
		TEXT("My Project"),
		WS_OVERLAPPEDWINDOW,
		50,
		80,
		1480,
		720,
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
	return((int)msg.wParam);


}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	BITMAP bitmap;
	HDC hdc, myhdc;
	RECT rc;
	PAINTSTRUCT ps;
	

	switch (iMsg)
	{
	case WM_CREATE:
		hbitmap = LoadBitmap(hgblInstance, MAKEINTRESOURCE(MYBITMAP));
	
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		//calling the specialist.
		hdc = BeginPaint(hwnd, &ps);
		//To select bitmap into hdc...
		myhdc = CreateCompatibleDC(NULL);
		//now select object dc
		SelectObject(myhdc, hbitmap);
		//Get the current object 
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, myhdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		DeleteDC(myhdc);

		EndPaint(hwnd, &ps);

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			
			DialogBox(hgblInstance, TEXT("MYDIALOGBOX"), hwnd, AboutDlgProc);	
			break;
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_DESTROY:
		pIWriteRecordFile->Release();
		pIReadRecordFile->Release();
		pIReadRecordFile = NULL;
		pIWriteRecordFile = NULL;
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT massage, WPARAM wParam, LPARAM lParam)
{

	switch (massage)
	{
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDDATAENTRY:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:
				DialogBox(hgblInstance, TEXT("DATAENTRY"), hwnd, DataEntry);
				EndDialog(hwnd, 0);
				break;
			}
			break;
		case IDREAD:
			switch (HIWORD(wParam))
			{

			case BN_CLICKED:
				DialogBox(hgblInstance, TEXT("DATAREAD"), hwnd, DataRead);
				EndDialog(hwnd, 0);
				break;
			}
			break;
		}
		break;
	

	}
	return FALSE;
}



INT_PTR CALLBACK DataEntry(HWND hwnd, UINT massage, WPARAM wParam, LPARAM lParam)
{
	TCHAR a[50][5] = {TEXT("1971"),TEXT("1972"),TEXT("1973"),TEXT("1974") ,TEXT("1975"),TEXT("1976") ,TEXT("1977"),TEXT("1978") ,TEXT("1979"),TEXT("1980"),TEXT("1981"),TEXT("1982"),TEXT("1983"),TEXT("1984") ,TEXT("1985"),TEXT("1986") ,TEXT("1987"),TEXT("1988") ,TEXT("1989"),TEXT("1990"),TEXT("1991"),TEXT("1992"),TEXT("1993"),TEXT("1994") ,TEXT("1995"),TEXT("1996") ,TEXT("1997"),TEXT("1998") ,TEXT("1999"),TEXT("2000"),TEXT("2001"),TEXT("2002"),TEXT("2003"),TEXT("2004") ,TEXT("2005"),TEXT("2006") ,TEXT("2007"),TEXT("2008") ,TEXT("2009"),TEXT("2010"),TEXT("2011"),TEXT("2012"),TEXT("2013"),TEXT("2014") ,TEXT("2015"),TEXT("2016") ,TEXT("2017"),TEXT("2018") ,TEXT("2019"),TEXT("2020")};
	int c;
	TCHAR A[12][5] = {TEXT("Jan"),TEXT("Feb"),TEXT("Mar"),TEXT("Apr") ,TEXT("May"),TEXT("Jun") ,TEXT("Jul"),TEXT("Aug") ,TEXT("Sep"),TEXT("Act"),TEXT("Nov"),TEXT("Des")};
	TCHAR b[31][3] = { TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4") ,TEXT("5"),TEXT("6") ,TEXT("7"),TEXT("8") ,TEXT("9"),TEXT("10"),TEXT("11"),TEXT("12"),TEXT("13"),TEXT("14") ,TEXT("15"),TEXT("16") ,TEXT("17"),TEXT("18") ,TEXT("19"),TEXT("20"),TEXT("21"),TEXT("22"),TEXT("23"),TEXT("24") ,TEXT("25"),TEXT("26") ,TEXT("27"),TEXT("28") ,TEXT("29"),TEXT("30"),TEXT("31") };
	char strB[13];
	

	switch (massage)
	{
	case WM_INITDIALOG:

		//Birth Date
		hwndListDayB = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 110, 168, 80, 35, hwnd, (HMENU)ID_LISTDAYB, NULL, NULL);
		hwndListMonthB = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 193, 168, 80, 35, hwnd, (HMENU)ID_LISTMONTHB, NULL, NULL);
		hwndListYearB = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 276, 168, 80, 35, hwnd, (HMENU)ID_LISTYEARB, NULL, NULL);
		//Joining Date
		hwndListDayJD = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 458, 168, 80, 35, hwnd, (HMENU)ID_LISTDAYJD, NULL, NULL);
		hwndListMonthJD = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 541, 168, 80, 35, hwnd, (HMENU)ID_LISTMONTHJD, NULL, NULL);
		hwndListYearJD = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 625, 168, 80, 35, hwnd, (HMENU)ID_LISTYEARJD, NULL, NULL);
		for (int g = 0; g < 12; g++)
		{
				SendMessage(hwndListMonthB, LB_ADDSTRING, g, (LPARAM)A[g]);
		}
		
		for (c = 0; c < 50; c++)
		{
			SendMessage(hwndListYearB, LB_ADDSTRING, c, (LPARAM)a[c]);
		}
		for (int j = 0; j < 31; j++)
		{
			SendMessage(hwndListDayB, LB_ADDSTRING, c, (LPARAM)b[j]);
		}

		for (int g = 0; g < 12; g++)
		{
			SendMessage(hwndListMonthJD, LB_ADDSTRING, g, (LPARAM)A[g]);
		}

		for (c = 0; c < 50; c++)
		{
			SendMessage(hwndListYearJD, LB_ADDSTRING, c, (LPARAM)a[c]);
		}
		for (int j = 0; j < 31; j++)
		{
			SendMessage(hwndListDayJD, LB_ADDSTRING, c, (LPARAM)b[j]);
		}
		break;
	
	
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			EndDialog(hwnd, 0);
			break;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDDATAOK:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			
				//DOT data Fetched
				iIndex = SendMessage(hwndListDayB, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListDayB, LB_GETTEXT, iIndex, (LPARAM)DTday);
				wcscat_s(DTday, 4, TEXT("/"));
				wcscat_s(FetchDob, 4, DTday);
		
				iIndex = SendMessage(hwndListMonthB, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListMonthB, LB_GETTEXT, iIndex, (LPARAM)DTmonth);
				wcscat_s(DTmonth, 5, TEXT("/"));
				wcscat_s(FetchDob, 9, DTmonth);
		
				iIndex = SendMessage(hwndListYearB, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListYearB, LB_GETTEXT, iIndex, (LPARAM)DTyear);
				wcscat_s(FetchDob, 13, DTyear);
				wcscat_s(FetchDob, 15, TEXT("\t"));
		
				//JD data Fetching
				iIndex = SendMessage(hwndListDayJD, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListDayJD, LB_GETTEXT, iIndex, (LPARAM)JDday);
				wcscat_s(JDday, 4, TEXT("/"));
				wcscat_s(FetchJd, 4, JDday);
				
				iIndex = SendMessage(hwndListMonthJD, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListMonthJD, LB_GETTEXT, iIndex, (LPARAM)JDmonth);
				wcscat_s(JDmonth, 5, TEXT("/"));
				wcscat_s(FetchJd, 9, JDmonth);

				iIndex = SendMessage(hwndListYearJD, LB_GETCURSEL, 0, 0);
				SendMessage(hwndListYearJD, LB_GETTEXT, iIndex, (LPARAM)JDyear);
				wcscat_s(FetchJd, 13, JDyear);
			
				
				if (IsDlgButtonChecked(hwnd, IDFEMALERADIO))
				{
					wsprintf(gender, TEXT("Female\t"));
				}
				if (IsDlgButtonChecked(hwnd, IDMALERADIO))
				{
					wsprintf(gender, TEXT("Male\t"));
				}
				
				GetDlgItemText(hwnd, IDADDRESSEDIT, Taddress, 100);
			
				GetDlgItemText(hwnd, IDNAMEEDIT, Tname, 50);
				
				GetDlgItemText(hwnd, EIDEBOX, Enumber, 10);
			
				//Employee ID-------------------------------------------
				len = wcslen(Enumber);
				for (int i = 0; i < len; i++)
				{
					EnumberR[i] = Enumber[i];
				}
				for (int i = len; i <= 10; i++)
				{
					EnumberR[i] = space[i];
				}
				
				len = wcslen(EnumberR);
				for (int i = 0; i < len; i++)
				{
					strEnumber[i] = EnumberR[i];
				}
			
				//Employee Name------------------------------------------
				len = wcslen(Tname);
				for (int i = 0; i < len; i++)
				{
					TnameR[i] = Tname[i];
				}
			
				for (int i = len; i < 50; i++)
				{
					
					TnameR[i] = space[i];
				}
				
				cunt = wcslen(TnameR);
			
				for (int i = 0; i < len; i++)
				{
					strTname[i] = TnameR[i];
				}
			
				len = 0;
				
				//Address
				len = wcslen(Taddress);
				for (int i = 0; i < len; i++)
				{
					TaddressR[i] = Taddress[i];
				}
				for (int i = len; i <= 100; i++)
				{
					TaddressR[i] = space[i];
				}
				len = wcslen(TaddressR);
				for (int i = 0; i < len; i++)
				{
					strTaddress[i] = TaddressR[i];
				}
				len = 0;
				
				//gender
				len = wcslen(gender);
				for (int i = 0; i < len; i++)
				{
					genderR[i] = gender[i];
				}

				for (int i = len; i <= 8; i++)
				{
					genderR[i] = space[i];
				}

				len = wcslen(genderR);
				for (int i = 0; i < len; i++)
				{
					strgender[i] = genderR[i];
				}
				len = 0;
			
				////Date Of Birth day
				len = wcslen(FetchDob);
				for (int i = 0; i <= len; i++)	
				{
					strFetchDobR[i] = FetchDob[i];
				}
			
				//data Of Joining
				len = wcslen(FetchJd);
				for (int i = 0; i <= len; i++)
				{
					strFetchJD[i] = FetchJd[i];
				}
	
				hr = CoCreateInstance(CLSID_ReadWrite, NULL, CLSCTX_INPROC_SERVER, IID_IWriteRecord, (void **)&pIWriteRecordFile);

				if (FAILED(hr))
				{
					MessageBox(hwnd, TEXT("IReadRecordFile Interface can not be obtained."), TEXT("Error"), MB_OK);
					DestroyWindow(hwnd);
				}
			    else
				{
				
				pIWriteRecordFile->WriteRecord(strEnumber, strTname, strgender, strTaddress, strFetchDobR, strFetchJD);
				MessageBox(hwnd, TEXT("Data has been Strored carefully,Thanks!"),TEXT("Inform"), MB_OK | MB_ICONINFORMATION);
				}
				
				wsprintf(Enumber, TEXT(""));
				sprintf_s(strEnumber, 1, "");
				wsprintf(EnumberR, TEXT(""));
				
				wsprintf(Tname, TEXT(""));
				sprintf_s(strTname, 1, "");
				wsprintf(TnameR, TEXT(""));
				
				wsprintf(Taddress, TEXT(""));
				sprintf_s(strTaddress, 1, "");
				wsprintf(TaddressR, TEXT(""));
				
				wsprintf(FetchDob, TEXT(""));
				sprintf_s(strFetchDobR, 1, "");
				wsprintf(FetchDobR, TEXT(""));
				
				wsprintf(FetchJd, TEXT(""));
				sprintf_s(strFetchJD, 1, "");
				

				wsprintf(gender, TEXT(""));
				sprintf_s(strgender, 1, "");
				wsprintf(genderR, TEXT(""));
				
				wsprintf(DTday, TEXT(""));
				wsprintf(DTmonth, TEXT(""));
				wsprintf(DTyear, TEXT(""));
				
				wsprintf(JDday, TEXT(""));
				wsprintf(JDmonth, TEXT(""));
				wsprintf(JDyear, TEXT(""));

			break;
			}
		break; 
		case IDDATACANCEL:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EndDialog(hwnd, 0);
				return TRUE;
			}
			return TRUE;
		case IDMALERADIO:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SendMessage(GetDlgItem(hwnd, IDMALERADIO), BM_SETCHECK, 1, 0);
				SendMessage(GetDlgItem(hwnd, IDFEMALERADIO), BM_SETCHECK, 0, 0);
			return TRUE;
		}
			return TRUE;
		case IDFEMALERADIO:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				SendMessage(GetDlgItem(hwnd, IDFEMALERADIO), BM_SETCHECK, 1, 0);
				SendMessage(GetDlgItem(hwnd, IDMALERADIO), BM_SETCHECK, 0, 0);
				return TRUE;
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}


INT_PTR CALLBACK DataRead(HWND hwnd, UINT massage, WPARAM wParam, LPARAM lParam)
{
	//struct EmpDet Emp;
	//EmpD = &Emp;
	//char str212[10];
	int n = 0,a = 0,c = 0;
	unsigned int d = 0;
	FILE *fpFile_RT = NULL;
	FILE *Check = NULL;
	int ch;
	int z = 0,x = 0,m = 0;
	//char strB[255];

	switch (massage)
	{
	case WM_INITDIALOG:
		//Structure Fill
		SetDlgItemText(hwnd, IDFRFCO, TEXT("ID"));
		SetDlgItemText(hwnd, IDFRFCS, TEXT("Name"));
		SetDlgItemText(hwnd, IDFRFCTH, TEXT("Address"));
		SetDlgItemText(hwnd,IDFRFCF, TEXT("Gender"));
		SetDlgItemText(hwnd, IDFRFCFI, TEXT("D.O.B."));
		SetDlgItemText(hwnd, IDFRFCSI, TEXT("Joining Date"));
		break;
	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("Hellow Welcome to Read Your Data!"), TEXT("Data Read"), MB_OK);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDDATACANCELR:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				EndDialog(hwnd, 0);
				return TRUE;
			}
			return TRUE;
		case IDDATAOKR:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetDlgItemText(hwnd, IDREADEMP, search, 10);
				z = wcslen(search);
				for (int i = 0; i <= z; i++)
				{
					searchR[i] = search[i];
				}
				for (int i = z; i <= 10; i++)
				{
					searchR[i] = space[i];
				}
				for (int i = 0; i < 10; i++)
				{
					search_[i] = searchR[i];
				}
				MessageBox(hwnd, TEXT("I AM Clicked."), TEXT("Error"), MB_OK);

				hr = CoCreateInstance(CLSID_ReadWrite, NULL, CLSCTX_INPROC_SERVER, IID_IReadRecord, (void **)&pIReadRecordFile);

				if (FAILED(hr))
				{
					MessageBox(hwnd, TEXT("IReadRecordFile Interface can not be obtained."), TEXT("Error"), MB_OK);
					DestroyWindow(hwnd);
				}
				else
				{

					pIReadRecordFile->ReadRecord(search_, hwnd, ENumber, EName, EGender, EAddress, EDob, EJD);

					MessageBox(hwnd, TEXT("I am Back."), TEXT("Happy"), MB_OK);
					fopen_s(&fpFile_RT, "DllOutPutCheck.txt", "a+");
							fprintf_s(fpFile_RT, "Entered Dll And Fetching the Data.\n");
							fprintf_s(fpFile_RT, ENumber);
							fprintf_s(fpFile_RT, EAddress);
							fprintf_s(fpFile_RT, EGender);
							fprintf_s(fpFile_RT, EDob);
							fprintf_s(fpFile_RT, EJD);
							fclose(fpFile_RT);
							
				}


				for (int i = 0; i < 10; i++)
				{
					EmpId[i] = ENumber[i];
				}
				
				for (int i = 0; i < 50; i++)
				{
					EmpName[i] = EName[i];
				}
				for (int i = 0; i < 7; i++)
				{
					EmpGen[i] = EGender[i];
				}
				for (int i = 0; i < 100; i++)
				{
					EmpAdd[i] = EAddress[i];
				}
				for (int i = 0; i < 13; i++)
				{
					EmpDOB[i] = EDob[i];
				}
				for (int i = 0; i < 13; i++)
				{
					EmpJD[i] = EJD[i];
				}
				

				SetDlgItemText(hwnd, IDSRSCO, EmpId);
							SetDlgItemText(hwnd, IDSRSCS, EmpName);
							SetDlgItemText(hwnd, IDSRSCTH, EmpAdd);
							SetDlgItemText(hwnd, IDSRSCF, EmpGen);
							SetDlgItemText(hwnd, IDSRSCFI, EmpDOB);
							SetDlgItemText(hwnd, IDSRSCSI, EmpJD);
							sprintf_s(search_, "");
							Name = 0;
							Add = 0;
							jd = 0;
							Gen = 0;
							dob = 0;
							//count = {"fgfdfg"};
							ZeroMemory(&count,  255 * sizeof(char));
							ZeroMemory(&EmpId, 10 * sizeof(char));
							ZeroMemory(&EmpAdd, 100 * sizeof(char));
							ZeroMemory(&EmpName, 50 * sizeof(char));
							ZeroMemory(&EmpGen, 7 * sizeof(char));
							ZeroMemory(&EmpDOB, 10 * sizeof(char));
							ZeroMemory(&EmpJD, 10 * sizeof(char));
							ZeroMemory(&search, 11 * sizeof(char));
							ZeroMemory(&searchR, 11 * sizeof(char));
							ZeroMemory(&str, 20 * sizeof(char));
							
					
					
				
				wsprintf(search, TEXT(""));
				wsprintf(searchR, TEXT(""));
				sprintf_s(search_, "");
				//
				
				
				return TRUE;
			}
			return TRUE;
			
		}
		break;

		}
	return FALSE;
}
