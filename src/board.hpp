#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <bitset>
#include <iostream>
#include "types.hpp"

typedef uint64_t U64;

class Undo {
private:
		U64 position;
		int move_;
		int castle_perm_;
		int en_passant_;
		int fifty_move_;
};

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
		U64 all_pawns_;

		// lookup tables
		U64 clear_file_[8];
		U64 clear_rank_[8];
		U64 mask_file_[8];
		U64 mask_rank_[8];
		U64 piece_[64];

		U64 position;
		
		int piece_array_[64];
		int side_; 
		int king_[2];
		int ply_;
		int history_ply_;
		int en_passant_;
		int fifty_move_;
		int castle_permisson_;
		int piece_big_[3]; // not pawns
		int piece_major_[3]; // rooks & queens
		int piece_minor_[3]; // bishops & knights
		int piece_number_[13]; // number of different piece types on the board
		int piece_list_[13][10];
		int bit_table[64];
		Undo history[4096];

		

	public:
		Board();
		void ShowBoard(U64 bitboard);
		U64 GetClearFile(int file);
		U64 GetClearRank(int rank);
		U64 GetMaskFile(int file);
		U64 GetMaskRank(int rank);
		U64 GetWhiteKing();
		U64 GetBlackKing();
		U64 GetWhiteKnights();
		U64 GetBlackKnights();
		U64 GetWhitePawns();
		U64 GetBlackPawns();
		U64 GetWhitePieces();
		U64 GetBlackPieces();
		U64 GetAllPieces();
		U64 GetPiece(int square);
		int GetSide();
		int GetEnPassant();
		U64 KingMoves(U64 kings, U64 side);
		U64 KnightMoves(U64 knights, U64 side);
		U64 WhitePawnMoves(U64 pawns, U64 black, U64 all);
		U64 BlackPawnMoves(U64 pawns, U64 white, U64 all);
		int GetPieceArray(int i);
		U64 GetBitTable(int index);
		int GetCastlePermission();
		int CountBits(U64 bitboard);
		int PopBit(U64* bitboard);
		void SetBit(U64& bitboard, int index);
		void ClearBit(U64& bitboard, int index);
		void ResetBoard(Board b);		
};

#endif
