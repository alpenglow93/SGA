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

	void Init(); //�ʱ�ȭ
	void Release(); // ���� 
	void Update(); //Ű�Է� , ���, ���콺 
	void Render(); //��� 
	void UpdatePosition();

private:
	void CreateWVPBuffer();
	void SetWVPData(D3DXMATRIX World);
private:
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;
};

