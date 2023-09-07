#include <Novice.h>
#include "Player.h"

const char kWindowTitle[] = "GC2B_07_マ_ドンウク";

enum SCENE {
	TITLE,//タイトル画面
	STAGE1,//ゲーム画面
	STAGE2,
	STAGE3,
	GAMECLEAR,//ゲームクリア
	GAMECLEAR2,//STAGE2
	GAMECLEAR3,//STAGE3
	GAMEOVER,//ゲームオーバー
	GAMEOVER2,//STAGE2
};

int sceneNo = TITLE;


//画像読み込み-----------------------------------------------------------




//ブロックサイズの設定
const int KBlockSize = 32;
int playerPosX = 13 * KBlockSize;
int playerPosY = 576;
int playerR = 32;
int playerSpeed = KBlockSize;

int playerTmpX = 0;
int playerTmpY = 0;
int playerMapX = 0;
int playerMapY = 0;

int caramelMapX = 0;
int caramelMapY = 0;
int caramelTmpX = 0;
int caramelTmpY;

int blockPosX = 32;
int blockPosY = 32;
int blockTmpX = 0;
int blockTmpY = 0;
int blockMapX = 0;
int blockMapY = 0;

//ステージ2
/*int playerPosX = 13 * KBlockSize;
int playerPosY = 320;*/


//タイマー
int goalTimer = 60;//ゴール
int caramelTimer = 200;//カラメル
int deathTimer = 60;//ゲームオーバー
//フラグ-----------
int caramelFlag = 0;

//マップずらすための変数
int mapShift = 200;

