#pragma once
#include <bitset>
#include <cassert>
#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "types.hpp"

int main() {
	Board my_board;
	for (int i = 0; i < 64; i++) {
		my_board.ShowBoard(my_board.GetPiece(i));
	};
	my_board.ShowBoard(my_board.KingMoves(my_board.GetWhiteKing(), my_board.GetMaskRank(7)));
	my_board.ShowBoard(my_board.KnightMoves(my_board.GetWhiteKnights(), my_board.GetMaskRank(7)));
	my_board.ShowBoard(my_board.WhitePawnMoves(my_board.GetWhitePawns(), my_board.GetBlackPieces(), my_board.GetAllPieces()));
	my_board.ShowBoard(my_board.BlackPawnMoves(my_board.GetBlackPawns(), my_board.GetWhitePieces(), my_board.GetAllPieces()));
	my_board.ParseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	my_board.ShowBoard(my_board.GetClearFile(FILE_A));
	my_board.ShowBoard(my_board.GetWhiteKnights());
	std::cout << "Count: " << my_board.CountBits(my_board.GetWhiteKnights()) << "\n";
	U64 temp = my_board.GetWhiteKnights();
	std::cout << "Index: " << my_board.PopBit(&temp) << "\n";
	my_board.SetBit(temp, G5);
	my_board.ShowBoard(temp);
	my_board.ClearBit(temp, G1);
	my_board.ShowBoard(temp);
	return 0;
};
