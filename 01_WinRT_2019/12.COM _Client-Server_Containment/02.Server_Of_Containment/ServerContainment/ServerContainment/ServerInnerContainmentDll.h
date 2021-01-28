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


