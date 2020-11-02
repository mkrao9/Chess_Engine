#include <gtest/gtest.h>
#include "../include/board.hpp"
#include <stdlib.h>



void checkNoOverlap(Board *board);

using namespace std;

TEST(BoardTests, board_default){
    Board *board = new Board();
    checkNoOverlap(board);
    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, true);
    ASSERT_EQ(board->turn_number, 1);
    ASSERT_EQ(board->white_pawn, (0xff << 8));
    ASSERT_EQ(board->getBlackPieces(), 0xFFFF000000000000) << hex << board->getBlackPieces(); 
    ASSERT_EQ(board->getWhitePieces(), 0xFFFF) << hex << board->getWhitePieces();
    ASSERT_EQ(board->getOccupiedSquares(), 0xFFFF00000000FFFF) << hex << board->getOccupiedSquares();
}
TEST(BoardTests, fen_test_default){
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, true);
    ASSERT_EQ(board->turn_number, 1);
    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights, 15);
    ASSERT_EQ(board->white_pawn, (0xFF << 8));
    ASSERT_EQ(board->white_rook, 0x81);
    ASSERT_EQ(board->white_bishop, 0x24);
    ASSERT_EQ(board->white_knight, 0x42);
    ASSERT_EQ(board->white_queen, 0x10);
    ASSERT_EQ(board->white_king, 0x08);
    ASSERT_EQ(board->black_pawn, (board->white_pawn << 40));
    ASSERT_EQ(board->black_rook, (board->white_rook << 56));
    ASSERT_EQ(board->black_knight, (board->white_knight << 56));
    ASSERT_EQ(board->black_queen, (board->white_queen << 56));
    ASSERT_EQ(board->black_king, (board->white_king << 56));
}
TEST(BoardTests, fen_test_1e4){
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 19);
    ASSERT_EQ(board->white_to_move, false);
    ASSERT_EQ(board->turn_number, 1);
    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights, 15);
    ASSERT_EQ(board->white_pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_rook, 0x81);
    ASSERT_EQ(board->white_bishop, 0x24);
    ASSERT_EQ(board->white_knight, 0x42);
    ASSERT_EQ(board->white_queen, 0x10);
    ASSERT_EQ(board->white_king, 0x08);
    ASSERT_EQ(board->black_pawn, (0xffLL << 48));
    ASSERT_EQ(board->black_rook, (board->white_rook << 56));
    ASSERT_EQ(board->black_knight, (board->white_knight << 56));
    ASSERT_EQ(board->black_queen, (board->white_queen << 56));
    ASSERT_EQ(board->black_king, (board->white_king << 56));
}
TEST(BoardTests, fen_test_1e4_c5){
    Board *board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 45);
    ASSERT_EQ(board->white_to_move, true);
    ASSERT_EQ(board->turn_number, 2);
    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights, 15);
    ASSERT_EQ(board->white_pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_rook, 0x81);
    ASSERT_EQ(board->white_bishop, 0x24);
    ASSERT_EQ(board->white_knight, 0x42);
    ASSERT_EQ(board->white_queen, 0x10);
    ASSERT_EQ(board->white_king, 0x08);
    ASSERT_EQ(board->black_pawn, (0xffLL << 48) & ~ SHIFT(53) | SHIFT(37));
    ASSERT_EQ(board->black_rook, (board->white_rook << 56));
    ASSERT_EQ(board->black_knight, (board->white_knight << 56));
    ASSERT_EQ(board->black_queen, (board->white_queen << 56));
    ASSERT_EQ(board->black_king, (board->white_king << 56));
}
TEST(BoardTests, fen_test_1e4_c5_2nf3){
    Board *board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, false);
    ASSERT_EQ(board->turn_number, 2);
    ASSERT_EQ(board->move_since, 1);
    ASSERT_EQ(board->castle_rights, 15);
    ASSERT_EQ(board->white_pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_rook, 0x81);
    ASSERT_EQ(board->white_bishop, 0x24);
    ASSERT_EQ(board->white_knight, SHIFT(6) | SHIFT(18));
    ASSERT_EQ(board->white_queen, 0x10);
    ASSERT_EQ(board->white_king, 0x08);
    ASSERT_EQ(board->black_pawn, (0xffLL << 48) & ~ SHIFT(53) | SHIFT(37));
    ASSERT_EQ(board->black_rook, (board->white_rook << 56));
    ASSERT_EQ(board->black_knight, SHIFT(62) | SHIFT(57));
    ASSERT_EQ(board->black_queen, (board->white_queen << 56));
    ASSERT_EQ(board->black_king, (board->white_king << 56));
}
TEST(BoardTests, fen_test_random_board){
    Board *board = new Board("r2r4/pp1qkQ2/2p3nB/4P3/P2P4/1BP5/2K2P2/7R b - - 17 74");
    ASSERT_EQ(board->castle_rights, 0);
    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, false);
    ASSERT_EQ(board->turn_number, 74);
    ASSERT_EQ(board->move_since, 17);
    ASSERT_EQ(board->white_pawn, SHIFT(10) | SHIFT(21) | SHIFT(28) | SHIFT(31) | SHIFT(35));
    ASSERT_EQ(board->white_knight, 0);
    ASSERT_EQ(board->white_rook, SHIFT(0));
    ASSERT_EQ(board->white_bishop, SHIFT(22) | SHIFT(40));
    ASSERT_EQ(board->white_king, SHIFT(13));
    ASSERT_EQ(board->white_queen, SHIFT(50));
    ASSERT_EQ(board->black_pawn, SHIFT(55) | SHIFT(54) | SHIFT(45));
    ASSERT_EQ(board->black_rook, SHIFT(63) | SHIFT(60));
    ASSERT_EQ(board->black_bishop, 0);
    ASSERT_EQ(board->black_knight, SHIFT(41));
    ASSERT_EQ(board->black_queen, SHIFT(52));
    ASSERT_EQ(board->black_king, SHIFT(51));
}

void checkNoOverlap(Board *board){
    /* push every piece */ 
    vector<uint64_t> piece_list;
    piece_list.push_back(board->white_pawn);     //0
    piece_list.push_back(board->white_rook);     //1 
    piece_list.push_back(board->white_knight);   //2
    piece_list.push_back(board->white_bishop);   //3
    piece_list.push_back(board->white_queen);    //4
    piece_list.push_back(board->white_king);     //5
    piece_list.push_back(board->black_pawn);     //6
    piece_list.push_back(board->black_rook);     //7
    piece_list.push_back(board->black_knight);   //8
    piece_list.push_back(board->black_bishop);   //9
    piece_list.push_back(board->black_queen);    //10
    piece_list.push_back(board->black_king);     //11

    /* compare each pieceset with every other one -- makes sure no overlap*/
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            if (i == j)
                continue;
            GTEST_ASSERT_EQ(piece_list[i] & piece_list[j], 0) << "i: " << i << ", " 
                << hex << piece_list[i] << "; j: " << j << ", " << hex << piece_list[j] << "\n";
        }
    }
}