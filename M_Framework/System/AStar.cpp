#include "stdafx.h"
#include "AStar.h"
#include "./Utilities/CSResource.h"
#include "./Components/Materials/Material.h"
#include "Tiles/Tile.h"
AStar::AStar(Tile * tile)
{
	info = tile->GetPixel();
	width = tile->GetWidth();
	height = tile->GetHeight();

	state = State::End;
	tiles = new AStarTile*[(INT)width];

	for (int i = 0; i < (INT)width; i++)
	{
		tiles[i] = new AStarTile[(INT)height];
	}
}

AStar::~AStar()
{
	for(int i =0 ; i < (INT)width; i++)
		SAFE_DELETE_ARRAY(tiles[i]);
}

void AStar::Update()
{
	if (state != State::Searching) return;

	AddOpenList();
	CalculateH();
	CaluclateF();
	AddCloseList();
	CheckArrive();
}

void AStar::Initialize(int startX, int startY, int endX, int endY)
{
	//사용전 현 맵상황에 맞춰서 수정 후 사용
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	FILE* fp;
	fopen_s(&fp, "MapData.txt", "w");
	for (int j = 0; j < (INT)width; j++)
	{
		for (int i = 0; i < (INT)height; i++)
		{
			if (info[j][i] & 0x00F00000)
			{
				tiles[j][i].type = Type::Wall;
				tiles[j][i].color = 0xFF0000FF;
				tiles[j][i].bWalkAble = false;
				tiles[j][i].ListOn = false;
				
			}
			else if (info[j][i] & 0x0000F000)
			{
				tiles[j][i].type = Type::Wall;
				tiles[j][i].color = 0xFF00FF00;
				tiles[j][i].bWalkAble = false;
				tiles[j][i].ListOn = false;
			}
			else if (info[j][i] & 0x000000F0)
			{
				tiles[j][i].type = Type::Wall;
				tiles[j][i].color = 0xFFFF0000;
				tiles[j][i].bWalkAble = false;
				tiles[j][i].ListOn = false;
			}
			else
			{
				tiles[j][i].type = Type::Empty;
				tiles[j][i].color = 0xFFFF0000;
				tiles[j][i].bWalkAble = true;
				tiles[j][i].ListOn = false;
			}
			tiles[j][i].i = i;
			tiles[j][i].j = j;
			tiles[j][i].F = BIGNUM;
			tiles[j][i].G = 0;
			tiles[j][i].H = 0;
			tiles[j][i].parent = NULL;

			if (startX == i && startY == j)
			{
				tiles[j][i].type = Type::Start;
				tiles[j][i].ListOn = true;
				tiles[j][i].bWalkAble = true;
				closeList.push_back(&tiles[j][i]);
				lastIndex = 0;
			}

			if (endX == i && endY == j)
			{
				tiles[j][i].type = Type::End;
				tiles[j][i].ListOn = false;
				tiles[j][i].bWalkAble = true;
			}

			if (i % 5 == 0) fprintf_s(fp, " ");
			if (tiles[j][i].bWalkAble) fprintf_s(fp, "1");
			else fprintf_s(fp, "0");
		}
		char str[10];
		sprintf_s(str, "\n");
		fputs(str, fp);
	}
	fclose(fp);

	state = State::Searching;
}

