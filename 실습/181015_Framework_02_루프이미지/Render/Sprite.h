#pragma once
#include "./Render/Shader.h"
class Sprite
{
private:
	VertexPT* vertices;	//��� ��ǥ + �̹��� ��� ����
	ID3D11Buffer* vertexBuffer;

private:
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;	//��ġ
	D3DXVECTOR2 scale;	//ũ��

	Shader* shader;	//���̴�

	ID3D11ShaderResourceView* srv;	//texture;

	//Alpha Blend -> ȭ�鿡 ����� �� + ����� Texture�� ���� color�� ��� ����� �Ѵ�.
	//[0]ȭ�� + [1]�̹���
	ID3D11BlendState* blendState[2];

	void CreateBlendState();
private:
	struct VertexUVDesc
	{
		D3DXVECTOR2 offset;
		D3DXVECTOR2 padding;
	}vertexUVData;

	ID3D11Buffer* VertexUVBuffer;
	ID3D11SamplerState* samplerState;

	void CreateSamplerState();
	void CreateVertexUVBuffer();

public:
	Sprite();
	Sprite(wstring file);
	~Sprite();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Offset(float x, float y);
	void Offset(D3DXVECTOR2 offset);

	void Update();
	void Render();


};

