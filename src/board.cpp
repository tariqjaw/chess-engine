#pragma once
#include <stdio.h>
#include <iostream>
#include "board.hpp"
#include "types.hpp"

Board::Board() {
	//precomputed lookup tables
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

	const int BitTable[64] = { // precomputed table
	63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	58, 20, 37, 17, 36, 8
	};

	white_king_ = 1ULL << E1;
	white_knights_ = 1ULL << B1 | 1ULL << G1;
	white_pawns_ = 1ULL << A2 | 1ULL << B2 | 1ULL << C2 | 1ULL << D2 | 1ULL << E2 | 1ULL << F2 | 1ULL << G2 | 1ULL << H2;
	black_pawns_ = 1ULL << A7 | 1ULL << B7 | 1ULL << C7 | 1ULL << D7 | 1ULL << E7 | 1ULL << F7 | 1ULL << G7 | 1ULL << H7;

	for (int i = 0; i < 64; i++) {
			piece_[i] = 1ULL << i;
	};

	white_king_moves_ = KingMoves(white_king_, white_pieces_);
	black_king_moves_ = KingMoves(black_king_, black_pieces_);
	white_knights_moves_ = KnightMoves(white_knights_, white_pieces_);
	black_knights_moves_ = KnightMoves(black_knights_, black_pieces_);

	
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
};

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

U64 Board::GetWhiteKingMoves() {
	return white_king_moves_;
};

U64 Board::GetBlackKingMoves() {
		return black_king_moves_;
};

U64 Board::GetWhiteKnightsMoves() {
		return white_knights_moves_;
};

U64 Board::GetBlackKnightsMoves() {
		return black_knights_moves_;
};

U64 Board::GetBitTable(int index) { // returns index from precomupted bit table
		return bit_table[index];
};

U64 Board::GetPieceArray(int i) {
		return piece_array_[i];
}

void Board::SetBit(U64& bitboard, int index) { // add a bit to the bitboard
		bitboard |= GetPiece(index);
};

void Board::ClearBit(U64& bitboard, int index) { // removes a bit from the bitboard
		bitboard &= ~GetPiece(index);
};

U64 Board::KingMoves(U64 king, U64 side) { // returns valid set of moves for kings
	U64 NW = king << 7 & GetClearFile(FILE_H);
	U64 N = king << 8;
	U64 NE = king << 9 & GetClearFile(FILE_A);
	U64 E = king << 1 & GetClearFile(FILE_A);
	U64 SE = king >> 7 & GetClearFile(FILE_A);
	U64 S = king >> 8;
	U64 SW = king >> 9 & GetClearFile(FILE_H);
	U64 W = king >> 1 & GetClearFile(FILE_H);

	U64 all_moves = NW | N | NE | E | SE | S | SW | W;
	U64 king_valid = all_moves & ~side;
	return king_valid;
};

U64 Board::KnightMoves(U64 knights, U64 side) { // returns valid set of moves for knights
		U64 NW1 = knights << 6 & GetClearFile(FILE_H) & GetClearFile(FILE_G);
		U64 NW2 = knights << 15 & GetClearFile(FILE_H);
		U64 NE1 = knights << 17 & GetClearFile(FILE_A);
		U64 NE2 = knights << 10 & GetClearFile(FILE_A) & GetClearFile(FILE_B);
		U64 SE1 = knights >> 6 & GetClearFile(FILE_A) & GetClearFile(FILE_B);
		U64 SE2 = knights >> 15 & GetClearFile(FILE_A);
		U64 SW1 = knights >> 17 & GetClearFile(FILE_H);
		U64 SW2 = knights >> 10 & GetClearFile(FILE_H) & GetClearFile(FILE_G); 

		U64 all_moves = NW1 | NW2 | NE1 | NE2 | SE1 | SE2 | SW1 | SW2;
		U64 knight_valid = all_moves & ~side;
		return knight_valid;
};

