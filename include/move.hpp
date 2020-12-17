#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include "board.hpp"
#include <stdlib.h>



/* OUTDATED: Bits: Will change piece captures
        0-5: Source Square
        6-11: Destination Square square 
        12-15: Special Flags 
        20-23: Piece Captures 
            1 = pawn 
            2 = knight 
            3 = bishop 
            4 = rook
            5 = queen 
        24+: ??
*/

/* Special flag codes: 
    0 - none 
    1 - king side castle 
    2 - queen side castle 
    3 - ep 
    4 - knight promo 
    5 - bishop promo 
    6 - rook promo 
    7 - queen promo 
*/

#define FLAG_CODE(a) ((uint8_t) (a & 0xFF))
#define SOURCE(a) ((uint8_t) ((a & 0x3F00) >> 8))
#define DEST(a) ((uint8_t) ((a & 0xFC000) >> 14))
#define CAPT_PIECE(a) ((uint8_t) ((a & 0xF00000) >> 20))



#define RANK(a) (0xFFLL << a)
#define COL(a) ((0x0101010101010101LL) << a)

extern int code_to_val[8];


// https://www.chessprogramming.org/Encoding_Moves#From-To_Based

/* first plan = implement attack sets 

*/


/* 
    attack sets w/ incremental updates: 
        1) loop through every square -- see what things attack it (from the current color) to figure out possible move 
        make: 
            a. for everything that attacked the source square extend the ray (if it's a ray piece) 
            -- update every respective square until it hits a piece 
            b. for everything that attacks the dest square, extend ray in opposite dirrection 
            -- update to reflect that square is no longer being hit, break once you hit a piece 
        unmake: pretty much the same thing 
*/


uint32_t generateAllMoves(Board *board, Move* move_list);


// /* first 4 bits: 0 = no check, 1 = blockable check, 2 = not blockable check
//    last 4 bits: code for direction, 0 = Left, 7 = down left */ 
// uint8_t checkStraightCheck(attack_set attack, int target_square, Pieces* other_pieces);

inline bool isSameDiag(uint8_t a, uint8_t b){
   return (((a / 8) - (b / 8)) == (-1 * ((a % 8) - (b % 8))));
}

inline bool isSameAntiDiag(uint8_t a, uint8_t b){
    return (((a / 8) - (b / 8)) == ((a % 8) - (b % 8)));
}

inline void addMove(Board* board, int from, int to, uint8_t special, uint8_t capture){
 
    Move mv{};
    mv.source = from; 
    mv.dest = to; 
    mv.special = special; 
    mv.capture = capture;
    board->move_list[board->curr_num_moves] = mv;

    board->curr_num_moves++;
}

inline uint8_t getPieceCode(uint64_t square, Pieces* other_pieces){
    if (other_pieces->pawn & square){
        return 1; 
    }
    if (other_pieces->rook & square){
        return 4;
    }
    if (other_pieces->knight & square){
        return 2;
    }
    if (other_pieces->bishop & square){
        return 3;
    }
    if (other_pieces->queen & square){
        return 5;
    }
    return 0;
}



#endif