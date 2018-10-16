#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"


MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}
//�̹��� Ȯ���� gif -> �� ó�� ����� 1�常 ���
//bmp -> ���� ������ �����Ӵ�. (����1. �뷮�� ũ��. ����2. ���İ��� ����)
//png -> 2��°�� ���������� �����Ӵ�. ���İ� ����, �뷮 �߰�
//jpg -> ���� ���������� ����, �뷮�� �۰�, ���İ��� ����.
//dds -> directx ���� �����̶� �ٸ� ���������� ���Ұ�

void MainGame::Init()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			loc[i][j].state = LOC::NONE;
			loc[i][j].sprite = NULL;
			loc[i][j].rect = new Rect;
			loc[i][j].rect->Position(i * desc.Width / 20, j * desc.Height / 20);
			loc[i][j].rect->Scale(desc.Width / 20, desc.Height / 20);
		}
	}
	sprite = new Sprite(L"AllMario.png");
	sprite->Position(300, 300);
	sprite->Scale(100, 150);
	sprite->Offset(0, 0);
}

void MainGame::Release()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			SAFE_DELETE(loc[i][j].sprite);
			SAFE_DELETE(loc[i][j].rect);
		}
	SAFE_DELETE(sprite);
}

void MainGame::Update()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			loc[i][j].rect->Update();
			if (loc[i][j].state != LOC::NONE) continue;

			if (Intersect::IsConstainsPoint(loc[i][j].rect, loc[i][j].rect->GetWorld(), vMouse))
			{
				if (Input->GetKeyDown(VK_LBUTTON))
				{
					loc[i][j].state = (LOC)(click % 2);
					if (loc[i][j].state == LOC::BLACK)
					{
						loc[i][j].sprite = new Sprite(L"Black.png");
					}
					else
					{
						loc[i][j].sprite = new Sprite(L"White.png");
					}
					loc[i][j].sprite->Position(loc[i][j].rect->GetPosition());
					loc[i][j].sprite->Scale(desc.Width / 20.0f, desc.Height / 20.0f);
					loc[i][j].sprite->Update();
					//click++;
				}
			}
		}
		this->CheckWinPlayer();

		if (bGameOver == true)
		{
			if (winPlayer == PLAYER::BLACK)
			{
				winLogo = new Sprite(L"Black Win.png");
			}
			else if(winPlayer == PLAYER::WHITE)
			{
				winLogo = new Sprite(L"White Win.png");
			}
			winLogo->Position(desc.Width / 2 - 300, desc.Height / 2.0f);
			winLogo->Scale(600, 400);
			winLogo->Update();
		}
		click++;
		sprite->Offset(click / 100, 0);
		sprite->Update();
	}
}

void MainGame::Render()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (Input->GetToggleKey(VK_F1))
			{
				loc[i][j].rect->SetColor(D3DXCOLOR(1, 0, 1, 1));
				loc[i][j].rect->Render();
			}

			if (loc[i][j].state == LOC::NONE) continue;

			loc[i][j].sprite->Render();
		}
	}
	if (bGameOver)
	{
		winLogo->Render();
	}
	sprite->Render();
}

void MainGame::CheckWinPlayer()
{
	//���ΰ˻�
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[i + 0][j].state == LOC::BLACK &&
				loc[i + 1][j].state == LOC::BLACK &&
				loc[i + 2][j].state == LOC::BLACK &&
				loc[i + 3][j].state == LOC::BLACK &&
				loc[i + 4][j].state == LOC::BLACK)
			{
				//������ �¸�
				winPlayer = PLAYER::BLACK;
				bGameOver = true;
			}
		}
	}
	//���ΰ˻�
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[j][i + 0].state == LOC::BLACK &&
				loc[j][i + 1].state == LOC::BLACK &&
				loc[j][i + 2].state == LOC::BLACK &&
				loc[j][i + 3].state == LOC::BLACK &&
				loc[j][i + 4].state == LOC::BLACK)
			{
				//������ �¸�
				winPlayer = PLAYER::BLACK;
				bGameOver = true;
			}
		}
	}
	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[j + 0][i + 0].state == LOC::BLACK &&
				loc[j + 1][i + 1].state == LOC::BLACK &&
				loc[j + 2][i + 2].state == LOC::BLACK &&
				loc[j + 3][i + 3].state == LOC::BLACK &&
				loc[j + 4][i + 4].state == LOC::BLACK)
			{
				//������ �¸�
				winPlayer == PLAYER::BLACK;
				bGameOver = true;
			}
		}
	}
	for (int j = 0; j < 16; j++)
	{
		for (int i = 4; i < 20; i++)
		{
			if (loc[i - 0][j - 0].state == LOC::BLACK &&
				loc[i - 1][j - 1].state == LOC::BLACK &&
				loc[i - 2][j - 2].state == LOC::BLACK &&
				loc[i - 3][j - 3].state == LOC::BLACK &&
				loc[i - 4][j - 4].state == LOC::BLACK)
			{
				//������ �¸�
				winPlayer == PLAYER::BLACK;
				bGameOver = true;
			}
		}
	}
	//���ΰ˻�
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[i + 0][j].state == LOC::WHITE &&
				loc[i + 1][j].state == LOC::WHITE &&
				loc[i + 2][j].state == LOC::WHITE &&
				loc[i + 3][j].state == LOC::WHITE &&
				loc[i + 4][j].state == LOC::WHITE)
			{
				//��� �¸�
				winPlayer = PLAYER::WHITE;
				bGameOver = true;
			}
		}
	}
	//���ΰ˻�
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[j][i + 0].state == LOC::WHITE &&
				loc[j][i + 1].state == LOC::WHITE &&
				loc[j][i + 2].state == LOC::WHITE &&
				loc[j][i + 3].state == LOC::WHITE &&
				loc[j][i + 4].state == LOC::WHITE)
			{
				//��� �¸�
				winPlayer = PLAYER::WHITE;
				bGameOver = true;
			}
		}
	}
	for (int j = 0; j < 16; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			if (loc[j + 0][i + 0].state == LOC::WHITE &&
				loc[j + 1][i + 1].state == LOC::WHITE &&
				loc[j + 2][i + 2].state == LOC::WHITE &&
				loc[j + 3][i + 3].state == LOC::WHITE &&
				loc[j + 4][i + 4].state == LOC::WHITE)
			{
				//��� �¸�
				winPlayer == PLAYER::WHITE;
				bGameOver = true;
			}
		}
	}
	for (int j = 0; j < 16; j++)
	{
		for (int i = 4; i < 20; i++)
		{
			if (loc[i - 0][j - 0].state == LOC::WHITE &&
				loc[i - 1][j - 1].state == LOC::WHITE &&
				loc[i - 2][j - 2].state == LOC::WHITE &&
				loc[i - 3][j - 3].state == LOC::WHITE &&
				loc[i - 4][j - 4].state == LOC::WHITE)
			{
				//��� �¸�
				winPlayer == PLAYER::WHITE;
				bGameOver = true;
			}
		}
	}
}
