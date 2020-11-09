#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include <string>


void printBoard(Board *b);

int main(){
    Board* board = new Board(); 
    // for (int i = 0; i < board->curr_num_moves; i++){
    //     uint32_t move = move_list[i];
    //     std::cout << "from: " << (move & 0x3f) << " to: " << 
    //         ((move >> 6) & 0x3f) << " special: " <<  ((move >> 12) & 0xf) << " capture: " << ((move >> 20) & 0xf) << "\n";
    // }


    
    return 0;
}
