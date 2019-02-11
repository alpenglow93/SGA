#include "stdafx.h"
#include "Tile.h"
#include "./Objects/Object.h"
#include "./Meshes/Rect.h"
#include "./Components/Transform.h"
#include "./Components/Materials/SplatShader.h"

Tile::Tile()
{
	BrushSize = 1;
	bDrawing = false;
	Base = new Object;
	Base->SetMesh(Meshes::Load<Rect>());
	trans = Base->GetComponent<Transform>();
	trans->SetWorldPosition(desc.Width / 2, desc.Height /2);

	SplatShader* shader = Materials::Get()->Load<SplatShader>(L"Splat.hlsl");
	Base->SetMaterial(shader);
	//ID3D11ShaderResourceView* control = Sprites::Load(_Texture + L"Control.png");
	ID3D11ShaderResourceView* tile[4];
	tile[0] = Sprites::Load(_Texture + L"Tile0.jpg");
	tile[1] = Sprites::Load(_Texture + L"Tile1.jpg");
	tile[2] = Sprites::Load(_Texture + L"Tile2.jpg");
	tile[3] = Sprites::Load(_Texture + L"Tile3.jpg");

	LoadControlTextureInfo();
	shader->Texture(control, tile);
}

Tile::~Tile()
{
	SAFE_RELEASE(src);
	SAFE_RELEASE(dest);
	SAFE_RELEASE(control);
	SAFE_DELETE_ARRAY(pixel);
	SAFE_DELETE(Base);
}

void Tile::Update()
{
	if (bDrawing)
	{
		if (Input->GetKeyDown(VK_ADD))
		{
			BrushSize = min(++BrushSize, 100);
		}
		if (Input->GetKeyDown(VK_SUBTRACT))
		{
			BrushSize = max(--BrushSize, 1);
		}

	}
	if (Input->GetKey(VK_LBUTTON) && bDrawing)
	{
		D3DXVECTOR2 TilePos;
		TilePos.x = ((BaseMouse.x + 50.f - BrushSize / 2) <0 ) ? 0 : ((BaseMouse.x + 50.f - BrushSize / 2));
		TilePos.y = ((100 - (BaseMouse.y + 50.f)) - BrushSize / 2 < 0) ? 0 : ((100 - (BaseMouse.y + 50.f)) - BrushSize / 2);

		D3DXVECTOR2 Size;
		Size.x = (TilePos.x + BrushSize / 2 > 100) ? 100 : (TilePos.x + BrushSize / 2);
		Size.y = (TilePos.y + BrushSize / 2 > 100) ? 100 : (TilePos.y + BrushSize / 2);

		TilePos *= width / 100.0f;
		Size *= width / 100.0f;

		for (int y = TilePos.y; y < Size.y; y++)
		{
			for (int x = TilePos.x; x < Size.x; x++)
			{
				pixel[y][x] = color;
			}
		}

		D3D11_MAPPED_SUBRESOURCE map;
		DEVICECONTEXT()->Map(dest, 0, D3D11_MAP_READ_WRITE,0, &map);
		{
			for (int i = 0; i < width;i++)
				memcpy((UINT*)map.pData + (i*width), pixel[i],
					sizeof(UINT) * width);
		}
		DEVICECONTEXT()->Unmap(dest, 0);

		D3DX11LoadTextureFromTexture
		(
			DEVICECONTEXT(),
			dest, NULL, src
		);
		//DEVICECONTEXT()->CopyResource(dest, src);

		SAFE_RELEASE(control);

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		//ShaderResourceView;
		DEVICE()->CreateShaderResourceView(src, &SRVDesc, &control);
		SplatShader* shader = Materials::Get()->Load<SplatShader>(L"Splat.hlsl");
		shader->Texture(control);
	}

	trans->Scale(5, 5);
	Base->Update();
}

