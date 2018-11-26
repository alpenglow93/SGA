#pragma once
class Sprite
{
private:
	wstring filePath;

	VertexPT * vertices; //��� ��ǥ + �̹��� ��� ����
	ID3D11Buffer* vertexBuffer;

	const UINT VertexCount = 6;
private:

	D3DXVECTOR2 position; //��ġ
	D3DXVECTOR2 scale; //ũ�� 
	float rotation;
	D3DXVECTOR2 textureSize; //�����̹��� ũ�� 

	Shader* shader; //���̴� 

	ID3D11ShaderResourceView* srv; //Texture;

	D3DXMATRIX world; //�����Ҷ� ����� �༮
	D3DXMATRIX local; //�θ��� ����� ������ ���� �ʴ� ��ǥ 


	//Alpha Blend -> ȭ�鿡 ����̵� + ����� Texture�� ���� 
	//Color �� ��� ����� �Ѵ�.
	//[0]ȭ�� + [1]�̹���
	ID3D11BlendState* blendState[2];

	void CreateBlendState();
private:
	struct VertexUVDesc
	{
		D3DXVECTOR2 offset;
		D3DXVECTOR2 maxFrame;
	}vertexUVData;

	ID3D11Buffer* VertexUVBUffer;
	ID3D11SamplerState* samplerState;

	void CreateSamplerState();
	void CreateVertexUVBuffer();

public:
	Sprite(wstring file);
	Sprite(wstring file, float endX, float endY);
	Sprite(wstring file, float startX, float startY, float endX, float endY);

	~Sprite();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	D3DXVECTOR2 Scale() { return scale; }
	D3DXVECTOR2 TextureSize() { return textureSize; }

	void Rotation(float angle);

	void Offset(float x, float y);
	void Offset(D3DXVECTOR2 offset);

	void MaxFrame(float x, float y);
	void MaxFrame(D3DXVECTOR2 offset);

	void Texture(wstring file); //�̹��� ��ü 

	ID3D11ShaderResourceView* Texture() { return srv; }
	D3DXVECTOR2 Position() { return position; }
	float Rotation() { return rotation; }


	void Update();
	void Render();

	D3DXMATRIX Local() { return local; }
	void World(D3DXMATRIX mat) { world = mat; };

private:
	void Init(wstring file, float startX, float startY, float endX, float endY);

};

//////////////////////////////////////////////////////////////////////

class Sprites
{
private:
	friend class Sprite;

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* Srv = NULL; //�̹��� ������ 
	};

	static map<wstring, SpriteDesc> descMap;
private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);
};