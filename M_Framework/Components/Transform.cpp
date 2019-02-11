#include "stdafx.h"
#include "Transform.h"
#include "./Materials/ColorShader.h"
#include "./Utilities/Intersect.h"
Transform::Transform()
	:pParent(NULL), pFirstChild(NULL), pNextSilbing(NULL)
{
	Reset();

	vertexCount = 4;
	vertices = new Vertex[vertexCount];

	vertices[0].position = { 0.0f,0.0f,0.0f };
	vertices[1].position = { 25.0f,0.0f,0.0f };

	vertices[2].position = { 0.0f,0.0f,0.0f };
	vertices[3].position = { 0.0f,25.0f,0.0f };

	CreateVertexBuffer(&buffer, vertices, sizeof(Vertex) * vertexCount);

	material = Materials::Get()->Load<ColorShader>(L"Effect.hlsl");
}


Transform::~Transform()
{
}

void Transform::Reset(DWORD flag)
{
	if (flag & RESET_LOCATION)
	{
		this->position = D3DXVECTOR2(0, 0);
	}
	if (flag & RESET_ROTATION)
	{
		this->angle = 0.0f;
		this->AxisX = D3DXVECTOR2(1, 0);
		this->AxisY = D3DXVECTOR2(0, 1);
	}
	if (flag & RESET_SCALE)
	{
		this->scale = D3DXVECTOR2(1, 1);
	}
	Update();
}

//자식으로 붙이겠다. 
void Transform::AddChild(Transform * pNewChild)
{
	if (pNewChild->pParent == this) return;

	//부모자식 부모는 1개만 가져야 된다. 
	pNewChild->ReleaseParent();

	//데이터들 좌표 + 축 + 크기
	//부모 기준으로 해서 

	//부모 행렬의 역행렬 
	//역행렬 어디서 왜 사용을 했는가?

	//부모 -> 로컬 좌표 * 월드
	//역행렬 * 행렬 -> identity 
	//부모 좌표 100, 100;        
	//자식 좌표 200, 200; //부모 자식관계 x
	//자식 좌표 200 - 100 , 200 - 100;
	
	D3DXMATRIX matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &this->world);
	D3DXVec2TransformCoord(
		&pNewChild->position, &pNewChild->position, &matInvWorld);

	for (int i = 0; i < 2; i++)
		D3DXVec2TransformNormal(
			pNewChild->Axis + i,
			pNewChild->Axis + i,
			&matInvWorld
		);
	//크기 변경
	pNewChild->scale.x = D3DXVec2Length(&pNewChild->AxisX);
	pNewChild->scale.y = D3DXVec2Length(&pNewChild->AxisY);

	//정규화
	D3DXVec2Normalize(&pNewChild->AxisX, &pNewChild->AxisX);
	D3DXVec2Normalize(&pNewChild->AxisY, &pNewChild->AxisY);

	pNewChild->pParent = this;

	Transform* pChild = this->pFirstChild;

	if (pChild == NULL)
	{
		pFirstChild = pNewChild;
	}
	else
	{
		while (pChild != NULL)
		{
			if (pChild->pNextSilbing == NULL)
			{
				pChild->pNextSilbing = pNewChild;
				break;
			}
			pChild = pChild->pNextSilbing;
		}
	}
	this->Update();
}

void Transform::AttachTo(Transform * pNewParent)
{
	pNewParent->AddChild(this);
}

void Transform::ReleaseParent()
{
}



void Transform::SetWorldPosition(float x, float y)
{
	SetWorldPosition(D3DXVECTOR2(x, y));
}

void Transform::SetWorldPosition(D3DXVECTOR2 vec)
{
	position = vec;
	if (pParent != NULL)
	{
		D3DXMATRIX matParentInvWorld;
		D3DXMatrixInverse(&matParentInvWorld, NULL, &pParent->world);
		D3DXVec2TransformCoord(&vec, &vec, &matParentInvWorld);
	}

	position = vec;

	Update();
}

void Transform::SetLocalPosition(float x, float y)
{
	SetLocalPosition(D3DXVECTOR2(x, y));
}

void Transform::SetLocalPosition(D3DXVECTOR2 vec)
{
	position = vec;

}

void Transform::Rotation(float rotation)
{
	angle = rotation;
}

void Transform::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x,y));
}

void Transform::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
	Update();
}

void Transform::MovePositionSelf(float x, float y)
{
	MovePositionSelf(D3DXVECTOR2(x, y));
}
//자신의 축의 방향으로 이동 녀석
void Transform::MovePositionSelf(D3DXVECTOR2 vec)
{
	D3DXVECTOR2 moveAxis[2];
	GetUnitAxis(moveAxis);
	
	D3DXVECTOR2 move = { 0.0f,0.0f };
	move += moveAxis[0] * vec.x;
	move += moveAxis[1] * vec.y;

	//월드에서 이동
	D3DXVECTOR2 nowWorldPos = this->GetWorldPosition();
	this->SetWorldPosition(nowWorldPos + move);

}

void Transform::LookDirection(D3DXVECTOR2 vec)
{
	float angle = Intersect::GetAngle(position, vec);
	Rotation(D3DXToDegree(angle));
	//외적
}

