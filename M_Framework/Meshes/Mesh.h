#pragma once
class Mesh
{
public:
	friend class Meshes;
public:
	Mesh();
	~Mesh();

	virtual void Update();
	virtual void Render();
protected:
	void CreateVertexBuffer(void* data, UINT size);
	void CreateIndexBuffer(UINT* data);
protected:
	VertexPT* vertices;
	ID3D11Buffer* vertexBuffer;
	UINT VertexCount; //������ 

	ID3D11Buffer* IndexBuffer;
	UINT IndexCount;  //�׸��� ����
};

class Meshes
{
public:
	friend class Mesh;

public:
	static void AddMesh(Mesh* mesh)
	{
		meshes.push_back(mesh);
	}
	static void Delete();
	template <typename T>
	static T* Load()
	{
		for (Mesh* temp : meshes)
		{
			T* result = dynamic_cast<T*>(temp);
			if (result != NULL)
				return result;
		}
		T* mesh = new T;

		meshes.push_back(mesh);
		return mesh;
	}
	
private:
	static vector<Mesh*> meshes;
};