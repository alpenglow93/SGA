#pragma once
class Shader
{
private:
	ID3D11VertexShader * vs;
	ID3D11PixelShader* ps;
	ID3D11ComputeShader* cs;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
	ID3D10Blob* csBlob;

private:
	struct WorldBufferDesc
	{
		D3DXMATRIX World;
	};
	ID3D11Buffer * WorldBuffer;
	WorldBufferDesc WorldBufferData;
	
	ID3D11InputLayout* vertexLayout; //Ãß°¡ 

	void CreateBuffer();

	bool bSubContext;

public:
	Shader(wstring file, bool bSubContext = false);
	~Shader();
	void SetWVPData(D3DXMATRIX World);
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
	void SetShader();
};

