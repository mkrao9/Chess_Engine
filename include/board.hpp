#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdint.h>
#include <vector>

struct Move {
    unsigned int source: 6; 
    unsigned int dest: 6; 
    unsigned int special: 3; 
    unsigned int capture: 3; 
};

/* constants for directions */ 
int constexpr LEFT_VAL = 1; 
int constexpr UP_LEFT_VAL = 9; 
int constexpr UP_VAL = 8; 
int constexpr UP_RIGHT_VAL = 7; 
int constexpr RIGHT_VAL = -1; 
int constexpr DOWN_RIGHT_VAL = -9; 
int constexpr DOWN_VAL = -8; 
int constexpr DOWN_LEFT_VAL = -7;
int constexpr N_UL_SHORT = 10; 
int constexpr N_UL_TALL= 17; 
int constexpr N_UR_TALL = 15; 
int constexpr N_UR_SHORT = 6; 
int constexpr N_DR_SHORT = -10; 
int constexpr N_DR_TALL = -17; 
int constexpr N_DL_TALL = -15; 
int constexpr N_DL_SHORT = -6; 


#define GET_N_HITS(a) ((a >> 24) & 0xFF)
#define GET_LINE_HITS(a) ((a & 0xFFFFFF))
#define SHIFT(a) (1LL << (a))


#define K_CASTLE 1
#define Q_CASTLE 2
#define EP 3
#define N_PROMO 4
#define B_PROMO 5
#define ROOK_PROMO 6
#define QUEEN_PROMO 7

typedef union {
    struct {
        unsigned int LEFT : 3;
        unsigned int UP_LEFT : 3;
        unsigned int UP : 3;
        unsigned int UP_RIGHT : 3;
        unsigned int RIGHT : 3;
        unsigned int DOWN_RIGHT : 3;
        unsigned int DOWN : 3;
        unsigned int DOWN_LEFT : 3;
        unsigned int N_UL_SHORT : 1;
        unsigned int N_UL_TALL : 1; 
        unsigned int N_UR_TALL : 1;
        unsigned int N_UR_SHORT : 1;
        unsigned int N_DR_SHORT : 1;
        unsigned int N_DR_TALL :  1;
        unsigned int N_DL_TALL : 1;
        unsigned int N_DL_SHORT : 1;
    } fields; 
    uint32_t bits;
} AttackSet;



struct NumPieces{
    uint8_t num_pawns; 
    uint8_t num_knights; 
    uint8_t num_bishops; 
    uint8_t num_rooks; 
    uint8_t num_queens; 
} __attribute__ ((__packed__));

struct Pieces {
    uint64_t pawn;
    uint64_t rook;
    uint64_t knight;
    uint64_t bishop;
    uint64_t queen;
    uint64_t king;
    NumPieces num_pieces;
} __attribute__ ((__packed__));

struct CastleRights{
    unsigned int white_q_castle : 1; 
    unsigned int white_k_castle : 1;
    unsigned int black_q_castle : 1; 
    unsigned int black_k_castle : 1;
} __attribute__ ((__packed__));

struct FullAttackSet{
    AttackSet white_attack_set[64];
    AttackSet black_attack_set[64];
} __attribute__ ((__packed__));

struct Board{
    /* pieces */

    struct Pieces white_pieces;
    struct Pieces black_pieces;

    int white_king_square; 
    int black_king_square; 


/* square-centric attack sets: 
    uint32_t attack_set[64]; 
*/  

    struct FullAttackSet full_attack_set;

    CastleRights castle_rights; 

    /* 1 << square = bit indication */
    int en_pass_square;

    /* game information */
    bool white_to_move;

    int move_since;

    bool in_check = false; 

    Move *move_list;
    uint32_t curr_num_moves;
    NumPieces num_white_pieces; 
    NumPieces num_black_pieces; 

    Pieces* current_pieces; 
    Pieces* other_pieces; 
    int current_king_square; 
    AttackSet* current_attack_set; 
    AttackSet* other_attack_set; 
    
    Board();

    Board(const char *fen);

    std::vector<uint32_t> getAllMoves();

    inline uint64_t getWhitePieces(){
        return (white_pieces.pawn | white_pieces.rook | white_pieces.knight | white_pieces.queen | white_pieces.bishop | white_pieces.king);
    }
    inline uint64_t getBlackPieces(){
        return (black_pieces.pawn | black_pieces.rook | black_pieces.knight | black_pieces.queen | black_pieces.bishop | black_pieces.king);
    }
    inline uint64_t getOccupiedSquares(){
        return getWhitePieces() | getBlackPieces();
    }
    inline uint64_t getCurrentPieces(){
        return (current_pieces->pawn | current_pieces->rook | current_pieces->knight | current_pieces->queen | current_pieces->bishop | current_pieces->king);
    }
    inline uint64_t getOtherPieces(){
        return (other_pieces->pawn | other_pieces->rook | other_pieces->knight | other_pieces->queen | other_pieces->bishop | other_pieces->king);
    }

    inline void setCurrentState(){
        if (white_to_move){
        current_pieces = &white_pieces;
        other_pieces = &black_pieces;
        current_king_square = white_king_square;
        current_attack_set = full_attack_set.white_attack_set;
        other_attack_set = full_attack_set.black_attack_set;
        }
        else{
            other_pieces = &white_pieces;
            current_pieces = &black_pieces;
            current_king_square = black_king_square;
            other_attack_set = full_attack_set.white_attack_set;
            current_attack_set = full_attack_set.black_attack_set;
        }
    }

    Board(const Board &b2){
        white_pieces = b2.white_pieces;
        black_pieces = b2.black_pieces;
        white_king_square = b2.white_king_square;
        black_king_square = b2.black_king_square;
        full_attack_set = b2.full_attack_set; 
        white_to_move = b2.white_to_move;
        castle_rights = b2.castle_rights;
        en_pass_square = b2.en_pass_square;
        setCurrentState();
    }
} __attribute__ ((__packed__));

#endif
