#pragma once
class Shader
{
private:
	ID3D11VertexShader * vs;
	ID3D11PixelShader* ps;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
private:
	struct WVPBufferDesc
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Projection;

	};
	ID3D11Buffer * WVPBuffer;
	WVPBufferDesc WVPBufferData;

	ID3D11InputLayout* vertexLayout;	//�߰�

	void CreateWVPBuffer();
public:
	Shader();
	Shader(wstring file, string vs = "VS", string ps = "PS");
	~Shader();
	void SetWVPData(D3DXMATRIX World);
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
	void SetShader();
};

