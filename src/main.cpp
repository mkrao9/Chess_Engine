#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include <string>


void printBoard(Board *b);

int main(){
    ;
    Board *board = new Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    return 0;
}
