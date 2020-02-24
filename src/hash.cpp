#pragma once
#include <bitset>
#include <cassert>
#include <stdio.h>
#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "hash.hpp"

U64 HashKey::Rand64() { // PRNG for 64 bit integers (https://www.chessprogramming.org/Looking_for_Magics)
	return (((U64)std::rand()) | ((U64)std::rand() << 15) | ((U64)std::rand() << 30) | ((U64)std::rand() << 45) | (((U64)std::rand() & 0xf) << 60));
}
U64 HashKey::PositionKey(Board b) {
	U64 key = 0;
	int square = 0;
	int target_piece = piece::EMPTY;

	for (square = 0; square < 64; ++square) {
		target_piece = b.GetPieceArray(square);
		if (target_piece != NO_SQUARE && target_piece != piece::EMPTY) {
			key ^= piece_keys[target_piece][square];
		}
	}

	if (b.GetSide() == WHITE) {
		key ^= side_key;
	}

	if (b.GetEnPassant() != NO_SQUARE) {
		key ^= piece_keys[piece::EMPTY][b.GetEnPassant()];
	}

	key ^= castle_keys[b.GetCastlePermission()];
	return key;
}
;

HashKey::HashKey()
{
	int index = 0;
	int index2 = 0;
	for (index = 0; index < 13; ++index) {
		for (index2 = 0; index2 < 64; ++index2) {
			piece_keys[index][index2] = Rand64();
		}
	}
	side_key = Rand64();
	for (index = 0; index < 16; ++index) {
		castle_keys[index] = Rand64();
	}
}
