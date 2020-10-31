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
    ASSERT_EQ(board->getBlackPieces(), 0xFFFF000000000000) << hex << board->getBlackPieces(); 
    ASSERT_EQ(board->getWhitePieces(), 0xFFFF) << hex << board->getWhitePieces();
    ASSERT_EQ(board->getOccupiedSquares(), 0xFFFF00000000FFFF) << hex << board->getOccupiedSquares();
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