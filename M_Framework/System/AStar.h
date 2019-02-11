#pragma once
#include "Components/Materials/Material.h"
#define BIGNUM 5000 //충분히 큰 F 값(초기값)
class AStar
{
private:
	enum class State
	{
		Searching = 0,  // 경로 검색중
		Found,			// 경로 발견
		Noway,			// 경로 없음
		End				// 경로 탐색전 
	};
	enum class Type
	{
		Empty = 0,  //빈타일(지나갈수있는)
		Start,		//시작 지점
		End,		//끝 지점
		Wall		//벽(지나갈수 없는 타일)
	};

	struct AStarTile
	{
		D3DXCOLOR color;	 //오픈리스트? 클로즈 리스트? 최단거리
		bool bWalkAble;		 //통과 여부 
		bool ListOn;		 //OpenList에 추가 여부 
		int i, j;			 //배열 인덱스 
		int F, G, H;		 //비용들 
		AStarTile* parent;	 //부모 타일 
		Type type;			 //타일 속성
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
	vector<AStarTile*> closeList; //!= 최단거리 

	State state;

	int startX, startY; //시작 지점
	int endX, endY; //끝지점
	int lastIndex; //마지막 인덱스 번호

	int Ci; //클로즈 리스트의 마지막 인덱스 i;
	int Cj; //클로즈 리스트의 마지막 인덱스 j;
	int Cg; //클로즈 리스트의 마지막 인덱스 g;

	UINT** info;
	float width, height; //타일 갯수
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