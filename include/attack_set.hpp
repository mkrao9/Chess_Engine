#ifndef _ATTACK_HPP_
#define _ATTACK_HPP_

#include "board.hpp"



void initializeAttackSet(Board* board);

void setQueen(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setBishop(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setRook(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setKnight(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setWhitePawn(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setKing(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

void setBlackPawn(AttackSet *attack_set, uint8_t square, uint64_t occupied_squares);

/* used for debugging */ 

void printAttackSet(AttackSet *attack_set);

#endif