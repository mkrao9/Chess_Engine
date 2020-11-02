#include "../include/board.hpp"
#include <stdlib.h>
#include <iostream>
#include <string.h>


/*default constructor */ 
Board::Board(){
    castle_rights = 15; 
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

Board::Board(const char *fen){

    uint64_t white_pawn = 0;
    uint64_t white_rook = 0;
    uint64_t white_knight = 0;
    uint64_t white_bishop = 0;
    uint64_t white_queen = 0;
    uint64_t white_king = 0;
    uint64_t black_pawn = 0;
    uint64_t black_rook = 0;
    uint64_t black_knight = 0;
    uint64_t black_bishop = 0;
    uint64_t black_queen = 0;
    uint64_t black_king = 0;

    castle_rights = 0; 
    en_pass_square = 0; 
    white_to_move = true;
    turn_number = 0; 
    curr_ply = 0;


    int counter = 63; 
    int index = 0;
    int len = strlen(fen);

    while (counter >= 0){
        char c = fen[index];
        switch (c){
            case 'r': 
                black_rook |= (1 << counter);
                break;
            case 'n': 
                black_knight |= (1 << counter);
                break;
            case 'b':
                black_bishop |= (1 << counter);
                break;
            case 'q': 
                black_queen  |= (1 << counter);
                break;
            case 'k':
                black_king  |= (1 << counter);
                break;
            case 'p':
                black_pawn  |= (1 << counter);
                break;
            case 'P': 
                white_pawn  |= (1 << counter);
                break;
            case 'R': 
                white_rook |= (1 << counter);
                break;
            case 'N': 
                white_knight |= (1 << counter);
                break;
            case 'B': 
                white_bishop |= (1 << counter);
                break;
            case 'Q': 
                white_queen |= (1 << counter);
                break;
            case 'K': 
                white_king |= (1 << counter);
                break;
            case '/': 
                counter++;
                break;
            default: 
                int num = c - '0';
                counter -= (num - 1);
        }
        counter--;
        index++;
    }

    index++;
    if (fen[index] == 'b'){
        white_to_move = false;
    }


    index+=2;

    int i = 0; 

    if (fen[index] == '-'){
        i = 4;
    }

    while (i < 4 && fen[index] != ' '){
        char c = fen[index];
        switch (c){
            case 'K':   
                castle_rights |= 2;
                break;
            case 'Q': 
                castle_rights |= 1;
                break;
            case 'k': 
                castle_rights |= 8;
                break;
            case 'q': 
                castle_rights |= 4;
                break;
        }

        index++;
        i++;
    }

    index++;

    if (fen[index] == '-'){
        en_pass_square = 0;
    }
    else{
        int col = 7 - (fen[index] - 'a');
        index++;
        int row = fen[index] - '1';
        en_pass_square = 8*row + col;
    }



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