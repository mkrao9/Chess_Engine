#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include "../include/make_unmake.hpp"
#include <string>
#include <time.h>


void printBoard(Board *b);

uint64_t perft(Board* board, uint32_t depth){
    Move ml[256];
    
    if (depth == 0){
        return 1; 
    }

    if (depth == 1){
        return generateAllMoves(board, ml); 
    }
    
    uint64_t nodes = 0; 
    int curr_num_moves = generateAllMoves(board, ml);
    for (int i = 0; i < curr_num_moves; i++){
        int old_ep = board->en_pass_square; 
        int old_moves_since = board->move_since; 
        CastleRights old_castle_rights = board->castle_rights; 
        makeMove(board, ml[i]);
        nodes += perft(board, depth - 1);
        unmakeMove(board, ml[i]); 
        board->en_pass_square = old_ep; 
        board->move_since = old_moves_since;
        board->castle_rights = old_castle_rights;
    }
    return nodes; 
}

uint64_t perft(const char *fen, int depth){
    Board *b = new Board(fen);
    return perft(b, depth);
}

uint64_t perft(int depth){
    Board *b = new Board(); 
    return perft(b, depth);
}

int main(){
    
    clock_t start = clock(); 
    uint64_t thing = perft(6);
    uint32_t thing2 = perft("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1", 6);


    clock_t end = clock(); 
    double time = double(end-start) / double(CLOCKS_PER_SEC);
    std::cout << thing << " " << thing2 << "\n";
    std::cout << time << "\n";

    // Board board{}; 
    // Board b2 = board;
    // board.castle_rights.white_k_castle = false; 

    return 0;
}