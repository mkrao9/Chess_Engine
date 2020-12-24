#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

#include "board.hpp"


inline bool isInCheck(Board* board){
    if (board->other_attack_set[board->current_king_square].bits)
        return true; 
    return false;
}


Move basicSearch(Board* board, int depth, Move* ml, int num_moves);

#endif