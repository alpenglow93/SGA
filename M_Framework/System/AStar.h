#pragma once
#include "Components/Materials/Material.h"
#define BIGNUM 5000 //����� ū F ��(�ʱⰪ)
class AStar
{
private:
	enum class State
	{
		Searching = 0,  // ��� �˻���
		Found,			// ��� �߰�
		Noway,			// ��� ����
		End				// ��� Ž���� 
	};
	enum class Type
	{
		Empty = 0,  //��Ÿ��(���������ִ�)
		Start,		//���� ����
		End,		//�� ����
		Wall		//��(�������� ���� Ÿ��)
	};

	struct AStarTile
	{
		D3DXCOLOR color;	 //���¸���Ʈ? Ŭ���� ����Ʈ? �ִܰŸ�
		bool bWalkAble;		 //��� ���� 
		bool ListOn;		 //OpenList�� �߰� ���� 
		int i, j;			 //�迭 �ε��� 
		int F, G, H;		 //���� 
		AStarTile* parent;	 //�θ� Ÿ�� 
		Type type;			 //Ÿ�� �Ӽ�
	};
public:
	AStar(class Tile* tile);
	~AStar();

	void Update();

	void Initialize(int startX = 0, int startY = 0, int endX= 0, int endY =0);
	vector<AStarTile*> GetWay() { return way; }
private:
	void AddOpenList();
	void CalculateH();
	void CaluclateF();
	void AddCloseList();
	void CheckArrive();
	void ShowWay(AStarTile* tile);
private:
	AStarTile** tiles;
	vector<AStarTile*> way;
	vector<AStarTile*> openList;
	vector<AStarTile*> closeList; //!= �ִܰŸ� 

	State state;

	int startX, startY; //���� ����
	int endX, endY; //������
	int lastIndex; //������ �ε��� ��ȣ

	int Ci; //Ŭ���� ����Ʈ�� ������ �ε��� i;
	int Cj; //Ŭ���� ����Ʈ�� ������ �ε��� j;
	int Cg; //Ŭ���� ����Ʈ�� ������ �ε��� g;

	UINT** info;
	float width, height; //Ÿ�� ����
};

class CsAtar
{
public:
	CsAtar();
	~CsAtar();

	void Update();
	void Render();

private:
	struct Parameters : public BufferDesc
	{
		Parameters() : BufferDesc(&Data, sizeof(Struct))
		{

		}
		void Initialize(int block, int dimensions)
		{
			Data.Block = block;
			Data.Dimensions = dimensions;
		}

	private:
		struct Struct
		{
			int Block = 0;
			int Dimensions = 0;
			D3DXVECTOR2 padding;
		}Data;
	}*param;
	struct SearchResult 
	{
		int AgentId;
		int FinalCost;
		D3DXVECTOR2 TargetLoc;
	};

	struct Agent 
	{
		int Id;
		D3DXVECTOR2 SourceLoc;
		D3DXVECTOR2 TargetLoc;
	};

	struct AstarObject
	{
		int x;
		int y; 
		int cost;
		int g_cost;
		int parent_id;
		int status;
		int n;
	};


	struct BufType 
	{
		float f;
	};
	struct SubType
	{
		float f1;
	};
	struct ParentType 
	{
		float f1[40];
	};
private:
	class CSResource* AgentList;
	ID3D11ShaderResourceView* Map;

	class CSResource* openList;
	class CSResource* gridNodeList;
	class CSResource* searchResult;

	class Shader* shader;
};