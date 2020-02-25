#pragma once
#include <bitset>
#include <cassert>
#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "types.hpp"
#include "hash.hpp"
#include <time.h>

int main() {
	Board my_board;
	HashKey h_key;
	/*
	for (int i = 0; i < 64; i++) {
		my_board.ShowBoard(my_board.GetPiece(i));
	};*/
	std::cout << "White King's moves:\n";
	my_board.ShowBoard(my_board.KingMoves(my_board.GetWhiteKing(), my_board.GetMaskRank(7)));
	std::cout << "White knight's moves:\n";
	my_board.ShowBoard(my_board.KnightMoves(my_board.GetWhiteKnights(), my_board.GetMaskRank(7)));
	std::cout << "White Pawns' moves:\n";
	my_board.ShowBoard(my_board.WhitePawnMoves(my_board.GetWhitePawns(), my_board.GetBlackPawns(), my_board.GetAllPieces()));
	std::cout << "Black Pawns' moves:\n";
	my_board.ShowBoard(my_board.BlackPawnMoves(my_board.GetBlackPawns(), my_board.GetWhitePawns(), my_board.GetAllPieces()));
	std::cout << "Clear file A:\n";
	my_board.ShowBoard(my_board.GetClearFile(FILE_A));
	std::cout << "White knight positions:\n";
	my_board.ShowBoard(my_board.GetWhiteKnights());
	std::cout << "Count: " << my_board.CountBits(my_board.GetWhiteKnights()) << "\n";
	U64 temp = my_board.GetWhiteKnights();
	std::cout << "Index: " << my_board.PopBit(&temp) << "\n";
	std::cout << "Set bit at G5:\n";
	my_board.SetBit(temp, G5);
	my_board.ShowBoard(temp);
	std::cout << "Clear Knight at G1:\n";
	my_board.ClearBit(temp, G1);
	my_board.ShowBoard(temp);
	srand(time(NULL));
	std::cout << h_key.Rand64();
	return 0;
};
