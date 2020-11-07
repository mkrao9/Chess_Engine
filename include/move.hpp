#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include "board.hpp"
#include <stdlib.h>


/* Bits: 
        0-5: Source Square
        6-11: Destination Square square 
        12-16: Special Flags 
        20-24: Piece Captures 
            1 = pawn 
            2 = rook
            3 = knight 
            4 = bishop 
            5 = queen 
        25+: ??
*/

#define FLAG_CODE(a) ((uint8_t) (a & 0xFF))
#define SOURCE(a) ((uint8_t) ((a & 0x3F00) >> 8))
#define DEST(a) ((uint8_t) ((a & 0xFC000) >> 14))
#define CAPT_PIECE(a) ((uint8_t) ((a & 0xF00000) >> 20))


#define RANK(a) (0xFFLL << a)
#define COL(a) ((0x0101010101010101LL) << a)


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


uint32_t generateAllMoves(Board *board);

uint8_t inCheck(Board* board);

bool checkHit(attack_set attack, int target_square, struct pieces other_pieces);

bool checkKnightHit(attack_set attack, int target_square, struct pieces other_pieces);

/* first 4 bits: 0 = no check, 1 = blockable check, 2 = not blockable check
   last 4 bits: code for direction, 0 = Left, 7 = down left */ 
uint8_t checkStraightCheck(attack_set attack, int target_square, struct pieces other_pieces);

void generateKingMoves(Board* board);

bool checkStraightHit(attack_set attack, int target_square, struct pieces other_pieces);

uint8_t getPieceCode(uint64_t square, pieces other_pieces);

#endif