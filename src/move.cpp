#include "../include/board.hpp"
#include "../include/move.hpp"
#include <stdlib.h>
#include <iostream>
#include <intrin.h>

int code_to_val[8] = {1, 9, 8, 7, -1, -9, -8, -7};

inline void generateKingMoves(Board* board, bool do_capture){

    Pieces* other_pieces = board->other_pieces;
    uint64_t other_pieces_board = board->getOtherPieces();
    uint64_t curr_pieces_board = board->getCurrentPieces();
    AttackSet* attack = board->other_attack_set;
    int king_square = board->current_king_square;
    AttackSet king_attack_set = attack[king_square];

    

    //up 
    if (king_square < 56 && (!king_attack_set.fields.DOWN)){
        int val = king_square + UP_VAL;
        uint64_t shifted_square = SHIFT(val);

        //occupied 
        if (!(curr_pieces_board & shifted_square)){

            //makes sure the square is not currently hit
            if (attack[val].bits == 0){

                //if it's a capture
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.UP){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }

            }
        }
    }

    //down
    if (king_square > 7 && (!king_attack_set.fields.UP)){
        int val = king_square + DOWN_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){

                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.DOWN){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            
            }
        }
    }

    //left
    if (king_square % 8 != 7 && (!king_attack_set.fields.RIGHT)){
        int val = king_square + LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.LEFT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }

    //right 
    if (king_square % 8 != 0 && (!king_attack_set.fields.LEFT)){
        int val = king_square + RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if (!(curr_pieces_board & shifted_square)){
            if (attack[val].bits == 0){
                
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.RIGHT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }

    //up left 
    if (king_square % 8 != 7 && king_square < 56){
        int val = king_square + UP_LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if ((!(curr_pieces_board & shifted_square)) && (attack[val].bits == 0)){
            if (!king_attack_set.fields.DOWN_RIGHT || 
                (SHIFT(king_square + king_attack_set.fields.DOWN_RIGHT * DOWN_RIGHT_VAL) & other_pieces->pawn)) {
                
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.UP_LEFT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }

    //up right 
    if (king_square % 8 != 0 && king_square < 56){
        int val = king_square + UP_RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if ((!(curr_pieces_board & shifted_square)) && (attack[val].bits == 0)){
             if (!king_attack_set.fields.DOWN_LEFT || 
                (SHIFT(king_square + king_attack_set.fields.DOWN_LEFT * DOWN_LEFT_VAL) & other_pieces->pawn)){
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.UP_RIGHT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }

    //down left 
    if(king_square % 8 != 7  && king_square > 7){
        int val = king_square + DOWN_LEFT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if ((!(curr_pieces_board & shifted_square)) && (attack[val].bits == 0)){
            if (!king_attack_set.fields.UP_RIGHT || 
                (SHIFT(king_square + king_attack_set.fields.UP_RIGHT * UP_RIGHT_VAL) & other_pieces->pawn)){
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.DOWN_LEFT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }

    //down right
    if (king_square % 8 != 0 && king_square > 7){
        int val = king_square + DOWN_RIGHT_VAL;
        uint64_t shifted_square = SHIFT(val);
        if ((!(curr_pieces_board & shifted_square)) && (attack[val].bits == 0)){
            if (!king_attack_set.fields.UP_LEFT || 
                (SHIFT(king_square + king_attack_set.fields.UP_LEFT * UP_LEFT_VAL) & other_pieces->pawn)){
                if (other_pieces_board & shifted_square){
                    if (do_capture || !king_attack_set.fields.DOWN_RIGHT){
                        addMove(board, king_square, val, 0, getPieceCode(shifted_square, other_pieces));
                    }
                }
                else{
                    addMove(board, king_square, val, 0, 0);
                }
            }
        }
    }
}

inline uint8_t checkStraightCheck(AttackSet attack, int target_square, Pieces* other_pieces){
    if (!(GET_LINE_HITS(attack.bits))){
        return 0;
    }

    uint64_t line_pieces = other_pieces->bishop | other_pieces->rook | other_pieces->pawn | other_pieces->queen;
    uint8_t count = 0; 
    uint8_t curr = 0; 

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

inline uint8_t inCheck(Board* board){

    int king_square = board->current_king_square;
    if (!(board->other_attack_set[king_square].bits)){
        return 0;
    }

    else{
        Pieces* other_pieces = board->other_pieces;

        AttackSet attack = board->other_attack_set[king_square];
        int target_square = king_square;
        if (GET_N_HITS(attack.bits)){
            if (GET_LINE_HITS(attack.bits)){
                return 2; 
            }
            else{
                return 3;
            }

        }
        return checkStraightCheck(attack, target_square, other_pieces);
    }
}

inline  bool leavesInCheck(Board* board, uint8_t from_square, uint8_t to_square, bool is_ep) {
    uint32_t king_square = board->current_king_square;
    AttackSet* opp_attack_set = board->other_attack_set;
    Pieces* other_pieces = board->other_pieces;
    uint64_t occupied_squares = board->getOccupiedSquares();

    if (from_square == king_square){
        return (opp_attack_set[to_square].bits != 0);
    }

    //handle edge case w/ en pessant (both pawns disappear from the same rank w/ the king)
    if (is_ep){
        int diff = board->white_to_move ? -8 : 8; 
        if (king_square / 8 == (uint32_t) ((board->en_pass_square + diff) / 8)){
            int left;
            int right;
            if ((board->en_pass_square + diff) > from_square){
                left = board->en_pass_square + diff; 
                right = from_square;
            }
            else{
                left = from_square ; 
                right = board->en_pass_square + diff;
            }

            bool king_direction_left = king_square > from_square;
            
            if (king_direction_left){
                if(opp_attack_set[right].fields.RIGHT &&
                    (SHIFT(right + opp_attack_set[right].fields.RIGHT*RIGHT_VAL) & (other_pieces->rook | other_pieces->queen))){
                    for (int j = king_square + RIGHT_VAL; j != left; j+= RIGHT_VAL){
                        if (SHIFT(j) & occupied_squares){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else{
                if(opp_attack_set[left].fields.LEFT &&
                    (SHIFT(left + opp_attack_set[left].fields.LEFT*LEFT_VAL) & (other_pieces->rook | other_pieces->queen))){
                    for (int j = king_square + LEFT_VAL; j != right; j+= LEFT_VAL){
                        if (SHIFT(j) & occupied_squares){
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    
    //same file 
    if ((from_square - king_square) % 8 == 0){
        if ((to_square - king_square) % 8 == 0){
            return false; 
        }

        bool is_up = king_square > from_square;
        if (is_up){
            if(opp_attack_set[from_square].fields.DOWN && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.DOWN*DOWN_VAL) & (other_pieces->rook | other_pieces->queen))){
                for (int j = king_square + DOWN_VAL; j != from_square; j+= DOWN_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true; 
            }
            return false;
        }
        else{
            if(opp_attack_set[from_square].fields.UP && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.UP*UP_VAL) & (other_pieces->rook | other_pieces->queen))){
                for (int j = king_square + UP_VAL; j != from_square; j+= UP_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }

    //same row 
    if ((from_square / 8 == king_square / 8)){  
        if (to_square / 8 == king_square / 8){
            return false; 
        }

        bool is_left = king_square > from_square;
        if (is_left){
            if(opp_attack_set[from_square].fields.RIGHT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.RIGHT*RIGHT_VAL) & (other_pieces->rook | other_pieces->queen))){
                for (int j = king_square + RIGHT_VAL; j != from_square; j+= RIGHT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        else{
            if(opp_attack_set[from_square].fields.LEFT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.LEFT*LEFT_VAL) & (other_pieces->rook | other_pieces->queen))){
                for (int j = king_square + LEFT_VAL; j != from_square; j+= LEFT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }

    if (isSameDiag(from_square, king_square)){
        if (isSameDiag(to_square, king_square)){
            return false; 
        }

        bool is_up = king_square > from_square;

         if (is_up){
            if(opp_attack_set[from_square].fields.DOWN_LEFT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.DOWN_LEFT*DOWN_LEFT_VAL) & (other_pieces->bishop | other_pieces->queen))){
                for (int j = king_square + DOWN_LEFT_VAL; j != from_square; j+= DOWN_LEFT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        else{
            if(opp_attack_set[from_square].fields.UP_RIGHT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.UP_RIGHT*UP_RIGHT_VAL) & (other_pieces->bishop | other_pieces->queen))){
                for (int j = king_square + UP_RIGHT_VAL; j != from_square; j+= UP_RIGHT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }

    if (isSameAntiDiag(from_square, king_square)){
        if (isSameAntiDiag(to_square, king_square)){
            return false; 
        }

        bool is_up = king_square > from_square;
        if (is_up){
            if(opp_attack_set[from_square].fields.DOWN_RIGHT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.DOWN_RIGHT*DOWN_RIGHT_VAL) & (other_pieces->bishop | other_pieces->queen))){
                for (int j = king_square + DOWN_RIGHT_VAL; j != from_square; j+= DOWN_RIGHT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        else{
            if(opp_attack_set[from_square].fields.UP_LEFT && 
                (SHIFT(from_square + opp_attack_set[from_square].fields.UP_LEFT*UP_LEFT_VAL) & (other_pieces->bishop | other_pieces->queen))){
                for (int j = king_square + UP_LEFT_VAL; j != from_square; j+= UP_LEFT_VAL){
                    if (SHIFT(j) & occupied_squares){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }

    return false;
}

inline void generatePawnBlocks(Board* board, int current_square, uint64_t occupied_squares, uint64_t curr_pawns){
    //generate pawn moves for pawns 
    if (board->white_to_move && current_square >= 16){
        if (curr_pawns & SHIFT(current_square - 8)){
            if (!leavesInCheck(board, current_square - 8, current_square, false)){
                if (current_square >= 56){
                    addMove(board, current_square - 8, current_square, N_PROMO, 0);
                    addMove(board, current_square - 8, current_square, B_PROMO, 0);
                    addMove(board, current_square - 8, current_square, ROOK_PROMO, 0);
                    addMove(board, current_square - 8, current_square, QUEEN_PROMO, 0);
                }
                else{
                    addMove(board, current_square - 8, current_square, 0, 0);
                }

            }
        }
        else{
            if (current_square < 32 && current_square >= 24){
                if ((SHIFT(current_square - 16) & curr_pawns) && 
                    !(SHIFT(current_square - 8) & occupied_squares)){
                    if (!leavesInCheck(board, current_square - 16, current_square, false)){
                        addMove(board, current_square - 16, current_square, 0, 0);
                    }
                }
            } 
        }
        
    }

    if (!board->white_to_move && current_square < 48){
        if (curr_pawns & SHIFT(current_square + 8)){
            if (!leavesInCheck(board, current_square + 8, current_square, false)){
                if (current_square < 8){
                    addMove(board, current_square + 8, current_square, N_PROMO, 0);
                    addMove(board, current_square + 8, current_square, B_PROMO, 0);
                    addMove(board, current_square + 8, current_square, ROOK_PROMO, 0);
                    addMove(board, current_square + 8, current_square, QUEEN_PROMO, 0);    
                }
                else{
                    addMove(board, current_square + 8, current_square, 0, 0);
                }
            }
        }
        else{
            if (current_square >= 32 && current_square < 40){
                if ((SHIFT(current_square + 16) & curr_pawns) && 
                    !(SHIFT(current_square + 8) & occupied_squares)){
                    if (!leavesInCheck(board, current_square + 16, current_square, false)){
                        addMove(board, current_square + 16, current_square, 0, 0);
                    }
                }
            }    
        }
    }
}

inline void generateMovesToSquare(Board *board, int to_square, uint64_t other_pieces_board){

    AttackSet current_attack_set = board->current_attack_set[to_square];
    Pieces* other_pieces = board->other_pieces;
    if (current_attack_set.fields.LEFT){
        int from_square = to_square + current_attack_set.fields.LEFT * LEFT_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.LEFT = 0;
        if (current_attack_set.bits == 0)
            return;
    }



    if (current_attack_set.fields.UP){
        int from_square = to_square + current_attack_set.fields.UP * UP_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.UP = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.RIGHT){
        int from_square = to_square + current_attack_set.fields.RIGHT * RIGHT_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.RIGHT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.DOWN){
        int from_square = to_square + current_attack_set.fields.DOWN * DOWN_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.DOWN = 0;
        if (current_attack_set.bits == 0)
            return;    
    }


    if (current_attack_set.fields.UP_LEFT){
        int from_square = to_square + current_attack_set.fields.UP_LEFT * UP_LEFT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square && board->en_pass_square != 0) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        } 
        current_attack_set.fields.UP_LEFT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.UP_RIGHT){
        int from_square = to_square + current_attack_set.fields.UP_RIGHT * UP_RIGHT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }
        current_attack_set.fields.UP_RIGHT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.DOWN_RIGHT){
        int from_square = to_square + current_attack_set.fields.DOWN_RIGHT * DOWN_RIGHT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }  
        current_attack_set.fields.DOWN_RIGHT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.DOWN_LEFT){
        int from_square = to_square + current_attack_set.fields.DOWN_LEFT * DOWN_LEFT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }
        current_attack_set.fields.DOWN_LEFT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_UL_SHORT){
        int from_square = to_square + N_UL_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UL_SHORT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_UL_TALL){
        int from_square = to_square + N_UL_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UL_TALL = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_UR_TALL){
        int from_square = to_square + N_UR_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UR_TALL = 0;
        if (current_attack_set.bits == 0)
            return;    
    }
    if (current_attack_set.fields.N_UR_SHORT){
        int from_square = to_square + N_UR_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UR_SHORT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_DR_SHORT){
        int from_square = to_square + N_DR_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DR_SHORT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_DR_TALL){
        int from_square = to_square + N_DR_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DR_TALL = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_DL_TALL){
        int from_square = to_square + N_DL_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DL_TALL = 0;
        if (current_attack_set.bits == 0)
            return;    
    }

    if (current_attack_set.fields.N_DL_SHORT){
        int from_square = to_square + N_DL_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DL_SHORT = 0;
        if (current_attack_set.bits == 0)
            return;    
    }
}

inline void generateCastleMoves(Board* board){
    if (board->white_to_move){
        if (board->castle_rights.white_k_castle){
            AttackSet* attack = board->other_attack_set;
            uint64_t occupied_squares = board->getOccupiedSquares(); 
            if (!(occupied_squares & 0x6)){
                if (!attack[1].bits && !attack[2].bits){
                    addMove(board, 3, 1, 1, 0);
                }
            }   
        }
        if (board->castle_rights.white_q_castle){
            AttackSet* attack = board->other_attack_set;
            uint64_t occupied_squares = board->getOccupiedSquares(); 
            if (!(occupied_squares & 0x70)){
                if (!attack[4].bits && !attack[5].bits){
                    addMove(board, 3, 5, 2, 0);
                }
            }
        }
        return;
    }
    else{
        if (board->castle_rights.black_k_castle){
            AttackSet* attack = board->other_attack_set;
            uint64_t occupied_squares = board->getOccupiedSquares(); 
            if (!(occupied_squares & 0x600000000000000)){
                if (!attack[57].bits && !attack[58].bits){
                    addMove(board, 59, 57, 1, 0);
                }
            }
        }
        if (board->castle_rights.black_q_castle){
            AttackSet* attack = board->other_attack_set;
            uint64_t occupied_squares = board->getOccupiedSquares(); 
            if (!(occupied_squares & 0x7000000000000000)){
                if (!attack[60].bits && !attack[61].bits){
                    addMove(board, 59, 61, 2, 0);
                }
            }
        }
    }
}

inline  void generateWhitePawnMoves(Board *board, int from_square, uint64_t occupied_squares){
    if (SHIFT(from_square + 8) & occupied_squares){
        return;
    }

    if (leavesInCheck(board, from_square, from_square + 8, false)){
        return;
    }

    if (from_square >= 48){
        addMove(board, from_square, from_square + 8, N_PROMO, 0);
        addMove(board, from_square, from_square + 8, B_PROMO, 0);
        addMove(board, from_square, from_square + 8, ROOK_PROMO, 0);
        addMove(board, from_square, from_square + 8, QUEEN_PROMO, 0);
        return;
    }

    addMove(board, from_square, from_square + 8, 0, 0);
    if (from_square < 16 && !(SHIFT(from_square + 16) & occupied_squares)){
        addMove(board, from_square, from_square + 16, 0, 0);
    }
}

inline void generateBlackPawnMoves(Board *board, int from_square, uint64_t occupied_squares){
    if (SHIFT(from_square - 8) & occupied_squares){
        return;
    }

    if (leavesInCheck(board, from_square, from_square - 8, false)){
        return;
    }

    if (from_square < 16){
        addMove(board, from_square, from_square - 8, N_PROMO, 0);
        addMove(board, from_square, from_square - 8, B_PROMO, 0);
        addMove(board, from_square, from_square - 8, ROOK_PROMO, 0);
        addMove(board, from_square, from_square - 8, QUEEN_PROMO, 0);
        return;
    }

    addMove(board, from_square, from_square - 8, 0, 0);
    if (from_square >= 48 && !(SHIFT(from_square - 16) & occupied_squares)){
        addMove(board, from_square, from_square - 16, 0, 0);
    }
}

inline  void generateAllPawnMoves(Board *board){
    uint64_t occupied_squares = board->getOccupiedSquares();
    uint64_t pawn_mask = board->current_pieces->pawn;
    unsigned long index;
    if (board->white_to_move){
        while (pawn_mask){
            _BitScanForward64(&index, pawn_mask);
            generateWhitePawnMoves(board, index, occupied_squares);
            pawn_mask ^= SHIFT(index);
        }
    }
    else{
        while (pawn_mask){
            _BitScanForward64(&index, pawn_mask);
            generateBlackPawnMoves(board, index, occupied_squares);
            pawn_mask ^= SHIFT(index);
        }
    }
}

inline void generateMovesToSquareOld(Board *board, int to_square, uint64_t other_pieces_board){

    AttackSet current_attack_set = board->current_attack_set[to_square];
    Pieces* other_pieces = board->other_pieces;
    if (current_attack_set.fields.LEFT){
        int from_square = to_square + current_attack_set.fields.LEFT * LEFT_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.LEFT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.UP){
        int from_square = to_square + current_attack_set.fields.UP * UP_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.UP = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.RIGHT){
        int from_square = to_square + current_attack_set.fields.RIGHT * RIGHT_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.RIGHT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.DOWN){
        int from_square = to_square + current_attack_set.fields.DOWN * DOWN_VAL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.DOWN = 0; 
        if (!current_attack_set.bits)
            return;
    }


    if (current_attack_set.fields.UP_LEFT){
        int from_square = to_square + current_attack_set.fields.UP_LEFT * UP_LEFT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        } 
        current_attack_set.fields.UP_LEFT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.UP_RIGHT){
        int from_square = to_square + current_attack_set.fields.UP_RIGHT * UP_RIGHT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }
        current_attack_set.fields.UP_RIGHT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.DOWN_RIGHT){
        int from_square = to_square + current_attack_set.fields.DOWN_RIGHT * DOWN_RIGHT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }  
        current_attack_set.fields.DOWN_RIGHT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.DOWN_LEFT){
        int from_square = to_square + current_attack_set.fields.DOWN_LEFT * DOWN_LEFT_VAL; 
        uint64_t shifted_square = SHIFT(to_square);
        if (SHIFT(from_square) & board->current_pieces->pawn){
            if ((shifted_square & other_pieces_board)){
                if (!leavesInCheck(board, from_square, to_square, false)){
                    int code = getPieceCode(shifted_square, other_pieces);
                    if (to_square < 8 || to_square >= 56){
                        addMove(board, from_square, to_square, N_PROMO, code);
                        addMove(board, from_square, to_square, B_PROMO, code);
                        addMove(board, from_square, to_square, ROOK_PROMO, code);
                        addMove(board, from_square, to_square, QUEEN_PROMO, code);
                    }
                    else{
                        addMove(board, from_square, to_square, 0, code);
                    }
                }
            }
            else{
                if((to_square == board->en_pass_square) && (!leavesInCheck(board, from_square, to_square, true))){
                    addMove(board, from_square, to_square, EP, 1);
                }
            }
        }
        else{
            if (!leavesInCheck(board, from_square, to_square, false)){
                int code = 0; 
                if (shifted_square & other_pieces_board){
                    code = getPieceCode(shifted_square, other_pieces);
                }
                addMove(board, from_square, to_square, 0, code);
            }
        }
        current_attack_set.fields.DOWN_LEFT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_UL_SHORT){
        int from_square = to_square + N_UL_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UL_SHORT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_UL_TALL){
        int from_square = to_square + N_UL_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UL_TALL = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_UR_TALL){
        int from_square = to_square + N_UR_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UR_TALL = 0; 
        if (!current_attack_set.bits)
            return;
    }
    if (current_attack_set.fields.N_UR_SHORT){
        int from_square = to_square + N_UR_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_UR_SHORT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_DR_SHORT){
        int from_square = to_square + N_DR_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DR_SHORT = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_DR_TALL){
        int from_square = to_square + N_DR_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DR_TALL = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_DL_TALL){
        int from_square = to_square + N_DL_TALL; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DL_TALL = 0; 
        if (!current_attack_set.bits)
            return;
    }

    if (current_attack_set.fields.N_DL_SHORT){
        int from_square = to_square + N_DL_SHORT; 
        if (!leavesInCheck(board, from_square, to_square, false)){
            uint64_t shifted_square = SHIFT(to_square);
            int code = 0; 
            if (shifted_square & other_pieces_board){
                code = getPieceCode(shifted_square, other_pieces);
            }
            addMove(board, from_square, to_square, 0, code);
        }
        current_attack_set.fields.N_DL_SHORT = 0; 
        if (!current_attack_set.bits)
            return;
    }
}

inline void generateBlockMoves(Board* board, uint8_t code){

    AttackSet* curr_attack_set = board->current_attack_set;
    int king_square = board->current_king_square;
    uint64_t other_pieces = board->getOtherPieces();
    uint64_t curr_pawns = board->current_pieces->pawn;
    uint64_t occupied_squares = board->getOccupiedSquares();

    int diff = code_to_val[code];
    int current_square = king_square + diff;

    while (!(SHIFT(current_square) & other_pieces)){

        generatePawnBlocks(board, current_square, occupied_squares, curr_pawns);

        if (curr_attack_set[current_square].bits == 0){
            current_square+= diff;
            continue;
        }

        generateMovesToSquareOld(board, current_square, other_pieces);
        
        current_square += diff;
    }

    if (curr_attack_set[current_square].bits != 0){
        generateMovesToSquareOld(board, current_square, other_pieces);
    }

    //ep edge case 
    if (board->en_pass_square != 0 && (board->other_pieces->pawn & SHIFT(king_square + diff))){
        uint64_t curr_pawns = board->current_pieces->pawn; 
        int pawn_check = king_square + diff; 
        if (pawn_check % 8 != 0 && (curr_pawns & SHIFT(pawn_check - 1))){
            if (!leavesInCheck(board, pawn_check - 1, board->en_pass_square, true)){
                addMove(board, pawn_check - 1, board->en_pass_square, EP, 1);
            }
        }

        if (pawn_check % 8 != 7 && (curr_pawns & (SHIFT(pawn_check + 1)))){
            if (!leavesInCheck(board, pawn_check + 1, board->en_pass_square, true)){
                addMove(board, pawn_check + 1, board->en_pass_square, EP, 1);
            }
        }

    }
}

inline void generateTakeKnight(Board* board){
    AttackSet king = board->other_attack_set[board->current_king_square];
    if (king.fields.N_DL_SHORT){
        generateMovesToSquare(board, board->current_king_square + N_DL_SHORT, board->getOtherPieces());
        return;
    }
    if (king.fields.N_DL_TALL){
        generateMovesToSquare(board, board->current_king_square + N_DL_TALL, board->getOtherPieces());
        return;
    }

    if (king.fields.N_DR_SHORT){
        generateMovesToSquare(board, board->current_king_square + N_DR_SHORT, board->getOtherPieces());
        return;
    }

    if (king.fields.N_DR_TALL){
        generateMovesToSquare(board, board->current_king_square + N_DR_TALL, board->getOtherPieces());
        return;
    }
    if (king.fields.N_UL_SHORT){
        generateMovesToSquare(board, board->current_king_square + N_UL_SHORT, board->getOtherPieces());
        return;
    }
    if (king.fields.N_UL_TALL){
        generateMovesToSquare(board, board->current_king_square + N_UL_TALL, board->getOtherPieces());
        return;
    }
    if (king.fields.N_UR_SHORT){
        generateMovesToSquare(board, board->current_king_square + N_UR_SHORT, board->getOtherPieces());
        return;
    }

    if (king.fields.N_UR_TALL){
        generateMovesToSquare(board, board->current_king_square + N_UR_TALL, board->getOtherPieces());
        return;
    }
    

}

uint32_t generateAllMoves(Board *board, Move* move_list){

    
    board->move_list = move_list;
    board->curr_num_moves = 0; 
    uint8_t check = inCheck(board);
    if (check){
        board->in_check = true; 
        if (check == 2){
            generateKingMoves(board, true);
        }
        else{
            if (check == 3){
                generateTakeKnight(board);
                generateKingMoves(board, false);
            }
            else{
                uint8_t code = check >> 4; 
                generateBlockMoves(board, code);
                generateKingMoves(board, false);
            }
        }
        //generate king moves 


        return board->curr_num_moves;
    }

    board->in_check = false; 

    uint64_t other_pieces_board = board->getOtherPieces(); 
    uint64_t curr_pieces_board = board->getCurrentPieces();
    AttackSet* curr_attack_set = board->current_attack_set;
    int8_t i = 64; 
    while (i != 0){
        i--;
        if ((curr_attack_set[i].bits != 0) && !(SHIFT(i) & curr_pieces_board) ){
            generateMovesToSquare(board, i, other_pieces_board);
        }
    }

    generateAllPawnMoves(board); 
    generateCastleMoves(board);

    return board->curr_num_moves;
}