#include "../include/board.hpp"
#include "../include/attack_set.hpp"
#include <stdlib.h>
#include <iostream>

void initializeAttackSet(Board* board){
    
    pieces white_pieces = board->white_pieces; 
    pieces black_pieces = board->black_pieces; 
    uint64_t occupied_squares = board->getOccupiedSquares();

    int count = 0; 
    for (uint8_t i = 0; i < 64; i++){
        uint64_t square = SHIFT(i);
        if (SHIFT(i) & occupied_squares){
            if (square & (black_pieces.queen)){
                setQueen(board->full_attack_set.black_attack_set, i, occupied_squares);
                continue;
            }   
            if (square & (white_pieces.queen)){
                setQueen(board->full_attack_set.white_attack_set, i, occupied_squares);
                continue;
            }

            if (square & (white_pieces.bishop)){
                setBishop(board->full_attack_set.white_attack_set, i, occupied_squares);
                continue;
            }

            if (square & (black_pieces.bishop)){
                setBishop(board->full_attack_set.black_attack_set, i, occupied_squares);
                continue;
            }

            if (square & (white_pieces.rook)){
                setRook(board->full_attack_set.white_attack_set, i, occupied_squares);
                continue;
            }

            if (square & (black_pieces.rook)){
                setRook(board->full_attack_set.black_attack_set, i, occupied_squares);
                continue;
            }


            if (square & (black_pieces.king)){
                setKing(board->full_attack_set.black_attack_set, i, occupied_squares); 
                continue;
            }

            if (square & (white_pieces.king)){
                setKing(board->full_attack_set.white_attack_set, i, occupied_squares); 
                continue;
            }

            if (square & (black_pieces.knight)){
                setKnight(board->full_attack_set.black_attack_set, i, occupied_squares);
                continue;
            }

            if (square & (white_pieces.knight)){
                setKnight(board->full_attack_set.white_attack_set, i, occupied_squares);
                continue;
            }

            if (square & white_pieces.pawn){
                setWhitePawn(board->full_attack_set.white_attack_set, i, occupied_squares);
                continue;
            }

            if (square & black_pieces.pawn){
                setBlackPawn(board->full_attack_set.black_attack_set, i, occupied_squares);
                continue;
            }

        }
    }
    
    return;
}



