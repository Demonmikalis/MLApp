#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* logical typedef */
#define true 1
#define false 0
typedef short bool;
/* chessboard structures */
typedef struct player
{
	char mark;
	int score;
}player;

const int ChessBoard_Row = 13;
const int ChessBoard_Col = 26;
const int GridNuber = 9;
const char Comp_Char = 'X';
const char Human_Char = 'O';
const char Blank_Char = ' ';

typedef struct chessboard
{
	char boardInOneDimens[9];
	char *board[13];
}chessboard;

/*---------------------- chess board function ---------------------- */
void initChessBoard(chessboard *cb)
{
	int i;
	char *chessStr[13] = {"- - - - - - - - - - - - -",
				   "|       |       |       |",
				   "|       |       |       |",
		           "|       |       |       |",
		           "- - - - - - - - - - - - -",
			       "|       |       |       |",
			       "|       |       |       |",
				   "|       |       |       |",
				   "- - - - - - - - - - - - -",
				   "|       |       |       |",
				   "|       |       |       |",
				   "|       |       |       |",
				   "- - - - - - - - - - - - -"};
	for(i=0;i<13;++i)
	{
		cb->board[i]=chessStr[i];
	}
}

void test(chessboard *cb,int sz)
{
	int i;
	for(i=0;i<sz;i++)
	{
		printf("%s\n",cb->board[i]);
	}
}
bool ChessBoardisEmpty(chessboard *cb, int pos) {
	return cb->boardInOneDimens[pos] == ' ';
}

bool ChessBoardisFull(chessboard *cb) {
	int i;
	for (i = 0; i < GridNuber; i++) {
		if (cb->boardInOneDimens[i] == ' ')
			return false;
	}
	return true;
}

bool canWin(chessboard *cb, char c) {
	//check every row
	for (int i = 0; i <= 6; i+=3) {
		if (cb->boardInOneDimens[i] == c&&cb->boardInOneDimens[i] == cb->boardInOneDimens[i + 1] &&
			cb->boardInOneDimens[i] == cb->boardInOneDimens[i + 2])
			return true;
	}
	//check every col
	for (int i = 0; i < 3; i++) {
		if (cb->boardInOneDimens[i] == c&&cb->boardInOneDimens[i] == cb->boardInOneDimens[i + 3] &&
			cb->boardInOneDimens[i] == cb->boardInOneDimens[i + 6])
			return true;
	}
	//check every diagonals
	if (cb->boardInOneDimens[0] == c&&cb->boardInOneDimens[4] == c&&cb->boardInOneDimens[8] == c)
		return true;
	if (cb->boardInOneDimens[2] == c&&cb->boardInOneDimens[4] == c&&cb->boardInOneDimens[6] == c)
		return true;
	return false;
}


bool immediateComWin(chessboard *cb, int *bestMove) {
	int i;
	for (i = 0; i < GridNuber; i++) {
		if (ChessBoardisEmpty(cb,i)) {
			cb->boardInOneDimens[i] =Comp_Char;
			bool Win = canWin(cb,Comp_Char); 
			cb->boardInOneDimens[i] = Blank_Char;   //backtraceing
			if (Win) {
				*bestMove = i;
				return true;
			}
		}
	}
	return false;
}

bool immediateHumanWin(chessboard *cb, int *bestMove) {
	for (int i = 0; i < GridNuber; i++) {
		if (ChessBoardisEmpty(cb,i)) {
			cb->boardInOneDimens[i] = Human_Char;
			bool Win = canWin(cb,Human_Char);
			cb->boardInOneDimens[i] = Blank_Char;   //backtraceing
			if (Win) {
				*bestMove = i;
				return true;
			}
		}
	}
	return false;
}

//
void placeComp(chessboard *cb, int pos) {
	cb->boardInOneDimens[pos] = 'X';
}
//
void placeHuman(chessboard *cb, int pos) {
	cb->boardInOneDimens[pos] = 'O';
}
//
void unPlace(chessboard *cb, int pos) {
	cb->boardInOneDimens[pos] = ' ';
}
//
void chessboardPrint(chessboard *cb) {
	int cnt = 0; int i,j;
	for (i = 2; i <= 10; i += 4) {
		for (j= 4; j <= 20; j += 8) {
			cb->board[i][j] = cb->boardInOneDimens[cnt++];
		}
	}
	for (i = 0; i < ChessBoard_Row; ++i) {
		printf("%s\n",cb->board[i]);
	}
}

/*---------------------- alphabeta or minmax function ---------------------- */


int main(int argc, char *argv[])
{
	chessboard cb; 
	initChessBoard(&cb);
	//printf("%s\n",b.fe[0]);
	//printf("%d\n",(int)sizeof(cc));
	return 0;
}
