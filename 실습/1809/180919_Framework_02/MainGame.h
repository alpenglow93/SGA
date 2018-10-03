#pragma once
class MainGame
{
private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* vertexLayout;
	//D3D11_INPUT_ELEMENT_DESC layoutDesc;


	struct Vertex
	{
		D3DXVECTOR3 position;
	};

	UINT vertexCount;

public:
	MainGame();
	~MainGame();

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
};

