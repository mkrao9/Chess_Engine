#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include <string>


void printBoard(Board *b);

int main(){
    Board* board = new Board("5b2/6pp/p1k2p2/1P3P2/3KN3/5P2/7P/8 b - - 0 37");
    // generateKingMoves(board);

    // /* Fix this :(  why is it not working QQ */
    // for (int i = 0; i < board->curr_num_moves; i++){
    //     std::cout << "to: " << ((board->move_list[i] & (0x3f << 6)) >> 6) << "\n";
    // }
    
    return 0;
}
