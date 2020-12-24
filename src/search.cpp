#include "../include/search.hpp"
#include "../include/move.hpp"
#include "../include/evaluate.hpp"
#include "../include/make_unmake.hpp"
#include <stdlib.h>
#include <iostream>


int basicRecursiveSearch(Board* board, int depth){
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

    int max_value = INT16_MAX;
    for (int i = 0; i < num_moves; i++){
        int old_ep = board->en_pass_square; 
        int old_moves_since = board->move_since; 
        CastleRights old_castle_rights = board->castle_rights; 
        makeMove(board, ml[i]);
        int res = basicRecursiveSearch(board, depth - 1);
        unmakeMove(board, ml[i]); 
        board->en_pass_square = old_ep; 
        board->move_since = old_moves_since;
        board->castle_rights = old_castle_rights;
        if (res < max_value)
            max_value = res;
    }

    return -1 * max_value;
}

Move basicSearch(Board* board, int depth, Move* ml, int num_moves){


    int max_value = INT32_MIN;
    int best_index = 0;
    for (int i = 0; i < num_moves; i++){
        int old_ep = board->en_pass_square; 
        int old_moves_since = board->move_since; 
        CastleRights old_castle_rights = board->castle_rights; 
        makeMove(board, ml[i]);
        int res = -1 * basicRecursiveSearch(board, depth - 1);
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
