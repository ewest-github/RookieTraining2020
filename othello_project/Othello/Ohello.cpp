#include "OthelloLib.h"

int main() {

	//配列の要素数の設定
	int board[WIDTH * HEIGHT];
	int* pboard = &board[0];
	POINT directions[DIRECTION_INDEX::NUM];

	//縦、横の配置指定(構造体)
	struct POINT position;

	//現在のプレイヤー(1 = ●、2 = ◯)
	int player = 1; 

	//パス入力用
	int pass = 1;

	// 挟める石の数(0 = 挟む石が無い 0以上 = 挟む石がある)
	int rbCount;

	//石の初期配置
	initializeBoard(board, WIDTH * HEIGHT);

	//盤面の表示
	printBoard(board, WIDTH * HEIGHT);

	printf("ゲームを開始します。\n");
	printf("先行プレイヤー●、後攻プレイヤーが◯です。\n");

	int playStone;
	POINT playPoint;

	while (true)
	{
		rbCount = 0;

		if (player == 1) {
			if (pass == 0) {
				pass = 1;
			}
			else if (pass == 1)
			{
				printf("現在のプレイヤー:%s\n", BLACK_STONE_STR);
				player = 2;
				playStone = BLACK_STONE;
			}
		}
		else if (player == 2)
		{
			if (pass == 0) {
				pass = 1;
			}
			else if (pass == 1)
			{
				printf("現在のプレイヤー:%s\n", WHITE_STONE_STR);
				player = 1;
				playStone = WHITE_STONE;
			}
		}

		while (true) {
			//配置場所の指定
			printf("石の位置を指定してください。\n");
			printf("横:"); scanf_s("%d", &position.x);
			printf("縦:"); scanf_s("%d", &position.y);

			if ((position.x > 7 || position.y > 7) || (position.x < 0 || position.y < 0)) { //盤面の範囲外の場合
				printf("盤面の範囲外です、違う場所を指定してください。");
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
		int reverseBoardCount = 0;

		//探索用(挟む石がない = false、ある = true)
		bool isFound = false;

		for (int y = initY, x = initX;
			(y >= 0 && y < HEIGHT) && (x >= 0 && x < WIDTH);
			y += Direction.y, x += Direction.x) {

			if (pboard[(x * 8) + y] == NONE_PLAY) {
				// 未プレイ
				break;
			}
			if (pboard[(x * 8) + y] == playStone) {
				// プレイヤー自身の石を発見
				isFound = true;

				//隣にプレイヤー自身の石があった場合
			    /*if (pboard[((x - Direction.x) * 8) + (y - Direction.y)] == playStone) {
					rbCount++;
				}*/

				break;
			}

			reverseBoardCount++;
			rbCount++;
		}

		if (isFound == true) {
			int ix = initX;
			int iy = initY;
			for (int i = 0; i < reverseBoardCount; i++) {
				if (player == BLACK_STONE) {
					board[(ix * 8) + iy] = BLACK_STONE;
				}
				else if (player == WHITE_STONE) {
					board[(ix * 8) + iy] = WHITE_STONE;
				}

				ix += Direction.x;
				iy += Direction.y;
			}
		}

	  }
 
	  if(rbCount == 0)  //挟む石が無い
	  {
		  while (true) {
			  printf("挟む石がありません。パス(0:しない、1:する)しますか?\n");
			  scanf_s("%d", &pass);

			  if (pass > 1 || pass < 0) {
				  printf("0か1を入力してください。\n");
			  }
			  else {
				  break;
			  }
		  }
	  }
	  else if (rbCount > 0) { //挟む石がある

		  //石を盤面に配置
		  if (playStone == BLACK_STONE) {
			  board[(position.x * 8) + position.y] = BLACK_STONE;
		  }
		  else if (playStone == WHITE_STONE)
		  {
			  board[(position.x * 8) + position.y] = WHITE_STONE;
		  }

		  //反転後の盤面表示
		  printBoard(board, WIDTH * HEIGHT);
	  }
	}

	return 0;
}