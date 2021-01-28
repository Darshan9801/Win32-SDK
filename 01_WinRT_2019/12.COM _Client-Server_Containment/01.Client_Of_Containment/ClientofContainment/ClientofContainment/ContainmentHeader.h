#include<windows.h>

class IMultiplication : public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;

};

class IDivision : public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;

};
// {B1E87516-F353-4F20-B9ED-AC946CEF5C23}
const CLSID CLSID_MultiplicationDivision =
{ 0xb1e87516, 0xf353, 0x4f20, 0xb9, 0xed, 0xac, 0x94, 0x6c, 0xef, 0x5c, 0x23 };

//{B96EA1C8-0828-45A9-A232-97088C3D026B}
const IID IID_IMultiplication =
{ 0xb96ea1c8, 0x828, 0x45a9, 0xa2, 0x32, 0x97, 0x8, 0x8c, 0x3d, 0x2, 0x6b};

// {7F8AD063-6865-410C-9E04-0BD50D910F30}
const IID IID_IDivision =
{ 0x7f8ad063, 0x6865, 0x410c, 0x9e, 0x4, 0xb, 0xd5, 0xd, 0x91, 0xf, 0x30 };

//OuterDLL
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



