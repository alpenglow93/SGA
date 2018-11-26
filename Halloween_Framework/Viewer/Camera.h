#pragma once
class Camera
{
private:
	struct VeiwOrthoBufferDesc
	{
		D3DXMATRIX View; //촬영하는 카메라
		D3DXMATRIX Ortho; //투영()
	}ViewOrthoBufferData;

	ID3D11Buffer* ViewOrthoBuffer;

	D3DXVECTOR3 position;

public:
	Camera();
	~Camera();

	void Update();

	void CreateBuffer();
	void SetBuffers();

	//Getter(데이터를 가지고 오는 함수 
	//Setter(데이터를 넣어주는 함수 

	//Setter
	void Position(D3DXVECTOR2 vec); 
	void Position(float x, float y);
	//Getter
	//D3DXVECTOR2 Position();
	//주소 값에 의한 호출에 의한 반환
	void Position(D3DXVECTOR2* vec);

};

