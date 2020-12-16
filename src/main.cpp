#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include "../include/make_unmake.hpp"
#include <string>
#include <time.h>


void printBoard(Board *b);


uint32_t PerftFourNoUnmake(const char *fen){
    // std::cout << "\n\n\n\n";
    Board board(fen);
    Move list[256];
    generateAllMoves(&board, list);

    uint32_t num_first_moves = board.curr_num_moves; 
    uint32_t count = 0; 

    for (int i = 0; i < num_first_moves; i++){
        Board new_board = board;

        makeMove(&new_board, list[i]);
        Move new_list[256];

        generateAllMoves(&new_board, new_list);

 
        for (int j = 0; j < new_board.curr_num_moves; j++){

            Board two_board = new_board;
            makeMove(&two_board, new_list[j]);
            Move third_list[256];
            generateAllMoves(&two_board, third_list);  

            for (int k = 0; k < two_board.curr_num_moves; k++){
                Board three_board = two_board;
                Move last_list[256];
                makeMove(&three_board, third_list[k]);
                generateAllMoves(&three_board, last_list);
                count += three_board.curr_num_moves;
                for (int l = 0; l < three_board.curr_num_moves; l++){
                    Board four_brd = three_board; 
                    makeMove(&four_brd, last_list[l]);
                }

            }
        }
    }

    return count; 
}


int main(){
    
    clock_t start = clock(); 
    uint32_t thing = PerftFourNoUnmake("2kr3r/pppq1ppp/2nbpn2/3p1b2/8/1P1PPN1P/PBPNBPP1/R2Q1RK1 b - - 0 9");
    uint32_t thing2 = PerftFourNoUnmake("r3kb1r/pppq1ppp/2n5/5b2/3P1B2/2P2N1P/P3BPP1/R2QK2R b KQkq - 2 11");
    uint32_t thing3 = PerftFourNoUnmake("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    uint32_t thing4 = PerftFourNoUnmake("r4rk1/ppp2ppp/2nq2B1/8/3P4/2P2N1P/P4PP1/R2Q1RK1 b - - 0 15");
    clock_t end = clock(); 
    double time = double(end-start) / double(CLOCKS_PER_SEC);
    std::cout << thing << "\n";
    std::cout << thing2 << "\n";
    std::cout << thing3 << "\n";
    std::cout << thing4 << "\n";
    std::cout << time << "\n";

    // Board board{}; 
    // Board b2 = board;
    // board.castle_rights.white_k_castle = false; 

    return 0;
}
