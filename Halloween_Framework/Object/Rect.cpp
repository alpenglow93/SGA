#include "stdafx.h"
#include "Rect.h"

void Rect::CreateColorBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ColorBufferDesc) ;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = DEVICE()->CreateBuffer(
		&bufferDesc,
		NULL, &colorBuffer);
	assert(SUCCEEDED(hr) && "Not Create ColorBuffer");
}

Rect::Rect()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matScale);

	line = new Line;

	Init();
}

Rect::~Rect()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE_ARRAY(vertices);
}

void Rect::Init()
{
	vertices = new Vertex[VertexCount];

	vertices[0].position = { -0.5f, -0.5f, 0.0f };
	vertices[1].position = { -0.5f,  0.5f, 0.0f };
	vertices[2].position = {  0.5f, -0.5f, 0.0f };

	vertices[3].position = {  0.5f, -0.5f, 0.0f };
	vertices[4].position = { -0.5f,  0.5f, 0.0f };
	vertices[5].position = {  0.5f,  0.5f, 0.0f };

	this->CreateVertexBuffer();
	this->CreateColorBuffer();

	shader = new Shader(L"Effect.hlsl");
	shader->CreateInputLayout(Vertex::desc, Vertex::count);
}


void Rect::Update()
{
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&matTrans, position.x + scale.x * 0.5f,position.y + scale.y * 0.5f,1.0f);
	D3DXMatrixRotationZ(&matRot, rotate);

	matWorld = matScale * matRot  * matTrans;
	shader->SetWVPData(matWorld);
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	shader->SetShader();

	DEVICECONTEXT()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT()->IASetVertexBuffers(0, 1, &vertexBuffer,&stride, &offset);
	DEVICECONTEXT()->Draw(VertexCount, 0);
}

void Rect::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //Defulat로 수정
	bufferDesc.ByteWidth = sizeof(Vertex) * VertexCount;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;

	HRESULT hr = DEVICE()->CreateBuffer(&bufferDesc,&data, &vertexBuffer);
	assert(SUCCEEDED(hr) && "Not Create VertexBuffer");
}

void Rect::GizmoRender()
{
	//AABB 
	this->SetColor(0xFF00FF00);
	this->GetRect();
	D3DXVECTOR2 GizmoPosition = D3DXVECTOR2(AABB.left, AABB.top);
	float GizmoAngle = rotate;

	//왼쪽 면
	line->Position(GizmoPosition);
	line->Scale(1, AABB.bottom - AABB.top);
	line->Rotation(0.0f);
	line->Update(shader);
	line->Render(shader);
	//아래면 
	GizmoPosition = D3DXVECTOR2(AABB.left, AABB.bottom);
	line->Position(GizmoPosition);
	line->Rotation(D3DXToRadian(-90.0f));
	line->Scale(1, AABB.right- AABB.left);
	line->Update(shader);
	line->Render(shader);

	//오른쪽면 
	GizmoPosition = D3DXVECTOR2(AABB.right, AABB.bottom);
	line->Position(GizmoPosition);
	line->Rotation(D3DXToRadian(-180.0f));
	line->Scale(1, AABB.bottom - AABB.top);
	line->Update(shader);
	line->Render(shader);

	//오른쪽면 
	GizmoPosition = D3DXVECTOR2(AABB.right, AABB.top);
	line->Position(GizmoPosition);
	line->Rotation(D3DXToRadian(-270.0f));
	line->Scale(1, AABB.right - AABB.left);
	line->Update(shader);
	line->Render(shader);

	//OBB 

	D3DXVECTOR3 temp[6];
	for (int i = 0; i < 6; i++)
		D3DXVec3TransformCoord(&temp[i], &vertices[i].position, &matWorld);

	this->SetColor(0xFF008000);
	//0,1,2 5

	GizmoPosition = { temp[0].x, temp[0].y };

	line->Position(GizmoPosition);
	line->Rotation(GizmoAngle);
	line->Scale(1.0f, scale.y);
	line->Update(shader);
	line->Render(shader);

	GizmoPosition = { temp[1].x, temp[1].y };

	line->Position(GizmoPosition);
	line->Rotation(GizmoAngle -D3DXToRadian(90.0f));
	line->Scale(1.0f, scale.x);
	line->Update(shader);
	line->Render(shader);

	GizmoPosition = { temp[5].x, temp[5].y };
	
	line->Position(GizmoPosition);
	line->Rotation(GizmoAngle - D3DXToRadian(180.0f));
	line->Scale(1.0f, scale.y);
	line->Update(shader);
	line->Render(shader);
	//
	//
	GizmoPosition = { temp[2].x, temp[2].y };
	
	line->Position(GizmoPosition);
	line->Rotation(GizmoAngle - D3DXToRadian(270.0f));
	line->Scale(1.0f, scale.x);
	line->Update(shader);
	line->Render(shader);
}

void Rect::GetRect(float * left, float * right, float * top, float * bottom)
{
	*left = vertices[0].position.x;
	*right = vertices[2].position.x;
	*top = vertices[1].position.y;
	*bottom = vertices[3].position.y;
}

RECT Rect::GetRect()
{
	D3DXVECTOR3 temp[6];
	for (int i = 0; i < 6; i++)
		D3DXVec3TransformCoord(&temp[i], &vertices[i].position, &matWorld);

	D3DXVECTOR2 vMin, vMax;
	vMin = { temp[0].x, temp[0].y };
	vMax = { temp[0].x,temp[0].y };

	for (int i = 1; i < 6; i++)
	{
		if (vMin.x > temp[i].x)
			vMin.x = temp[i].x;
		if (vMin.y > temp[i].y)
			vMin.y = temp[i].y;
		if (vMax.x < temp[i].x)
			vMax.x = temp[i].x;
		if (vMax.y < temp[i].y)
			vMax.y = temp[i].y;
	}

	AABB = { (LONG)vMin.x, (LONG)vMin.y, (LONG)vMax.x, (LONG)vMax.y };

	return AABB;
}

void Rect::SetColor(D3DXCOLOR color)
{
	colorBufferData.color = color;
	DEVICECONTEXT()->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DEVICECONTEXT()->PSSetConstantBuffers(0, 1, &colorBuffer);
}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Rect::Rotation(float angle)
{
	rotate = angle;
}
