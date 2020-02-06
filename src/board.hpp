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
		U64 white_pawns;
		U64 white_rooks;
		U64 white_knights;
		U64 white_bishops;
		U64 white_queens;
		U64 white_king;
		U64 white_pieces;

		U64 black_pawns;
		U64 black_rooks;
		U64 black_knights;
		U64 black_bishops;
		U64 black_queens;
		U64 black_king;
		U64 black_pieces;

		U64 all_pieces;

		// lookup tables
		U64 clear_file[8];
		U64 clear_rank[8];
		U64 mask_file[8];
		U64 mask_rank[8];
	public:
		Board();
		void ShowBoard(U64 bitboard);
		U64 GetClearFile(int file);
		U64 GetClearRank(int rank);
		U64 GetMaskFile(int file);
		U64 GetMaskRank(int rank);
		
		
};



class Undo {
	private:
		int move;
		int castle_perm;
		int en_passant;
		int fifty_move;
};

class BoardStruct {
	private:
		int pieces[64];
		int king;
		U64 pawns[3];

		int ply;
		int h_ply;

		int en_passant;
		int fifty_move;
		int castle_permisson;
		int side;

		int piece_number;
		int piece_big;
		int piece_major;
		int piece_minor;

		Undo History[2048];

		U64 poskey;
};

#endif
