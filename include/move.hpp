#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include "board.hpp"
#include <stdlib.h>

/* extra bits: 4 for old castle rights: 3 bits for old ep square,  3 bits for half move counter
/* Bits: 
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
    1 - double pawn push 
    2 - king side castle 
    3 - queen side castle 
    4 - ep 
    5 - knight promo 
    6 - bishop promo 
    7 - rook promo 
    8 - queen promo 
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

void generateMovesToSquare(Board *board, int to_square, uint64_t other_pieces_board);

void generateBlackPawnMoves(Board *board, int from_square, uint64_t occupied_squares);

void generateAllPawnMoves(Board *board);

void generateCastleMoves(Board* board);

uint32_t generateAllMoves(Board *board, uint32_t* move_list);

uint8_t inCheck(Board* board);

/* first 4 bits: 0 = no check, 1 = blockable check, 2 = not blockable check
   last 4 bits: code for direction, 0 = Left, 7 = down left */ 
uint8_t checkStraightCheck(attack_set attack, int target_square, pieces* other_pieces);

void generateKingMoves(Board* board, bool do_capture);

void generatePawnBlocks(Board* board, int current_square, uint64_t occupied_squares, uint64_t curr_pawns);

void generateBlockMoves(Board *board, uint8_t code);

bool leavesInCheck(Board* board, uint8_t from_square, uint8_t to_square, bool is_ep);

void generateWhitePawnMove(Board *board, int from_square, uint64_t occupied_squares);

inline bool isSameDiag(uint8_t a, uint8_t b){
   return (((a / 8) - (b / 8)) == (-1 * ((a % 8) - (b % 8))));
}

inline bool isSameAntiDiag(uint8_t a, uint8_t b){
    return (((a / 8) - (b / 8)) == ((a % 8) - (b % 8)));
}

inline void addMove(Board* board, int from, int to, uint8_t special, uint8_t capture){
    board->move_list[board->curr_num_moves] = from | (to << 6) | (special << 12) | (capture << 20);
    board->curr_num_moves++;
}

inline uint8_t getPieceCode(uint64_t square, pieces* other_pieces){
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