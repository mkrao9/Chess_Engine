#include <gtest/gtest.h>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include <stdlib.h>

TEST(CheckTests, board_default){
    Board *board = new Board(); 
    ASSERT_EQ(inCheck(board), 0);
}

/* https://lichess.org/9DaNnx7g/white#57*/ 
TEST(CheckTests, game_one){
    Board *board = new Board("3r3k/1pR3Qp/pB4p1/8/P7/3r4/6PP/6K1 b - - 0 29");
    ASSERT_EQ(inCheck(board), 1 | (7 << 4));
}

/* https://lichess.org/D4YGXjbK/white#8 */
TEST(CheckTests, game_two){
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
    ASSERT_EQ(inCheck(board), 0);
    board = new Board("rnb1kb1r/ppp1pppp/5n2/q7/3P4/2N5/PPP2PPP/R1BQKBNR w KQkq - 1 5");
    ASSERT_EQ(inCheck(board), 0);
    board = new Board("r3kb1r/1pp1pppp/p1q2n2/8/3P2b1/2B2NN1/PPP2PPP/R2QK2R b KQkq - 1 11");
    ASSERT_EQ(inCheck(board), 0);
    board = new Board("2kr3r/1pp3pp/p3pp2/8/3PNP2/b1P5/P1P2P1P/2KR2R1 w - - 1 19");
    ASSERT_EQ(inCheck(board), 1 | (1 << 4));
    board = new Board("2k3r1/1pp3pp/p3pp2/8/3P1P2/b1P3N1/P1P2P1P/Kr4R1 w - - 0 23");
    ASSERT_EQ(inCheck(board), 1 | (4 << 4));
    board = new Board("5b2/6pp/p1k2p2/1P3P2/3KN3/5P2/7P/8 b - - 0 37");
    ASSERT_EQ(inCheck(board), 1 | (7 << 4));
    board = new Board("8/6pp/2k2p2/1pb2P2/3K4/2N2P2/7P/8 w - - 2 39");
    ASSERT_EQ(inCheck(board), 1 | (1 << 4));
    board = new Board("8/7p/5p2/5P1N/1p6/1Kb3kP/8/8 b - - 2 51");
    ASSERT_EQ(inCheck(board), 2);
    board = new Board("8/8/2K1q3/8/3k4/8/8/8 w - - 10 68");
    ASSERT_EQ(inCheck(board), 1 | (4 << 4));
    board = new Board("8/2K5/4q3/2k5/8/8/8/8 w - - 12 69");
    ASSERT_EQ(inCheck(board), 0);
}

TEST(CheckTests, double_check_test){
    Board* board = new Board("rnbk1b1r/pp3ppp/2p5/4q1B1/4n3/8/PPP2PPP/2KR1BNR b - - 1 10");
    ASSERT_EQ(inCheck(board), 2);
}

/* https://lichess.org/D4YGXjbK/white#36 */
/* a lot of these tests assume that i'm generating moves in the same directions that is coded right now -- will fail if i change the order*/ 
TEST(GenerateKingMoves, game_one){
    Board* board = new Board("2kr3r/1pp3pp/p3pp2/8/3PNP2/b1P5/P1P2P1P/2KR2R1 w - - 1 19");
    generateKingMoves(board);
    ASSERT_EQ(board->curr_num_moves, 2);
    ASSERT_EQ(board->move_list[0], 5 | (6 << 6));
    ASSERT_EQ(board->move_list[1], 5 | (12 << 6));
    board = new Board("2k3r1/1pp3pp/p3pp2/8/3P1P2/b1P3N1/P1P2P1P/Kr4R1 w - - 0 23");
    generateKingMoves(board);
    ASSERT_EQ(board->curr_num_moves, 1);  
    ASSERT_EQ(board->move_list[0], 7 | (6 << 6) | (2 << 20));
    board = new Board("5b2/6pp/p1k2p2/1P3P2/3KN3/5P2/7P/8 b - - 0 37");
    generateKingMoves(board);
    ASSERT_EQ(board->curr_num_moves, 5);
    ASSERT_EQ(board->move_list[0], 45 | (53 << 6));
    ASSERT_EQ(board->move_list[1], 45 | (46 << 6));
    ASSERT_EQ(board->move_list[2], 45 | (54 << 6));
    ASSERT_EQ(board->move_list[3], 45 | (52 << 6));
    ASSERT_EQ(board->move_list[4], 45 | (38 << 6) | (1 << 20));
    board = new Board("8/6pp/2k2p2/1pb2P2/3K4/2N2P2/7P/8 w - - 2 39");
    generateKingMoves(board);
    for (int i = 0; i < board->curr_num_moves; i++){
        std::cout << "to: " << ((board->move_list[i] & (0x3f << 6)) >> 6) << "\n";
    }
    ASSERT_EQ(board->curr_num_moves, 2);



    ASSERT_EQ(board->move_list[0], 28 | (20 << 6));
    ASSERT_EQ(board->move_list[1], 28 | (27 << 6));

}