U64 Board::WhitePawnMoves(U64 white_pawns, U64 black, U64 all) { // returns valid set of moves for pawns
		// one space in front of pawn
		U64 white_pawn_single = white_pawns << 8 & ~all;
		// two spaces in front of pawn
		U64 white_pawn_double = white_pawns << 16 & GetMaskRank(RANK_4) & ~all;
		U64 white_pawn_moves = white_pawn_single | white_pawn_double;
		U64 white_pawn_attack_left = white_pawns << 7 & GetClearFile(FILE_A);
		U64 white_pawn_attack_right = white_pawns << 9 & GetClearFile(FILE_H);
		U64 white_pawn_attacks = (white_pawn_attack_left | white_pawn_attack_right) & black;
		U64 white_pawn_valid = white_pawn_moves | white_pawn_attacks;
		return white_pawn_valid;
};

U64 Board::BlackPawnMoves(U64 black_pawns, U64 black, U64 all) { // returns valid set of moves for pawns
		// one space in front of pawn
		U64 black_pawn_single = black_pawns >> 8 & ~all;
		// two spaces in front of pawn
		U64 black_pawn_double = black_pawns >> 16 & GetMaskRank(RANK_5) & ~all;
		U64 black_pawn_moves = black_pawn_single | black_pawn_double;
		U64 black_pawn_attack_left = black_pawns << 7 & GetClearFile(FILE_A);
		U64 black_pawn_attack_right = black_pawns << 9 & GetClearFile(FILE_H);
		U64 black_pawn_attacks = (black_pawn_attack_left | black_pawn_attack_right) & black;
		U64 black_pawn_valid = black_pawn_moves | black_pawn_attacks;
		return black_pawn_valid;
};

U64 Board::CountBits(U64 bitboard) { // return count of bits set to 1 in a bitboard
		int bit_count;
		for (bit_count = 0; bitboard; bit_count++, bitboard &= bitboard - 1);
		return bit_count;
}

U64 Board::PopBit(U64 *bitboard) { // return LSB, then set it to 0
		U64 board = *bitboard ^ (*bitboard - 1);
		unsigned int fold = (unsigned)((board & 0xffffffff) ^ (board >> 32));
		*bitboard &= (*bitboard - 1);
		return bit_table[(fold * 0x783a9b23) >> 26];
}

int Board::ParseFEN(const char* fen) {
		int rank = RANK_8;
		int file = FILE_A;
		int piece = 0;
		int count = 0;
		int i = 0;
		int sq = 0;

		while ((rank >= RANK_1) && *fen) {
				count = 1;
				switch (*fen) {
						case 'P': piece = piece::W_PAWN; break;
						case 'R': piece = piece::W_ROOK; break;
						case 'N': piece = piece::W_KNIGHT; break;
						case 'B': piece = piece::W_BISHOP; break;
						case 'Q': piece = piece::W_QUEEN; break;
						case 'K': piece = piece::W_KING; break;
						case 'p': piece = piece::B_PAWN; break;
						case 'r': piece = piece::B_ROOK; break;
						case 'n': piece = piece::B_KNIGHT; break;
						case 'b': piece = piece::B_BISHOP; break;
						case 'q': piece = piece::B_QUEEN; break;
						case 'k': piece = piece::B_KING; break;

						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
								piece = piece::EMPTY;
								count = *fen - '0';
								break;

						case '/':
						case ' ':
								rank--;
								file = FILE_A;
								fen++;
								continue;
						default:
								std::cout << "FEN Invalid \n";
								return -1;

				}

				for (i = 0; i < count; i++) {
						sq = rank * 8 + file;
						if (piece != piece::EMPTY) {
								piece_array_[sq] = piece;
						}
						file++;
				}
				fen++;
		}
		side_ = (*fen == 'w') ? WHITE : BLACK;
		fen += 2;

		for (i = 0; i < 4; i++) {
				if (*fen == ' ') {
						break;
				}
				switch (*fen) {

				}
		}

		if (*fen != '-') {
				file = fen[0] - 'a';
				rank = fen[1] - '1';
				en_passant_ = (file)+(rank * 8);
		}

};
