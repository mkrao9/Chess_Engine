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

    if (b1->castle_rights.black_k_castle != b2->castle_rights.black_k_castle)
        return false; 
    if (b1->castle_rights.black_q_castle != b2->castle_rights.black_q_castle)
        return false; 
    if (b1->castle_rights.white_k_castle != b2->castle_rights.white_k_castle)
        return false; 
    if (b1->castle_rights.white_q_castle != b2->castle_rights.white_q_castle)
        return false;         
    for (int i = 0; i < 64; i++){
        if (b1->full_attack_set.black_attack_set[i].bits != b2->full_attack_set.black_attack_set[i].bits)
            return false;
        if (b1->full_attack_set.white_attack_set[i].bits != b2->full_attack_set.white_attack_set[i].bits)
            return false;
    }

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
        int old_ep = b1->en_pass_square; 
        int old_moves_since = b1->move_since; 
        CastleRights old_castle_rights = b1->castle_rights; 
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        b1->en_pass_square = old_ep; 
        b1->move_since = old_moves_since;
        b1->castle_rights = old_castle_rights;
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
        int old_ep = b1->en_pass_square; 
        int old_moves_since = b1->move_since; 
        CastleRights old_castle_rights = b1->castle_rights; 
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        b1->en_pass_square = old_ep; 
        b1->move_since = old_moves_since;
        b1->castle_rights = old_castle_rights;

        ASSERT_TRUE(isBoardEqual(b1, b2));
    }
}

