#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <iostream>
#include "types.hpp"

typedef uint64_t U64;

class Board {
	private:
		U64 *bitboard;
	public:
		Board(),
		~Board();
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
		int castle_perm_;
		int side_;

		int piece_num_;
		int piece_big_;
		int piece_maj_;
		int piece_min_;

		Undo History[2048];

		U64 poskey;
};

#endif
