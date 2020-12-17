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
 
    ASSERT_EQ(board->white_pieces.pawn, (0xff << 8));
    ASSERT_EQ(board->getBlackPieces(), 0xFFFF000000000000) << hex << board->getBlackPieces(); 
    ASSERT_EQ(board->getWhitePieces(), 0xFFFF) << hex << board->getWhitePieces();
    ASSERT_EQ(board->getOccupiedSquares(), 0xFFFF00000000FFFF) << hex << board->getOccupiedSquares();
}
TEST(BoardTests, fen_test_default){
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, true);
    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights.black_k_castle, 1);
    ASSERT_EQ(board->castle_rights.black_q_castle, 1);
    ASSERT_EQ(board->castle_rights.white_k_castle, 1);
    ASSERT_EQ(board->castle_rights.white_q_castle, 1);
    ASSERT_EQ(board->white_pieces.pawn, (0xFF << 8));
    ASSERT_EQ(board->white_pieces.rook, 0x81);
    ASSERT_EQ(board->white_pieces.bishop, 0x24);
    ASSERT_EQ(board->white_pieces.knight, 0x42);
    ASSERT_EQ(board->white_pieces.queen, 0x10);
    ASSERT_EQ(board->white_pieces.king, 0x08);
    ASSERT_EQ(board->black_pieces.pawn, (board->white_pieces.pawn << 40));
    ASSERT_EQ(board->black_pieces.rook, (board->white_pieces.rook << 56));
    ASSERT_EQ(board->black_pieces.knight, (board->white_pieces.knight << 56));
    ASSERT_EQ(board->black_pieces.queen, (board->white_pieces.queen << 56));
    ASSERT_EQ(board->black_pieces.king, (board->white_pieces.king << 56));
}
TEST(BoardTests, fen_test_1e4){
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 19);
    ASSERT_EQ(board->white_to_move, false);

    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights.black_k_castle, 1);
    ASSERT_EQ(board->castle_rights.black_q_castle, 1);
    ASSERT_EQ(board->castle_rights.white_k_castle, 1);
    ASSERT_EQ(board->castle_rights.white_q_castle, 1);
    ASSERT_EQ(board->white_pieces.pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_pieces.rook, 0x81);
    ASSERT_EQ(board->white_pieces.bishop, 0x24);
    ASSERT_EQ(board->white_pieces.knight, 0x42);
    ASSERT_EQ(board->white_pieces.queen, 0x10);
    ASSERT_EQ(board->white_pieces.king, 0x08);
    ASSERT_EQ(board->black_pieces.pawn, (0xffLL << 48));
    ASSERT_EQ(board->black_pieces.rook, (board->white_pieces.rook << 56));
    ASSERT_EQ(board->black_pieces.knight, (board->white_pieces.knight << 56));
    ASSERT_EQ(board->black_pieces.queen, (board->white_pieces.queen << 56));
    ASSERT_EQ(board->black_pieces.king, (board->white_pieces.king << 56));
}
TEST(BoardTests, fen_test_1e4_c5){
    Board *board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 45);
    ASSERT_EQ(board->white_to_move, true);
    ASSERT_EQ(board->move_since, 0);
    ASSERT_EQ(board->castle_rights.black_k_castle, 1);
    ASSERT_EQ(board->castle_rights.black_q_castle, 1);
    ASSERT_EQ(board->castle_rights.white_k_castle, 1);
    ASSERT_EQ(board->castle_rights.white_q_castle, 1);
    ASSERT_EQ(board->white_pieces.pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_pieces.rook, 0x81);
    ASSERT_EQ(board->white_pieces.bishop, 0x24);
    ASSERT_EQ(board->white_pieces.knight, 0x42);
    ASSERT_EQ(board->white_pieces.queen, 0x10);
    ASSERT_EQ(board->white_pieces.king, 0x08);
    ASSERT_EQ(board->black_pieces.pawn, (0xffLL << 48) & ~ SHIFT(53) | SHIFT(37));
    ASSERT_EQ(board->black_pieces.rook, (board->white_pieces.rook << 56));
    ASSERT_EQ(board->black_pieces.knight, (board->white_pieces.knight << 56));
    ASSERT_EQ(board->black_pieces.queen, (board->white_pieces.queen << 56));
    ASSERT_EQ(board->black_pieces.king, (board->white_pieces.king << 56));
}
TEST(BoardTests, fen_test_1e4_c5_2nf3){
    Board *board = new Board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"); 

    checkNoOverlap(board);

    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, false);

    ASSERT_EQ(board->move_since, 1);
    ASSERT_EQ(board->castle_rights.black_k_castle, 1);
    ASSERT_EQ(board->castle_rights.black_q_castle, 1);
    ASSERT_EQ(board->castle_rights.white_k_castle, 1);
    ASSERT_EQ(board->castle_rights.white_q_castle, 1);
    ASSERT_EQ(board->white_pieces.pawn, ((0xFF << 8) & ~ SHIFT(11)) | SHIFT(27) );
    ASSERT_EQ(board->white_pieces.rook, 0x81);
    ASSERT_EQ(board->white_pieces.bishop, 0x24);
    ASSERT_EQ(board->white_pieces.knight, SHIFT(6) | SHIFT(18));
    ASSERT_EQ(board->white_pieces.queen, 0x10);
    ASSERT_EQ(board->white_pieces.king, 0x08);
    ASSERT_EQ(board->black_pieces.pawn, (0xffLL << 48) & ~ SHIFT(53) | SHIFT(37));
    ASSERT_EQ(board->black_pieces.rook, (board->white_pieces.rook << 56));
    ASSERT_EQ(board->black_pieces.knight, SHIFT(62) | SHIFT(57));
    ASSERT_EQ(board->black_pieces.queen, (board->white_pieces.queen << 56));
    ASSERT_EQ(board->black_pieces.king, (board->white_pieces.king << 56));
}
TEST(BoardTests, fen_test_random_board){
    Board *board = new Board("r2r4/pp1qkQ2/2p3nB/4P3/P2P4/1BP5/2K2P2/7R b - - 17 74");
    ASSERT_EQ(board->castle_rights.white_k_castle, 0);
    ASSERT_EQ(board->castle_rights.black_k_castle, 0);
    ASSERT_EQ(board->castle_rights.black_q_castle, 0);
    ASSERT_EQ(board->castle_rights.white_q_castle, 0);
    ASSERT_EQ(board->en_pass_square, 0);
    ASSERT_EQ(board->white_to_move, false);
    ASSERT_EQ(board->move_since, 17);
    ASSERT_EQ(board->white_pieces.pawn, SHIFT(10) | SHIFT(21) | SHIFT(28) | SHIFT(31) | SHIFT(35));
    ASSERT_EQ(board->white_pieces.knight, 0);
    ASSERT_EQ(board->white_pieces.rook, SHIFT(0));
    ASSERT_EQ(board->white_pieces.bishop, SHIFT(22) | SHIFT(40));
    ASSERT_EQ(board->white_pieces.king, SHIFT(13));
    ASSERT_EQ(board->white_pieces.queen, SHIFT(50));
    ASSERT_EQ(board->black_pieces.pawn, SHIFT(55) | SHIFT(54) | SHIFT(45));
    ASSERT_EQ(board->black_pieces.rook, SHIFT(63) | SHIFT(60));
    ASSERT_EQ(board->black_pieces.bishop, 0);
    ASSERT_EQ(board->black_pieces.knight, SHIFT(41));
    ASSERT_EQ(board->black_pieces.queen, SHIFT(52));
    ASSERT_EQ(board->black_pieces.king, SHIFT(51));
}

void checkNoOverlap(Board *board){
    /* push every piece */ 
    vector<uint64_t> piece_list;
    piece_list.push_back(board->white_pieces.pawn);     //0
    piece_list.push_back(board->white_pieces.rook);     //1 
    piece_list.push_back(board->white_pieces.knight);   //2
    piece_list.push_back(board->white_pieces.bishop);   //3
    piece_list.push_back(board->white_pieces.queen);    //4
    piece_list.push_back(board->white_pieces.king);     //5
    piece_list.push_back(board->black_pieces.pawn);     //6
    piece_list.push_back(board->black_pieces.rook);     //7
    piece_list.push_back(board->black_pieces.knight);   //8
    piece_list.push_back(board->black_pieces.bishop);   //9
    piece_list.push_back(board->black_pieces.queen);    //10
    piece_list.push_back(board->black_pieces.king);     //11

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