TEST(Unmake_Units, test_ep){
    Board *b1 = new Board("rnbqkbnr/ppppp1p1/8/4Pp1p/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    Board *b2 = new Board("rnbqkbnr/ppppp1p1/8/4Pp1p/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");  
    Move ml1[256];
    int num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        int old_ep = b1->en_pass_square; 
        int old_moves_since = b1->move_since; 
        CastleRights old_castle_rights = b1->castle_rights; 
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        b1->en_pass_square = old_ep; 
        b1->move_since = old_moves_since;
        b1->castle_rights = old_castle_rights;
        ASSERT_TRUE(isBoardEqual(b1, b2));
    }

    b1 = new Board("rnbqkbnr/p1ppp1p1/8/4PpNp/1pP5/8/PP1P1PPP/RNBQKB1R b KQkq c3 0 5");
    b2 = new Board("rnbqkbnr/p1ppp1p1/8/4PpNp/1pP5/8/PP1P1PPP/RNBQKB1R b KQkq c3 0 5");

    num_moves = generateAllMoves(b1, ml1);
    for (int i = 0; i < num_moves; i++){
        int old_ep = b1->en_pass_square; 
        int old_moves_since = b1->move_since; 
        CastleRights old_castle_rights = b1->castle_rights; 
        makeMove(b1, ml1[i]);
        unmakeMove(b1, ml1[i]);
        b1->en_pass_square = old_ep; 
        b1->move_since = old_moves_since;
        b1->castle_rights = old_castle_rights;
        std::cout << "from: " << ml1[i].source << " to: " << ml1[i].dest << std::endl; 
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
    ASSERT_TRUE(unmakeOne("r3kbnr/ppp1pppp/2nq4/3p1b2/3P1B2/2NQ4/PPP1PPPP/R3KBNR w KQkq - 6 5"));
    ASSERT_TRUE(unmakeOne("r3kbnr/ppp1pppp/2nq4/3p1b2/3P1B2/2NQ4/PPP1PPPP/2KR1BNR b kq - 7 5"));
}

TEST(Unmake_Units, random_positions){
    ASSERT_TRUE(unmakeOne("B3R3/6k1/N5N1/2B5/K6q/5PP1/3P4/8 w - - 0 1"));
    ASSERT_TRUE(unmakeOne("b4r2/4p1K1/nb4n1/k6Q/8/8/8/8 b - - 0 1"));
    ASSERT_TRUE(unmakeOne("7K/8/8/8/8/8/4p3/5R1k b - - 0 1"));
    ASSERT_TRUE(unmakeOne("3k4/8/8/4pP2/8/8/8/3K4 w - e6 0 2"));
    ASSERT_TRUE(unmakeOne("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    ASSERT_TRUE(unmakeOne("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2"));
    ASSERT_TRUE(unmakeOne("r1bqkbnr/pp1ppppp/2n5/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 3"));
    ASSERT_TRUE(unmakeOne("r1bqkbnr/pp1p1ppp/2n1p3/8/3NP3/8/PPP2PPP/RNBQKB1R w KQkq - 0 5"));
    ASSERT_TRUE(unmakeOne("r1bqkbnr/pp1p1ppp/2n1p3/8/3NP3/4B3/PPP2PPP/RN1QKB1R b KQkq - 1 5"));
    ASSERT_TRUE(unmakeOne("r1bqkb1r/pp1pnppp/2n1p3/8/3NP3/4B3/PPP2PPP/RN1QKB1R w KQkq - 2 6"));
    ASSERT_TRUE(unmakeOne("r1bqkb1r/pp1pnppp/2n1p3/8/3NP3/2N1B3/PPP2PPP/R2QKB1R b KQkq - 3 6"));
    ASSERT_TRUE(unmakeOne("r1bqkb1r/pp1pnp1p/2n1p1p1/8/3NP3/2N1B3/PPP2PPP/R2QKB1R w KQkq - 0 7"));
    ASSERT_TRUE(unmakeOne("r1bqkb1r/pp1pnp1p/2n1p1p1/8/3NP3/2N1BP2/PPP3PP/R2QKB1R b KQkq - 0 7"));
    ASSERT_TRUE(unmakeOne("r1bqk2r/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP3PP/R2QKB1R w KQkq - 1 8"));
    ASSERT_TRUE(unmakeOne("r1bqk2r/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2QK2R b KQkq - 2 8"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2QK2R w KQ - 3 9"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/pp1pnpbp/2n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2Q1RK1 b - - 4 9"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p1pnpbp/p1n1p1p1/8/3NP3/2N1BP2/PPP1B1PP/R2Q1RK1 w - - 0 10"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p1pnpbp/p1n1p1p1/8/P2NP3/2N1BP2/1PP1B1PP/R2Q1RK1 b - - 0 10"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p2npbp/p1n1p1p1/3p4/P2NP3/2N1BP2/1PP1B1PP/R2Q1RK1 w - - 0 11"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p2npbp/p1n1p1p1/3P4/P2N4/2N1BP2/1PP1B1PP/R2Q1RK1 b - - 0 11"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p3pbp/p1n1p1p1/3n4/P2N4/2N1BP2/1PP1B1PP/R2Q1RK1 w - - 0 12"));
    ASSERT_TRUE(unmakeOne("r1bq1rk1/1p3pbp/p1n1p1p1/3N4/P2N4/4BP2/1PP1B1PP/R2Q1RK1 b - - 0 12"));
    ASSERT_TRUE(unmakeOne("r1b2rk1/1p3pbp/p1n1p1p1/3q4/P2N4/4BP2/1PP1B1PP/R2Q1RK1 w - - 0 13"));
    ASSERT_TRUE(unmakeOne("r1b2rk1/1p3pbp/p1N1p1p1/3q4/P7/4BP2/1PP1B1PP/R2Q1RK1 b - - 0 13"));
    ASSERT_TRUE(unmakeOne("r1b2rk1/1p3pbp/p1q1p1p1/8/P7/4BP2/1PP1B1PP/R2Q1RK1 w - - 0 14"));
    ASSERT_TRUE(unmakeOne("r1b2rk1/1p3pbp/p1q1p1p1/8/P7/2P1BP2/1P2B1PP/R2Q1RK1 b - - 0 14"));
    ASSERT_TRUE(unmakeOne("r4rk1/1p1b1pbp/p1q1p1p1/8/P2B4/2P2P2/1P2B1PP/R2Q1RK1 b - - 2 15"));
    ASSERT_TRUE(unmakeOne("r4rk1/1p1b1pbp/p1q3p1/4p3/P2B4/2P2P2/1P2B1PP/R2Q1RK1 w - - 0 16"));
    ASSERT_TRUE(unmakeOne("r4rk1/1p1b1pbp/p1q3p1/4p3/P7/2P1BP2/1P2B1PP/R2Q1RK1 b - - 1 16"));
    ASSERT_TRUE(unmakeOne("r4rk1/1p3pbp/pq4p1/8/P4B2/2P2R2/1P4PP/R2Q2K1 w - - 1 21"));
    ASSERT_TRUE(unmakeOne("r2r2k1/1p3pbp/p5p1/2B5/P7/2q2R2/6PP/R4QK1 w - - 0 24"));
    ASSERT_TRUE(unmakeOne("3r3k/1pR3Qp/pB4p1/8/P7/3r4/6PP/6K1 b - - 0 29"));
}



uint32_t perftDoubleCheckUnmake (Board* board, int depth){
    Move ml[256];
    
    if (depth == 0){
        return 1; 
    }
    uint32_t nodes = 0; 
    generateAllMoves(board, ml);
    int curr_num_moves = board->curr_num_moves;
    for (int i = 0; i < curr_num_moves; i++){
        Board b2 = *board; 
        int old_ep = board->en_pass_square; 
        int old_moves_since = board->move_since; 
        CastleRights old_castle_rights = board->castle_rights; 
        makeMove(board, ml[i]);
        unmakeMove(board, ml[i]);
        board->en_pass_square = old_ep; 
        board->move_since = old_moves_since;
        board->castle_rights = old_castle_rights;
        if(!isBoardEqual(board, &b2)){
            return -1;
        }
        makeMove(board, ml[i]);
        nodes += perftDoubleCheckUnmake(board, depth - 1); 
        unmakeMove(board, ml[i]); 
        board->en_pass_square = old_ep; 
        board->move_since = old_moves_since;
        board->castle_rights = old_castle_rights;
    }
    return nodes; 
}

int perftTwoDoubleCheckUnmake(const char *fen){
    Board *b = new Board(fen);
    return perftDoubleCheckUnmake(b, 2); 
}

int perftThreeDoubleCheckUnmake(const char *fen){
    Board *b = new Board(fen);
    return perftDoubleCheckUnmake(b, 3); 
}

int perftFourDoubleCheckUnmake(const char *fen){
    Board *b = new Board(fen); 
    return perftDoubleCheckUnmake(b, 4); 
}

TEST(Perft_Tests, starting_pos){
    Board *b = new Board(); 
    ASSERT_EQ(perftDoubleCheckUnmake(b, 1), 20);
    ASSERT_EQ(perftDoubleCheckUnmake(b, 2), 400);
    ASSERT_EQ(perftDoubleCheckUnmake(b, 3), 8902);
    ASSERT_EQ(perftDoubleCheckUnmake(b, 4), 197281);
    ASSERT_EQ(perftDoubleCheckUnmake(b, 5), 4865609);
    // ASSERT_EQ(perftDoubleCheckUnmake(b, 6), 119060324); /* This takes a ton of time */
}


TEST(Perft_Tests, random_positions){
    ASSERT_EQ(perftTwoDoubleCheckUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0"), 400);
    ASSERT_EQ(perftTwoDoubleCheckUnmake("r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3"), 724);
    ASSERT_EQ(perftTwoDoubleCheckUnmake("r1bqkbnr/pp1ppppp/2n5/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 3"), 963);
    ASSERT_EQ(perftTwoDoubleCheckUnmake("r2q1rk1/1b3pbp/p2pp1p1/1p4Pn/3BP3/1BN2P2/PPPQ3P/2KR3R w - - 1 15"), 1288);
    ASSERT_EQ(perftTwoDoubleCheckUnmake("r2q1rk1/1b3pBp/p2pp1p1/1p4Pn/4P3/1BN2P2/PPPQ3P/2KR3R b - - 0 15"), 1119);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 8902);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r1bq1rk1/1p3pbp/p2ppnp1/8/2BnP1P1/2N1BP2/PPPQ3P/2KR3R w - - 0 12"), 54605);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("8/3k1Qpp/8/2P5/3b4/8/6PP/3q1B1K b - - 10 36"), 1610);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r1b1k2r/pp3ppp/1qn1p3/3pPn2/1b1P4/2N1BN2/PP1QBPPP/R3K2R b KQkq - 4 10"), 68830);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r4rk1/pp1bbppp/1qn1p3/3pP3/1P1P4/P1N1PN2/3QB1PP/R4RK1 b - - 0 14"), 64453);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("2r2rk1/1pqbb1pp/4p3/1R1pN3/1P1P4/4P3/3QB1PP/5RK1 b - - 0 21"), 70922);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("5rk1/1p4pp/4qb2/2Pp4/1Q1P4/3B4/6PP/5RK1 b - - 2 27"), 48446);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r5N1/pppqb3/2np1nk1/8/4P2B/2N5/PPP2PPP/R2QK2R b KQ - 0 14"), 48990);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r2qk2r/ppp1bpp1/2npBn1p/8/3NP2B/2N5/PPP2PPP/R2QK2R b KQkq - 0 9"), 47703);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("7r/pppq4/2np2k1/6b1/4P3/2N2Q2/PPP2PPP/2KR3R w - - 2 18"), 6383);
    ASSERT_EQ(perftThreeDoubleCheckUnmake("r2qk2r/ppp2ppp/2nbpn2/3p1b2/8/1P1PPN2/PBP1BPPP/RN1Q1RK1 b kq - 0 7"), 64591);
    ASSERT_EQ(perftFourDoubleCheckUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 197281);
    ASSERT_EQ(perftFourDoubleCheckUnmake("2kr3r/pppq1ppp/2n5/3pPb1n/4p3/1P2P2P/PBPNBPP1/R2Q1RK1 w - - 1 13"), 1325697);
    ASSERT_EQ(perftFourDoubleCheckUnmake("r2qk2r/ppp2ppp/2nbpn2/3p1b2/8/1P2PN2/PBPPBPPP/RN1Q1RK1 w kq - 6 7"), 2274252);
    ASSERT_EQ(perftFourDoubleCheckUnmake("2kr3r/pppq1ppp/2nb1n2/3ppb2/3P4/1P2PN1P/PBPNBPP1/R2Q1RK1 b - - 0 10"), 1919391);
    ASSERT_EQ(perftFourDoubleCheckUnmake("8/PK1k1p2/6p1/3Pp3/8/8/8/7q b - - 0 56"), 44809); 
    ASSERT_EQ(perftFourDoubleCheckUnmake("8/2p2pk1/p1P3p1/P3p2p/B1P1P3/5K2/1r6/8 b - - 0 42"), 31091);
    ASSERT_EQ(perftFourDoubleCheckUnmake("r3kb1r/pppq1ppp/2n5/5b2/3P1B2/2P2N1P/P3BPP1/R2QK2R b KQkq - 2 11"), 3299142);
    ASSERT_EQ(perftFourDoubleCheckUnmake("r4rk1/ppp2ppp/2nq2B1/8/3P4/2P2N1P/P4PP1/R2Q1RK1 b - - 0 15"), 1796262);
    ASSERT_EQ(perftFourDoubleCheckUnmake("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0"), 4085603);
    ASSERT_EQ(perftTwoDoubleCheckUnmake("8/2p5/3p4/KP3k1r/5p2/5R2/4P1P1/8 w - - 4 3"), 293);
}

TEST(NumPiecesChange, qf7){
    Board *b = new Board("rnbqkbnr/1ppp1Qpp/8/p3p3/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 0 3");
    Move ml[256];
    generateAllMoves(b, ml);
    makeMove(b, ml[0]);
    ASSERT_EQ(b->white_pieces.num_pieces.num_queens, 0);
    unmakeMove(b, ml[0]);
    ASSERT_EQ(b->white_pieces.num_pieces.num_queens, 1);
}