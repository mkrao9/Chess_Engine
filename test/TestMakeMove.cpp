#include <gtest/gtest.h>
#include "../include/board.hpp"
#include "../include/make_unmake.hpp"
#include "../include/move.hpp"
#include <stdlib.h>


uint32_t PerftTwoNoUnmake(const char *fen){
    Board *board = new Board(fen);
    uint32_t list[256];
    generateAllMoves(board, list);
    uint32_t num_first_moves = board->curr_num_moves; 
    uint32_t count = 0; 
    for (int i = 0; i < num_first_moves; i++){
        Board* new_board = new Board(fen);
        makeMove(new_board, list[i]);
        uint32_t new_list[256];
        generateAllMoves(new_board, new_list);

        count += new_board->curr_num_moves;
    }

    return count; 
}




uint8_t toInd(const char *str){
    int col = 7 - (str[0] - 'a');
    int row = str[1] - '1';
    return 8*row + col;
}


uint32_t getMove(const char *from, const char* to, uint8_t special, uint8_t capture){
    return (toInd(from) | (toInd(to) << 6) | (special << 12) | (capture << 20));
}



uint32_t PerftThreeNoUnmake(const char *fen){
    Board *board = new Board(fen);
    uint32_t list[256];
    generateAllMoves(board, list);

    uint32_t num_first_moves = board->curr_num_moves; 
    uint32_t count = 0; 

    for (int i = 0; i < num_first_moves; i++){
        Board* new_board = new Board(fen);
        makeMove(new_board, list[i]);
        uint32_t new_list[256];
        generateAllMoves(new_board, new_list);
        for (int j = 0; j < new_board->curr_num_moves; j++){
            Board* two_board = new Board(fen);
            makeMove(two_board, list[i]);
            makeMove(two_board, new_list[j]);
            
            uint32_t third_list[256];
            generateAllMoves(two_board, third_list);  

            if (two_board->curr_num_moves == 51){
                uint32_t move = list[i];
                std::cout << "from: " << (move & 0x3f) << " to: " << 
                    ((move >> 6) & 0x3f) << " special: " <<  ((move >> 12) & 0xf) << " capture: " << ((move >> 20) & 0xf) << "\n";
                move = new_list[j]; 
                std::cout << "from: " << (move & 0x3f) << " to: " << 
                    ((move >> 6) & 0x3f) << " special: " <<  ((move >> 12) & 0xf) << " capture: " << ((move >> 20) & 0xf) << "\n";

            }    
            count += two_board->curr_num_moves;
        }

    }

    return count; 
}

TEST(MakeMoveTests, board_default){
    Board* board = new Board();
    uint32_t move_list[256];
    generateAllMoves(board, move_list);
    makeMove(board, 11 | (27 << 6) | (1 << 12));
    ASSERT_NE(board->white_pieces.pawn & (SHIFT(27)), 0);
    ASSERT_EQ(board->curr_num_moves, 20);
    makeMove(board, 53 | (37 << 6) | (1 << 12));
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 30);
    makeMove(board, 1 | (18 << 6));
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 22);
    makeMove(board, 62 | (45 << 6));
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 28);
    ASSERT_EQ(PerftTwoNoUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0"), 400);
    ASSERT_EQ(PerftTwoNoUnmake("r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3"), 724);
    ASSERT_EQ(PerftTwoNoUnmake("r1bqkbnr/pp1ppppp/2n5/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 3"), 963);

    ASSERT_EQ(PerftTwoNoUnmake("r2q1rk1/1b3pbp/p2pp1p1/1p4Pn/3BP3/1BN2P2/PPPQ3P/2KR3R w - - 1 15"), 1288);
    ASSERT_EQ(PerftTwoNoUnmake("r2q1rk1/1b3pBp/p2pp1p1/1p4Pn/4P3/1BN2P2/PPPQ3P/2KR3R b - - 0 15"), 1119);
    ASSERT_EQ(PerftThreeNoUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 8902);
    ASSERT_EQ(PerftThreeNoUnmake("r1bq1rk1/1p3pbp/p2ppnp1/8/2BnP1P1/2N1BP2/PPPQ3P/2KR3R w - - 0 12"), 54605);
    // board = new Board("r1bq1rk1/1p3pbp/p2ppnp1/8/2BnP1P1/2N1BP2/PPPQ3P/2KR3R w - - 0 12");
    // generateAllMoves(board, move_list);
    // // for (int i = 0; i < board->curr_num_moves; i++){
    // //     uint32_t move = move_list[i];
    // //     std::cout << "from: " << (move & 0x3f) << " to: " << 
    // //         ((move >> 6) & 0x3f) << " special: " <<  ((move >> 12) & 0xf) << " capture: " << ((move >> 20) & 0xf) << "\n";
    // // }
    // ASSERT_EQ(board->curr_num_moves, 42);

}