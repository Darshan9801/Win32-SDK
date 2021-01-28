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
// {C59ACCEA-FAF8-44DB-971E-F113A1748B7D}
const CLSID CLSID_SumSubtract =
{0xc59accea,0xfaf8,0x44db,0x97,0x1e,0xf1,0x13,0xa1,0x74,0x8b,0x7d};

// {A2201498-E9DA-47A4-A8F4-851934A6191F}
const IID IID_ISum =
{0xa2201498,0xe9da,0x47a4,0xa8,0xf4,0x85,0x19,0x34,0xa6,0x19,0x1f};

// {DC9236C9-2362-43AC-9778-849AFA573835}
const IID IID_ISubtract =
{0xdc9236c9,0x2362,0x43ac,0x97,0x78,0x84,0x9a,0xfa,0x57,0x38,0x35};