int map[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,4,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,5,2,5,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int mapFormat[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,4,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,5,2,5,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int map2[22][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,4,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,1,1,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,5,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,1},
{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapFormat2[22][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,4,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,1,1,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,5,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,0,0,7,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,1},
{1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,5,7,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int map3[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,6,0,0,0,0,0,7,0,5,5,7,0,0,0,0,0,0,6,0,0,0,0,1},
{1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1},
{1,1,1,5,5,1,1,1,1,1,5,1,7,1,5,1,1,1,1,1,1,5,5,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,6,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,7,7,0,7,7,0,0,6,0,0,0,6,0,0,7,7,0,7,7,7,7,7,7,1},
{1,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,1},
{1,6,5,5,7,5,5,5,5,0,0,0,0,0,0,0,5,5,5,5,7,5,5,6,6,6,1},
{1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapFormat3[20][27] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,6,0,0,0,0,0,7,0,5,5,7,0,0,0,0,0,0,6,0,0,0,0,1},
{1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1},
{1,1,1,5,5,1,1,1,1,1,5,1,7,1,5,1,1,1,1,1,1,5,5,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,6,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,7,7,7,0,7,7,0,0,6,0,0,0,6,0,0,7,7,0,7,7,7,7,7,7,1},
{1,0,0,0,0,7,0,0,7,0,0,0,0,0,0,0,7,0,0,7,0,0,0,0,0,0,1},
{1,6,5,5,7,5,5,5,5,0,0,0,0,0,0,0,5,5,5,5,7,5,5,6,6,6,1},
{1,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
int mapCountY = sizeof(map) / sizeof(map[0]);

int mapCountX2 = sizeof(map2[0]) / sizeof(map2[0][0]);
int mapCountY2 = sizeof(map2) / sizeof(map2[0]);

int mapCountX3 = sizeof(map3[0]) / sizeof(map3[0][0]);
int mapCountY3 = sizeof(map3) / sizeof(map3[0]);

enum MapInfo {
	YUKA,//0
	BLOCK,//1
	THORN,//2
	BLOCK2,//3
	GOAL,//4
	SYRUP,//5
	CANDY,//6
	CARAMEL,//7
};

Player playerClass;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int title = Novice::LoadTexture("./images/TITLE.png");
	int player = Novice::LoadTexture("./images/player.png");
	int block = Novice::LoadTexture("./images/block.png");
	int goal = Novice::LoadTexture("./images/GOALS.png");
	int thorn = Novice::LoadTexture("./images/THORN.png");
	int syrup = Novice::LoadTexture("./images/SYRUP.png");
	int candy = Novice::LoadTexture("./images/CANDY.png");
	int caramel = Novice::LoadTexture("./images/CARAMEL.png");


	int gameClear = Novice::LoadTexture("./images/GAMECLEARR.png");
	int gameOver = Novice::LoadTexture("./images/GAMEOVERR.png");

	int MANUAL = Novice::LoadTexture("./images/MANUALS.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			//初期化------------------------------------------------------------
			goalTimer = 60;
			deathTimer = 60;
			playerPosY = 576;
			playerSpeed = KBlockSize;
			for (int y = 0; y < mapCountY; y++)
			{
				for (int x = 0; x < mapCountX; x++)
				{
					map[y][x] = mapFormat[y][x];
				}
			}
			//--------------------------------------------------------------------
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = STAGE1;
			}

			break;

		case STAGE1:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 13 * KBlockSize;//プレイヤーの位置
				playerPosY = 576;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY; y++)
				{
					for (int x = 0; x < mapCountX; x++)
					{
						map[y][x] = mapFormat[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map[playerMapY][playerMapX] == YUKA)
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
						if (map[1][1] == THORN)
						{
							map[playerMapY][playerMapX] = THORN;
							map[1][1] = YUKA;
						}
						playerPosY += playerSpeed;
					}
				}

				/*if (map[playerMapY][playerMapX] == SYRUP)
				{
					if (map[playerMapY + 1][playerMapX] == YUKA && map[1][1] == THORN)
					{
						map[1][1] = YUKA;
						map[playerMapY - 1][playerMapX] = THORN;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SYRUP;
						playerPosY += playerSpeed;
					}
				}*/

				if (map[playerMapY][playerMapX] == SYRUP)
				{
					
					if (map[playerMapY + 1][playerMapX] == THORN)
					{
						map[1][1] = THORN;
						map[playerMapY][playerMapX] = YUKA;
						map[playerMapY + 1][playerMapX] = SYRUP;
						playerPosY += playerSpeed;
					}
				}

			
			}

			//状態変化--------------------------------------------------------------------------------------------------
			if (keys[DIK_1] && preKeys[DIK_1] == 0)
			{
				for (int y = 0; y < mapCountY; y++)
				{
					for (int x = 0; x < mapCountX; x++)
					{
						if (map[y][x] == SYRUP)
						{
							map[y][x] = CANDY;
						}

						else if (map[y][x] == CANDY)
						{
							map[y][x] = CARAMEL;
							caramelFlag = 1;
						}

						//else if (map[y][x] == CARAMEL)
						//{
						//	if (caramelTimer <= 0)
						//	{
						//		map[y][x] = YUKA;
						//		caramelFlag = 0;
						//	}
						//	//if (map[y][x] = YUKA)
						//	//{
						//	//	caramelTimer = 200;
						//	//}

						//	caramelMapX = x;
						//	caramelMapY = y;

						//	if (map[caramelMapY - 1][caramelMapX] == YUKA)//上
						//	{
						//		map[caramelMapY - 1][caramelMapX] = THORN;
						//	}
						//	if (map[caramelMapY + 1][caramelMapX] == YUKA)//下
						//	{
						//		map[caramelMapY + 1][caramelMapX] = THORN;
						//	}

						//	if (map[caramelMapY][caramelMapX - 1] == YUKA)//左
						//	{
						//		map[caramelMapY][caramelMapX - 1] = THORN;
						//	}
						//	if (map[caramelMapY][caramelMapX + 1] == YUKA)//右
						//	{
						//		map[caramelMapY][caramelMapX + 1] = THORN;
						//	}
						//}
					}
				}
			}
			if (caramelFlag == 1)
			{
				caramelTimer--;
			}


			//ゴール条件---------------------------------
			if (map[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR;
				}
			}

			/*if (map[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}*/
			break;

		case STAGE2:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY2; y++)
				{
					for (int x = 0; x < mapCountX2; x++)
					{
						map2[y][x] = mapFormat2[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY - 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY - 1][playerMapX] = SYRUP;
						playerPosY -= playerSpeed;
					}
				}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}
				//if (map2[playerMapY][playerMapX] == SYRUP)
				//{
				//	if (map2[playerMapY][playerMapX - 1] == YUKA)
				//	{
				//		map2[playerMapY][playerMapX] = YUKA;
				//		map2[playerMapY][playerMapX - 1] = SYRUP;
				//		playerPosX -= playerSpeed;
				//	}
				//}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY][playerMapX + 1] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY][playerMapX + 1] = SYRUP;
						playerPosX += playerSpeed;
					}
				}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map2[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}
				if (map2[playerMapY][playerMapX] == THORN)
				{
					playerPosY += playerSpeed;
				}
				//シロップを動かす処理
				if (map2[playerMapY][playerMapX] == SYRUP)
				{
					if (map2[playerMapY + 1][playerMapX] == YUKA)
					{
						map2[playerMapY][playerMapX] = YUKA;
						map2[playerMapY + 1][playerMapX] = SYRUP;
						playerPosY += playerSpeed;
					}
				}
			}

			//状態変化--------------------------------------------------------------------------------------------------
			if (keys[DIK_1] && preKeys[DIK_1] == 0)
			{
				for (int y = 0; y < mapCountY2; y++)
				{
					for (int x = 0; x < mapCountX2; x++)
					{
						if (map2[y][x] == SYRUP)
						{
							map2[y][x] = CANDY;
						}

						else if (map2[y][x] == CANDY)
						{
							map2[y][x] = CARAMEL;
							caramelFlag = 1;
						}

						//else if (map2[y][x] == CARAMEL)
						//{
						//	if (caramelTimer <= 0)
						//	{
						//		map2[y][x] = YUKA;
						//		caramelFlag = 0;
						//	}
						//	if (map2[y][x] = YUKA)
						//	{
						//		caramelTimer = 200;
						//	}

						//	caramelMapX = x;
						//	caramelMapY = y;

						//	if (map2[caramelMapY - 1][caramelMapX] == YUKA)//上
						//	{
						//		map2[caramelMapY - 1][caramelMapX] = THORN;
						//	}
						//	if (map2[caramelMapY + 1][caramelMapX] == YUKA)//下
						//	{
						//		map2[caramelMapY + 1][caramelMapX] = THORN;
						//	}

						//	if (map2[caramelMapY][caramelMapX - 1] == YUKA)//左
						//	{
						//		map2[caramelMapY][caramelMapX - 1] = THORN;
						//	}
						//	if (map2[caramelMapY][caramelMapX + 1] == YUKA)//右
						//	{
						//		map2[caramelMapY][caramelMapX + 1] = THORN;
						//	}
						//}
					}
				}
			}
			if (caramelFlag == 1)
			{
				caramelTimer--;
			}


			//ゴール条件---------------------------------
			if (map2[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR2;
				}
			}

			if (map2[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}

			break;

		case STAGE3:
			//マップ情報-----------------------------------------------------------------------------------
			playerMapX = playerPosX / KBlockSize;//map[x][]
			playerMapY = playerPosY / KBlockSize;//map[][y]

			blockMapX = blockPosX / KBlockSize;
			blockMapY = blockPosY / KBlockSize;

			//リスタート
			if (keys[DIK_R] && preKeys[DIK_R] == 0)
			{
				goalTimer = 60;//初期化
				deathTimer = 60;
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerSpeed = KBlockSize;
				for (int y = 0; y < mapCountY3; y++)
				{
					for (int x = 0; x < mapCountX3; x++)
					{
						map3[y][x] = mapFormat3[y][x];
					}
				}
			}

			//プレイヤー移動-------------------------------------------------------------------------------
			if (keys[DIK_W] && preKeys[DIK_W] == 0 || keys[DIK_UP] && preKeys[DIK_UP] == 0)
			{
				playerTmpY = playerPosY - playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosY -= playerSpeed;
				}
				//if (map3[playerMapY][playerMapX] == SYRUP)
				//{
				//	if (map3[playerMapY - 1][playerMapX] == YUKA)
				//	{
				//		map3[playerMapY][playerMapX] = YUKA;
				//		map3[playerMapY - 1][playerMapX] = SYRUP;
				//		playerPosY -= playerSpeed;
				//	}
				//}
			}

			if (keys[DIK_A] && preKeys[DIK_A] == 0 || keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0)
			{
				playerTmpX = playerPosX - playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX -= playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == SYRUP)
				{
					if (map3[playerMapY][playerMapX - 1] == YUKA)
					{
						map3[playerMapY][playerMapX] = YUKA;
						map3[playerMapY][playerMapX - 1] = SYRUP;
						playerPosX -= playerSpeed;
					}
				}
			}

			if (keys[DIK_D] && preKeys[DIK_D] == 0 || keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0)
			{
				playerTmpX = playerPosX + playerSpeed;
				playerMapX = playerTmpX / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosX += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosX += playerSpeed;
				}
				//if (map3[playerMapY][playerMapX] == SYRUP)
				//{
				//	if (map3[playerMapY][playerMapX + 1] == YUKA)
				//	{
				//		map3[playerMapY][playerMapX] = YUKA;
				//		map3[playerMapY][playerMapX + 1] = SYRUP;
				//		playerPosX += playerSpeed;
				//	}
				//}
			}

			if (keys[DIK_S] && preKeys[DIK_S] == 0 || keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0)
			{
				playerTmpY = playerPosY + playerSpeed;
				playerMapY = playerTmpY / KBlockSize;
				//何もないから実際に進ませる
				if (map3[playerMapY][playerMapX] == YUKA)
				{
					playerPosY += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == GOAL)
				{
					playerPosY += playerSpeed;
				}
				if (map3[playerMapY][playerMapX] == THORN)
				{
					playerPosY += playerSpeed;
				}
				////シロップを動かす処理
				//if (map3[playerMapY][playerMapX] == SYRUP)
				//{
				//	if (map3[playerMapY + 1][playerMapX] == YUKA)
				//	{
				//		map3[playerMapY][playerMapX] = YUKA;
				//		map3[playerMapY + 1][playerMapX] = SYRUP;
				//		playerPosY += playerSpeed;
				//	}
				//}
			}

			//状態変化--------------------------------------------------------------------------------------------------
			if (keys[DIK_1] && preKeys[DIK_1] == 0)
			{
				for (int y = 0; y < mapCountY3; y++)
				{
					for (int x = 0; x < mapCountX3; x++)
					{
						if (map3[y][x] == SYRUP)
						{
							map3[y][x] = CANDY;
						}

						else if (map3[y][x] == CANDY)
						{
							map3[y][x] = CARAMEL;
							caramelFlag = 1;
						}

						//else if (map3[y][x] == CARAMEL)
						//{
						//	if (caramelTimer <= 0)
						//	{
						//		map3[y][x] = YUKA;
						//		caramelFlag = 0;
						//	}
						//	if (map3[y][x] = YUKA)
						//	{
						//		caramelTimer = 200;
						//	}

						//	caramelMapX = x;
						//	caramelMapY = y;

						//	if (map3[caramelMapY - 1][caramelMapX] == YUKA)//上
						//	{
						//		map3[caramelMapY - 1][caramelMapX] = THORN;
						//	}
						//	if (map3[caramelMapY + 1][caramelMapX] == YUKA)//下
						//	{
						//		map3[caramelMapY + 1][caramelMapX] = THORN;
						//	}

						//	if (map3[caramelMapY][caramelMapX - 1] == YUKA)//左
						//	{
						//		map3[caramelMapY][caramelMapX - 1] = THORN;
						//	}
						//	if (map3[caramelMapY][caramelMapX + 1] == YUKA)//右
						//	{
						//		map3[caramelMapY][caramelMapX + 1] = THORN;
						//	}
						//}
					}
				}
			}
			if (caramelFlag == 1)
			{
				caramelTimer--;
			}


			//ゴール条件---------------------------------
			if (map3[playerMapY][playerMapX] == GOAL)
			{
				goalTimer--;
				playerSpeed = 0;
				if (goalTimer == 0)
				{
					sceneNo = GAMECLEAR3;
				}
			}

			if (map3[playerMapY][playerMapX] == THORN)
			{
				deathTimer--;
				playerSpeed = 0;
				if (deathTimer == 0)
				{
					sceneNo = GAMEOVER;
				}
			}

			break;

		case GAMECLEAR:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 1 * KBlockSize;//プレイヤーの位置
				playerPosY = 20 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE2;
			}
			break;

		case GAMECLEAR2:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				playerPosX = 12 * KBlockSize;//プレイヤーの位置
				playerPosY = 18 * KBlockSize;
				playerMapX = playerPosX / KBlockSize;//map[x][]
				playerMapY = playerPosY / KBlockSize;//map[][y]
				playerSpeed = KBlockSize;
				goalTimer = 60;

				sceneNo = STAGE3;
			}
			break;

		case GAMECLEAR3:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;


		case GAMEOVER:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				sceneNo = TITLE;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (sceneNo)
		{
		case TITLE:
			Novice::DrawSprite(0, 0, title, 2, 2, 0, WHITE);
			break;
		case STAGE1:
			//数値見やすく--------------------------------------------------------------
			/*Novice::ScreenPrintf(865, 32, "goalTimer=%d", goalTimer);
			Novice::ScreenPrintf(865, 64, "deathTimer=%d",deathTimer);
			Novice::ScreenPrintf(865, 96, "playerSpeed=%d", playerSpeed);
			Novice::ScreenPrintf(865, 128, "caramelTimer=%d", caramelTimer);*/



			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
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
				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE2:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY2; y++)
			{
				for (int x = 0; x < mapCountX2; x++)
				{
					if (map2[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map2[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == THORN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, thorn, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == BLOCK2)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}
					if (map2[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == SYRUP)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, syrup, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == CANDY)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, candy, 1, 1, 0, WHITE);
					}
					if (map2[y][x] == CARAMEL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, caramel, 1, 1, 0, WHITE);
					}
				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case STAGE3:
			Novice::DrawBox(0, 0, 1280, 720, 0, BLACK, kFillModeSolid);
			for (int y = 0; y < mapCountY3; y++)
			{
				for (int x = 0; x < mapCountX3; x++)
				{
					if (map3[y][x] == YUKA)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, BLUE, kFillModeSolid);
					}
					if (map3[y][x] == BLOCK)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, block, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == THORN)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, thorn, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == BLOCK2)
					{
						Novice::DrawBox(x * KBlockSize, y * KBlockSize, KBlockSize, KBlockSize, 0, RED, kFillModeSolid);
					}
					if (map3[y][x] == GOAL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, goal, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == SYRUP)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, syrup, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == CANDY)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, candy, 1, 1, 0, WHITE);
					}
					if (map3[y][x] == CARAMEL)
					{
						Novice::DrawSprite(x * KBlockSize, y * KBlockSize, caramel, 1, 1, 0, WHITE);
					}
				}
			}
			Novice::DrawSprite(playerPosX, playerPosY, player, 1, 1, 0, WHITE);
			Novice::DrawSprite(864, 0, MANUAL, 1, 1, 0, WHITE);
			break;

		case GAMECLEAR:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR2:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMECLEAR3:
			Novice::DrawSprite(0, 0, gameClear, 2, 2, 0, WHITE);
			break;

		case GAMEOVER2:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		case GAMEOVER:
			Novice::DrawSprite(0, 0, gameOver, 2, 2, 0, WHITE);
			break;

		}

		//debug
	/*	Novice::ScreenPrintf(0, 0, "%d", playerPosX / KBlockSize);
		Novice::ScreenPrintf(0, 20, "%d", playerPosY / KBlockSize);
		Novice::ScreenPrintf(0,40,"%d", goalTimer);*/

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
