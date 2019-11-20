#include "OthelloLib.h"

void printBoardInfo(int* pBoard);
void printSearchResult(int** pBoard, size_t size);
void getStoneStr(char* pStr, size_t size, int stone);

int main() {

	//配列の要素数の設定
	int board[WIDTH * HEIGHT];
	int* pboard = &board[0];
	POINT directions[DIRECTION_INDEX::NUM];

	//縦、横の配置指定(構造体)
	struct POINT position;
	//struct POINT* directions[HEIGHT][WIDTH] = {0};

	//現在のプレイヤー(1 = ●、2 = ◯)
	int player = 1;

	//石の初期配置
	initializeBoard(board, WIDTH * HEIGHT);

	//setDirection(directions[position.x][position.y], 8);

	//盤面の表示
	printBoard(board, WIDTH * HEIGHT);

	printf("ゲームを開始します。\n");
	printf("先行プレイヤー●、後攻プレイヤーが◯です。\n");

	int playStone;
	POINT playPoint;

	while (true)
	{
		if (player == 1) {
			printf("現在のプレイヤー:%s\n", BLACK_STONE_STR);
			player = 2;
			playStone = BLACK_STONE;
		}
		else if (player == 2)
		{
			printf("現在のプレイヤー:%s\n", WHITE_STONE_STR);
			player = 1;
			playStone = WHITE_STONE;
		}

		while (true) {
			//配置場所の指定
			printf("石の位置を指定してください。\n");
			printf("横:"); scanf_s("%d", &position.y);
			printf("縦:"); scanf_s("%d", &position.x);

			if ((position.x > 7 || position.y > 7) || (position.x < 0 || position.y < 0)) { //盤面の範囲外の場合
				printf("盤面の範囲外です、違う場所を指定ください。");
			}
			else {
				break;
			}
		}

		playPoint.y = position.y;
		playPoint.x = position.x;

		setDirection(directions, sizeof(directions) / sizeof(POINT));

		//8方向探索 左,左下,下,右下,右,右上,上,左上の順で探索;
		for (int i = 0; i < 8; i++) {
		// 探索の方向
		POINT Direction = directions[i];
		// 探索初期位置
		int initY = playPoint.y + Direction.y;
		int initX = playPoint.x + Direction.x;

		// 探索
		bool isFound = false;
		int reverseBoardCount = 0;
		int* pReverseBoard[WIDTH * HEIGHT] = { NULL }; // 余裕を持った領域にしておく
		for (int y = initY, x = initX;
			(y >= 0 && y < HEIGHT) && (x >= 0 && x < WIDTH);
			y += Direction.y, x += Direction.x) {

			if (pboard[(x * 8) + y] == NONE_PLAY) {
				// 未プレイ
				continue;
			}
			if (pboard[(x * 8) + y] == playStone) {
				// プレイヤー自身の石を発見
				isFound = true;
				break;
			}
			// 対戦相手の石で、反転対象となる
			pReverseBoard[reverseBoardCount] = &pboard[(x * 8) + y];
			// 盤面上の石反転
			if (player == BLACK_STONE) {
				board[(x * 8) + y] = BLACK_STONE;
			}
			else if (player == WHITE_STONE){
				board[(x * 8) + y] = WHITE_STONE;
			}
			reverseBoardCount++;
		}

		if (isFound) {
			// 探索結果の出力(テスト用)
			printSearchResult(pReverseBoard, reverseBoardCount);
		}
		else {
			printf("\n【探索結果なし】\n");
		}
	  }
		printBoard(board, WIDTH * HEIGHT);
	}

	return 0;
}

// テスト用
void printSearchResult(int** pBoard, size_t size) {
	printf("\n【探索した盤面情報】\n");
	printf("===================\n");
	printf("       石  アドレス\n");
	printf("===================\n");
	for (unsigned int i = 0; i < size; i++) {
		char stoneStr[10] = { '\0' };
		getStoneStr(stoneStr, sizeof(stoneStr) / sizeof(char), (*pBoard[i]));
		printf("       %s  %p\n", stoneStr, pBoard[i]);
	}
	printf("===================\n");
}

void getStoneStr(char* pStr, size_t size, int stone) {
	if (stone == BLACK_STONE) {
		sprintf_s(pStr, size, "%s", BLACK_STONE_STR);
	}
	else{
		sprintf_s(pStr, size, "%s", WHITE_STONE_STR);
	}
}