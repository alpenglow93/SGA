#pragma once

#define RESET_LOCATION 1 //Position 초기화
#define RESET_ROTATION 2 //Angle 초기화
#define RESET_SCALE    4 //Scale 초기화 



//이동 회전 크기 + 부모자식 관계 
class Transform
{
private:
	D3DXVECTOR2 position;
	float angle;
	D3DXVECTOR2 scale;

	union
	{
		struct 
		{
			D3DXVECTOR2 AxisX;
			D3DXVECTOR2 AxisY;
		};
		struct
		{
			D3DXVECTOR2 Axis[2];
		};
	};
	
	D3DXMATRIX world;
	D3DXMATRIX local;

private:
	Transform* pParent;	//부모

	Transform* pFirstChild; //첫번째 자식

	Transform* pNextSilbing; //형제

public:
	Transform();
	~Transform();

	void Reset(DWORD flag = RESET_LOCATION | RESET_ROTATION | RESET_SCALE);
	// 
	void AddChild(Transform* pNewChild);
	void AttachTo(Transform* pNewParent);
	void ReleaseParent();

	void SetWorldPosition(float x, float y);
	void SetWorldPosition(D3DXVECTOR2 vec);

	void SetLocalPosition(float x ,float y);
	void SetLocalPosition(D3DXVECTOR2 vec);

	void Rotation(float rotation);

	void Scale(float x, float y); //대입
	void Scale(D3DXVECTOR2 vec);

	void Scaling(float x, float y); //증감 
	void Scaling(D3DXVECTOR2 vec);

	void MovePositionSelf(float x, float y);
	void MovePositionSelf(D3DXVECTOR2 vec);

	void DefaultControl();


	void Update();
	void Render(); //기즈모 랜더 

public:

	//Position
	D3DXVECTOR2 GetWorldPosition() const;
	D3DXVECTOR2 GetLocalPosition() const;

	//Rotate
	float GetRotation() const;
	D3DXQUATERNION GetWorldRotateQuaternion() const;

	//scale
	D3DXVECTOR2 GetScale() const;

	//Axis
	void GetUnitAxis(OUT D3DXVECTOR2* axis) const; //방향만 
	void GetScaledAxis(OUT D3DXVECTOR2* axis) const; //방향 + 크기 

	//Matrix
	D3DXMATRIX World() const;
	D3DXMATRIX WorldRotateMatrix() const;
};