void Transform::DefaultControl()
{
	static float accelate = 30.0f;		//초당 이동 증가값
	static float nowSpeed = 30.0f;		//현재 속도 
	static float maxSpeed = 100.0f;	    //최고 속도 

	if (!Input->GetKey(VK_RBUTTON))
	{
		D3DXVECTOR2 inputVector = { 0.0f,0.0f };
		if (Input->GetKey('W'))
			inputVector.y = 1.0f;
		else if(Input->GetKey('S'))
			inputVector.y = -1.0f;

		if (Input->GetKey('D'))
			inputVector.x = 1.0f;
		else if (Input->GetKey('A'))
			inputVector.x = -1.0f;
		
		if (VEC2ZERO(inputVector) == false)
		{
			D3DXVec2Normalize(&inputVector, &inputVector);
		}

		//이동
		D3DXVECTOR2 target = inputVector * maxSpeed;
		this->MovePositionSelf(target * Time->Elapsed());

		//회전 처리 
	}

}

void Transform::DefaultControl2()
{
	static D3DXVECTOR2 StartPos = { 0.0f,0.0f };
	static D3DXVECTOR2 EndPos = { 0.0f,0.0f };

	static float Distance = 200.0f;
	static float TimeScale = 0.0f;

	if (Input->GetKey(VK_RBUTTON))
	{
		if (Input->GetKeyDown('A'))
		{
			TimeScale = 0.0f;
			StartPos = GetWorldPosition();
			EndPos = { StartPos.x - Distance, StartPos.y };
		}
		if (Input->GetKey('A'))
		{
			TimeScale += Time->Elapsed();
		}
		if (Input->GetKeyUp('A'))
		{
			SetWorldPosition(StartPos);
			StartPos = { 0.0f,0.0f };
			EndPos = { 0.0f,0.0f };
		}
		D3DXVECTOR2 result;
		D3DXVec2Lerp(&result, &StartPos, &EndPos, TimeScale);
		if(!VEC2ZERO(StartPos) || !VEC2ZERO(EndPos))
			SetWorldPosition(result);
	}
}

void Transform::Update()
{
	if (!bActive) return;
	D3DXMatrixIdentity(&local);

	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, D3DXToRadian(angle));
	D3DXVECTOR2 axis[2];
	for (int i = 0; i < 2; i++)
	{
		D3DXVec2TransformNormal(axis + i, Axis + i, &R);
		D3DXVec2Normalize(axis + i, axis + i);
	}

	//스케일을 가진 축 
	D3DXVECTOR2 scaledRight = axis[0] * scale.x;
	D3DXVECTOR2 scaledUp = axis[1] * scale.y;
	/*
		1 0 0 0 -> X축 - 크기 * 방향
		0 1 0 0 -> Y축 - 크기 * 방향
		0 0 1 0
		0 0 0 1 -> Positin (위치)
	*/

	memcpy(&local._11, &scaledRight, sizeof(D3DXVECTOR2));
	memcpy(&local._21, &scaledUp, sizeof(D3DXVECTOR2));
	memcpy(&local._41, &position, sizeof(D3DXVECTOR2));

	if (this->pParent == NULL)
	{
		world = local;
	}
	else
	{
		world = local * pParent->world;
	}

	Transform* pChild = this->pFirstChild;
	while (pChild != NULL)
	{
		pChild->Update();
		pChild = pChild->pNextSilbing;
	}
}

void Transform::Render()
{
	if (!bActive) return;

	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	material->Color(0xFFFF0000);
	material->World(World());
	material->Render();
	DEVICECONTEXT()->Draw(vertexCount /2, 0);

	material->Color(0xFF00FF00);
	material->Render();
	DEVICECONTEXT()->Draw(vertexCount / 2, vertexCount /2);
}


//================================ Get ===============================//

D3DXVECTOR2 Transform::GetWorldPosition() const
{
	D3DXVECTOR2 pos = this->position;

	if (this->pParent)
		D3DXVec2TransformCoord(&pos, &pos, &pParent->world);

	return pos;
}

D3DXVECTOR2 Transform::GetLocalPosition() const
{

	return position;
}

D3DXQUATERNION Transform::GetWorldRotateQuaternion() const
{
	D3DXQUATERNION quat; 
	D3DXQuaternionRotationMatrix(&quat, &world);

	return quat;
}

D3DXVECTOR2 Transform::GetScale() const
{
	return scale;
}

void Transform::GetUnitAxis(OUT D3DXVECTOR2 * axis) const
{
	for (int i = 0; i < 2; i++)
		D3DXVec2Normalize(axis + i, this->Axis + i);

	if (this->pParent) {
		for (int i = 0; i < 2; i++)
			D3DXVec2TransformNormal(
				&axis[i], &axis[i], &pParent->world
			);
	}
}

D3DXMATRIX Transform::World() const
{
	return world;
}
///////////////////////////////////////////////////////////////////////////
void Transform::SetInsfector()
{
	ImGui::Checkbox("Transform", &bActive);

	ImGui::InputFloat2("Position", position,2);
	ImGui::InputFloat("Rotation", &angle);
	ImGui::InputFloat2("Scale", scale,2);

	ImGui::Separator();//선을 그어 주는 녀셕
}
