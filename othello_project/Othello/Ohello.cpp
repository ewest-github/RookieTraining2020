#include "OthelloLib.h"

int main() {

	//配列の要素数の設定
	int board[WIDTH * HEIGHT];

	//縦、横の配置指定用変数
	struct POINT position;

	//現在のプレイヤー(1 = ●、2 = ◯)
	int player = 1;

	//石の初期配置
	initializeBoard(board, WIDTH * HEIGHT);

	//盤面の表示
	printBoard(board, WIDTH * HEIGHT);

	printf("ゲームを開始します。\n");
	printf("先行プレイヤー●、後攻プレイヤーが◯です。\n");

	while (true)
	{
		if (player == 1) {
			printf("現在のプレイヤー:%s\n", BLACK_STONE_STR);
			player = 2;
		}
		else if (player == 2)
		{
			printf("現在のプレイヤー:%s\n", WHITE_STONE_STR);
			player = 1;
		}

		while (true) {
			//配置場所の指定
			printf("石の位置を指定してください。\n");
			printf("横:"); scanf_s("%d", &position.x);
			printf("縦:"); scanf_s("%d", &position.y);

			if ((position.x > 7 || position.y > 7) || (position.y < 0 || position.y < 0)) {
				printf("盤面の範囲外です、違う場所を指定ください。");
			}
			//else if () {
			//	printf("");
			//}
			else {
				break;
			}
		}

	}

	return 0;
}
