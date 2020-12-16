#include <gtest/gtest.h>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include "../include/make_unmake.hpp"
#include <stdlib.h>


bool isBoardEqual(Board* b1, Board* b2){
    if (b1->black_king_square != b2->black_king_square)
        return false; 
    if (b1->white_king_square != b2->white_king_square)
        return false; 
    if (b1->black_pieces.bishop != b2->black_pieces.bishop)
        return false; 
    if (b1->black_pieces.king != b2->black_pieces.king)
        return false; 
    if (b1->black_pieces.knight != b2->black_pieces.knight)
        return false; 
    if (b1->black_pieces.pawn != b2->black_pieces.pawn)
        return false; 
    if (b1->black_pieces.queen != b2->black_pieces.queen)
        return false; 
    if (b1->black_pieces.rook != b2->black_pieces.rook)
        return false;
    if (b1->white_pieces.bishop != b2->white_pieces.bishop)
        return false; 
    if (b1->white_pieces.king != b2->white_pieces.king)
        return false; 
    if (b1->white_pieces.knight != b2->white_pieces.knight)
        return false; 
    if (b1->white_pieces.pawn != b2->white_pieces.pawn)
        return false; 
    if (b1->white_pieces.queen != b2->white_pieces.queen)
        return false; 
    if (b1->white_pieces.rook != b2->white_pieces.rook)
        return false;
    if (b1->white_to_move != b2->white_to_move)
        return false;
    if (b1->turn_number != b2->turn_number)
        return false;
    if (b1->full_attack_set.black_attack_set->bits != b2->full_attack_set.black_attack_set->bits)
        return false;
    if (b1->full_attack_set.white_attack_set->bits != b2->full_attack_set.white_attack_set->bits)
        return false;
    if (b1->en_pass_square != b2->en_pass_square)
        return false;
    return true;
}

bool unmakeOne(const char *fen){
    Board *b1 = new Board(fen);
    Board *b2 = new Board(fen);
    Move ml1[256];

    int num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        if (!isBoardEqual(b1, b2)){
            std::cout << "from: " << ml1[i].source << " to: " << ml1[i].dest << std::endl;
            return false;
        }
    }

    return true;
}
TEST(Unmake_Units, test_all_first_moves){
    Board *b1 = new Board();
    Board *b2 = new Board();  
    Move ml1[256];
    int num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        ASSERT_TRUE(isBoardEqual(b1, b2));
    }
}

TEST(Unmake_Units, test_ep){
    Board *b1 = new Board("rnbqkbnr/ppppp1p1/8/4Pp1p/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    Board *b2 = new Board("rnbqkbnr/ppppp1p1/8/4Pp1p/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");  
    Move ml1[256];
    int num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        ASSERT_TRUE(isBoardEqual(b1, b2));
    }

    b1 = new Board("rnbqkbnr/p1ppp1p1/8/4PpNp/1pP5/8/PP1P1PPP/RNBQKB1R b KQkq c3 0 5");
    b2 = new Board("rnbqkbnr/p1ppp1p1/8/4PpNp/1pP5/8/PP1P1PPP/RNBQKB1R b KQkq c3 0 5");

    num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        ASSERT_TRUE(isBoardEqual(b1, b2));
    }
}

TEST(Unmake_Units, test_promo){
    ASSERT_TRUE(unmakeOne("rn1qkbn1/p1P1p1p1/b2p3r/4PpNp/1p1p4/8/PP3PPP/RNBQKB1R w KQq - 1 10"));
    ASSERT_TRUE(unmakeOne("r2qkbn1/p1P1p1p1/b2pP2r/n4pNp/1p4Q1/N3K3/PP1p1PPP/R1B2B1R b q - 0 14"));
}

TEST(Unmake_Units, test_castle){
    ASSERT_TRUE(unmakeOne("r2qkbn1/p1P1p1p1/b2pP2r/n4pNp/1p4Q1/N3K3/PP1p1PPP/R1B2B1R b q - 0 14"));
    ASSERT_TRUE(unmakeOne("rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 5 4"));
}