#pragma once
#include "./Singleton/SingletonBase.h"
#include "../Component.h"
#include "./Render/Shader.h"
struct BufferDesc
{
	ID3D11Buffer* buffer;
	void* data;
	UINT dataSize;

	BufferDesc(void* data, UINT size)
		:data(data), dataSize(size)
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = size;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;

		DEVICE()->CreateBuffer(&desc, NULL, &buffer);
	}
	virtual ~BufferDesc()
	{
		SAFE_RELEASE(buffer);
	}
	void Map(void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResouce;
		
		DEVICECONTEXT()->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResouce);

		memcpy(mappedResouce.pData, data, size);

		DEVICECONTEXT()->Unmap(buffer, 0);
	}
	void SetPSBuffer(UINT slot)
	{
		Map(data, dataSize);

		DEVICECONTEXT()->PSSetConstantBuffers(slot, 1, &buffer);
	}
	void SetVSBuffer(UINT slot)
	{
		Map(data, dataSize);

		DEVICECONTEXT()->VSSetConstantBuffers(slot, 1, &buffer);
	}
};


class Material : public Component
{
protected:
	friend class Materials;
	Shader* shader;

	static ID3D11SamplerState* SamplerWrap;
public:
	Material(wstring file, string vs = "VS", string ps = "PS");
	virtual ~Material();

	void World(D3DXMATRIX World);
	void CreateInputLayOut(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
	virtual void Render();

	// Component을(를) 통해 상속됨
	virtual void SetInsfector() override;
protected:
	void SetMaterialMap(wstring file, Material* mat);

	static void CreateSampler();
};

class Materials : public SingletonBase<Materials>
{
private:
	friend class Material;
public:
	Materials();
	~Materials();

	template<typename T>
	T* Load(wstring file)
	{
		auto iter = MaterialMap.find(file);
		if (iter == MaterialMap.end())
		{
			T* result = new T(file);
			return result;
		}
		return (T*)iter->second;
	}
	Material* Find(wstring name);
private:
	map<wstring, Material*> MaterialMap;
};

