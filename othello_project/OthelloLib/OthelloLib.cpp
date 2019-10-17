#include "OthelloLib.h"

#define TEMP_AREA_SIZE 10

void convertFull(int value, size_t valueSize, char* full);

void initializeBoard(int* board, size_t size)
{
	// check param
	if (board == NULL) {
		printf("ERROR!! board == NULL");
		return;
	}
	if (size != (WIDTH * HEIGHT)) {
		printf("ERROR!! size != %d", size);
		return;
	}

	for (unsigned int i = 0; i < size; i++) {
		board[i] = NONE_PLAY;
	}

	board[(INIT_BOARD_FIRST_X  * WIDTH) + INIT_BOARD_FIRST_Y]  = INIT_BOARD_FIRST_STONE;
	board[(INIT_BOARD_SECOND_X * WIDTH) + INIT_BOARD_SECOND_Y] = INIT_BOARD_SECOND_STONE;
	board[(INIT_BOARD_THIRD_X  * WIDTH) + INIT_BOARD_THIRD_Y]  = INIT_BOARD_THIRD_STONE;
	board[(INIT_BOARD_FOURTH_X * WIDTH) + INIT_BOARD_FOURTH_Y] = INIT_BOARD_FOURTH_STONE;
}

void setDirection(POINT* direction, size_t size)
{
	// check param
	if (direction == NULL) {
		printf("ERROR!! direction = NULL");
		return;
	}
	if (size != DIRECTION_INDEX::NUM) {
		printf("ERROR!! size = %d", DIRECTION_INDEX::NUM);
		return;
	}

	direction[DIRECTION_INDEX::LEFT]         = { -1,  0 };
	direction[DIRECTION_INDEX::LEFT_BOTTOM]  = { -1,  1 };
	direction[DIRECTION_INDEX::BOTTOM]       = {  0,  1 };
	direction[DIRECTION_INDEX::RIGHT_BOTTOM] = {  1,  1 };
	direction[DIRECTION_INDEX::RIGHT]        = {  1,  0 };
	direction[DIRECTION_INDEX::RIGHT_TOP]    = {  1, -1 };
	direction[DIRECTION_INDEX::TOP]          = {  0, -1 };
	direction[DIRECTION_INDEX::LEFT_TOP]     = { -1, -1 };
}

void printBoard(int* board, size_t size)
{
	// check param
	if (board == NULL) {
		printf("ERROR!! board == NULL");
		return;
	}
	if (size != (WIDTH * HEIGHT)) {
		printf("ERROR!! size != %d", size);
		return;
	}

	for (int y = 0; y < HEIGHT; y++) {
		if (y == 0) {
			for (int x = 0; x < WIDTH; x++) {
				printf(" ");
			}
			printf("\n\r     ");

			for (int x = 0; x < WIDTH; x++) {
				char numStr[TEMP_AREA_SIZE] = { '\0' };
				convertFull(x, sizeof(numStr), numStr);
				printf("| %s ", numStr);
			}
			printf("|\n\r");
			for (int x = 0; x < WIDTH; x++) {
				if (x == 0) {
					printf(" ――");
				}
				printf("|――");
			}
			printf("|\n\r");
		}

		for (int x = 0; x < WIDTH; x++) {
			if (x == 0) {
				char numStr[TEMP_AREA_SIZE] = { '\0' };
				convertFull(y, sizeof(numStr), numStr);
				printf("  %s ", numStr);
			}
			printf("| ");
			int p = (y * WIDTH) + x;
			if (board[p] == NONE_PLAY) printf("　");
			if (board[p] == WHITE_STONE) printf(WHITE_STONE_STR);
			if (board[p] == BLACK_STONE) printf(BLACK_STONE_STR);
			printf(" ");
		}
		printf("|\n\r");
		for (int x = 0; x < WIDTH; x++) {
			if (x == 0) {
				printf(" ――");
			}
			printf("|――");
		}
		printf("|\n\r");
	}
}

// private method
void convertFull(int value, size_t valueSize, char* full) {
	switch (value) {
	case BOARD_LINE_INDEX_1: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_1); break;
	case BOARD_LINE_INDEX_2: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_2); break;
	case BOARD_LINE_INDEX_3: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_3); break;
	case BOARD_LINE_INDEX_4: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_4); break;
	case BOARD_LINE_INDEX_5: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_5); break;
	case BOARD_LINE_INDEX_6: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_6); break;
	case BOARD_LINE_INDEX_7: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_7); break;
	case BOARD_LINE_INDEX_8: sprintf_s(full, valueSize, "%s", BOARD_LINE_STR_8); break;
	default:
		printf("ERROR!! value = %d", value);
		break;
	}
}
