#pragma once
#include "Component.h"
class Camera : public Component
{
public:
	Camera(class Object* obj);
	~Camera();

	void Update();
	void Render();

	void SetViewOrhto(D3DXMATRIX* view, D3DXMATRIX* ortho = NULL);
	D3DXMATRIX GetViewOrhto();

	// Component을(를) 통해 상속됨
	virtual void SetInsfector() override;

private:
	struct ViewOrtho
	{
		ViewOrtho()
		{
			D3DXMatrixIdentity(&Data.View);
			D3DXMatrixIdentity(&Data.Ortho);

			D3D11_BUFFER_DESC bufferDesc = { 0 };
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.ByteWidth = sizeof(Struct);
			DEVICE()->CreateBuffer(&bufferDesc, NULL, &Buffer);
		}

		void SetView(D3DXMATRIX view)
		{
			Data.View = view;
			bChanged = true;
		}
		void SetOrtho(D3DXMATRIX ortho)
		{
			Data.Ortho = ortho;
			bChanged = true;
		}
		void Change()
		{
			if (bChanged)
			{
				D3D11_MAPPED_SUBRESOURCE map;
				Struct s;
				D3DXMatrixTranspose(&s.View, &Data.View);
				D3DXMatrixTranspose(&s.Ortho, &Data.Ortho);
				DEVICECONTEXT()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
				{
					memcpy(map.pData, &s, sizeof(Struct));
				}
				DEVICECONTEXT()->Unmap(Buffer, 0);
			}
			DEVICECONTEXT()->VSSetConstantBuffers(0, 1, &Buffer);
		}

		D3DXMATRIX Get() { return Data.Ortho, Data.View; }

	private:
		struct Struct
		{
			D3DXMATRIX View;
			D3DXMATRIX Ortho;
		}Data;

		ID3D11Buffer* Buffer;

		bool bChanged = false;
	}*Buffer;

	class Transform* transform;

	
};

