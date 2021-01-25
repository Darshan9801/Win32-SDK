#pragma once
#include<windows.h>

class IReadRecordFile : public IUnknown
{
public:
	virtual VOID __stdcall ReadRecord(char [10],HWND, char*, char*, char*, char*, char*, char*) = 0;


};
class IWriteRecordFile : public IUnknown
{
public:
	virtual VOID __stdcall WriteRecord(char[10], char[50], char[7], char[100], char[15], char[13]) = 0;

};

// {D1B0AE0B-8976-408B-8BF4-B80A0981CD47}
const CLSID CLSID_ReadWrite ={ 0xd1b0ae0b, 0x8976, 0x408b, 0x8b, 0xf4, 0xb8, 0xa, 0x9, 0x81, 0xcd, 0x47 };

const IID IID_IReadRecord = { 0x594042db, 0x3b04, 0x42af, 0x9a, 0x71, 0x67, 0x6b, 0x27, 0x9e, 0x83, 0x4c };

const IID IID_IWriteRecord = { 0x2bfe7a46, 0xd233, 0x447b, 0x93, 0x18, 0xbe, 0xbe, 0x6c, 0x95, 0x86, 0xee };






