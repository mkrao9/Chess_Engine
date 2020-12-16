#include <gtest/gtest.h>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include <stdlib.h>

TEST(MoveGenTests, default_board){
    Board* board = new Board(); 
    Move move_list[256];
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 20);
}

TEST(LeavesInCheckTests, basic_pin_tests){
    Board* board = new Board("k3q3/8/8/8/8/4R3/8/4K3 w - - 0 1");
    for (int i = 11; i < 64; i+=8){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), false);
    }
    for (int i = 16; i < 24; i++){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), true);
    }

    board = new Board("k3q3/8/8/4R3/8/4R3/8/4K3 w - - 0 1");
    for (int i = 16; i < 24; i++){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), false);
    }

    //same thing but flipped for black
    board = new Board("K3R3/8/8/8/8/4q3/8/4k3 b - - 0 1");
    for (int i = 11; i < 64; i+=8){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), false);
    }
    for (int i = 16; i < 24; i++){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), true);
    }

    board = new Board("k3q3/8/8/4R3/8/4R3/8/4K3 w - - 0 1");
    for (int i = 16; i < 24; i++){
        if (i == 19){
            continue;
        }
        ASSERT_EQ(leavesInCheck(board, 19, i, false), false);
    }
}

TEST(BlockGenTests, test_basic_block){
    Board* board = new Board("B3R3/6k1/N5N1/2B5/K6q/5PP1/3P4/8 w - - 0 1");
    generateBlockMoves(board, 4);
    for (int i = 0; i < board->curr_num_moves; i++){
        std::cout << "from: " <<  (board->move_list[i].source) << "to: " << ((board->move_list[i].dest) >> 6) << std::endl;
    }
    ASSERT_EQ(board->curr_num_moves, 11);
    board = new Board("b3r3/6K1/n5n1/2b5/k6Q/5pp1/3p4/8 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 7);
    board = new Board("b3r3/3p2K1/n5n1/2b2pp1/k6Q/8/8/8 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 10);
    board = new Board("b3r3/4p1K1/n5n1/2b2pp1/k6Q/8/8/8 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 9);
    board = new Board("b4r2/4p1K1/nb4n1/k6Q/8/8/8/8 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 6);
    board = new Board("b4r2/4p1K1/nb2p1n1/k6Q/8/8/8/8 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 6);
    board = new Board("b4r2/4p1K1/n3p1n1/k6Q/8/b7/8/R7 b - - 0 1");
    generateBlockMoves(board, 4);
    ASSERT_EQ(board->curr_num_moves, 5);
}

TEST(BlockGenTests, block_promo_test){
    Board* board = new Board("r6K/3P4/8/8/8/8/8/5k2 w - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 4);
    board = new Board("4r2K/3P4/8/8/8/8/8/5k2 w - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 4);
    board = new Board("4r2K/3p4/8/8/8/8/8/5k2 w - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 0);
    board = new Board("4r2K/1P6/8/8/8/8/8/5k2 w - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 0);
    board = new Board("7K/8/8/8/8/8/4p3/R6k b - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 4);
    board = new Board("7K/8/8/8/8/8/4p3/5R1k b - - 0 1");
    generateBlockMoves(board, 0);
    ASSERT_EQ(board->curr_num_moves, 4);
}

void checkMove(const char * str, int num){
    Board* board = new Board(str);
    Move move_list[256];
    generateAllMoves(board, move_list);
    if (board->curr_num_moves != num){
        for (int i = 0; i < board->curr_num_moves; i++){
            std::cout << "from: " << (board->move_list[i].source) << " to: " << board->move_list[i].dest << "\n";
        }
    }
    ASSERT_EQ(board->curr_num_moves, num);
}

TEST(EPTests, gen_ep_tests){
    Move move_list[256];
    Board* board = new Board("3k4/8/8/4pP2/8/8/8/3K4 w - e6 0 2");
    generateMovesToSquare(board, 43, board->getOtherPieces());
    ASSERT_EQ(board->curr_num_moves, 1);
    board = new Board("3k4/8/8/4pP2/8/8/8/3K4 w - - 0 2");
    generateMovesToSquare(board, 43, board->getOtherPieces());
    ASSERT_EQ(board->curr_num_moves, 0);
    board = new Board("3k4/8/8/8/4pP2/8/8/1K6 b - f3 0 1");
    generateMovesToSquare(board, 18, board->getOtherPieces());
    ASSERT_EQ(board->curr_num_moves, 1);
    board = new Board("8/8/8/1K4k1/6pP/8/8/8 b - h3 0 1");
    generateBlockMoves(board, 5);
    ASSERT_EQ(board->curr_num_moves, 2);
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 8);
    board = new Board("8/8/8/k4PpP/5K2/8/8/8 w - g6 0 2");
    generateBlockMoves(board, 3);
    ASSERT_EQ(board->curr_num_moves, 3);
    board = new Board("8/8/8/k5Pp/6K1/8/8/8 w - h6 0 2");
    generateBlockMoves(board, 3);
    ASSERT_EQ(board->curr_num_moves, 2);
    board = new Board("4k3/8/8/1K2Pp1q/8/8/8/8 w - f6 0 2");
    ASSERT_TRUE(leavesInCheck(board, 35, 42, true));
}

TEST(MoveGenTests, game_one){
    Move move_list[256];
    Board* board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 20);
    board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 30);
    board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 22);

    board = new Board("r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 28);

    board = new Board("r1bqkbnr/pp1ppppp/2n5/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 3");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 27);

    board = new Board("r1bqkbnr/pp1ppppp/2n5/8/3pP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 4");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 37);

    board = new Board("r1bqkbnr/pp1ppppp/2n5/8/3NP3/8/PPP2PPP/RNBQKB1R b KQkq - 0 4");
    generateAllMoves(board, move_list);
    ASSERT_EQ(board->curr_num_moves, 25);

    checkMove("r1bqkbnr/pp1p1ppp/2n1p3/8/3NP3/8/PPP2PPP/RNBQKB1R w KQkq - 0 5", 42);
    checkMove("r1bqkbnr/pp1p1ppp/2n1p3/8/3NP3/4B3/PPP2PPP/RN1QKB1R b KQkq - 1 5", 36);
    checkMove("r1bqkb1r/pp1pnppp/2n1p3/8/3NP3/4B3/PPP2PPP/RN1QKB1R w KQkq - 2 6", 43);
    checkMove("r1bqkb1r/pp1pnppp/2n1p3/8/3NP3/2N1B3/PPP2PPP/R2QKB1R b KQkq - 3 6", 27);
    checkMove("r1bqkb1r/pp1pnp1p/2n1p1p1/8/3NP3/2N1B3/PPP2PPP/R2QKB1R w KQkq - 0 7", 46);
    checkMove("r1bqkb1r/pp1pnp1p/2n1p1p1/8/3NP3/2N1BP2/PPP3PP/R2QKB1R b KQkq - 0 7", 27);
    checkMove("r1bqk2r/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP3PP/R2QKB1R w KQkq - 1 8", 44);
    checkMove("r1bqk2r/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2QK2R b KQkq - 2 8", 33);
    checkMove("r1bq1rk1/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2QK2R w KQ - 3 9", 43);
    checkMove("r1bq1rk1/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2Q1RK1 b - - 4 9", 31);
    checkMove("r1bq1rk1/1p1pnpbp/p1n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2Q1RK1 w - - 0 10", 40);
    checkMove("r1bq1rk1/1p1pnpbp/p1n1p1p1/8/P2NP3/2N1BP2/1PP1B1PP/R2Q1RK1 b - - 0 10", 32);
    checkMove("r1bq1rk1/1p2npbp/p1n1p1p1/3p4/P2NP3/2N1BP2/1PP1B1PP/R2Q1RK1 w - - 0 11", 42);
    checkMove("r1bq1rk1/1p2npbp/p1n1p1p1/3P4/P2N4/2N1BP2/1PP1B1PP/R2Q1RK1 b - - 0 11", 35);
    checkMove("r1bq1rk1/1p3pbp/p1n1p1p1/3n4/P2N4/2N1BP2/1PP1B1PP/R2Q1RK1 w - - 0 12", 41);
    checkMove("r1bq1rk1/1p3pbp/p1n1p1p1/3N4/P2N4/4BP2/1PP1B1PP/R2Q1RK1 b - - 0 12", 38);
    checkMove("r1b2rk1/1p3pbp/p1n1p1p1/3q4/P2N4/4BP2/1PP1B1PP/R2Q1RK1 w - - 0 13", 38);
    checkMove("r1b2rk1/1p3pbp/p1N1p1p1/3q4/P7/4BP2/1PP1B1PP/R2Q1RK1 b - - 0 13", 43);
    checkMove("r1b2rk1/1p3pbp/p1q1p1p1/8/P7/4BP2/1PP1B1PP/R2Q1RK1 w - - 0 14", 42);
    checkMove("r1b2rk1/1p3pbp/p1q1p1p1/8/P7/2P1BP2/1P2B1PP/R2Q1RK1 b - - 0 14", 34);
    checkMove("r4rk1/1p1b1pbp/p1q1p1p1/8/P2B4/2P2P2/1P2B1PP/R2Q1RK1 b - - 2 15", 38);
    checkMove("r4rk1/1p1b1pbp/p1q3p1/4p3/P2B4/2P2P2/1P2B1PP/R2Q1RK1 w - - 0 16", 34);
    checkMove("r4rk1/1p1b1pbp/p1q3p1/4p3/P7/2P1BP2/1P2B1PP/R2Q1RK1 b - - 1 16", 42);
    checkMove("r4rk1/1p3pbp/pq4p1/8/P4B2/2P2R2/1P4PP/R2Q2K1 w - - 1 21", 6);
    checkMove("r2r2k1/1p3pbp/p5p1/2B5/P7/2q2R2/6PP/R4QK1 w - - 0 24", 43);
    checkMove("3r3k/1pR3Qp/pB4p1/8/P7/3r4/6PP/6K1 b - - 0 29", 0);
}