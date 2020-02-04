#pragma once
#include <bitset>
#include <cassert>
#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "types.hpp"

void ShowBoard(U64 bb) {
	U64 shift_bb = 1ULL;
	int rank = 0;
	int file = 0;
	int sq = 0;
	std::cout << "\n";
	for (rank = RANK_8; rank >= RANK_1; rank--) {
		for (file = FILE_A; file <= FILE_H; file++) {
			sq = ((file) + (rank*8));
			if ((shift_bb << sq) & bb) {
				std::cout << "X ";
			}
			else {
				std::cout << "- ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
};

int main() {
  int x;
	U64 bitboard = 0ULL;
	ShowBoard(bitboard);
	std::cout << "Added A1:\n";
	bitboard |= (1ULL << A1);
	ShowBoard(bitboard);
	std::cout << "Added A2:\n";
	bitboard |= (1ULL << A2);
	ShowBoard(bitboard);
	std::cout << "Added A3:\n";
	bitboard |= (1ULL << A3);
	ShowBoard(bitboard);
	std::cout << "Added G5:\n";
	bitboard |= (1ULL << G5);
	ShowBoard(bitboard);
	std::cout << "Added B4:\n"; 
	bitboard |= (1ULL << B4);
	ShowBoard(bitboard);
  std::cin >> x;
}




