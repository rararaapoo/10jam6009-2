#include "Player.h"
#include <Novice.h>
void Player::Initialize()
{
	playerPosX = 13 * KBlockSize;
	playerPosY = 576;
	playerR = 32;
	playerSpeed = KBlockSize;

	playerTmpX;
	playerTmpY;
	playerMapX;
	playerMapY;

	//タイマー
	goalTimer = 60;//ゴール
	caramelTimer = 200;//カラメル
	deathTimer = 60;//ゲームオーバー


	playerDraw = Novice::LoadTexture("./images/player.png");
}

void Player::Update()
{
	playerMapX = playerPosX / KBlockSize;
	playerMapY = playerPosY / KBlockSize;
}

void Player::Draw()
{
	Novice::DrawSprite(playerPosX, playerPosY, playerDraw, 1, 1, 0, WHITE);
}

void Player::Move(char* keys, char* preKeys, int map[])
{
	if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
	{
		playerTmpY = playerPosY - playerSpeed;
		playerMapY = playerTmpY / KBlockSize;
		//何もないから実際に進ませる
		if (map[playerMapY][playerMapX] == YUKA                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        KA)
		{
			playerPosY -= playerSpeed;
		}

		if (map[playerMapY][playerMapX] == GOAL)
		{
			playerPosY -= playerSpeed;
		}
		if (map[playerMapY][playerMapX] == THORN)
		{
			playerPosY -= playerSpeed;
		}
		//シロップを動かす処理
		if (map[playerMapY][playerMapX] == SYRUP)
		{
			if (map[playerMapY - 1][playerMapX] == YUKA)
			{
				map[playerMapY][playerMapX] = YUKA;
				map[playerMapY - 1][playerMapX] = SYRUP;
				playerPosY -= playerSpeed;
			}
		}
	}

	if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
	{
		playerTmpX = playerPosX - playerSpeed;
		playerMapX = playerTmpX / KBlockSize;
		//何もないから実際に進ませる
		if (map[playerMapY][playerMapX] == YUKA)
		{
			playerPosX -= playerSpeed;
		}
		if (map[playerMapY][playerMapX] == GOAL)
		{
			playerPosX -= playerSpeed;
		}
		if (map[playerMapY][playerMapX] == THORN)
		{
			playerPosX -= playerSpeed;
		}
		//シロップを動かす処理
		if (map[playerMapY][playerMapX] == SYRUP)
		{
			if (map[playerMapY][playerMapX - 1] == YUKA)
			{
				map[playerMapY][playerMapX] = YUKA;
				map[playerMapY][playerMapX - 1] = SYRUP;
				playerPosX -= playerSpeed;
			}
		}
	}

	if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
	{
		playerTmpX = playerPosX + playerSpeed;
		playerMapX = playerTmpX / KBlockSize;
		//何もないから実際に進ませる
		if (map[playerMapY][playerMapX] == YUKA)
		{
			playerPosX += playerSpeed;
		}
		if (map[playerMapY][playerMapX] == GOAL)
		{
			playerPosX += playerSpeed;
		}
		if (map[playerMapY][playerMapX] == THORN)
		{
			playerPosX += playerSpeed;
		}
		//シロップを動かす処理
		if (map[playerMapY][playerMapX] == SYRUP)
		{
			if (map[playerMapY][playerMapX + 1] == YUKA)
			{
				map[playerMapY][playerMapX] = YUKA;
				map[playerMapY][playerMapX + 1] = SYRUP;
				playerPosX += playerSpeed;
			}
		}
	}

	if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
	{
		playerTmpY = playerPosY + playerSpeed;
		playerMapY = playerTmpY / KBlockSize;
		//何もないから実際に進ませる
		if (map[playerMapY][playerMapX] == YUKA)
		{
			playerPosY += playerSpeed;
		}
		if (map[playerMapY][playerMapX] == GOAL)
		{
			playerPosY += playerSpeed;
		}
		if (map[playerMapY][playerMapX] == THORN)
		{
			playerPosY += playerSpeed;
		}
		//シロップを動かす処理
		if (map[playerMapY][playerMapX] == SYRUP)
		{
			if (map[playerMapY + 1][playerMapX] == YUKA)
			{
				map[playerMapY][playerMapX] = YUKA;
				map[playerMapY + 1][playerMapX] = SYRUP;
				playerPosY += playerSpeed;
			}
		}
	}
}
