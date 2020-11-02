#include "../include/board.hpp"
#include <stdlib.h>
#include <iostream>


/*default constructor */ 
Board::Board(){
    white_to_move = true; 
    turn_number = 1;
    curr_ply = 0;
    en_pass_square = 0;

    white_pawn = (0xFF << 8);
    white_rook = 0x81;

    white_knight = 0x42;
    white_bishop = 0x24;
    white_queen = 0x10;
    white_king = 0x08;

    black_pawn = white_pawn << 40;
    black_rook = white_rook << 56;
    black_knight = white_knight << 56;
    black_bishop = white_bishop << 56;
    black_queen = white_queen << 56; 
    black_king = white_king << 56;

    white_pieces = white_pawn | white_rook | white_knight | white_queen | white_bishop | white_king;
    black_pieces = black_pawn | black_rook | black_knight | black_queen | black_bishop | black_king;

    occupied_squares = white_pieces | black_pieces;

}

uint64_t Board::getWhitePieces(){
    return white_pawn | white_rook | white_knight | white_queen | white_bishop | white_king;
}

uint64_t Board::getBlackPieces(){
    return black_pieces = black_pawn | black_rook | black_knight | black_queen | black_bishop | black_king;
}

uint64_t Board::getOccupiedSquares(){
    return getWhitePieces() | getBlackPieces();
}