void Tile::Render()
{
	Base->Render();
	Base->Insfector();
	ImGui::SetNextWindowPos(ImVec2(0, desc.Height + 2));
	ImGui::SetNextWindowSize(ImVec2(desc.Width, 150));
	ImGui::Begin("Log");
	{
		if (ImGui::Button("Drawing"))
			bDrawing = true;
		ImGui::SameLine();
		if (ImGui::Button("Apply"))
		{
			bDrawing = false;
			D3DX11SaveTextureToFile(
				DEVICECONTEXT(),
				dest,
				D3DX11_IFF_PNG,
				L"map.png"
			);
		}
		ImGui::ColorEdit4("Color", color);
		ImGui::LabelText("Brush Size", "Size : %d", BrushSize);
		ImGui::LabelText("Mouse", "X : %0.1f, Y : %0.1f ", vMouse.x, vMouse.y);
		D3DXVECTOR2 camMouse;
		//mainCamera->Position(&camMouse);
		camMouse.x += vMouse.x;
		camMouse.y += vMouse.y;
		ImGui::LabelText("Inv", "X : %0.1f, Y : %0.1f ", camMouse.x, camMouse.y);
		
		D3DXMATRIX invWorld;
		D3DXMatrixInverse(&invWorld, 0, &trans->World());
		D3DXVec2TransformCoord(&BaseMouse, &camMouse, &invWorld);
		ImGui::LabelText("Base", "X : %0.1f, Y : %0.1f ", BaseMouse.x, BaseMouse.y);


	}
	ImGui::End();
}

void Tile::LoadControlTextureInfo()
{
	wstring path = _Texture + L"terrainControl2.jpg";
	HRESULT hr;
	D3DX11CreateTextureFromFile
	(
		DEVICE(),
		path.c_str(),
		NULL,
		NULL,
		(ID3D11Resource**)&src,
		&hr
	);
	assert(SUCCEEDED(hr));

	D3D11_TEXTURE2D_DESC srcDesc;
	src->GetDesc(&srcDesc);
	width = srcDesc.Width;
	height = srcDesc.Height;

	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags 
		= D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

	hr= DEVICE()->CreateTexture2D(&destDesc, NULL, &dest);
	assert(SUCCEEDED(hr));
	//색상값을 채워주는 녀석
	hr = D3DX11LoadTextureFromTexture
	(
		DEVICECONTEXT(),
		src,
		NULL,
		dest
	);
	assert(SUCCEEDED(hr));
	//색상정보 얻기
	pixel = new UINT*[height];
	
	D3D11_MAPPED_SUBRESOURCE Data;
	DEVICECONTEXT()->Map(dest, 0, D3D11_MAP_READ_WRITE, 0, &Data);
	{
		for (int i = 0; i < height; i++)
		{
			pixel[i] = new UINT[width];
			memcpy(pixel[i], (UINT*)Data.pData + (i * width), 
				sizeof(UINT) * width);
		}
	}
	DEVICECONTEXT()->Unmap(dest, 0);

	D3DX11LoadTextureFromTexture(DEVICECONTEXT(), dest, NULL, src);

	//픽셀 데이터 저장
	//{
	//	FILE* fp;
	//	fopen_s(&fp, "Pixel.txt", "w");
	//	{
	//		for (int i = 0; i < height; i++)
	//		{
	//			for (int j = 0; j < width; j++)
	//			{
	//				float a = (float)((pixel[i][j] & 0xFF000000) >> 24);
	//				float b = (float)((pixel[i][j] & 0x00FF0000) >> 16);
	//				float g = (float)((pixel[i][j] & 0x0000FF00) >> 8 );
	//				float r = (float)((pixel[i][j] & 0x000000FF) >> 0 ); 
	//				char str[64];
	//				sprintf_s(str, "[%d][%d] : %f, %f, %f, %f\n",j,i, a, r, g, b);
	//				fputs(str, fp);
	//
	//			}
 	//		}
	//	}
	//	fclose(fp);
	//}
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	SRVDesc.Format = destDesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	//ShaderResourceView;
	DEVICE()->CreateShaderResourceView(src, &SRVDesc, &control);
}
