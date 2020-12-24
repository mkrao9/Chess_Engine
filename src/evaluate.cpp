#include "../include/evaluate.hpp"
#include <stdlib.h>
#include <iostream>

int evaluatePosition(Board* board){
    NumPieces curr_num_pieces = board->current_pieces->num_pieces; 
    NumPieces other_num_pieces = board->other_pieces->num_pieces;
    int queen_diff = (curr_num_pieces.num_queens - other_num_pieces.num_queens) * QUEEN_VALUE;
    int rook_diff = (curr_num_pieces.num_rooks - other_num_pieces.num_rooks) * ROOK_VALUE;
    int pawn_diff = (curr_num_pieces.num_pawns - other_num_pieces.num_pawns) * PAWN_VALUE; 
    int bishop_diff = (curr_num_pieces.num_bishops - other_num_pieces.num_bishops) * BISHOP_VALUE; 
    int knight_diff = (curr_num_pieces.num_knights - other_num_pieces.num_knights) * KNIGHT_VALUE;

    int res = queen_diff + rook_diff + pawn_diff + bishop_diff + knight_diff;       
    return res;
}