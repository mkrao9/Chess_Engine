#ifndef _ATTACK_HPP_
#define _ATTACK_HPP_

#include "board.hpp"



void initializeAttackSet(Board* board);

void setQueen(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setBishop(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setRook(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setKnight(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setWhitePawn(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setKing(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

void setBlackPawn(attack_set *attack_set, uint8_t square, uint64_t occupied_squares);

/* used for debugging */ 

void printAttackSet(attack_set *attack_set);

#endif