#include "OthelloLib.h"

int main() {

	//配列の要素数の設定
	int board[WIDTH * HEIGHT];
	int* pboard = &board[0];
	POINT directions[DIRECTION_INDEX::NUM];

	//縦、横の配置指定(構造体)
	struct POINT position;

	//現在のプレイヤー(BLACK_STONE = ●、WHITE_STONE = ◯)
	int player = BLACK_STONE; 

	//石の数(●)
	int Bp = 2;

	//石の数(◯)
	int Wp = 2;

	//パス入力用
	int pass = PASS;

	//挟める石の数(8 = 挟む石が無い 8以外 = 挟む石がある)
	int rbCount;

	//隣にあるプレイヤー自身の石の数
	int PCount = 0;

	//未配置の場所(NONE_PLAYの数)
	int NCount = 0;

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
		if (player == BLACK_STONE) {
			if (pass == NOT_PASS) {
				pass = PASS;
			}
			else if (pass == PASS)
			{
				printf("現在のプレイヤー:%s\n", BLACK_STONE_STR);
				player = WHITE_STONE;
				playStone = BLACK_STONE;
			}
		}
		else if (player == WHITE_STONE)
		{
			if (pass == NOT_PASS) {
				pass = PASS;
			}
			else if (pass == PASS)
			{
				printf("現在のプレイヤー:%s\n", WHITE_STONE_STR);
				player = BLACK_STONE;
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
			else if (pboard[(position.x * WIDTH) + position.y] != NONE_PLAY)
			{
				printf("既に石を配置済みなので、違う場所を指定ください。");
			}
			else {
				break;
			}
		}

		rbCount = 0;

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
					//未プレイ
					PCount++;
					break;
				}

				//隣にプレイヤー自身の石があった場合
				if (pboard[((x - Direction.x) * WIDTH) + (y - Direction.y)] == playStone) {
					PCount++;
					break;
				}

				if (pboard[(x * 8) + y] == playStone) {
					// プレイヤー自身の石を発見
					isFound = true;
					break;
				}
				reverseBoardCount++;
			}

			if (isFound == true) {
				int ix = initX;
				int iy = initY;
				for (int i = 0; i < reverseBoardCount; i++) {
					if (player == BLACK_STONE) {
						board[(ix * 8) + iy] = BLACK_STONE;
						Bp++;
						Wp--;
					}
					else if (player == WHITE_STONE) {
						board[(ix * 8) + iy] = WHITE_STONE;
						Wp++;
						Bp--;
					}

					ix += Direction.x;
					iy += Direction.y;
				}
			}

			//反転対象の石を追加
			rbCount += reverseBoardCount;
			PCount += reverseBoardCount;
	  }
 
	  if(rbCount == 0 || PCount == 8)  //挟む石が無い
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
	  else if(rbCount > 0){ //挟む石がある

		  //石を盤面に配置
		  if (playStone == BLACK_STONE) 
		  {
			  board[(position.x * 8) + position.y] = BLACK_STONE;
			  Bp++;
		  }
		  else if (playStone == WHITE_STONE)
		  {
			  board[(position.x * 8) + position.y] = WHITE_STONE;
			  Wp++;
		  }

		  //反転後の盤面表示
		  printBoard(board, WIDTH * HEIGHT);
	  }

	  NCount = 0;

	  //未配置の探索
	  for (int nx = 0; nx < 8 ; nx++) {
		  for (int ny = 0; ny < 8; ny++) {
			  if (pboard[(nx * 8) + ny] == NONE_PLAY) {
				  NCount++;
			  }
		  }
	  }

	  //勝利メッセージ(どちらかの石が無くなったら)
	  if (Bp == 0) //●が無くなったら
	  {
		  printf("WINNER!!!%s", WHITE_STONE_STR);
		  break;
	  } 
	  else if (Wp == 0) //◯が無くなったら
	  {
		  printf("WINNER!!!%s", BLACK_STONE_STR);
		  break;
	  }

	  //勝利メッセージ(置く場所がない場合)
	  if (NCount == 0)
	  {
		  if (Wp > Bp) //◯が●より多かったら
		  {
			  printf("WINNER!!!%s", WHITE_STONE_STR);
			  break;
		  }
		  else if (Bp > Wp) //●が◯より多かったら 
		  {
			  printf("WINNER!!!%s", BLACK_STONE_STR);
			  break;
		  }
		  else if (Wp == Bp) //数が同じだったら
		  {
			  printf("DRAW");
			  break;
		  }
	  }
	}

	return 0;
}