#pragma once

class CSResourceBase
{
public:
	CSResourceBase();
	virtual ~CSResourceBase();
	ID3D11ShaderResourceView* SRV() { return srv; }
	ID3D11UnorderedAccessView* UAV() { return uav; }

protected:
	ID3D11ShaderResourceView* srv; //2���� �迭 
	ID3D11UnorderedAccessView* uav; //1���� �迭
};

class CSResource : public CSResourceBase
{
public:
	CSResource(UINT strid, UINT count, void* InitData);
	~CSResource();

	void Read(OUT void* data);

private:
	void CreateBuffer(UINT strid, UINT count, void* InitData, ID3D11Buffer* buffer);
	void CreateSRV();
	void CreateUAV();

private:
	UINT byteWidth;

	ID3D11Buffer* buffer; //�ڵ����� ������ ������ 
	ID3D11Buffer* result; //Read�� ��� 
};

//Compute Shader-> Gpu 64-> 
class CSAppend : public CSResourceBase
{
public:
	CSAppend(UINT stride, UINT count, void* InitData);
	~CSAppend();

	void Write(void* data);
	void Read(void* data);
private:
	void CreateBuffer(UINT stride, UINT count, void* initData, ID3D11Buffer* buffer);
	void CreateUAV();

	UINT byteWidth;
	UINT count;

	ID3D11Buffer* buffer;
	ID3D11Buffer* result;
};

