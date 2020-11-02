#include <stdint.h>
#include <vector> 

struct Board{

    /* pieces */
    uint64_t white_pawn;
    uint64_t white_rook;
    uint64_t white_knight;
    uint64_t white_bishop;
    uint64_t white_queen;
    uint64_t white_king;
    uint64_t black_pawn;
    uint64_t black_rook;
    uint64_t black_knight;
    uint64_t black_bishop;
    uint64_t black_queen;
    uint64_t black_king;

    /* general board information */
    uint64_t occupied_squares;
    uint64_t white_pieces;
    uint64_t black_pieces;

    /* bits: {0 - white queen side, 1 - white king side, 2 - black queen side , 3 - black king side} */
    uint8_t castle_rights; 

    /* 1 << square = bit indication */
    uint8_t en_pass_square;

    /* game information */
    bool white_to_move;
    uint32_t turn_number; 
    uint32_t curr_ply;
    
    Board();

    /* bits 0-5: source square, bits 6-11: target square, bits 12-16: flags see https://www.chessprogramming.org/Encoding_Moves#From-To_Based for more details */
    

    /* TODO: testing framework --
        1) Convert fen -->my board position  
        2) Use stockfish -- run perf 1 
        3) Make sure the number of moves = the number of moves generated 
    */

    /* TODO: gerenate moves -- ignore optimizations 
        1) Check each piece see where it can move 
        2) If it ends with check -- end 
        3) if all end in check -- mate 
        4) Update castling rights 
        5) Update en pessant square 
    */
    std::vector<uint16_t> getAllMoves();
    

    uint64_t getWhitePieces();
    uint64_t getBlackPieces();
    uint64_t getOccupiedSquares();
};