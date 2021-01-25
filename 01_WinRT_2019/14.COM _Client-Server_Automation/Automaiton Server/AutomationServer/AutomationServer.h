
#include<windows.h>

class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;

	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};
// {68652B97-8503-4134-8BCE-48FBA6DCB1B7}
const CLSID CLSID_MyMath = {0x68652b97, 0x8503, 0x4134, 0x8b, 0xce, 0x48, 0xfb, 0xa6, 0xdc, 0xb1, 0xb7 };

// {26E8753B-2B20-42E5-BF36-FD027296B768}
const IID IID_IMyMath =	{ 0x26e8753b, 0x2b20, 0x42e5, 0xbf, 0x36, 0xfd, 0x2, 0x72, 0x96, 0xb7, 0x68 };


