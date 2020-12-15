#include <gtest/gtest.h>
#include "../include/board.hpp"
#include "../include/make_unmake.hpp"
#include "../include/move.hpp"
#include <stdlib.h>

void printSqr(uint8_t square){
    char rank = square / 8 + '1'; 
    char file = (7 - square % 8) + 'a';
    std::cout << file; 
    std::cout << rank; 
}

void printMove(uint32_t move){
    int from = move & 0x3f; 
    int to = (move >> 6) & 0x3f; 
    int special = (move >> 12) & 0xf; 
    int capture = (move >> 20) & 0xf; 
    printSqr(from);
    std::cout << ",";
    printSqr(to);
    std::cout << " ";
}


uint32_t PerftTwoNoUnmake(const char *fen){
    // std::cout << "\n\n\n";
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
        
        // printMove(list[i]);
        // std::cout << " " << new_board->curr_num_moves << "\n";
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



uint32_t PerftFourNoUnmake(const char *fen){
    // std::cout << "\n\n\n\n";
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

        int count_a = 0;
 
        for (int j = 0; j < new_board->curr_num_moves; j++){

            Board* two_board = new Board(fen);
            makeMove(two_board, list[i]);
            makeMove(two_board, new_list[j]);
            uint32_t third_list[256];
            generateAllMoves(two_board, third_list);  

            for (int k = 0; k < two_board->curr_num_moves; k++){
                Board* three_board = new Board(fen);
                uint32_t last_list[256];
                makeMove(three_board, list[i]);
                makeMove(three_board, new_list[j]);
                makeMove(three_board, third_list[k]);
                generateAllMoves(three_board, last_list);
                count += three_board->curr_num_moves;
                count_a += three_board->curr_num_moves;
            }
        }
        // printMove(list[i]);
        // std::cout << " num: " << count_a << "\n";
    }

    return count; 
}


uint32_t P3Given(const char *fen, uint32_t move){
    // std::cout << "\n\n\n\n";
    Board *board = new Board(fen);
    makeMove(board, move);
    uint32_t list[256];
    generateAllMoves(board, list);

    uint32_t num_first_moves = board->curr_num_moves; 
    uint32_t count = 0; 

    for (int i = 0; i < num_first_moves; i++){
        Board* new_board = new Board(fen);
        makeMove(new_board, move);
        makeMove(new_board, list[i]);
        uint32_t new_list[256];
        generateAllMoves(new_board, new_list);
        int count_a = 0; 

        for (int j = 0; j < new_board->curr_num_moves; j++){

            Board* two_board = new Board(fen);
            makeMove(two_board, move);
            makeMove(two_board, list[i]);
            makeMove(two_board, new_list[j]);
            uint32_t third_list[256];
            generateAllMoves(two_board, third_list);  


            count += two_board->curr_num_moves;
            count_a += two_board->curr_num_moves;
        }


    }

    return count; 
}

uint32_t PerftThreeNoUnmake(const char *fen){
    // std::cout << "\n\n\n\n";
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
        int count_a = 0; 

        for (int j = 0; j < new_board->curr_num_moves; j++){

            Board* two_board = new Board(fen);
            makeMove(two_board, list[i]);
            makeMove(two_board, new_list[j]);
            uint32_t third_list[256];
            generateAllMoves(two_board, third_list);  

            count += two_board->curr_num_moves;
            count_a += two_board->curr_num_moves;
        }

        // printMove(list[i]);
        // std::cout << " " << count_a << "\n";

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
    ASSERT_EQ(PerftThreeNoUnmake("8/3k1Qpp/8/2P5/3b4/8/6PP/3q1B1K b - - 10 36"), 1610);
    ASSERT_EQ(PerftThreeNoUnmake("r1b1k2r/pp3ppp/1qn1p3/3pPn2/1b1P4/2N1BN2/PP1QBPPP/R3K2R b KQkq - 4 10"), 68830);
    ASSERT_EQ(PerftThreeNoUnmake("r4rk1/pp1bbppp/1qn1p3/3pP3/1P1P4/P1N1PN2/3QB1PP/R4RK1 b - - 0 14"), 64453);
    ASSERT_EQ(PerftThreeNoUnmake("2r2rk1/1pqbb1pp/4p3/1R1pN3/1P1P4/4P3/3QB1PP/5RK1 b - - 0 21"), 70922);
    ASSERT_EQ(PerftThreeNoUnmake("5rk1/1p4pp/4qb2/2Pp4/1Q1P4/3B4/6PP/5RK1 b - - 2 27"), 48446);
    ASSERT_EQ(PerftThreeNoUnmake("r5N1/pppqb3/2np1nk1/8/4P2B/2N5/PPP2PPP/R2QK2R b KQ - 0 14"), 48990);
    ASSERT_EQ(PerftThreeNoUnmake("r2qk2r/ppp1bpp1/2npBn1p/8/3NP2B/2N5/PPP2PPP/R2QK2R b KQkq - 0 9"), 47703);
    ASSERT_EQ(PerftThreeNoUnmake("7r/pppq4/2np2k1/6b1/4P3/2N2Q2/PPP2PPP/2KR3R w - - 2 18"), 6383);
    ASSERT_EQ(PerftThreeNoUnmake("r2qk2r/ppp2ppp/2nbpn2/3p1b2/8/1P1PPN2/PBP1BPPP/RN1Q1RK1 b kq - 0 7"), 64591);
    ASSERT_EQ(PerftFourNoUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 197281);
    ASSERT_EQ(PerftFourNoUnmake("2kr3r/pppq1ppp/2n5/3pPb1n/4p3/1P2P2P/PBPNBPP1/R2Q1RK1 w - - 1 13"), 1325697);
    ASSERT_EQ(PerftFourNoUnmake("r2qk2r/ppp2ppp/2nbpn2/3p1b2/8/1P2PN2/PBPPBPPP/RN1Q1RK1 w kq - 6 7"), 2274252);
    ASSERT_EQ(PerftFourNoUnmake("2kr3r/pppq1ppp/2nb1n2/3ppb2/3P4/1P2PN1P/PBPNBPP1/R2Q1RK1 b - - 0 10"), 1919391);
    ASSERT_EQ(PerftFourNoUnmake("8/PK1k1p2/6p1/3Pp3/8/8/8/7q b - - 0 56"), 44809); 
    ASSERT_EQ(PerftFourNoUnmake("8/2p2pk1/p1P3p1/P3p2p/B1P1P3/5K2/1r6/8 b - - 0 42"), 31091);
    ASSERT_EQ(PerftFourNoUnmake("r3kb1r/pppq1ppp/2n5/5b2/3P1B2/2P2N1P/P3BPP1/R2QK2R b KQkq - 2 11"), 3299142);
    ASSERT_EQ(PerftFourNoUnmake("r4rk1/ppp2ppp/2nq2B1/8/3P4/2P2N1P/P4PP1/R2Q1RK1 b - - 0 15"), 1796262);

}