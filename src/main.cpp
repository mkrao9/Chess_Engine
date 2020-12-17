#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include "../include/make_unmake.hpp"
#include <string>
#include <time.h>


void printBoard(Board *b);

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

uint32_t PerftFourNoUnmake(const char *fen){
    // std::cout << "\n\n\n\n";
    Board board(fen);
    Move list[256];
    generateAllMoves(&board, list);

    uint32_t num_first_moves = board.curr_num_moves; 
    uint32_t count = 0; 

    for (uint32_t i = 0; i < num_first_moves; i++){
        Board new_board = board;

        makeMove(&new_board, list[i]);
        Move new_list[256];

        generateAllMoves(&new_board, new_list);

 
        for (uint32_t j = 0; j < new_board.curr_num_moves; j++){

            Board two_board = new_board;
            makeMove(&two_board, new_list[j]);
            Move third_list[256];
            generateAllMoves(&two_board, third_list);  

            for (uint32_t k = 0; k < two_board.curr_num_moves; k++){
                Board three_board = two_board;
                Move last_list[256];
                makeMove(&three_board, third_list[k]);
                generateAllMoves(&three_board, last_list);
                count += three_board.curr_num_moves;
                for (uint32_t l = 0; l < three_board.curr_num_moves; l++){
                    Board four_brd = three_board; 
                    makeMove(&four_brd, last_list[l]);
                }

            }
        }
    }

    return count; 
}

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
        // Board b2 = *board; 
        // makeMove(board, ml[i]);
        // unmakeMove(board, ml[i]); 
        // if (!isBoardEqual(board, &b2)){
        //     std::cout << "PANIC: " << "from: " << ml[i].source << " to: " << ml[i].dest << std::endl;
        // }

        makeMove(board, ml[i]);
        uint64_t thing = perft(board, depth - 1);
        // if (depth == 2){
        //     std::cout << "from: " << ml[i].source << " to: " << ml[i].dest << " special: " << ml[i].special << " " << thing << std::endl;
        // } 
        nodes += thing;
        unmakeMove(board, ml[i]); 
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
    uint64_t thing = perft(5);
    clock_t end = clock(); 
    double time = double(end-start) / double(CLOCKS_PER_SEC);
    std::cout << thing << "\n";
    std::cout << time << "\n";

    // Board board{}; 
    // Board b2 = board;
    // board.castle_rights.white_k_castle = false; 

    return 0;
}
