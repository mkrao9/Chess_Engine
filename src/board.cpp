#include "../include/board.hpp"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "../include/attack_set.hpp"

/*default constructor */ 
Board::Board(){
    castle_rights.black_k_castle = 1;
    castle_rights.white_k_castle = 1; 
    castle_rights.black_q_castle = 1; 
    castle_rights.white_q_castle = 1; 

    white_to_move = true; 
    turn_number = 1;
    en_pass_square = 0;
    move_since = 0; 

    white_pieces.pawn = (0xFF << 8);
    white_pieces.rook = 0x81;

    white_pieces.knight = 0x42;
    white_pieces.bishop = 0x24;
    white_pieces.queen = 0x10;
    white_pieces.king = 0x08;

    black_pieces.pawn = white_pieces.pawn << 40;
    black_pieces.rook = white_pieces.rook << 56;
    black_pieces.knight = white_pieces.knight << 56;
    black_pieces.bishop = white_pieces.bishop << 56;
    black_pieces.queen = white_pieces.queen << 56; 
    black_pieces.king = white_pieces.king << 56;

    black_king_square = 59; 
    white_king_square = 3;

    for (int i = 0; i < 64; i++){
        full_attack_set.black_attack_set[i].bits = 0; 
        full_attack_set.white_attack_set[i].bits = 0; 
    }
    
    initializeAttackSet(this);

    move_list = new uint32_t[256];
    curr_num_moves = 0;

    setCurrentState();
}

/*
    constructor that takes in a fen 
    doesn't handle any error codes -- assumes input is valid.
    This is used for testing purposes for right now. 
*/
Board::Board(const char *fen){

    
    white_pieces.pawn = 0;
    white_pieces.rook = 0;
    white_pieces.knight = 0;
    white_pieces.bishop = 0;
    white_pieces.queen = 0;
    white_pieces.king = 0;
    black_pieces.pawn = 0;
    black_pieces.rook = 0;
    black_pieces.knight = 0;
    black_pieces.bishop = 0;
    black_pieces.queen = 0;
    black_pieces.king = 0;
    
    castle_rights.white_k_castle = 0; 
    castle_rights.black_k_castle = 0; 
    castle_rights.white_q_castle = 0; 
    castle_rights.black_q_castle = 0; 

    en_pass_square = 0; 
    white_to_move = true;
    turn_number = 0; 



    int counter = 63; 
    int index = 0;
    int len = strlen(fen);

    while (counter >= 0){
        char c = fen[index];
        switch (c){
            case 'r': 
                black_pieces.rook |= (1LL << counter);
                break;
            case 'n': 
                black_pieces.knight |= (1LL << counter);
                break;
            case 'b':
                black_pieces.bishop |= (1LL << counter);
                break;
            case 'q': 
                black_pieces.queen  |= (1LL << counter);
                break;
            case 'k':
                black_pieces.king  |= (1LL << counter);
                black_king_square = counter;
                break;
            case 'p':
                black_pieces.pawn  |=  (1LL << counter);
                break;
            case 'P': 
            white_pieces.pawn  |= (1LL << counter);
                break;
            case 'R': 
                white_pieces.rook |= (1LL << counter);
                break;
            case 'N': 
                white_pieces.knight |= (1LL << counter);
                break;
            case 'B': 
                white_pieces.bishop |= (1LL << counter);
                break;
            case 'Q': 
                white_pieces.queen |= (1LL << counter);
                break;
            case 'K': 
                white_pieces.king |= (1LL << counter);
                white_king_square = counter;
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
        index++;
    }

    while (i < 4 && fen[index] != ' '){
        char c = fen[index];
        switch (c){
            case 'K':   
                castle_rights.white_k_castle  = 1;
                break;
            case 'Q': 
                castle_rights.white_q_castle = 1;
                break;
            case 'k': 
                castle_rights.black_k_castle = 1;
                break;
            case 'q': 
                castle_rights.black_q_castle = 1;
                break;
        }

        index++;
        i++;
    }

    index++;

    if (fen[index] == '-'){
        en_pass_square = 0;
        index++;
    }
    else{
        int col = 7 - (fen[index] - 'a');
        index++;
        int row = fen[index] - '1';
        en_pass_square = 8*row + col;

        index++;
    }


    index++;

    uint32_t curr = 0; 
    while (fen[index] != ' '){
        curr *= 10;
        uint32_t num = fen[index] - '0';
        curr += num;

        index++;
    }

    move_since = curr;


    index++;


    curr = 0; 
    while (fen[index] != ' ' && fen[index] != 0){
        uint32_t num = fen[index] - '0';
        curr *=10;
        curr += num;
        index++;
    }

    turn_number = curr;

    for (int i = 0; i < 64; i++){
        full_attack_set.black_attack_set[i].bits = 0; 
        full_attack_set.white_attack_set[i].bits = 0; 
    }


    move_list = new uint32_t[256];
    curr_num_moves = 0; 

    initializeAttackSet(this);
    setCurrentState();
}
