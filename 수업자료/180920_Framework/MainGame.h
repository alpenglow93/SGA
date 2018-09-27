#pragma once
struct WVPBufferDesc
{
	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

class MainGame
{
private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* vertexLayout;

	ID3D11Buffer* RectBuffer;
	UINT RectCount;
	UINT vertexCount;

	D3DXVECTOR3 position;
	VertexPC* RectVertex;

public:
	MainGame();
	~MainGame();

	void Init(); //초기화
	void Release(); // 삭제 
	void Update(); //키입력 , 계산, 마우스 
	void Render(); //출력 
	void UpdatePosition();

private:
	void CreateWVPBuffer();
	void SetWVPData(D3DXMATRIX World);
private:
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
};

