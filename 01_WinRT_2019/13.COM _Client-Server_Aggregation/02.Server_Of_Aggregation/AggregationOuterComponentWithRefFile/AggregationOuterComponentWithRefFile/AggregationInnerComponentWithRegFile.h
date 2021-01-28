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
// {7C02917F-1A1E-49E1-96F5-C0A0C0663281}
const CLSID CLSID_MultiplicationDivision =
{ 0x7c02917f, 0x1a1e, 0x49e1,{ 0x96, 0xf5, 0xc0, 0xa0, 0xc0, 0x66, 0x32, 0x81 } };



const IID IID_IMultiplication =
{ 0xabc1783a, 0x31a3, 0x4304,{ 0x9b, 0xb4, 0x31, 0xe4, 0xe6, 0xdd, 0x74, 0xa4 } };


const IID IID_IDivision =
{ 0xe0f9c3dc, 0x82f3, 0x47c0,{ 0x81, 0x40, 0xb0, 0xae, 0x89, 0x97, 0x94, 0x9c } };


