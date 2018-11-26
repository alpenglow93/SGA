#pragma once
class Sprite
{
private:
	wstring filePath;

	VertexPT * vertices; //출력 좌표 + 이미지 출력 영역
	ID3D11Buffer* vertexBuffer;

	const UINT VertexCount = 6;
private:

	D3DXVECTOR2 position; //위치
	D3DXVECTOR2 scale; //크기 
	float rotation;
	D3DXVECTOR2 textureSize; //원본이미지 크기 

	Shader* shader; //쉐이더 

	ID3D11ShaderResourceView* srv; //Texture;

	D3DXMATRIX world; //랜더할때 사용할 녀석
	D3DXMATRIX local; //부모의 행렬의 영향을 받지 않는 좌표 


	//Alpha Blend -> 화면에 출력이된 + 사용항 Texture에 대한 
	//Color 를 섞어서 출력을 한다.
	//[0]화면 + [1]이미지
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

	void Texture(wstring file); //이미지 교체 

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
		ID3D11ShaderResourceView* Srv = NULL; //이미지 데이터 
	};

	static map<wstring, SpriteDesc> descMap;
private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);
};