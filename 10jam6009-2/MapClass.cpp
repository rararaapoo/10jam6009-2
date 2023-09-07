#include "MapClass.h"

void MapClass::Initialize()
{
	mapCountX;
	mapCountY;

	blockPosX = 32;
	blockPosY = 32;
	blockTmpX = 0;
	blockTmpY = 0;
	blockMapX = 0;
	blockMapY = 0;


	//for (int y = 0; y < mapCountY; y++)
	//{
	//	for (int x = 0; x < mapCountX; x++)
	//	{
	//		map[y][x] = mapFormat[y][x];
	//	}
	//}

	block = Novice::LoadTexture("./images/block.png");
	goal = Novice::LoadTexture("./images/GOALS.png");
	thorn = Novice::LoadTexture("./images/THORN.png");
	syrup = Novice::LoadTexture("./images/SYRUP.png");
	candy = Novice::LoadTexture("./images/CANDY.png");
	caramel = Novice::LoadTexture("./images/CARAMEL.png");
	MANUAL = Novice::LoadTexture("./images/MANUALS.png");

	title = Novice::LoadTexture("./images/TITLE.png");
	gameClear = Novice::LoadTexture("./images/GAMECLEARR.png");
	gameOver = Novice::LoadTexture("./images/GAMEOVERR.png");
}

void MapClass::Update()
{
	blockMapX = blockPosX / KBlockSize;
	blockMapY = blockPosY / KBlockSize;

	mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
	mapCountY = sizeof(map) / sizeof(map[0]);
}

void MapClass::stage1()
{
	for (int y = 0; y < mapCountY; y++)
	{
		for (int x = 0; x < mapCountX; x++)
		{
			map[y][x] = mapFormat[y][x];
		}
	}
}

void MapClass::DrawStage1()
{
	for (int y = 0; y < mapCountY; y++)
	{
		for (int x = 0; x < mapCountX; x++)
		{
			if (map[y][x] == YUKA)
			{
				Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
			}
			if (map[y][x] == BLOCK)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
			}
			if (map[y][x] == THORN)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, thorn, 1, 1, 0, WHITE);
			}
			if (map[y][x] == BLOCK2)
			{
				Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
			}
			if (map[y][x] == GOAL)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
			}
			if (map[y][x] == SYRUP)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, syrup, 1, 1, 0, WHITE);
			}
			if (map[y][x] == CANDY)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, candy, 1, 1, 0, WHITE);
			}
			if (map[y][x] == CARAMEL)
			{
				Novice::DrawSprite(x * KBlockSize, y * KBlockSize, caramel, 1, 1, 0, WHITE);
			}

			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
		}
	}
	
}

void MapClass::DrawTitle()
{
	Novice::DrawSprite(0, 0, title, 2, 2, 0, WHITE);
}

void MapClass::DrawGameClear()
{
	Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
}

void MapClass::DrawGameOver()
{
	Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
}
