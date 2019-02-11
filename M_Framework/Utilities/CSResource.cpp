#include "stdafx.h"
#include "CSResource.h"


CSResourceBase::CSResourceBase()
	:srv(NULL),uav(NULL)
{
}

CSResourceBase::~CSResourceBase()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(uav);
}
//-----------------------------------------------------------------------------//
// CSResource (1회 계산용)
//----------------------------------------------------------------------------//
CSResource::CSResource(UINT stride, UINT count, void * InitData)
	:buffer(NULL),result(NULL), byteWidth(stride * count)
{
	CreateBuffer(stride, count, InitData, buffer);
	CreateBuffer(stride, count, NULL, result);

	CreateSRV();
	CreateUAV();
}

CSResource::~CSResource()
{
	SAFE_RELEASE(buffer);
	SAFE_RELEASE(result);
}

void CSResource::Read(OUT void * data)
{
	DEVICECONTEXT()->CopyResource(result, buffer);
	D3D11_MAPPED_SUBRESOURCE map = { 0 };
	DEVICECONTEXT()->Map(result, 0, D3D11_MAP_READ, 0, &map);
	{
		memcpy(data, map.pData, byteWidth);
	}
	DEVICECONTEXT()->Unmap(result, 0);
}

void CSResource::CreateBuffer(UINT stride, UINT count, void * InitData, ID3D11Buffer* buffer)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	HRESULT hr;
	if (this->buffer == NULL)
	{
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufferDesc.StructureByteStride = stride;
		bufferDesc.ByteWidth = byteWidth;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		if (InitData != NULL)
		{
			D3D11_SUBRESOURCE_DATA subResource;
			subResource.pSysMem = InitData;

			hr = DEVICE()->CreateBuffer(&bufferDesc, &subResource, &this->buffer);
		}
		else
			hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &this->buffer);
	}
	else
	{
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferDesc.ByteWidth = byteWidth;
		bufferDesc.StructureByteStride = stride;

		hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &result);
	}
	assert(SUCCEEDED(hr));
}

void CSResource::CreateSRV()
{
	D3D11_BUFFER_DESC bufferDesc;
	buffer->GetDesc(&bufferDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	if (bufferDesc.MiscFlags &D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
	{
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = bufferDesc.ByteWidth / 4;
	}
	else if (bufferDesc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
	{
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = bufferDesc.ByteWidth / bufferDesc.StructureByteStride;
	}

	HRESULT hr = DEVICE()->CreateShaderResourceView(buffer, &srvDesc, &srv);
	assert(SUCCEEDED(hr));
}

void CSResource::CreateUAV()
{
	D3D11_BUFFER_DESC bufferDesc;
	buffer->GetDesc(&bufferDesc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;

	if (bufferDesc.MiscFlags &D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
	{
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = bufferDesc.ByteWidth / 4;
	}
	else if (bufferDesc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
	{
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = bufferDesc.ByteWidth / bufferDesc.StructureByteStride;
	}

	HRESULT hr = DEVICE()->CreateUnorderedAccessView(buffer, &uavDesc, &uav);
	assert(SUCCEEDED(hr));
}

CSAppend::CSAppend(UINT stride, UINT count, void * InitData)
	: buffer(NULL), result(NULL), count(count), byteWidth(stride * count)
{
	CreateBuffer(stride, count, InitData, buffer);
	CreateBuffer(stride, count, NULL, result);

	CreateUAV();
}

CSAppend::~CSAppend()
{
	SAFE_RELEASE(buffer);
	SAFE_RELEASE(result);
}

void CSAppend::Write(void * data)
{
	DEVICECONTEXT()->UpdateSubresource(buffer, 0, NULL, data, byteWidth, 0);
}

void CSAppend::Read(void * data)
{
	DEVICECONTEXT()->CopyResource(result, buffer);
	D3D11_MAPPED_SUBRESOURCE map = { 0 };
	DEVICECONTEXT()->Map(result, 0, D3D11_MAP_READ, 0, &map);
	{
		memcpy(data, map.pData, byteWidth);
	}
	DEVICECONTEXT()->Unmap(result, 0);
}

void CSAppend::CreateBuffer(UINT stride, UINT count, void * initData, ID3D11Buffer * buffer)
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	HRESULT hr;
	if (this->buffer == NULL)
	{
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufferDesc.StructureByteStride = stride;
		bufferDesc.ByteWidth = byteWidth;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		if (initData != NULL)
		{
			D3D11_SUBRESOURCE_DATA subResource;
			subResource.pSysMem = initData;

			hr = DEVICE()->CreateBuffer(&bufferDesc, &subResource, &this->buffer);
		}
		else
			hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &this->buffer);
	}
	else
	{
		bufferDesc.Usage = D3D11_USAGE_STAGING;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferDesc.ByteWidth = byteWidth;
		bufferDesc.StructureByteStride = stride;

		hr = DEVICE()->CreateBuffer(&bufferDesc, NULL, &result);
	}
	assert(SUCCEEDED(hr));
}

void CSAppend::CreateUAV()
{
	D3D11_BUFFER_DESC bufferDesc;
	buffer->GetDesc(&bufferDesc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;

	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.NumElements = count;
	uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;

	HRESULT hr = DEVICE()->CreateUnorderedAccessView(buffer, &uavDesc, &uav);
	assert(SUCCEEDED(hr));
}
