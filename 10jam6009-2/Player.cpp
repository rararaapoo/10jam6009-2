#include "Player.h"
#include <Novice.h>
void Player::Initialize()
{
	playerPosX = 13 * KBlockSize;
	playerPosY = 576;
	playerR = 32;
	playerSpeed = KBlockSize;

	playerTmpX = 0;
	playerTmpY = 0;
	playerMapX = 0;
	playerMapY = 0;

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

void Player::Move()
{

}
