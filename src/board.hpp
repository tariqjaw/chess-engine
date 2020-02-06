#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <bitset>
#include <iostream>
#include "types.hpp"

typedef uint64_t U64;

class Board {
	private:
		// piece bitboards
		U64 *bitboard;
		U64 white_pawns_;
		U64 white_rooks_;
		U64 white_knights_;
		U64 white_bishops_;
		U64 white_queens_;
		U64 white_king_;
		U64 white_pieces_;

		U64 black_pawns_;
		U64 black_rooks_;
		U64 black_knights_;
		U64 black_bishops_;
		U64 black_queens_;
		U64 black_king_;
		U64 black_pieces_;

		U64 all_pieces_;

		// lookup tables
		U64 clear_file_[8];
		U64 clear_rank_[8];
		U64 mask_file_[8];
		U64 mask_rank_[8];
		U64 piece_[64];
	public:
		Board();
		void ShowBoard(U64 bitboard);
		U64 GetClearFile(int file);
		U64 GetClearRank(int rank);
		U64 GetMaskFile(int file);
		U64 GetMaskRank(int rank);
		U64 GetWhiteKing();
		U64 GetPiece(int square);
		U64 KingValid(Board b);
		
		
};



class Undo {
	private:
		int move_;
		int castle_perm_;
		int en_passant_;
		int fifty_move_;
};

class BoardStruct {
	private:
		int pieces_[64];
		int king_;
		U64 pawns_[3];

		int ply_;
		int h_ply_;

		int en_passant_;
		int fifty_move_;
		int castle_permisson_;
		int side_;

		int piece_number_;
		int piece_big_;
		int piece_major_;
		int piece_minor_;

		Undo History_[2048];

		U64 poskey_;
};

#endif
