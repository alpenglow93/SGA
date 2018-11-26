#pragma once
class Camera
{
private:
	struct VeiwOrthoBufferDesc
	{
		D3DXMATRIX View; //�Կ��ϴ� ī�޶�
		D3DXMATRIX Ortho; //����()
	}ViewOrthoBufferData;

	ID3D11Buffer* ViewOrthoBuffer;

	D3DXVECTOR3 position;

public:
	Camera();
	~Camera();

	void Update();

	void CreateBuffer();
	void SetBuffers();

	//Getter(�����͸� ������ ���� �Լ� 
	//Setter(�����͸� �־��ִ� �Լ� 

	//Setter
	void Position(D3DXVECTOR2 vec); 
	void Position(float x, float y);
	//Getter
	//D3DXVECTOR2 Position();
	//�ּ� ���� ���� ȣ�⿡ ���� ��ȯ
	void Position(D3DXVECTOR2* vec);

};

