#include "../include/search.hpp"
#include "../include/move.hpp"
#include "../include/evaluate.hpp"
#include "../include/make_unmake.hpp"
#include <stdlib.h>
#include <iostream>
#include <random>

/* 
    piece values:
        0 - king 
        1 - pawn 
        2 - knight 
        3 - bishop 
        4 - rook 
        5 - queen 
*/ 

/* 
    zorbist keys: 
        0 - 5 * 64 = white pieces  (64 indexes / square)
        6 * 64 - 11 * 64 = black pieces (64 indexes / square) 
        769 = side to move 
        770 - 773 = castle rights (white q, white k, black q, black k)
        774 - 781 - = ep file (0 = h, 7 = a)

*/

uint64_t zorbist_keys[781]; 

void initializeZorbistKeys(){
    std::mt19937_64 prng;
    prng.seed(927927927927927);
    for (int i = 0; i < 781; i++){
        zorbist_keys[i] = prng();
    }
}


int basicRecursiveSearch(Board* board, int depth, int alpha, int beta){
    Move ml[256];
    int num_moves = generateAllMoves(board, ml);
    if (num_moves == 0){
        if (isInCheck(board)){
            return INT16_MIN;
        }
        else
        {
            return 0;
        } 
    }

    if (depth == 0){
        int eval = evaluatePosition(board); 
        return eval;
    }

    if (depth % 2){
        int min_value = INT16_MAX;
        for (int i = 0; i < num_moves; i++){
            int old_ep = board->en_pass_square; 
            int old_moves_since = board->move_since; 
            CastleRights old_castle_rights = board->castle_rights; 
            makeMove(board, ml[i]);
            int res = basicRecursiveSearch(board, depth - 1, alpha, beta);
            unmakeMove(board, ml[i]); 
            board->en_pass_square = old_ep; 
            board->move_since = old_moves_since;
            board->castle_rights = old_castle_rights;
            if (res < min_value)
                min_value = res;
            if (beta < min_value)
                beta = min_value;

            if (beta <= alpha)
                break;
        }
        return min_value;
    }
    else{
        int max_value = INT16_MIN;
        for (int i = 0; i < num_moves; i++){
            int old_ep = board->en_pass_square; 
            int old_moves_since = board->move_since; 
            CastleRights old_castle_rights = board->castle_rights; 
            makeMove(board, ml[i]);
            int res = basicRecursiveSearch(board, depth - 1, alpha, beta);
            unmakeMove(board, ml[i]); 
            board->en_pass_square = old_ep; 
            board->move_since = old_moves_since;
            board->castle_rights = old_castle_rights;
            if (res > max_value)
                max_value = res;
            if (alpha > max_value)
                alpha = max_value;

            if (beta <= alpha)
                break;
        }
        return max_value;
    }


}

Move basicSearch(Board* board, int depth, Move* ml, int num_moves){

    int best_index = 0; 
    if (depth % 2){
        int min_value = INT16_MAX;
        for (int i = 0; i < num_moves; i++){
            int old_ep = board->en_pass_square; 
            int old_moves_since = board->move_since; 
            CastleRights old_castle_rights = board->castle_rights; 
            makeMove(board, ml[i]);
            int res = basicRecursiveSearch(board, depth - 1, INT16_MIN, INT16_MAX);
            unmakeMove(board, ml[i]); 
            board->en_pass_square = old_ep; 
            board->move_since = old_moves_since;
            board->castle_rights = old_castle_rights;
            if (res < min_value){
                min_value = res;
                best_index = i;
            }

        }
        return ml[best_index];
    }
    else{
        int max_value = INT16_MIN;
        for (int i = 0; i < num_moves; i++){
            int old_ep = board->en_pass_square; 
            int old_moves_since = board->move_since; 
            CastleRights old_castle_rights = board->castle_rights; 
            makeMove(board, ml[i]);
            int res = basicRecursiveSearch(board, depth - 1, INT16_MIN, INT16_MAX);
            unmakeMove(board, ml[i]); 
            board->en_pass_square = old_ep; 
            board->move_since = old_moves_since;
            board->castle_rights = old_castle_rights;
            if (res > max_value){
                max_value = res;
                best_index = i;
            }
                
        }
        return ml[best_index];
    }
}
