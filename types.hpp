#pragma once
#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

typedef uint64_t U64;

namespace piece {
	enum PieceType: unsigned int {
	 	PAWN = 0,
		KNIGHT = 1,
		BISHOP = 2,
		ROOK = 3,
		QUEEN = 4,
		KING = 5,
		NO_PIECE_TYPE = 6,
		PIECE_TYPE_NB = 7
	};

	enum Pieces: unsigned int {
		W_PAWN = 0,
		W_KNIGHT = 1,
		W_BISHOP = 2,
		W_ROOK = 3,
		W_QUEEN = 4,
		W_KING = 5,
		B_PAWN = 6,
		B_KNIGHT = 7,
		B_BISHOP = 8,
		B_ROOK = 9,
		B_QUEEN = 10,
		B_KING = 11,
		W_PIECES = 12,
		B_PIECES = 13,
		EMPTY = 14
	};

	enum PieceValue: unsigned int {
		PAWN_VALUE = 100,
		KNIGHT_VALUE = 325,
		BISHOP_VALUE = 325,
		ROOK_VALUE = 500,
		QUEEN_VALUE = 900,
		KING_VALUE = 10000
	};
};

enum Colour {
	WHITE = 0,
	BLACK = 1,
	BOTH = 2
};

enum Square {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
	NO_SQ
};

enum File {
	FILE_A,
	FILE_B,
	FILE_C,
	FILE_D,
	FILE_E,
	FILE_F,
	FILE_G,
	FILE_H,
  FILE_NULL
};

enum Rank {
	RANK_1,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_NULL
};

#endif