void AStar::AddOpenList()
{
	Ci = closeList[lastIndex]->j;
	Cj = closeList[lastIndex]->i;
	Cg = closeList[lastIndex]->G;

	if (Ci != 0) //윗이 있냐?
	{
		if (tiles[Ci - 1][Cj].bWalkAble) //바로 윗녀석이 지나갈수 있냐?
		{
			if (!tiles[Ci - 1][Cj].ListOn) //리스트에 추가 되었는냐?
			{
				tiles[Ci - 1][Cj].ListOn = true;
				tiles[Ci - 1][Cj].color = 0xFFF0FFF0;
				tiles[Ci - 1][Cj].G = Cg + 10;
				tiles[Ci - 1][Cj].parent = closeList[lastIndex];
				openList.push_back(&tiles[Ci - 1][Cj]);
			}
			else //오픈 리스트에 추가 되었다면
			{
				if (Cg + 10 < tiles[Ci - 1][Cj].G)
				{
					tiles[Ci - 1][Cj].G = Cg + 10;
					tiles[Ci - 1][Cj].parent = closeList[lastIndex];
				}
			}
		}//end of if(tiles[Ci - 1][Cj].bWalkable)
		if (Cj != 0)
		{
			if (tiles[Ci - 1][Cj - 1].bWalkAble &&
				tiles[Ci - 1][Cj].bWalkAble &&
				tiles[Ci][Cj - 1].bWalkAble) //좌상단 
			{
				if (!tiles[Ci - 1][Cj -1].ListOn) //리스트에 추가 되었는냐?
				{
					tiles[Ci - 1][Cj - 1].ListOn = true;
					tiles[Ci - 1][Cj - 1].color = 0xFFF0FFF0;
					tiles[Ci - 1][Cj - 1].G = Cg + 14;
					tiles[Ci - 1][Cj - 1].parent = closeList[lastIndex];
					openList.push_back(&tiles[Ci - 1][Cj - 1]);
				}
				else //오픈 리스트에 추가 되었다면
				{
					if (Cg + 14 < tiles[Ci - 1][Cj - 1].G)
					{
						tiles[Ci - 1][Cj - 1].G = Cg + 14;
						tiles[Ci - 1][Cj - 1].parent = closeList[lastIndex];
					}
				}
			}
		}//end of if (Cj != 0)
		if (Cj != (UINT)width - 1)
		{
			if (tiles[Ci - 1][Cj + 1].bWalkAble &&
				tiles[Ci - 1][Cj].bWalkAble &&
				tiles[Ci][Cj + 1].bWalkAble)
			{
				if (!tiles[Ci - 1][Cj + 1].ListOn)
				{
					tiles[Ci - 1][Cj + 1].ListOn = true;
					tiles[Ci - 1][Cj + 1].color = 0xFFF0FF0F0;
					tiles[Ci - 1][Cj + 1].G = Cg + 14;
					tiles[Ci - 1][Cj + 1].parent = closeList[lastIndex];
					openList.push_back(&tiles[Ci - 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < tiles[Ci - 1][Cj + 1].G)
					{
						tiles[Ci - 1][Cj + 1].G = Cg + 14;
						tiles[Ci - 1][Cj + 1].parent = closeList[lastIndex];
					}
				}
			}
		}//end of if(Cj != (UINT)width - 1)
	} //end of if(Ci != 0)

	if (Ci != (UINT)height - 1) //아래가 있냐?
	{
		if (tiles[Ci + 1][Cj].bWalkAble) //바로 윗녀석이 지나갈수 있냐?
		{
			if (!tiles[Ci + 1][Cj].ListOn) //리스트에 추가 되었는냐?
			{
				tiles[Ci + 1][Cj].ListOn = true;
				tiles[Ci + 1][Cj].color = 0xFFF0FFF0;
				tiles[Ci + 1][Cj].G = Cg + 10;
				tiles[Ci + 1][Cj].parent = closeList[lastIndex];
				openList.push_back(&tiles[Ci + 1][Cj]);
			}
			else //오픈 리스트에 추가 되었다면
			{
				if (Cg + 10 < tiles[Ci + 1][Cj].G)
				{
					tiles[Ci + 1][Cj].G = Cg + 10;
					tiles[Ci + 1][Cj].parent = closeList[lastIndex];
				}
			}
		}//end of if(tiles[Ci - 1][Cj].bWalkable)
		if (Cj != 0)
		{
			if (tiles[Ci + 1][Cj - 1].bWalkAble &&
				tiles[Ci + 1][Cj].bWalkAble &&
				tiles[Ci][Cj - 1].bWalkAble) //좌상단 
			{
				if (!tiles[Ci + 1][Cj - 1].ListOn) //리스트에 추가 되었는냐?
				{
					tiles[Ci + 1][Cj - 1].ListOn = true;
					tiles[Ci + 1][Cj - 1].color = 0xFFF0FFF0;
					tiles[Ci + 1][Cj - 1].G = Cg + 14;
					tiles[Ci + 1][Cj - 1].parent = closeList[lastIndex];
					openList.push_back(&tiles[Ci + 1][Cj - 1]);
				}
				else //오픈 리스트에 추가 되었다면
				{
					if (Cg + 14 < tiles[Ci + 1][Cj - 1].G)
					{
						tiles[Ci + 1][Cj - 1].G = Cg + 14;
						tiles[Ci + 1][Cj - 1].parent = closeList[lastIndex];
					}
				}
			}
		}//end of if (Cj != 0)
		if (Cj != (UINT)width - 1)
		{
			if (tiles[Ci + 1][Cj + 1].bWalkAble &&
				tiles[Ci + 1][Cj].bWalkAble &&
				tiles[Ci][Cj + 1].bWalkAble)
			{
				if (!tiles[Ci + 1][Cj + 1].ListOn)
				{
					tiles[Ci + 1][Cj + 1].ListOn = true;
					tiles[Ci + 1][Cj + 1].color = 0xFFF0FF0F0;
					tiles[Ci + 1][Cj + 1].G = Cg + 14;
					tiles[Ci + 1][Cj + 1].parent = closeList[lastIndex];
					openList.push_back(&tiles[Ci + 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < tiles[Ci + 1][Cj + 1].G)
					{
						tiles[Ci + 1][Cj + 1].G = Cg + 14;
						tiles[Ci + 1][Cj + 1].parent = closeList[lastIndex];
					}
				}
			}
		}//end of if(Cj != (UINT)width - 1)
	} //end of if(Ci != 0)

	if (Cj != 0)
	{
		if (tiles[Ci][Cj - 1].bWalkAble)
		{
			if (!tiles[Ci][Cj - 1].ListOn)
			{
				tiles[Ci][Cj - 1].ListOn = true;
				tiles[Ci][Cj - 1].color = 0xFFF0FFF0;
				tiles[Ci][Cj - 1].G = Cg + 10;
				tiles[Ci][Cj - 1].parent = closeList[lastIndex];
				openList.push_back(&tiles[Ci][Cj - 1]);
			}
			else
			{
				if (Cg + 10 < tiles[Ci][Cj - 1].G)
				{
					tiles[Ci][Cj - 1].G = Cg + 10;
					tiles[Ci][Cj - 1].parent = closeList[lastIndex];
				}
			}
		}
	}//end of if(Cj != 0)

	if (Cj != (UINT)width - 1)
	{
		if (tiles[Ci][Cj + 1].bWalkAble)
		{
			if (!tiles[Ci][Cj + 1].ListOn)
			{
				tiles[Ci][Cj + 1].ListOn = true;
				tiles[Ci][Cj + 1].color = 0xFFF0FFF0;
				tiles[Ci][Cj + 1].G = Cg + 10;
				tiles[Ci][Cj + 1].parent = closeList[lastIndex];
				openList.push_back(&tiles[Ci][Cj + 1]);
			}
			else
			{
				if (Cg + 10 < tiles[Ci][Cj + 1].G)
				{
					tiles[Ci][Cj + 1].G = Cg + 10;
					tiles[Ci][Cj + 1].parent = closeList[lastIndex];
				}
			}
		}
	}
}

void AStar::CalculateH()
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->H != 0) continue;
		int vertical = (endY - openList[i]->j) * 10;
		int horizontal = (endX - openList[i]->i) * 10;
	
		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		openList[i]->H = vertical + horizontal;
	}
}

