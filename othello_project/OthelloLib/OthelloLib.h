#pragma once

#include <stdio.h>

/** @def
 * 盤面の横サイズ
 */
#define WIDTH           8

 /** @def
  * 盤面の縦サイズ
  */
#define HEIGHT          8

/** @def
 * 盤面上の未配置の値
 */
#define NONE_PLAY       0

/** @def
 * 盤面上の白石の値
 */
#define WHITE_STONE     1

/** @def
 * 盤面上の黒石の値
 */
#define BLACK_STONE     2

/** @def
 * 白石の表示文字列
 */
#define WHITE_STONE_STR "●"

/** @def
 * 黒石の表示文字列
 */
#define BLACK_STONE_STR "〇"

/** @def
 * 未勝利
 */
#define NONE_FINISH 0

/** @def
 * 白石プレイヤーの勝利
 */
#define WIN_WHITE_STONE 1

/** @def
 * 黒石プレイヤーの勝利
 */
#define WIN_BLACK_STONE 2

/** @def
 * パスしない
 */
#define NOT_PASS 0

/** @def
 * パスする
 */
#define PASS 1

/** @def
 * 盤の初期位置１ x座標
 */
#define INIT_BOARD_FIRST_X 3

/** @def
 * 盤の初期位置１ y座標
 */
#define INIT_BOARD_FIRST_Y 3

/** @def
 * 盤の初期位置１ 石
 */
#define INIT_BOARD_FIRST_STONE WHITE_STONE

/** @def
 * 盤の初期位置２ x座標
 */
#define INIT_BOARD_SECOND_X 3

/** @def
 * 盤の初期位置２ y座標
 */
#define INIT_BOARD_SECOND_Y 4

/** @def
 * 盤の初期位置２ 石
 */
#define INIT_BOARD_SECOND_STONE BLACK_STONE

/** @def
 * 盤の初期位置３ x座標
 */
#define INIT_BOARD_THIRD_X 4

/** @def
 * 盤の初期位置３ y座標
 */
#define INIT_BOARD_THIRD_Y 3

/** @def
 * 盤の初期位置３ 石
 */
#define INIT_BOARD_THIRD_STONE BLACK_STONE

/** @def
 * 盤の初期位置４ x座標
 */
#define INIT_BOARD_FOURTH_X 4

/** @def
 * 盤の初期位置４ y座標
 */
#define INIT_BOARD_FOURTH_Y 4

/** @def
 * 盤の初期位置４ 石
 */
#define INIT_BOARD_FOURTH_STONE WHITE_STONE

/** @def
 * 盤の行・列インデックス１
 */
#define BOARD_LINE_INDEX_1 0

/** @def
 * 盤の行・列インデックス２
 */
#define BOARD_LINE_INDEX_2 1

/** @def
 * 盤の行・列インデックス３
 */
#define BOARD_LINE_INDEX_3 2

/** @def
 * 盤の行・列インデックス４
 */
#define BOARD_LINE_INDEX_4 3

/** @def
 * 盤の行・列インデックス５
 */
#define BOARD_LINE_INDEX_5 4

/** @def
 * 盤の行・列インデックス６
 */
#define BOARD_LINE_INDEX_6 5

/** @def
 * 盤の行・列インデックス７
 */
#define BOARD_LINE_INDEX_7 6

/** @def
 * 盤の行・列インデックス８
 */
#define BOARD_LINE_INDEX_8 7

/** @def
 * 盤の行・列文字列１
 */
#define BOARD_LINE_STR_1 "０"

/** @def
 * 盤の行・列文字列２
 */
#define BOARD_LINE_STR_2 "１"

/** @def
 * 盤の行・列文字列３
 */
#define BOARD_LINE_STR_3 "２"

/** @def
 * 盤の行・列文字列４
 */
#define BOARD_LINE_STR_4 "３"

/** @def
 * 盤の行・列文字列５
 */
#define BOARD_LINE_STR_5 "４"

/** @def
 * 盤の行・列文字列６
 */
#define BOARD_LINE_STR_6 "５"

/** @def
 * 盤の行・列文字列７
 */
#define BOARD_LINE_STR_7 "６"

/** @def
 * 盤の行・列文字列８
 */
#define BOARD_LINE_STR_8 "７"

/** @enum DIRECTION_INDEX
 * 方向配列のインデックスnum定義
 */
enum DIRECTION_INDEX {
	LEFT = 0,
	LEFT_BOTTOM,
	BOTTOM,
	RIGHT_BOTTOM,
	RIGHT,
	RIGHT_TOP,
	TOP,
	LEFT_TOP,

	// インデックス合計
	NUM
};

/** @struct POINT
 * 座標構造体
 */
struct POINT
{
	int x;
	int y;
};

/**
 * @fn printBoard(int*)
 * 盤面をコンソール上に出力する。
 * @param board 盤面の配列ポインタ
 * @param size  配列のサイズ
 */
void printBoard(int* board, size_t size);

/**
 * @fn initializeBoard(int*)
 * 盤面の初期配置を行う。
 * @param board 盤面の配列ポインタ(出力)
 * @param size  配列のサイズ
 */
void initializeBoard(int* board, size_t size);

/**
 * @fn setDirection(POINT*)
 * 方向の重み配列の設定を行う。
 * @param directions 方向の重み配列のポインタ(出力)
 * @param size       配列のサイズ
 */
void setDirection(POINT* direction, size_t size);
