#pragma once
#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "types.hpp"
#include "hash.hpp"

Board::Board() {
	//precomputed lookup tables
  clear_rank_[RANK_1] = 0xFFFFFFFFFFFFFF00; // every bit on the board is set to 1 except the rank at the current index
  clear_rank_[RANK_2] = 0xFFFFFFFFFFFF00FF; // this allows us to compute without considering a certain rank
  clear_rank_[RANK_3] = 0xFFFFFFFFFF00FFFF;
  clear_rank_[RANK_4] = 0xFFFFFFFF00FFFFFF;
  clear_rank_[RANK_5] = 0xFFFFFF00FFFFFFFF;
  clear_rank_[RANK_6] = 0xFFFF00FFFFFFFFFF;
  clear_rank_[RANK_7] = 0xFF00FFFFFFFFFFFF;
  clear_rank_[RANK_8] = 0x00FFFFFFFFFFFFFF;

	clear_file_[FILE_A] = 0xFEFEFEFEFEFEFEFE; // same concept as clearing a rank, just vertical
	clear_file_[FILE_B] = 0xFDFDFDFDFDFDFDFD; // this is especially useful for preventing pieces from travelling off the board
	clear_file_[FILE_C] = 0xFBFBFBFBFBFBFBFB;
	clear_file_[FILE_D] = 0xF7F7F7F7F7F7F7F7;
	clear_file_[FILE_E] = 0xEFEFEFEFEFEFEFEF;
	clear_file_[FILE_F] = 0xDFDFDFDFDFDFDFDF;
	clear_file_[FILE_G] = 0xBFBFBFBFBFBFBFBF;
	clear_file_[FILE_H] = 0x7F7F7F7F7F7F7F7F;

  mask_rank_[RANK_1] = 0x00000000000000FF; // bits are turned on for the rank at the current index
  mask_rank_[RANK_2] = 0x000000000000FF00; // useful for only computing pieces on a specific rank, such as a double-stepping pawn
  mask_rank_[RANK_3] = 0x0000000000FF0000;
  mask_rank_[RANK_4] = 0x00000000FF000000;
  mask_rank_[RANK_5] = 0x000000FF00000000;
  mask_rank_[RANK_6] = 0x0000FF0000000000;
  mask_rank_[RANK_7] = 0x00FF000000000000;
  mask_rank_[RANK_8] = 0xFF00000000000000;

	mask_file_[FILE_A] = 0x101010101010101; // same concept as masking a rank, but for files
	mask_file_[FILE_B] = 0x202020202020202;
	mask_file_[FILE_C] = 0x404040404040404;
	mask_file_[FILE_D] = 0x808080808080808;
	mask_file_[FILE_E] = 0x1010101010101010;
	mask_file_[FILE_F] = 0x2020202020202020;
	mask_file_[FILE_G] = 0x4040404040404040;
	mask_file_[FILE_H] = 0x8080808080808080;

	const int BitTable[64] = { // precomputed table (https://www.chessprogramming.org/Looking_for_Magics)
	63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	58, 20, 37, 17, 36, 8
	};

	white_king_ = 1ULL << E1;
	white_knights_ = 1ULL << B1 | 1ULL << G1;
	white_pawns_ = 1ULL << A2 | 1ULL << B2 | 1ULL << C2 | 1ULL << D2 | 1ULL << E2 | 1ULL << F2 | 1ULL << G2 | 1ULL << H2 | 1ULL << G4;
	black_pawns_ = 1ULL << A7 | 1ULL << B7 | 1ULL << C7 | 1ULL << D7 | 1ULL << E7 | 1ULL << F7 | 1ULL << G7 | 1ULL << H7 | 1ULL << H5 | 1ULL << F5;

	for (int i = 0; i < 64; i++) { // assign board indexes to the piece array
			piece_[i] = 1ULL << i;
	};	
};

