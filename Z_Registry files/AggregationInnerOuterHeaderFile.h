
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
// {35A598B7-2678-4BE2-ADF2-0CEAE80024B2}
const CLSID CLSID_SumSubtract =
{ 0x35a598b7, 0x2678, 0x4be2, 0xad, 0xf2, 0xc, 0xea, 0xe8, 0x0, 0x24, 0xb2 };


const IID IID_ISum =
{ 0x18cab79f, 0xbdf0, 0x4315, 0xbf, 0xfc, 0xaa, 0xdb, 0xc0, 0x48, 0xef, 0x53 };


const IID IID_ISubtract =
{ 0x3f6ae256, 0x55f5, 0x4167, 0xa7, 0xe8, 0xda, 0xf3, 0xd1, 0x98, 0x56, 0x66 };



// {7C02917F-1A1E-49E1-96F5-C0A0C0663281}
const CLSID CLSID_MultiplicationDivision =
{ 0x7c02917f, 0x1a1e, 0x49e1,0x96, 0xf5, 0xc0, 0xa0, 0xc0, 0x66, 0x32, 0x81 };



const IID IID_IMultiplication =
{ 0xabc1783a, 0x31a3, 0x4304, 0x9b, 0xb4, 0x31, 0xe4, 0xe6, 0xdd, 0x74, 0xa4 };


const IID IID_IDivision =
{ 0xe0f9c3dc, 0x82f3, 0x47c0, 0x81, 0x40, 0xb0, 0xae, 0x89, 0x97, 0x94, 0x9c };


