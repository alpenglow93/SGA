#pragma once

class BinaryWrite
{
public:
	BinaryWrite();
	~BinaryWrite();

	bool Open(wstring file);
	void Close();

	void Int(int i);
	void UInt(UINT i);
	void Float(float f);
	void Bool(bool b);
	void Data(void* data, size_t size);
	void String(string str);

private:
	HANDLE handle;
	DWORD size;
};
class BinaryRead
{
public:
	BinaryRead();
	~BinaryRead();

	bool Open(wstring file);
	void Close();

	int Int();
	UINT UInt();
	float Float();
	bool Bool();
	void Data(void** data, size_t dataSize);
	string String();

private:
	HANDLE handle;
	DWORD size;
};