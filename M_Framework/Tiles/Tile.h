#pragma once
class Tile
{
public:
	Tile();
	~Tile();

	void Update();
	void Render();

	float GetWidth() { return width; }
	float GetHeight() { return height; }
	UINT** GetPixel() { return pixel; }
	class Transform* GetTransform() { return trans; }
private:
	class Object* Base;
	class Transform* trans;
	bool bDrawing;
	//bool bApply;
	D3DXVECTOR2 BaseMouse;

	UINT BrushSize;

	D3DXCOLOR color;

	UINT width; //control Texture width
	UINT height; // "		"	  height
	ID3D11Texture2D* src;  //원본 텍스쳐 
	ID3D11Texture2D* dest; //데이터를 읽을 텍스쳐 
	ID3D11ShaderResourceView* control; //쉐이더에 보낼 텍스쳐 

	UINT** pixel; //색상정보 

	void LoadControlTextureInfo();
};

