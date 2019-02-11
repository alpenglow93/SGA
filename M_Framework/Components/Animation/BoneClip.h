#pragma once


struct FrameData //한개의 트랜스 폼 frame 
{
	D3DXMATRIX frameMatrix;

	D3DXVECTOR3 translation;
	D3DXQUATERNION Rotation;
	D3DXVECTOR3 scale;

	FrameData()
	{

	}

	FrameData(D3DXMATRIX mat)
	{
		D3DXMatrixDecompose(&scale, &Rotation, &translation,
			&mat);//메트릭스 분할 
	}


	void MakeTransform()
	{
		D3DXMATRIX T;
		D3DXMatrixTranslation(&T,
			translation.x, translation.y, translation.z);

		D3DXMATRIX R;
		D3DXMatrixRotationQuaternion(&R, &Rotation);

		D3DXMATRIX S;
		D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);

		frameMatrix = S * R * T;
	}
};

struct Frame //모든 트랜스 폼에 대한 1프레임 
{
	Frame()
	{

	}

	Frame(wstring name, FrameData* data, float time)
	{
		this->name = name;
		datas.push_back(data);
		this->time = time; //다음 프레임으로 넘어 가는 시간
	}

	float time;
	wstring name;
	vector<FrameData*> datas;
};

class  BoneClip //Animation 1동작
{
public:
	BoneClip();
	~BoneClip();

	void Update();
	void Render();

	void AddFrameData(Frame* frame, float time = 0.3f);
	void SaveFile(wstring file);
	void LoadFile(wstring file);

	void Play() { bPlay = true; }
	vector<D3DXMATRIX> GetFrame() { return renderFrame; }
	UINT GetFrameCount() { return frames.size(); }
private:

	bool bPlay = false;

	float time;
	float deltaTime;
	FrameData* result;

	UINT currentFrame;
	UINT nextFrame;
	vector<D3DXMATRIX> renderFrame;
	vector<Frame*> frames;
};

