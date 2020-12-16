#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdint.h>
#include <vector>

struct Move {
    unsigned int source: 6; 
    unsigned int dest: 6; 
    unsigned int special: 4; 
    unsigned int capture: 4; 
    unsigned int old_ep: 4; /*Bit 3: whether or not there was ep; rest: col (0 = h file, 7 = a file) */
    unsigned int old_castle: 2; 
    unsigned int old_half_move: 6;
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
#define SHIFT(a) (1LL << a)

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
} attack_set;


struct Pieces {
    uint64_t pawn;
    uint64_t rook;
    uint64_t knight;
    uint64_t bishop;
    uint64_t queen;
    uint64_t king;
} __attribute__ ((__packed__));

struct CastleRights{
    unsigned int white_q_castle : 1; 
    unsigned int white_k_castle : 1;
    unsigned int black_q_castle : 1; 
    unsigned int black_k_castle : 1;
} __attribute__ ((__packed__));

struct FullAttackSet{
    attack_set white_attack_set[64];
    attack_set black_attack_set[64];
} __attribute__ ((__packed__));

struct Board{
    /* pieces */

    struct Pieces white_pieces;
    struct Pieces black_pieces;

    uint8_t white_king_square; 
    uint8_t black_king_square; 


/* square-centric attack sets: 
    uint32_t attack_set[64]; 
*/  

    struct FullAttackSet full_attack_set;

    CastleRights castle_rights; 

    /* 1 << square = bit indication */
    uint8_t en_pass_square;

    /* game information */
    bool white_to_move;
    uint32_t turn_number; 
    uint32_t move_since;

    Move *move_list;
    uint32_t curr_num_moves;

    Pieces* current_pieces; 
    Pieces* other_pieces; 
    int current_king_square; 
    attack_set* current_attack_set; 
    attack_set* other_attack_set; 
    
    uint8_t old_ep; 
    uint8_t old_castle; 
    uint8_t old_half_move; 
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
