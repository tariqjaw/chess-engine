#pragma once
#include <stdio.h>
#include <iostream>
#include "board.hpp"

Board::Board() {
  clear_rank_[0] = 0xFFFFFFFFFFFFFF00;
  clear_rank_[1] = 0xFFFFFFFFFFFF00FF;
  clear_rank_[2] = 0xFFFFFFFFFF00FFFF;
  clear_rank_[3] = 0xFFFFFFFF00FFFFFF;
  clear_rank_[4] = 0xFFFFFF00FFFFFFFF;
  clear_rank_[5] = 0xFFFF00FFFFFFFFFF;
  clear_rank_[6] = 0xFF00FFFFFFFFFFFF;
  clear_rank_[7] = 0x00FFFFFFFFFFFFFF;

  mask_rank_[0] = 0x00000000000000FF;
  mask_rank_[1] = 0x000000000000FF00;
  mask_rank_[2] = 0x0000000000FF0000;
  mask_rank_[3] = 0x00000000FF000000;
  mask_rank_[4] = 0x000000FF00000000;
  mask_rank_[5] = 0x0000FF0000000000;
  mask_rank_[6] = 0x00FF000000000000;
  mask_rank_[7] = 0xFF00000000000000;

	clear_file_[0] = 0xFEFEFEFEFEFEFEFE;
	clear_file_[1] = 0xFDFDFDFDFDFDFDFD;
	clear_file_[2] = 0xFBFBFBFBFBFBFBFB;
	clear_file_[3] = 0xF7F7F7F7F7F7F7F7;
	clear_file_[4] = 0xEFEFEFEFEFEFEFEF;
	clear_file_[5] = 0xDFDFDFDFDFDFDFDF;
	clear_file_[6] = 0xBFBFBFBFBFBFBFBF;
	clear_file_[7] = 0x7F7F7F7F7F7F7F7F;

	mask_file_[0] = 0x101010101010101;
	mask_file_[1] = 0x202020202020202;
	mask_file_[2] = 0x404040404040404;
	mask_file_[3] = 0x808080808080808;
	mask_file_[4] = 0x1010101010101010;
	mask_file_[5] = 0x2020202020202020;
	mask_file_[6] = 0x4040404040404040;
	mask_file_[7] = 0x8080808080808080;

	for (int i = 0; i < 64; i++) {
		piece_[i] = 1ULL << i;
	}
};

void Board::ShowBoard(U64 bb) {
	U64 shift = 1ULL;
	int rank = 0;
	int file = 0;
	int square = 0;
	std::cout << "\n";
	for (rank = RANK_8; rank >= RANK_1; rank--) {
		for (file = FILE_A; file <= FILE_H; file++) {
			square = ((file)+(rank * 8));
			if ((shift << square) & bb) {
				std::cout << "x ";
			}
			else {
				std::cout << "- ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
};


U64 Board::GetClearFile(int file) {
	return clear_file_[file];
};

U64 Board::GetClearRank(int rank) {
	return clear_rank_[rank];
};

U64 Board::GetMaskFile(int file) {
	return mask_file_[file];
};

U64 Board::GetMaskRank(int rank) {
	return mask_rank_[rank];
};

U64 Board::GetPiece(int square) {
	return piece_[square];
};
