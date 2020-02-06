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

	return 0;
};
