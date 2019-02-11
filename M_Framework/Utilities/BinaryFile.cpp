#include "stdafx.h"
#include "BinaryFile.h"



//-----------------------------------------------------------
// Write;
//-------------------------------------------------------------
BinaryWrite::BinaryWrite()
	:handle(NULL)
{
}

BinaryWrite::~BinaryWrite()
{
}

bool BinaryWrite::Open(wstring file)
{
	handle = CreateFile
	(
		file.c_str(),
		GENERIC_WRITE, //� �뵵�� ���
		0, //��ü ���� ���
		0, //��Ÿ �Ӽ� 
		CREATE_ALWAYS,
		0,
		0
	);

	return handle != NULL;
}

void BinaryWrite::Close()
{
	CloseHandle(handle);
}

void BinaryWrite::Int(int i)
{
	WriteFile(handle, &i, sizeof(int), &size, NULL);
}

void BinaryWrite::UInt(UINT i)
{
	WriteFile(handle, &i, sizeof(UINT), &size, NULL);
}

void BinaryWrite::Float(float f)
{
	WriteFile(handle, &f, sizeof(float), &size, NULL);

}

void BinaryWrite::Bool(bool b)
{
	WriteFile(handle, &b, sizeof(bool), &size, NULL);

}

void BinaryWrite::Data(void * data, size_t dataSize)
{
	WriteFile(handle, data, dataSize, &size, NULL);
}

void BinaryWrite::String(string str)
{
	UInt(str.size());
	WriteFile(handle, &str, str.size(), &size, NULL);
}

//--------------------------------------------------------------
// Reader
//--------------------------------------------------------------

BinaryRead::BinaryRead()
{
}

BinaryRead::~BinaryRead()
{
}

bool BinaryRead::Open(wstring file)
{
	handle = CreateFile
	(
		file.c_str(),
		GENERIC_READ,
		0,
		0,
		OPEN_EXISTING, //������ ������ ���� 
		0,
		0
	);
	bool b = handle != INVALID_HANDLE_VALUE;
	return b;
}

void BinaryRead::Close()
{
	if (handle != NULL)
	{
		CloseHandle(handle);
		handle = NULL;
	}
}

int BinaryRead::Int()
{
	int temp = 0;
	ReadFile(handle, &temp, sizeof(int), &size, NULL);
	return temp;
}

UINT BinaryRead::UInt()
{
	UINT temp = 0;
	ReadFile(handle, &temp, sizeof(UINT), &size, NULL);
	return temp;
}

float BinaryRead::Float()
{
	float temp = 0;
	ReadFile(handle, &temp, sizeof(float), &size, NULL);
	return temp;
}

bool BinaryRead::Bool()
{
	bool temp = 0;
	ReadFile(handle, &temp, sizeof(bool), &size, NULL);
	return temp;
}

void BinaryRead::Data(void ** data, size_t dataSize)
{
	ReadFile(handle, *data, dataSize, &size, NULL);
}

string BinaryRead::String()
{
	UINT size = UInt();
	char* temp = new char[size + 1];// +1-> NULL ���� 
	ReadFile(handle, temp, sizeof(char) * size, &this->size, NULL);
	temp[size] = '\0';
	return temp;
}