void Board::ShowBoard(U64 bitboard) { // prints board to console
	int rank = 0;
	int file = 0;
	int pos = 0; // number of times to shift left to assign position
	std::cout << "\n";
	for (rank = RANK_8; rank >= RANK_1; rank--) {
		for (file = FILE_A; file <= FILE_H; file++) {
			pos = rank * 8 + file; // multiply rank by 8 to find correct row in bitboard, then add on file integer to move across
			if ((bitboard & 1ULL << pos)) { // bitwise left shift to given position
				std::cout << "1 "; // bit is on; a piece is present
			}
			else {
				std::cout << ". "; // bit is off; there is no piece at this position
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
};

// getters
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
}
int Board::GetSide()
{
	return side_;
}
int Board::GetEnPassant()
{
	return en_passant_;
}
;

U64 Board::GetWhiteKing() {
	return white_king_; 
};

U64 Board::GetBlackKing() {
	return black_king_;
};

U64 Board::GetWhiteKnights() {
	return white_knights_;
};

U64 Board::GetBlackKnights() {
	return black_knights_;
};

U64 Board::GetWhitePawns() {
		return white_pawns_;
};

U64 Board::GetBlackPawns() {
		return black_pawns_;
};

U64 Board::GetWhitePieces() {
		return white_pieces_;
};

U64 Board::GetBlackPieces() {
		return black_pieces_;
};

U64 Board::GetAllPieces() {
		return all_pieces_;
};

U64 Board::GetBitTable(int index) { // returns index from precomupted bit table
		return bit_table[index];
}
int Board::GetCastlePermission()
{
	return castle_permisson_;
}
;

int Board::GetPieceArray(int i) {
		return piece_array_[i];
}

void Board::SetBit(U64& bitboard, int index) { // add a bit to the bitboard
		bitboard |= GetPiece(index);
};

void Board::ClearBit(U64& bitboard, int index) { // removes a bit from the bitboard
		bitboard &= ~GetPiece(index);
}

void Board::ResetBoard(Board b) { // reset board values to empty
	int index = 0;
	for (index = 0; index < 64; ++index) {
		piece_array_[index] = piece::EMPTY;
	}
	
	for (index = 0; index < 3; ++index) {
		piece_big_[index] = 0;
		piece_major_[index] = 0;
		piece_minor_[index] = 0;
	}
	white_pawns_ = 0ULL;
	black_pawns_ = 0ULL;
	all_pawns_ = white_pawns_ | black_pawns_;

	for (index = 0; index < 13; ++index) {
		piece_number_[index] = 0;
	}
	position = 0ULL;
	king_[0] = NO_SQUARE;
	king_[1] = NO_SQUARE;
	side_ = BOTH;
	en_passant_ = NO_SQUARE;
	fifty_move_ = 0;
	ply_ = 0;
	history_ply_ = 0;
	castle_permisson_ = 0;	
}
;

U64 Board::KingMoves(U64 king, U64 side) { // returns valid set of moves for kings
	U64 NW = king << 7 & GetClearFile(FILE_H); // bitwise left shift to move to appropriate square
	U64 N = king << 8;
	U64 NE = king << 9 & GetClearFile(FILE_A); // files are cleared depending on which way the king is moving to stop it moving off the board
	U64 E = king << 1 & GetClearFile(FILE_A); // by performing a bitwise AND, when the king moves east all moves generated on file A are ignored, and vice versa
	U64 SE = king >> 7 & GetClearFile(FILE_A); // similarly, bitwise right shifts to move to the remaining positions
	U64 S = king >> 8;
	U64 SW = king >> 9 & GetClearFile(FILE_H);
	U64 W = king >> 1 & GetClearFile(FILE_H);

	U64 all_moves = NW | N | NE | E | SE | S | SW | W; // return the set of all moves generated
	U64 king_all = all_moves & ~side; // bitwise AND with own side to prevent the piece colliding with existing pieces of the same colour
	return king_all;
};

U64 Board::KnightMoves(U64 knights, U64 side) { // returns valid set of moves for knights, same method of generation as king's moves
		U64 NW1 = knights << 6 & GetClearFile(FILE_H) & GetClearFile(FILE_G); // two files are cleared for moves that are able to move 2 across
		U64 NW2 = knights << 15 & GetClearFile(FILE_H);
		U64 NE1 = knights << 17 & GetClearFile(FILE_A);
		U64 NE2 = knights << 10 & GetClearFile(FILE_A) & GetClearFile(FILE_B);
		U64 SE1 = knights >> 6 & GetClearFile(FILE_A) & GetClearFile(FILE_B);
		U64 SE2 = knights >> 15 & GetClearFile(FILE_A);
		U64 SW1 = knights >> 17 & GetClearFile(FILE_H);
		U64 SW2 = knights >> 10 & GetClearFile(FILE_H) & GetClearFile(FILE_G); 

		U64 all_moves = NW1 | NW2 | NE1 | NE2 | SE1 | SE2 | SW1 | SW2;
		U64 knight_all = all_moves & ~side;
		return knight_all;
};

U64 Board::WhitePawnMoves(U64 white_pawns, U64 black, U64 all) { // returns valid set of moves for white pawns
		// find position one space in front of pawn
		U64 white_pawn_single = white_pawns << 8 & ~all;
		// find position two spaces in front of pawn ONLY if the pawn is on the second rank
		U64 white_pawn_double = white_pawns << 16 & GetMaskRank(RANK_4) & ~all; // the pawn can only move onto rank 4 if it started on rank 2
		U64 white_pawn_moves = white_pawn_single | white_pawn_double;
		U64 white_pawn_attack_left = white_pawns << 7 &GetClearFile(FILE_H); // clear file A 
		U64 white_pawn_attack_right = white_pawns << 9 & GetClearFile(FILE_A);
		U64 white_pawn_attacks = (white_pawn_attack_left | white_pawn_attack_right) & black; // AND with black pieces; attacking is only allowed when there is a target
		U64 white_pawn_all = white_pawn_moves | white_pawn_attacks; // set of valid moves and attacks
		return white_pawn_all;
};

U64 Board::BlackPawnMoves(U64 black_pawns, U64 black, U64 all) { // same as white pawns; shift direction swapped as black pawns travel in the opposite direction
		U64 black_pawn_single = black_pawns >> 8 & ~all;
		U64 black_pawn_double = black_pawns >> 16 & GetMaskRank(RANK_5) & ~all; 
		U64 black_pawn_moves = black_pawn_single | black_pawn_double;
		U64 black_pawn_attack_left = black_pawns >> 7 & GetClearFile(FILE_A);
		U64 black_pawn_attack_right = black_pawns >> 9 & GetClearFile(FILE_H);
		U64 black_pawn_attacks = (black_pawn_attack_left | black_pawn_attack_right) & black;
		U64 black_pawn_all = black_pawn_moves | black_pawn_attacks;
		return black_pawn_all;
};

int Board::CountBits(U64 bitboard) { // return count of bits set to 1 in a bitboard (https://www.chessprogramming.org/Looking_for_Magics)
		int bit_count;
		for (bit_count = 0; bitboard; bit_count++, bitboard &= bitboard - 1);
		return bit_count;
}

int Board::PopBit(U64 *bitboard) { // pop LSB off the bitboard (https://www.chessprogramming.org/Looking_for_Magics)
		U64 board = *bitboard ^ (*bitboard - 1);
		unsigned int fold = (unsigned)((board & 0xffffffff) ^ (board >> 32));
		*bitboard &= (*bitboard - 1);
		return bit_table[(fold * 0x783a9b23) >> 26];
}