void setDiags(attack_set* attack_set, uint8_t square, uint64_t occupied_squares){

    uint32_t ind = 0; 
    int square_num = square;

    //up left 
    while (square_num % 8 != 7 && square_num < 56){
        square_num += UP_LEFT_VAL;
        ind++;
        attack_set[square_num].fields.DOWN_RIGHT = ind; 
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //up right 
    square_num = square; 
    ind = 0; 
    while (square_num % 8 != 0 && square_num < 56){
        square_num += UP_RIGHT_VAL;
        ind++; 
        attack_set[square_num].fields.DOWN_LEFT = ind;
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //down left 
    square_num = square; 
    ind = 0; 
    while (square_num % 8 != 7 && square_num > 7){
        square_num += DOWN_LEFT_VAL;
        ind++; 
        attack_set[square_num].fields.UP_RIGHT = ind; 
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //down right 
    square_num = square; 
    ind = 0; 
    while (square_num % 8 != 0 && square_num > 7){
        square_num += DOWN_RIGHT_VAL;
        ind++; 
        attack_set[square_num].fields.UP_LEFT = ind; 
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }
}

void setLat(attack_set *attack_set, uint8_t square, uint64_t occupied_squares){
    uint32_t ind = 0; 
    int square_num = square;

    //left 
    while (square_num % 8 != 7){
        square_num += LEFT_VAL;
        ind++;
        attack_set[square_num].fields.RIGHT = ind; 
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //right 
    ind = 0; 
    square_num = square; 
    while (square_num % 8 != 0){
        square_num += RIGHT_VAL;
        ind++;
        attack_set[square_num].fields.LEFT = ind;
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //up 
    ind = 0; 
    square_num = square; 
    while (square_num < 56){
        square_num += UP_VAL;
        ind++;
        attack_set[square_num].fields.DOWN = ind;
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }

    //down 
    ind = 0; 
    square_num = square; 
    while (square_num > 7) {
        square_num += DOWN_VAL;
        ind++;
        attack_set[square_num].fields.UP = ind;
        if (occupied_squares & SHIFT(square_num)){
            break;
        }
    }
}

void setQueen(attack_set *attack_set, uint8_t square, uint64_t occupied_squares){
    setDiags(attack_set, square, occupied_squares);
    setLat(attack_set, square, occupied_squares);
}

void setBishop(attack_set *attack_set, uint8_t square, uint64_t occupied_squares){
    setDiags(attack_set, square, occupied_squares);
}

void setRook(attack_set *attack_set, uint8_t square, uint64_t occupied_squares){
    setLat(attack_set, square, occupied_squares);
}

void setKing(attack_set *attack_set, uint8_t square, uint64_t occupied_squares){

    int square_num = square; 

    //up 
    if (square_num < 56){
        attack_set[square_num + UP_VAL].fields.DOWN = 1; 
    }

    //down
    if (square_num > 7){
        attack_set[square_num + DOWN_VAL].fields.UP = 1;
    }

    //left
    if (square_num % 8 != 7){
        attack_set[square_num + LEFT_VAL].fields.RIGHT = 1;
    }

    //right 
    if (square_num % 8 != 0){
        attack_set[square_num + RIGHT_VAL].fields.LEFT = 1;
    }

    //up left 
    if (square_num % 8 != 7 && square_num < 56){
        attack_set[square_num + UP_LEFT_VAL].fields.DOWN_RIGHT = 1; 
    }

    //up right 
    if (square_num % 8 != 0 && square_num < 56){
        attack_set[square_num + UP_RIGHT_VAL].fields.DOWN_LEFT = 1;
    }

    //down left 
    if(square_num % 8 != 7  && square_num > 7){
        attack_set[square_num + DOWN_LEFT_VAL].fields.UP_RIGHT = 1;
    }

    //down right
    if (square_num % 8 != 0 && square_num > 7){
        attack_set[square_num + DOWN_RIGHT_VAL].fields.UP_LEFT = 1;
    }

}

void setKnight(attack_set *attack_set, uint8_t square, uint64_t occupied_sqares){
    int square_num = square; 

    //ul short 
    if (square_num % 8 < 6 && square_num < 56){
        attack_set[square_num + N_UL_SHORT].fields.N_DR_SHORT = 1;
    }

    //ul tall 
    if (square_num % 8 != 7 && square_num < 48){
        attack_set[square_num + N_UL_TALL].fields.N_DR_TALL = 1;
    }

    //ur tall 
    if (square_num % 8 != 0 && square_num < 48){
        attack_set[square_num + N_UR_TALL].fields.N_DL_TALL = 1;;
    }

    //ur short 
    if (square_num % 8 > 1 && square_num < 56){
        attack_set[square_num + N_UR_SHORT].fields.N_DL_SHORT = 1;;
    }

    //dr short 
    if (square_num % 8 > 1 && square_num > 7){
        attack_set[square_num + N_DR_SHORT].fields.N_UL_SHORT = 1;
    }

    //dr tall
    if (square_num % 8 != 0 && square_num > 15){
        attack_set[square_num + N_DR_TALL].fields.N_UL_TALL = 1;
    } 

    //dl tall 
    if (square_num % 8 != 7 && square_num > 15){
        attack_set[square_num + N_DL_TALL].fields.N_UR_TALL = 1;
    }

    //dl short 
    if (square_num % 8 < 6 && square_num > 7){
        attack_set[square_num + N_DL_SHORT].fields.N_UR_SHORT = 1;
    }
}

void setWhitePawn(attack_set *attack_set, uint8_t square, uint64_t occupied_sqares){
    int square_num = square; 
    
    if (square_num % 8 != 7){
        attack_set[square_num + UP_LEFT_VAL].fields.DOWN_RIGHT = 1;
    }
    
    if (square_num % 8 != 0){
        attack_set[square_num + UP_RIGHT_VAL].fields.DOWN_LEFT = 1;
    }
}

void setBlackPawn(attack_set *attack_set, uint8_t square, uint64_t occupied_sqares){

    int square_num = square; 
    
    if (square_num % 8 != 7){
        attack_set[square_num + DOWN_LEFT_VAL].fields.UP_RIGHT = 1;
    }
    
    if (square_num % 8 != 0){
        attack_set[square_num + DOWN_RIGHT_VAL].fields.UP_LEFT = 1;
    }
}

void printAttackSet(attack_set *attack_set){
    for (int i = 48; i < 64; i++){
        if (attack_set[i].bits != 0){
            std::cout << "\n"; 
            std::cout << "Square: " << i << std::endl; 
            std::cout << "\tLeft: " << ((attack_set[i]).fields.LEFT) << std::endl;
            std::cout << "\tUp left: " << ((attack_set[i]).fields.UP_LEFT) << std::endl;
            std::cout << "\tUp: " << ((attack_set[i]).fields.UP) << std::endl;
            std::cout << "\tUp right: " << ((attack_set[i]).fields.UP_RIGHT) << std::endl;
            std::cout << "\tRight: " << ((attack_set[i]).fields.RIGHT) << std::endl;
            std::cout << "\tDown right: " << ((attack_set[i]).fields.DOWN_RIGHT) << std::endl; 
            std::cout << "\tDown: " << ((attack_set[i]).fields.DOWN) << std::endl;  
            std::cout << "\tDown left: " << ((attack_set[i]).fields.DOWN_LEFT) << std::endl; 
            std::cout << "\tKnight up-left-short: " << ((attack_set[i]).fields.N_UL_SHORT) << std::endl;
            std::cout << "\tKnight up-left-tall: " << ((attack_set[i]).fields.N_UL_TALL) << std::endl;
            std::cout << "\tKnight up-right-tall: " << ((attack_set[i]).fields.N_UR_TALL) << std::endl;
            std::cout << "\tKnight up-right-short: " << ((attack_set[i]).fields.N_UR_SHORT) << std::endl;
            std::cout << "\tKnight down-right-short: " << ((attack_set[i]).fields.N_DR_SHORT) << std::endl;
            std::cout << "\tKnight down-right-tall: " << ((attack_set[i]).fields.N_DR_TALL) << std::endl;
            std::cout << "\tKnight down-left-tall: " << ((attack_set[i]).fields.N_DR_TALL) << std::endl;
            std::cout << "\tKnight down-left-short: " << ((attack_set[i]).fields.N_DL_SHORT) << std::endl;
        }
    }
}