#pragma once


struct FrameData //�Ѱ��� Ʈ���� �� frame 
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
			&mat);//��Ʈ���� ���� 
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

struct Frame //��� Ʈ���� ���� ���� 1������ 
{
	Frame()
	{

	}

	Frame(wstring name, FrameData* data, float time)
	{
		this->name = name;
		datas.push_back(data);
		this->time = time; //���� ���������� �Ѿ� ���� �ð�
	}

	float time;
	wstring name;
	vector<FrameData*> datas;
};

class  BoneClip //Animation 1����
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

