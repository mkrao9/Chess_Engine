#ifndef _EVALUATE_HPP_
#define _EVALUATE_HPP_

#include "../include/board.hpp"


#define PAWN_VALUE 100
#define KNIGHT_VALUE 350 
#define BISHOP_VALUE 350
#define ROOK_VALUE 520
#define QUEEN_VALUE 1000
 
int evaluatePosition(Board* board);

#endif