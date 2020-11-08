#include "../include/board.hpp"
#include "../include/move.hpp"
#include <stdlib.h>
#include <iostream>



uint32_t generateAllMoves(Board *board){

    uint8_t check = inCheck(board);
    if (check){
        if (check != 2){
            uint8_t code = check >> 4; 
            
        }
        //generate king moves 
        generateKingMoves(board);
    }
    else{
        std::cout << "not in check! \n";
    }

    return 0;
}


void generateKingMoves(Board* board){

    pieces other_pieces; 
    uint64_t other_pieces_board;
    uint64_t curr_pieces_board;
    attack_set* attack;
    int king_square; 
    attack_set king_attack_set; 

    if (board->white_to_move){
        other_pieces = board->black_pieces;
        king_square = board->white_king_square;
        curr_pieces_board = board->getWhitePieces();
        other_pieces_board = board->getBlackPieces();
        attack = board->full_attack_set.black_attack_set;
    }
    else{
        other_pieces = board->white_pieces;
        king_square = board->black_king_square;
        curr_pieces_board = board->getBlackPieces();
        other_pieces_board = board->getWhitePieces();
        attack = board->full_attack_set.white_attack_set;
    }

    king_attack_set = attack[king_square];



    //up 
    if (king_square < 56 && (!king_attack_set.fields.DOWN)){
        int val = king_square + UP_VAL;
        uint64_t shifted_square = SHIFT(val);

        //occupied 
        if (!(curr_pieces_board & shifted_square)){

            //makes sure the square is not currently hit
            if (attack[val].bits == 0){
                board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));

                //if it's a capture
                if (other_pieces_board & shifted_square){
                    board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                }

                board->curr_num_moves++;
            }
        }
    }

    //down
    if (king_square > 7 && (!king_attack_set.fields.UP)){
        int val = king_square + DOWN_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                board->move_list[board->curr_num_moves] = (king_square | ((val) << 6));

                //if it's a capture
                if (other_pieces_board & shifted_square){
                    board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                }
                board->curr_num_moves++;
            
            }
        }
    }

    //left
    if (king_square % 8 != 7 && (!king_attack_set.fields.RIGHT)){
        int val = king_square + LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));
                //if it's a capture
                if (other_pieces_board & shifted_square){
                    board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                }
                board->curr_num_moves++;
            }
        }
    }

    //right 
    if (king_square % 8 != 0 && (!king_attack_set.fields.LEFT)){
        int val = king_square + RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));

                //if it's a capture
                if (other_pieces_board & shifted_square){
                    board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                }
                board->curr_num_moves++;
            }
        }
    }

    //up left 
    if (king_square % 8 != 7 && king_square < 56){
        int val = king_square + UP_LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                if (!king_attack_set.fields.DOWN_RIGHT || (SHIFT(king_square + king_attack_set.fields.DOWN_RIGHT * DOWN_RIGHT_VAL) & other_pieces.pawn)) {
                    board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));

                    //if it's a capture
                    if (other_pieces_board & shifted_square){
                        board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                    }
                    board->curr_num_moves++;
                }
            }
        }
    }

    //up right 
    if (king_square % 8 != 0 && king_square < 56){
        int val = king_square + UP_RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0) {
             if (!king_attack_set.fields.DOWN_LEFT || (SHIFT(king_square + king_attack_set.fields.DOWN_LEFT * DOWN_LEFT_VAL) & other_pieces.pawn)){
                board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));
                //if it's a capture
                if (other_pieces_board & shifted_square){
                    board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                }
                board->curr_num_moves++;
             }
            }
        }
    }

    //down left 
    if(king_square % 8 != 7  && king_square > 7){
        int val = king_square + DOWN_LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                if (!king_attack_set.fields.UP_RIGHT || (SHIFT(king_square + king_attack_set.fields.UP_RIGHT * UP_RIGHT_VAL) & other_pieces.pawn)){
                    board->move_list[board->curr_num_moves] = (king_square | ((val ) << 6));

                    //if it's a capture
                    if (other_pieces_board & shifted_square){
                        board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                    }
                    board->curr_num_moves++;
                }
            }
        }
    }

    //down right
    if (king_square % 8 != 0 && king_square > 7){
        int val = king_square + DOWN_RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                if (!king_attack_set.fields.UP_LEFT || (SHIFT(king_square + king_attack_set.fields.UP_LEFT * UP_LEFT_VAL) & other_pieces.pawn)){
                    board->move_list[board->curr_num_moves] = (king_square | ((val) << 6));

                    //if it's a capture
                    if (other_pieces_board & shifted_square){
                        board->move_list[board->curr_num_moves] |= (getPieceCode(shifted_square, other_pieces)) << 20;
                    }
                    board->curr_num_moves++;
                }
               
            }
        }
    }
}