void AStar::CaluclateF()
{
	for (int i = 0; i < openList.size(); i++)
	{
		openList[i]->F = openList[i]->G + openList[i]->H;
	}
}

void AStar::AddCloseList()
{
	if (openList.size() == 0)
	{
		state = State::Noway;
		return;
	}

	int index = 0;
	int lowest = BIGNUM;

	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->F < lowest)
		{
			lowest = openList[i]->F;
			index = i;
		}
	}

	openList[index]->color = 0xFFA0A0FF;

	closeList.push_back(openList[index]);
	openList.erase(openList.begin() + index);

	lastIndex++;
}

void AStar::CheckArrive()
{
	if (closeList[lastIndex]->i == endY &&
		closeList[lastIndex]->j == endX)
	{
		state = State::Found;
		closeList[lastIndex]->color = 0xFFFF4040;
		ShowWay(closeList[lastIndex]);
	}
}

void AStar::ShowWay(AStarTile * tile)
{
	if (!(tile->i == endY && tile->j == endX))
		tile->color = 0xFFFF8080;
	way.push_back(tile);
	tile = tile->parent;
	if (tile->parent == NULL)
		return;
	else
		ShowWay(tile);
}

CsAtar::CsAtar()
{
	const int NUM_AGENTS = 32 * 32;
	Agent agentList[NUM_AGENTS];
	Agent a1;
	//Start 
	a1.SourceLoc = { 0, 4 };
	//end;
	a1.TargetLoc = { 6,4 };

	for (int i = 0; i < NUM_AGENTS; i++)
	{
		a1.Id = i;
		agentList[i] = a1;
	}
	const int NUM_SEARCH_RESULTS = NUM_AGENTS;
	const int NUM_OPENLIST_COUNT = NUM_AGENTS * 64;
	AgentList = new CSResource(sizeof(Agent),NUM_AGENTS,agentList);
	openList = new CSResource(sizeof(int),NUM_OPENLIST_COUNT, NULL);
	gridNodeList = new CSResource(sizeof(AstarObject), NUM_OPENLIST_COUNT, NULL);
	searchResult = new CSResource(sizeof(SearchResult), NUM_SEARCH_RESULTS, NULL);

	param = new Parameters;
	param->Initialize(8, 2);
	ID3D11ShaderResourceView* worldMap;

	ID3D11ShaderResourceView* map[2] = { AgentList->SRV(),worldMap };
	ID3D11UnorderedAccessView* uav[3] = { openList->UAV(), searchResult->UAV(),
	gridNodeList->UAV() };

	DEVICECONTEXT()->CSSetConstantBuffers(0, 1, &param->buffer);
	DEVICECONTEXT()->CSSetShaderResources(0, 2, map);
	DEVICECONTEXT()->CSSetUnorderedAccessViews(0, 3, uav, NULL);
	DEVICECONTEXT()->Dispatch(2, 2, 1);

	int node[NUM_OPENLIST_COUNT];
	openList->Read(node);
	SearchResult result[NUM_SEARCH_RESULTS];
	searchResult->Read(result);
}

CsAtar::~CsAtar()
{
	SAFE_DELETE(AgentList);
	SAFE_DELETE(openList);
	SAFE_DELETE(gridNodeList);
	SAFE_DELETE(searchResult);
	SAFE_DELETE(param);
}

void CsAtar::Update()
{
}

void CsAtar::Render()
{
}
