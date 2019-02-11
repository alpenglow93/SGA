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
	ID3D11Texture2D* src;  //���� �ؽ��� 
	ID3D11Texture2D* dest; //�����͸� ���� �ؽ��� 
	ID3D11ShaderResourceView* control; //���̴��� ���� �ؽ��� 

	UINT** pixel; //�������� 

	void LoadControlTextureInfo();
};