uint8_t getPieceCode(uint64_t square, pieces other_pieces){
    if (other_pieces.pawn & square){
        return 1; 
    }
    if (other_pieces.rook & square){
        return 2;
    }
    if (other_pieces.knight & square){
        return 3;
    }
    if (other_pieces.bishop & square){
        return 4;
    }
    if (other_pieces.queen & square){
        return 5;
    }
    return 0;
}


uint8_t inCheck(Board* board){
    bool white_to_move = board->white_to_move;

    if (white_to_move){
        int king_square = board->white_king_square;
        if (!(board->full_attack_set.black_attack_set[king_square].bits)){
            return 0;
        }
        else{
            struct pieces other_pieces = board->black_pieces;

            attack_set attack = board->full_attack_set.black_attack_set[king_square];
            int target_square = king_square;
            if (GET_N_HITS(attack.bits)){
                return 2; 
            }
            return checkStraightCheck(attack, target_square, other_pieces);
        }
    }
    else{
        int king_square = board->black_king_square;
        if (!(board->full_attack_set.white_attack_set[king_square].bits)){
            
            return false;
        }
        else{
            struct pieces other_pieces = board->white_pieces;

            attack_set attack = board->full_attack_set.white_attack_set[king_square];
            if (GET_N_HITS(attack.bits)){
                return 2; 
            }
            return checkStraightCheck(attack, king_square, other_pieces);
        }
    }
}


uint8_t checkStraightCheck(attack_set attack, int target_square, struct pieces other_pieces){
    if (!(GET_LINE_HITS(attack.bits))){
        return 0;
    }

    uint64_t line_pieces = other_pieces.bishop | other_pieces.rook | other_pieces.pawn | other_pieces.queen;
    uint8_t count = 0; 
    uint8_t curr = 0; 
    uint32_t hit;

    if (attack.fields.LEFT && (SHIFT(target_square + LEFT_VAL * attack.fields.LEFT) & line_pieces)){
        curr = 0;  
        count++; 
    }

    if (attack.fields.UP_LEFT && (SHIFT(target_square + UP_LEFT_VAL * attack.fields.UP_LEFT) & line_pieces)){
        curr = 1;
        count++; 
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.UP && (SHIFT(target_square + UP_VAL * attack.fields.UP) & line_pieces)){
        curr = 2; 
        count++; 
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.UP_RIGHT && (SHIFT(target_square + UP_RIGHT_VAL * attack.fields.UP_RIGHT) & line_pieces)){
        curr = 3; 
        count++; 
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.RIGHT && (SHIFT(target_square + RIGHT_VAL * attack.fields.RIGHT) & line_pieces)){
        curr = 4; 
        count++; 
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.DOWN_RIGHT && (SHIFT(target_square + DOWN_RIGHT_VAL * attack.fields.DOWN_RIGHT) & line_pieces)){
        curr = 5; 
        count++;
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.DOWN && (SHIFT(target_square + DOWN_VAL * attack.fields.DOWN) & line_pieces)){
        curr = 6; 
        count++; 
        if (count == 2){
            return count;
        }
    }

    if (attack.fields.DOWN_LEFT && (SHIFT(target_square + DOWN_LEFT_VAL * attack.fields.DOWN_LEFT) & line_pieces)){
        curr = 7; 
        count++; 

        if (count == 2){
            return count;
        }
    }

    return count | (curr << 4);
}

