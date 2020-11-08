#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdint.h>
#include <vector>

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


struct pieces {
    uint64_t pawn;
    uint64_t rook;
    uint64_t knight;
    uint64_t bishop;
    uint64_t queen;
    uint64_t king;

};

struct full_attack_set{
    attack_set white_attack_set[64];
    attack_set black_attack_set[64];
};

struct Board{
    /* pieces */

    struct pieces white_pieces;
    struct pieces black_pieces;

    uint8_t white_king_square; 
    uint8_t black_king_square; 


/* square-centric attack sets: 
    uint32_t attack_set[64]; 
*/  

    struct full_attack_set full_attack_set;


    /*Another option is just having a list of moves (or maybe even just a list of origin squares?) 
        and when checking if castle check to make sure no piece has been moved && the rook is there -- might be a big 
        memory tradeoff with this though */

    /* bits: {0 - white queen side, 1 - white king side, 2 - black queen side , 3 - black king side} */
    uint8_t castle_rights; 

    /* 1 << square = bit indication */
    uint8_t en_pass_square;

    /* game information */
    bool white_to_move;
    uint32_t turn_number; 
    uint32_t move_since;

    uint32_t *move_list;
    uint32_t curr_num_moves;
    
    Board();

    Board(const char *fen);


    /* TODO: testing framework --
        2) Use a given engine -- run perf 1 
        3) Make sure the number of moves = the number of moves generated 
    */

    /* TODO: gerenate moves -- ignore optimizations 
        1) Check each piece see where it can move 
        2) If it ends with check -- end 
        3) if there are no moves -- mate  
        4) Update castling rights 
        5) Update en pessant square 
    */

    /* bits 0-5: source square, bits 6-11: target square, bits 12-16: flags see https://www.chessprogramming.org/Encoding_Moves#From-To_Based for more details */
    std::vector<uint32_t> getAllMoves();
    

    uint64_t getWhitePieces();
    uint64_t getBlackPieces();
    uint64_t getOccupiedSquares();
};

#endif
