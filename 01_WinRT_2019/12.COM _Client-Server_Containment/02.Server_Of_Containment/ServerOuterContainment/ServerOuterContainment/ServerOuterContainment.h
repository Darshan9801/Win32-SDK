#include<windows.h>

class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;

};

// {9531B6D9-1660-4AD0-9E60-5F2B8358BA56}
const CLSID CLSID_SumSubtract =
{ 0x9531b6d9, 0x1660, 0x4ad0, 0x9e, 0x60, 0x5f, 0x2b, 0x83, 0x58, 0xba, 0x56 };

// {5897751A-71B9-42F7-8C4D-5F33DCA5FE67}
const IID IID_ISum =
{ 0x5897751a, 0x71b9, 0x42f7,0x8c, 0x4d, 0x5f, 0x33, 0xdc, 0xa5, 0xfe, 0x67 };

// {69D0D6FF-CA7C-4D64-A0BC-11EE5B857B09}
const IID IID_ISubtract =
{ 0x69d0d6ff, 0xca7c, 0x4d64, 0xa0, 0xbc, 0x11, 0xee, 0x5b, 0x85, 0x7b, 0x9 };



