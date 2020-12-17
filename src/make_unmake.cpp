#include "../include/make_unmake.hpp"
#include "../include/board.hpp"


inline void removeKing(attack_set* attack_set, int square){
    //up 
    if (square < 56){
        attack_set[square + UP_VAL].fields.DOWN = 0; 
    }

    //down
    if (square > 7){
        attack_set[square + DOWN_VAL].fields.UP = 0;
    }

    //left
    if (square % 8 != 7){
        attack_set[square + LEFT_VAL].fields.RIGHT = 0;
    }

    //right 
    if (square % 8 != 0){
        attack_set[square + RIGHT_VAL].fields.LEFT = 0;
    }

    //up left 
    if (square % 8 != 7 && square < 56){
        attack_set[square + UP_LEFT_VAL].fields.DOWN_RIGHT = 0; 
    }

    //up right 
    if (square % 8 != 0 && square < 56){
        attack_set[square + UP_RIGHT_VAL].fields.DOWN_LEFT = 0;
    }

    //down left 
    if(square % 8 != 7  && square > 7){
        attack_set[square + DOWN_LEFT_VAL].fields.UP_RIGHT = 0;
    }

    //down right
    if (square % 8 != 0 && square > 7){
        attack_set[square + DOWN_RIGHT_VAL].fields.UP_LEFT = 0;
    }
}
inline void removePawn(Board* board, attack_set* attack_set, int square, bool is_white){
    if (is_white){
        attack_set[square + UP_LEFT_VAL].fields.DOWN_RIGHT = 0; 
        attack_set[square + UP_RIGHT_VAL].fields.DOWN_LEFT = 0; 
    }
    else{
        attack_set[square + DOWN_LEFT_VAL].fields.UP_RIGHT = 0; 
        attack_set[square + DOWN_RIGHT_VAL].fields.UP_LEFT = 0; 
    }
}
inline void removeRook(Board* board, attack_set* attack_set, int from, uint64_t occupied_squares){
    int curr = from + LEFT_VAL;
    while (curr % 8 != 0){
        attack_set[curr].fields.RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += LEFT_VAL; 
    }

    curr = from + UP_VAL; 
    while (curr < 64){
        attack_set[curr].fields.DOWN = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += UP_VAL; 
    }


    curr = from + RIGHT_VAL; 
    while ((unsigned) curr % 8 != 7 ){
        attack_set[curr].fields.LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += RIGHT_VAL; 
    }

    curr = from + DOWN_VAL; 
    while (curr >= 0){
        attack_set[curr].fields.UP = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_VAL;
    }

}
inline void removeBishop(Board* board, attack_set* attack_set, int square, uint64_t occupied_squares){
    //go each direction until you hit smth 

   //go each direction until you hit smth 

    int curr = square + UP_LEFT_VAL; 
    while (curr % 8 != 0 && curr < 64){
        attack_set[curr].fields.DOWN_RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr+= UP_LEFT_VAL;
    }


    curr = square + UP_RIGHT_VAL; 
    while (curr % 8 != 7 && curr < 64){
        attack_set[curr].fields.DOWN_LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += UP_RIGHT_VAL;
    }

    curr = square + DOWN_RIGHT_VAL; 
    while (curr % 8 != 7 && curr >= 0){
        attack_set[curr].fields.UP_LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_RIGHT_VAL;
    }

 
    curr = square + DOWN_LEFT_VAL; 
    while (curr % 8 != 0 && curr > 0){
        attack_set[curr].fields.UP_RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_LEFT_VAL;
    }

}
/* can change this to avoid shifting and just seeing if the value increases like i did for block */
inline void removeQueen(Board* board, attack_set* attack_set, int from, uint64_t occupied_squares){
    int curr = from + LEFT_VAL;
    while (curr % 8 != 0){
        attack_set[curr].fields.RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += LEFT_VAL; 
    }

    curr = from + UP_LEFT_VAL; 
    while (curr % 8 != 0 && curr < 64){
        attack_set[curr].fields.DOWN_RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr+= UP_LEFT_VAL;
    }

    curr = from + UP_VAL; 
    while (curr < 64){
        attack_set[curr].fields.DOWN = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += UP_VAL; 
    }

    curr = from + UP_RIGHT_VAL; 
    while (curr % 8 != 7 && curr < 64){
        attack_set[curr].fields.DOWN_LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += UP_RIGHT_VAL;
    }

    curr = from + RIGHT_VAL; 
    while ((unsigned) curr % 8 != 7 ){
        attack_set[curr].fields.LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += RIGHT_VAL; 
    }

    curr = from + DOWN_RIGHT_VAL; 
    while (curr % 8 != 7 && curr >= 0){
        attack_set[curr].fields.UP_LEFT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_RIGHT_VAL;
    }

    curr = from + DOWN_VAL; 
    while (curr >= 0){
        attack_set[curr].fields.UP = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_VAL;
    }

    curr = from + DOWN_LEFT_VAL; 
    while (curr % 8 != 0 && curr > 0){
        attack_set[curr].fields.UP_RIGHT = 0; 
        if ((SHIFT(curr) & occupied_squares)){
            break;
        }
        curr += DOWN_LEFT_VAL;
    }
}
inline void removeKnight(attack_set* attack_set, int from){

    //ul short 
    if (from % 8 < 6 && from < 56){
        attack_set[from + N_UL_SHORT].fields.N_DR_SHORT = 0;
    }

    //ul tall 
    if (from % 8 != 7 && from < 48){
        attack_set[from + N_UL_TALL].fields.N_DR_TALL = 0;
    }

    //ur tall 
    if (from % 8 != 0 && from < 48){
        attack_set[from + N_UR_TALL].fields.N_DL_TALL = 0;
    }

    //ur short 
    if (from % 8 > 1 && from < 56){
        attack_set[from + N_UR_SHORT].fields.N_DL_SHORT = 0;
    }

    //dr short 
    if (from % 8 > 1 && from > 7){
        attack_set[from + N_DR_SHORT].fields.N_UL_SHORT = 0;
    }

    //dr tall
    if (from % 8 != 0 && from > 15){
        attack_set[from + N_DR_TALL].fields.N_UL_TALL = 0;
    } 

    //dl tall 
    if (from % 8 != 7 && from > 15){
        attack_set[from + N_DL_TALL].fields.N_UR_TALL = 0;
    }

    //dl short 
    if (from % 8 < 6 && from > 7){
        attack_set[from + N_DL_SHORT].fields.N_UR_SHORT = 0;
    }
}

inline void removeCapturePiece(Board* board, attack_set* attack_set, int square, int code, uint64_t ouccpied_squares){
    switch(code){
        case 1:    
            removePawn(board, attack_set, square, !board->white_to_move);
            board->other_pieces->pawn ^= SHIFT(square);
            return;
        case 2: 
            removeKnight(attack_set, square);
            board->other_pieces->knight ^= SHIFT(square);
            return; 
        case 3: 
            removeBishop(board, attack_set, square, ouccpied_squares);
            board->other_pieces->bishop ^= SHIFT(square);
            return;
        case 4: 
            if (square == 0){
                board->castle_rights.white_k_castle = 0; 
            }
            else{
                if (square == 7){
                    board->castle_rights.white_q_castle = 0; 
                }
                else{
                    if (square == 56){
                        board->castle_rights.black_k_castle = 0; 
                    }
                    else{
                        if (square == 63){
                            board->castle_rights.black_q_castle = 0; 
                        }
                    }
                }
            }
            removeRook(board, attack_set, square, ouccpied_squares); 
            board->other_pieces->rook ^= SHIFT(square);
            return; 
        case 5: 
            removeQueen(board, attack_set, square, ouccpied_squares);
            board->other_pieces->queen ^= SHIFT(square);
            return;
        default: 
            return;
    }
}

inline void extendRayAttack(Board* board, attack_set* attack_set, int square, uint64_t occupied_squares, uint64_t lat_pieces, uint64_t diags){
    int curr = attack_set[square].fields.LEFT; 
    if (curr != 0){
        if (SHIFT((square + curr*LEFT_VAL)) & lat_pieces){
            int new_sq = square + RIGHT_VAL; 
            while ((unsigned) new_sq % 8 != 7){
                attack_set[new_sq].fields.LEFT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += RIGHT_VAL; 
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.UP_LEFT; 
    if (curr != 0){
        if (SHIFT(square + curr*UP_LEFT_VAL) & diags){
            int new_sq = square + DOWN_RIGHT_VAL; 
            while ((unsigned) new_sq % 8 != 7 && new_sq >= 0){
               attack_set[new_sq].fields.UP_LEFT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += DOWN_RIGHT_VAL;
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.UP; 
    if (curr != 0){
        if (SHIFT(square + curr*UP_VAL) & lat_pieces){
            int new_sq = square + DOWN_VAL; 
            while (new_sq >= 0){
                attack_set[new_sq].fields.UP = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += DOWN_VAL; 
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.UP_RIGHT; 
    if (curr != 0){
        if (SHIFT(square + curr*UP_RIGHT_VAL) & diags){
            int new_sq = square + DOWN_LEFT_VAL; 
            while (new_sq % 8 != 0 && new_sq >= 0){
                attack_set[new_sq].fields.UP_RIGHT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += DOWN_LEFT_VAL;
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.RIGHT; 
    if (curr != 0){
        if (SHIFT(square + curr*RIGHT_VAL) & lat_pieces){
            int new_sq = square + LEFT_VAL; 
            while (new_sq % 8 != 0){
                attack_set[new_sq].fields.RIGHT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += LEFT_VAL; 
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.DOWN_RIGHT; 
    if (curr != 0){
        if (SHIFT(square + curr*DOWN_RIGHT_VAL) & diags){
            int new_sq = square + UP_LEFT_VAL; 
            while ((unsigned) new_sq % 8 != 0 && new_sq < 64){
                attack_set[new_sq].fields.DOWN_RIGHT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += UP_LEFT_VAL;
                curr++;
            }
        }
    }

    curr = attack_set[square].fields.DOWN; 
    if (curr != 0){
        if (SHIFT(square + curr*DOWN_VAL) & lat_pieces){
            int new_sq = square + UP_VAL; 
            while (new_sq < 64){
                attack_set[new_sq].fields.DOWN = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += UP_VAL; 
                curr++;
            }
        }
    }

   curr = attack_set[square].fields.DOWN_LEFT; 
    if (curr != 0){
        if (SHIFT(square + curr*DOWN_LEFT_VAL) & diags){
            int new_sq = square + UP_RIGHT_VAL; 
            while ((unsigned) new_sq % 8 != 7 && new_sq < 64){
                attack_set[new_sq].fields.DOWN_LEFT = curr + 1; 
                if (SHIFT(new_sq) & occupied_squares){
                    break;
                }
                new_sq += UP_RIGHT_VAL;
                curr++;
            }
        }
    }

}
inline void blockRayAttacks(Board* board, attack_set* attack_set, int square){
    int curr; 
    
    int old = attack_set[square].fields.LEFT;
    if(old != 0){
        curr = square + RIGHT_VAL; 
        while ((unsigned) curr % 8 != 7 && attack_set[curr].fields.LEFT > old){
            old++;
            attack_set[curr].fields.LEFT = 0; 
            curr += RIGHT_VAL;
        }
    }

    old = attack_set[square].fields.UP_LEFT;
    if(old != 0){
        curr = square + DOWN_RIGHT_VAL; 
        while ((unsigned) curr % 8 != 7 && curr >= 0 && attack_set[curr].fields.UP_LEFT > old){
            old++;
            attack_set[curr].fields.UP_LEFT = 0; 
            curr += DOWN_RIGHT_VAL;
        }
    }
 
  
    old = attack_set[square].fields.UP;
    if(old != 0){
        curr = square + DOWN_VAL; 
        while (curr >= 0 && attack_set[curr].fields.UP > old){
            old++;
            attack_set[curr].fields.UP = 0; 
            curr += DOWN_VAL;
        }
    }
 
    old = attack_set[square].fields.UP_RIGHT;
    if(old != 0){
        curr = square + DOWN_LEFT_VAL; 
        while ((unsigned) curr % 8 != 0 && curr >= 0 && attack_set[curr].fields.UP_RIGHT > old){
            old++;
            attack_set[curr].fields.UP_RIGHT = 0; 
            curr += DOWN_LEFT_VAL;
        }
    }

    old = attack_set[square].fields.RIGHT;
    if(old != 0){
        curr = square + LEFT_VAL; 
        while ((unsigned) curr % 8 != 0 && attack_set[curr].fields.RIGHT > old){
            old++;
            attack_set[curr].fields.RIGHT = 0; 
            curr += LEFT_VAL;
        }
    }

    old = attack_set[square].fields.DOWN_RIGHT;
    if(old != 0){
        curr = square + UP_LEFT_VAL; 
        while ((unsigned) curr % 8 != 0 && curr < 64 && attack_set[curr].fields.DOWN_RIGHT > old){
            old++;
            attack_set[curr].fields.DOWN_RIGHT = 0; 
            curr += UP_LEFT_VAL;
        }
    }

    old = attack_set[square].fields.DOWN;
    if(old != 0){
        curr = square + UP_VAL; 
        while (curr < 64 && attack_set[curr].fields.DOWN > old){
            old++;
            attack_set[curr].fields.DOWN = 0; 
            curr += UP_VAL;
        }
    }
 
    old = attack_set[square].fields.DOWN_LEFT;
    if(old != 0){
        curr = square + UP_RIGHT_VAL; 
        while ((unsigned) curr % 8 != 7 && curr < 64 && attack_set[curr].fields.DOWN_LEFT > old){
            old++;
            attack_set[curr].fields.DOWN_LEFT = 0; 
            curr += UP_RIGHT_VAL;
        }
    }
}



inline void addDiags(attack_set* attack_set, int square, uint64_t occupied_squares){
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
inline void addLat(attack_set* attack_set, int square, uint64_t occupied_squares){
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
    while ((unsigned) square_num % 8 != 0){
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

inline void addKing(attack_set* attack_set, int square){
    //up 
    if (square < 56){
        attack_set[square + UP_VAL].fields.DOWN = 1; 
    }

    //down
    if (square > 7){
        attack_set[square + DOWN_VAL].fields.UP = 1;
    }

    //left
    if (square % 8 != 7){
        attack_set[square + LEFT_VAL].fields.RIGHT = 1;
    }

    //right 
    if (square % 8 != 0){
        attack_set[square + RIGHT_VAL].fields.LEFT = 1;
    }

    //up left 
    if (square % 8 != 7 && square < 56){
        attack_set[square + UP_LEFT_VAL].fields.DOWN_RIGHT = 1; 
    }

    //up right 
    if (square % 8 != 0 && square < 56){
        attack_set[square + UP_RIGHT_VAL].fields.DOWN_LEFT = 1;
    }

    //down left 
    if(square % 8 != 7  && square > 7){
        attack_set[square + DOWN_LEFT_VAL].fields.UP_RIGHT = 1;
    }

    //down right
    if (square % 8 != 0 && square > 7){
        attack_set[square + DOWN_RIGHT_VAL].fields.UP_LEFT = 1;
    }
}

inline void addKnight(attack_set* attack_set, int square){

    //ul short 
    if ((unsigned) square % 8 < 6 && square < 56){
        attack_set[square + N_UL_SHORT].fields.N_DR_SHORT = 1;
    }

    //ul tall 
    if ((unsigned) square % 8 != 7 && square < 48){
        attack_set[square + N_UL_TALL].fields.N_DR_TALL = 1;
    }

    //ur tall 
    if ((unsigned) square % 8 != 0 && square < 48){
        attack_set[square + N_UR_TALL].fields.N_DL_TALL = 1;;
    }

    //ur short 
    if ((unsigned) square % 8 > 1 && square < 56){
        attack_set[square + N_UR_SHORT].fields.N_DL_SHORT = 1;;
    }

    //dr short 
    if ((unsigned) square % 8 > 1 && square > 7){
        attack_set[square + N_DR_SHORT].fields.N_UL_SHORT = 1;
    }

    //dr tall
    if ((unsigned) square % 8 != 0 && square > 15){
        attack_set[square + N_DR_TALL].fields.N_UL_TALL = 1;
    } 

    //dl tall 
    if ((unsigned) square % 8 != 7 && square > 15){
        attack_set[square + N_DL_TALL].fields.N_UR_TALL = 1;
    }

    //dl short 
    if ((unsigned) square % 8 < 6 && square > 7){
        attack_set[square + N_DL_SHORT].fields.N_UR_SHORT = 1;
    }
}
inline void addWhitePawn(attack_set* attack_set, int square){
    if (square % 8 != 7){
        attack_set[square + UP_LEFT_VAL].fields.DOWN_RIGHT = 1;
    }
    
    if (square % 8 != 0){
        attack_set[square + UP_RIGHT_VAL].fields.DOWN_LEFT = 1;
    }
}
inline void addBlackPawn(attack_set* attack_set, int square){
    if (square % 8 != 7){
        attack_set[square + DOWN_LEFT_VAL].fields.UP_RIGHT = 1;
    }
    
    if (square % 8 != 0){
        attack_set[square + DOWN_RIGHT_VAL].fields.UP_LEFT = 1;
    }
}


inline void addQueen(attack_set* curr_attack_set, int square, uint64_t occupied_squares){
    addDiags(curr_attack_set, square, occupied_squares);
    addLat(curr_attack_set, square, occupied_squares);
}

inline void blockRays(Board* board, int square){
    blockRayAttacks(board, board->current_attack_set, square);
    blockRayAttacks(board, board->other_attack_set, square);
}
inline void extendRays(Board* board, int square, uint64_t occupied_squares){
    uint64_t queens = board->white_pieces.queen | board->black_pieces.queen;
    uint64_t lat_pieces = board->white_pieces.rook | board->black_pieces.rook | queens; 
    uint64_t diags = board->white_pieces.bishop | board->black_pieces.bishop | queens;
    extendRayAttack(board, board->current_attack_set, square, occupied_squares, lat_pieces, diags);
    extendRayAttack(board, board->other_attack_set, square, occupied_squares, lat_pieces, diags);    
}


inline void addCapturePiece(Board* board, attack_set* attack_set, int square, int code, uint64_t ouccpied_squares){
    switch(code){
        case 1:
            if (board->white_to_move){
                addWhitePawn(attack_set, square); 
            } 
            else{
                addBlackPawn(attack_set, square); 
            }  
            board->current_pieces->pawn |= SHIFT(square);
            return;
        case 2: 
            addKnight(attack_set, square);
            board->current_pieces->knight |= SHIFT(square);
            return; 
        case 3: 
            addDiags(attack_set, square, ouccpied_squares);
            board->current_pieces->bishop |= SHIFT(square);
            return;
        case 4: 
            addLat(attack_set, square, ouccpied_squares); 
            board->current_pieces->rook |= SHIFT(square);
            return; 
        case 5: 
            addQueen(attack_set, square, ouccpied_squares);
            board->current_pieces->queen |= SHIFT(square);
            return;
        default: 
            return;
    }
}



inline void handleKCastle(Board* board, bool is_white){
    if (is_white){
        removeRook(board, board->current_attack_set, 0, board->getOccupiedSquares());
        removeKing(board->current_attack_set, 3);
        board->current_attack_set[2].fields.LEFT = board->current_attack_set[3].fields.LEFT ? board->current_attack_set[3].fields.LEFT + 1 : 0 ; 
        board->white_pieces.king = 2; 
        board->white_pieces.rook ^= 1; 
        board->white_pieces.rook |= 4;
        board->white_king_square = 1;
        addKing(board->current_attack_set, 1);
        addLat(board->current_attack_set, 2, board->getOccupiedSquares()); 
    }
    else{
        removeRook(board, board->current_attack_set, 56, board->getOccupiedSquares());
        removeKing(board->current_attack_set, 59);
        board->current_attack_set[58].fields.LEFT = board->current_attack_set[59].fields.LEFT ? board->current_attack_set[59].fields.LEFT + 1 : 0; 
        board->black_pieces.king = 0x200000000000000; 
        board->black_pieces.rook ^= 0x100000000000000; 
        board->black_pieces.rook |= 0x400000000000000;
        board->black_king_square = 57;
        addKing(board->current_attack_set, 57);
        addLat(board->current_attack_set, 58, board->getOccupiedSquares()); 
    }
}

inline void handleKUnCastle(Board* board, bool is_white){
    if (is_white){
        removeRook(board, board->other_attack_set, 2, board->getOccupiedSquares());
        removeKing(board->other_attack_set, 1);
        board->white_pieces.king = 0x8; 
        board->white_pieces.rook ^= 4; 
        board->white_pieces.rook |= 1;
        board->white_king_square = 3;
        addKing(board->other_attack_set, 3);
        addLat(board->other_attack_set, 0, board->getOccupiedSquares()); 
    }
    else{
        removeRook(board, board->other_attack_set, 58, board->getOccupiedSquares());
        removeKing(board->other_attack_set, 57);
        board->black_pieces.king = 0x800000000000000; 
        board->black_pieces.rook |= 0x100000000000000; 
        board->black_pieces.rook ^= 0x400000000000000;
        board->black_king_square = 59;
        addKing(board->other_attack_set, 59);
        addLat(board->other_attack_set, 56, board->getOccupiedSquares()); 
    }
}

inline void handleQCastle(Board* board, bool is_white){
    if (is_white){
        removeRook(board, board->current_attack_set, 7, board->getOccupiedSquares());
        removeKing(board->current_attack_set, 3);
        board->current_attack_set[4].fields.RIGHT = board->current_attack_set[3].fields.RIGHT ? board->current_attack_set[3].fields.RIGHT + 1 : 0; 
        board->white_king_square = 5;
        board->white_pieces.king = 0x20; 
        board->white_pieces.rook ^= 0x80; 
        board->white_pieces.rook |= 0x10;
        addKing(board->current_attack_set, 5);
        addLat(board->current_attack_set, 4, board->getOccupiedSquares()); 
    }
    else{
        removeRook(board, board->current_attack_set, 63, board->getOccupiedSquares());
        removeKing(board->current_attack_set, 59);
        board->current_attack_set[60].fields.RIGHT = board->current_attack_set[59].fields.RIGHT ? board->current_attack_set[59].fields.RIGHT + 1 : 0; 
        board->black_king_square = 61;
        board->black_pieces.king = 0x2000000000000000; 
        board->black_pieces.rook ^= 0x8000000000000000; 
        board->black_pieces.rook |= 0x1000000000000000;
        addKing(board->current_attack_set, 61);
        addLat(board->current_attack_set, 60, board->getOccupiedSquares()); 
    }
}

inline void handleQUnCastle(Board* board, bool is_white){
    if (is_white){
        removeRook(board, board->other_attack_set, 4, board->getOccupiedSquares());
        removeKing(board->other_attack_set, 5);
        blockRayAttacks(board, board->other_attack_set, 3);
        board->white_king_square = 3;
        board->white_pieces.king = 0x8; 
        board->white_pieces.rook |= 0x80; 
        board->white_pieces.rook ^= 0x10;
        addKing(board->other_attack_set, 3);
        addLat(board->other_attack_set, 7, board->getOccupiedSquares()); 
    }
    else{
        removeRook(board, board->other_attack_set, 60, board->getOccupiedSquares());
        removeKing(board->other_attack_set, 61);
        board->black_king_square = 59;
        board->black_pieces.king = 0x800000000000000; 
        board->black_pieces.rook |= 0x8000000000000000; 
        board->black_pieces.rook ^= 0x1000000000000000;
        addKing(board->other_attack_set, 59);
        addLat(board->other_attack_set, 63, board->getOccupiedSquares()); 
    }
}

inline void handleKingMove(Board* board, int from, int to, int special, int capture){
    board->en_pass_square = 0; 

    if (from == 3){
        board->castle_rights.white_k_castle = 0; 
        board->castle_rights.white_q_castle = 0;
    }
    else{
        if (from == 59){
            board->castle_rights.black_q_castle = 0; 
            board->castle_rights.black_k_castle = 0;
        }
    }

    if (special){
        if (special == 1){
            handleKCastle(board, from < 32);
        }
        else{
            handleQCastle(board, from < 32);
        }
        return;
    }



    if (board->white_to_move){
        board->white_king_square = to;
    }
    else{
        board->black_king_square = to;
    }
    
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removeKing(board->current_attack_set, from);
        board->current_pieces->king ^= SHIFT(from);
        extendRays(board, from, occupied_squares);
        board->current_pieces->king = SHIFT(to);
        addKing(board->current_attack_set, to);
    }
    else{
        removeKing(board->current_attack_set, from);
        board->current_pieces->king = SHIFT(to);
        blockRays(board, to);
        extendRays(board, from, board->getOccupiedSquares());
        addKing(board->current_attack_set, to);
    }
}
inline void handleQueenMove(Board* board, int from, int  to, int capture){
    board->en_pass_square = 0; 
    /* first remove all the attack squares from the old queen */
    if (capture){
    
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removeQueen(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->queen ^= SHIFT(from);
        board->current_pieces->queen |= SHIFT(to);
        extendRays(board, from, occupied_squares);

        addQueen(board->current_attack_set, to, board->getOccupiedSquares());
    }
    else{
        board->current_pieces->queen |= SHIFT(to);
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeQueen(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->queen ^= SHIFT(from);
        blockRays(board, to);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, from, occupied_squares);
            
        addQueen(board->current_attack_set, to, occupied_squares);
    }
}
inline void handleBishopMove(Board* board, int from, int to, int capture){
    board->en_pass_square = 0; 
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removeBishop(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->bishop ^= SHIFT(from);
        board->current_pieces->bishop |= SHIFT(to);
        extendRays(board, from, occupied_squares);
        addDiags(board->current_attack_set, to, board->getOccupiedSquares());
    }
    else{
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeBishop(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->bishop ^= SHIFT(from);
        board->current_pieces->bishop |= SHIFT(to);
        blockRays(board, to);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, from, occupied_squares);
        addDiags(board->current_attack_set, to, occupied_squares);
    }

}
inline void handleRookMoves(Board* board, int from, int to, int capture){
    board->en_pass_square = 0; 
    switch (from){
        case 0: 
            board->castle_rights.white_k_castle = 0; 
            break; 
        case 7: 
            board->castle_rights.white_q_castle = 0; 
            break; 
        case 56: 
            board->castle_rights.black_k_castle = 0; 
            break;
        case 63: 
            board->castle_rights.black_q_castle = 0; 
            break;
    }

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removeRook(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->rook ^= SHIFT(from);
        board->current_pieces->rook |= SHIFT(to);
        extendRays(board, from, occupied_squares);

        addLat(board->current_attack_set, to, board->getOccupiedSquares());
    }
    else{
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeRook(board, board->current_attack_set, from, occupied_squares);
        board->current_pieces->rook ^= SHIFT(from);
        board->current_pieces->rook |= SHIFT(to);
        blockRays(board, to);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, from, occupied_squares);
        addLat(board->current_attack_set, to, occupied_squares);
    }
}
inline void handleKnightMoves(Board* board, int from, int to, int capture){
    board->en_pass_square = 0; 
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removeKnight(board->current_attack_set, from);
        board->current_pieces->knight ^= SHIFT(from);
        extendRays(board, from, occupied_squares);
        board->current_pieces->knight |= SHIFT(to);
        addKnight(board->current_attack_set, to);
    }
    else{
        board->current_pieces->knight |= SHIFT(to);
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeKnight(board->current_attack_set, from);
        board->current_pieces->knight ^= SHIFT(from);
        blockRays(board, to);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, from, occupied_squares);
        addKnight(board->current_attack_set, to);
    }   
}
inline void handleBlackPawnMoves(Board* board, int from, int to, int special, int capture){     
    if (from - to == 16){
        board->en_pass_square = to + 8;
    }
    else{
        board->en_pass_square = 0; 

        //ep capture
        if (special == EP){
            board->current_pieces->pawn ^= SHIFT(from);
            board->other_pieces->pawn ^= SHIFT(to + 8);
            removePawn(board, board->current_attack_set, from, false);
            removePawn(board, board->other_attack_set, to + 8, true);
            board->current_pieces->pawn |= SHIFT(to);
            blockRays(board, to);
            addBlackPawn(board->current_attack_set, to);
            uint64_t occupied_squares = board->getOccupiedSquares();
            extendRays(board, from, occupied_squares);
            extendRays(board, to + 8, occupied_squares);

            return;
        }
    }

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removePawn(board, board->current_attack_set, from, false);
        board->current_pieces->pawn ^= SHIFT(from);
        occupied_squares |= SHIFT(to);
        extendRays(board, from, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->current_pieces->knight |= SHIFT(to);
                addKnight(board->current_attack_set, to);
                break;
            case B_PROMO: 
                board->current_pieces->bishop |= SHIFT(to);
                addDiags(board->current_attack_set, to, board->getOccupiedSquares());
                break;
            case ROOK_PROMO: 
                board->current_pieces->rook |= SHIFT(to);
                addLat(board->current_attack_set, to, board->getOccupiedSquares());
                break; 
            case QUEEN_PROMO: 
                board->current_pieces->queen |= SHIFT(to);
                addQueen(board->current_attack_set, to, board->getOccupiedSquares());
                break;
            default: 
                board->current_pieces->pawn |= SHIFT(to);
                addBlackPawn(board->current_attack_set, to);
        }
    }
    else{

        removePawn(board, board->current_attack_set, from, false);
        board->current_pieces->pawn ^= SHIFT(from);
        uint64_t occupied_squares = board->getOccupiedSquares();
        occupied_squares |= SHIFT(to);
        blockRays(board, to);
        extendRays(board, from, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->current_pieces->knight |= SHIFT(to);
                addKnight(board->current_attack_set, to);
                break;
            case B_PROMO: 
                board->current_pieces->bishop |= SHIFT(to);
                addDiags(board->current_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->current_pieces->rook |= SHIFT(to);
                addLat(board->current_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->current_pieces->queen |= SHIFT(to);
                addQueen(board->current_attack_set, to, occupied_squares);
                break;
            default: 
                board->current_pieces->pawn |= SHIFT(to);
                addBlackPawn(board->current_attack_set, to);
        }
    }
    
}
inline void handleWhitePawnMoves(Board* board, int from, int to, int special, int capture){
    if (to - from == 16){
        board->en_pass_square = to - 8;
    }
    else{
        board->en_pass_square = 0; 

        //ep capture
        if (special == EP){
            board->other_pieces->pawn ^= SHIFT(to - 8);
            removePawn(board, board->current_attack_set, from, true);
            removePawn(board, board->other_attack_set, to - 8, false);
            board->current_pieces->pawn ^= SHIFT(from);
            blockRays(board, to);
            addWhitePawn(board->current_attack_set, to);
            board->current_pieces->pawn |= SHIFT(to);
            uint64_t occupied_squares = board->getOccupiedSquares();
            extendRays(board, from, occupied_squares);
            extendRays(board, to - 8, occupied_squares);


            return;
        }
    }

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeCapturePiece(board, board->other_attack_set, to, capture, occupied_squares);
        removePawn(board, board->current_attack_set, from, true);
        board->current_pieces->pawn ^= SHIFT(from);
        occupied_squares |= SHIFT(to);
        extendRays(board, from, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->current_pieces->knight |= SHIFT(to);
                addKnight(board->current_attack_set, to);
                break;
            case B_PROMO: 
                board->current_pieces->bishop |= SHIFT(to);
                addDiags(board->current_attack_set, to, board->getOccupiedSquares());
                break;
            case ROOK_PROMO: 
                board->current_pieces->rook |= SHIFT(to);
                addLat(board->current_attack_set, to, board->getOccupiedSquares());
                break; 
            case QUEEN_PROMO: 
                board->current_pieces->queen |= SHIFT(to);
                addQueen(board->current_attack_set, to, board->getOccupiedSquares());
                break;
            default: 
                board->current_pieces->pawn |= SHIFT(to);
                addWhitePawn(board->current_attack_set, to);
        }
    }
    else{
        removePawn(board, board->current_attack_set, from, true);
        board->current_pieces->pawn ^= SHIFT(from);
        uint64_t occupied_squares = board->getOccupiedSquares();
        occupied_squares |= SHIFT(to);
        blockRays(board, to);
        extendRays(board, from, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->current_pieces->knight |= SHIFT(to);
                addKnight(board->current_attack_set, to);
                break;
            case B_PROMO: 
                board->current_pieces->bishop |= SHIFT(to);
                addDiags(board->current_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->current_pieces->rook |= SHIFT(to);
                addLat(board->current_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->current_pieces->queen |= SHIFT(to);
                addQueen(board->current_attack_set, to, occupied_squares);
                break;
            default: 
                board->current_pieces->pawn |= SHIFT(to);
                addWhitePawn(board->current_attack_set, to);
        }
    }
}

void makeMove(Board* board, Move move){

    int from = move.source; 
    int to = move.dest;
    int special = move.special; 
    int capture = move.capture;
    uint64_t shifted = SHIFT(from);
    if (shifted & board->current_pieces->queen){
        handleQueenMove(board, from, to, capture);
    }
    else{
        if (shifted & board->current_pieces->bishop){
            handleBishopMove(board, from, to, capture);
        }
        else{
            if (shifted & board->current_pieces->knight){
                handleKnightMoves(board, from, to, capture);
            }
            else{
                if (shifted & board->current_pieces->king){
                    handleKingMove(board, from, to, special, capture);
                }
                else{
                    if (shifted & board->current_pieces->rook){
                        handleRookMoves(board, from, to, capture);
                    }
                    else{
                        if (board->white_to_move){
                            handleWhitePawnMoves(board, from, to, special, capture);
                        }
                        else{
                            handleBlackPawnMoves(board, from, to, special, capture);
                        }
                    }
                }
            }
        }
    }

    board->white_to_move = !board->white_to_move;
    board->setCurrentState();

    if ((SHIFT(move.source) & (board->white_pieces.pawn | board->black_pieces.pawn)) || move.capture){
        board->move_since = 0; 
    } 
    else{
        board->move_since++;
    }
    
    if (board->white_to_move) board->turn_number++;
}


inline void handleKnightUnMoves(Board* board, int from, int to, int capture){
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        removeKnight(board->other_attack_set, to);
        board->other_pieces->knight ^= SHIFT(to);
        blockRays(board, from);
        board->other_pieces->knight |= SHIFT(from);
        addKnight(board->other_attack_set, from);
    }
    else{
        board->other_pieces->knight |= SHIFT(from);
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeKnight(board->other_attack_set, to);
        board->other_pieces->knight ^= SHIFT(to);
        blockRays(board, from);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);
        addKnight(board->other_attack_set, from);
    }   
}


inline void handleKingUnMove(Board* board, int from, int to, int special, int capture){

    if (special){
        if (special == 1){
            handleKUnCastle(board, from < 32);
        }
        else{
            handleQUnCastle(board, from < 32);
        }
        return;
    }

    if (board->white_to_move){
        board->black_king_square = from;
    }
    else{
        board->white_king_square = from;
    }
    
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        removeKing(board->other_attack_set, to);
        board->other_pieces->king |= SHIFT(from);
        blockRays(board, from);
        board->other_pieces->king = SHIFT(from);
        addKing(board->other_attack_set, from);
    }
    else{
        removeKing(board->other_attack_set, to);
        board->other_pieces->king = SHIFT(from);
        blockRays(board, from);
        extendRays(board, to, board->getOccupiedSquares());
        addKing(board->other_attack_set, from);
    }
}

inline void handleRookUnMoves(Board* board, int from, int to, int capture){

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        removeRook(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->rook ^= SHIFT(to);
        board->other_pieces->rook |= SHIFT(from);
        blockRays(board, from);

        addLat(board->other_attack_set, from, board->getOccupiedSquares());
    }
    else{
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeRook(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->rook ^= SHIFT(to);
        board->other_pieces->rook |= SHIFT(from);
        blockRays(board, from);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);
        addLat(board->other_attack_set, from, occupied_squares);
    }
}

inline void handleWhitePawnUnMove(Board* board, int from, int to, int special, int capture){

    //ep capture
    if (special == EP){
        board->current_pieces->pawn |= SHIFT(to - 8);
        removePawn(board, board->other_attack_set, to, true);
        blockRays(board, from);
        blockRays(board, to - 8);
        addBlackPawn(board->current_attack_set, to - 8);
        board->other_pieces->pawn |= SHIFT(from);
        addWhitePawn(board->other_attack_set, from);
        board->other_pieces->pawn ^= SHIFT(to);
        uint64_t occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);

        return;
    }

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->other_pieces->knight ^= SHIFT(to);
                removeKnight(board->other_attack_set, to);
                break;
            case B_PROMO: 
                board->other_pieces->bishop ^= SHIFT(to);
                removeBishop(board, board->other_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->other_pieces->rook ^= SHIFT(to);
                removeRook(board, board->other_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->other_pieces->queen ^= SHIFT(to);
                removeQueen(board, board->other_attack_set, to, occupied_squares);
                break;
            default: 
                board->other_pieces->pawn ^= SHIFT(to);
                removePawn(board, board->other_attack_set, to, true);
        }
        blockRays(board, from);
        addWhitePawn(board->other_attack_set, from);
        board->other_pieces->pawn |= SHIFT(from);
    }
    else{

        uint64_t occupied_squares = board->getOccupiedSquares();
        switch(special){
            case N_PROMO: 
                board->other_pieces->knight ^= SHIFT(to);
                removeKnight(board->other_attack_set, to);
                break;
            case B_PROMO: 
                board->other_pieces->bishop ^= SHIFT(to);
                removeBishop(board, board->other_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->other_pieces->rook ^= SHIFT(to);
                removeRook(board, board->other_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->other_pieces->queen ^= SHIFT(to);
                removeQueen(board, board->other_attack_set, to, occupied_squares);
                break;
            default: 
                board->other_pieces->pawn ^= SHIFT(to);
                removePawn(board, board->other_attack_set, to, true);
        }
        extendRays(board, to, occupied_squares);
        blockRays(board, from);
        addWhitePawn(board->other_attack_set, from);
        board->other_pieces->pawn |= SHIFT(from);
    }
}

inline void handleBlackPawnUnMove(Board* board, int from, int to, int special, int capture){

    //ep capture
    if (special == EP){
        board->current_pieces->pawn |= SHIFT(to + 8);
        removePawn(board, board->other_attack_set, to, false);
        blockRays(board, from);
        blockRays(board, to + 8);
        addWhitePawn(board->current_attack_set, to + 8);
        board->other_pieces->pawn |= SHIFT(from);
        addBlackPawn(board->other_attack_set, from);
        board->other_pieces->pawn ^= SHIFT(to);
        uint64_t occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);

        return;
    }

    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        switch(special){
            case N_PROMO: 
                board->other_pieces->knight ^= SHIFT(to);
                removeKnight(board->other_attack_set, to);
                break;
            case B_PROMO: 
                board->other_pieces->bishop ^= SHIFT(to);
                removeBishop(board, board->other_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->other_pieces->rook ^= SHIFT(to);
                removeRook(board, board->other_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->other_pieces->queen ^= SHIFT(to);
                removeQueen(board, board->other_attack_set, to, occupied_squares);
                break;
            default: 
                board->other_pieces->pawn ^= SHIFT(to);
                removePawn(board, board->other_attack_set, to, false);
        }
        blockRays(board, from);
        addBlackPawn(board->other_attack_set, from);
        board->other_pieces->pawn |= SHIFT(from);
    }
    else{

        uint64_t occupied_squares = board->getOccupiedSquares(); 
        switch(special){
            case N_PROMO: 
                board->other_pieces->knight ^= SHIFT(to);
                removeKnight(board->other_attack_set, to);
                break;
            case B_PROMO: 
                board->other_pieces->bishop ^= SHIFT(to);
                removeBishop(board, board->other_attack_set, to, occupied_squares);
                break;
            case ROOK_PROMO: 
                board->other_pieces->rook ^= SHIFT(to);
                removeRook(board, board->other_attack_set, to, occupied_squares);
                break; 
            case QUEEN_PROMO: 
                board->other_pieces->queen ^= SHIFT(to);
                removeQueen(board, board->other_attack_set, to, occupied_squares);
                break;
            default: 
                board->other_pieces->pawn ^= SHIFT(to);
                removePawn(board, board->other_attack_set, to, false);
        }
        extendRays(board, to, occupied_squares);
        blockRays(board, from);
        addBlackPawn(board->other_attack_set, from);
        board->other_pieces->pawn |= SHIFT(from);
    }
}


inline void handleQueenUnMove(Board* board, int from, int to, int capture){
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        removeQueen(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->queen ^= SHIFT(to);
        board->other_pieces->queen |= SHIFT(from);
        blockRays(board, from);
        addQueen(board->other_attack_set, from, board->getOccupiedSquares());
    }
    else{
        board->other_pieces->queen |= SHIFT(from);
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeQueen(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->queen ^= SHIFT(to);
        blockRays(board, from);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);
        addQueen(board->other_attack_set, from, occupied_squares);
    }
}

inline void handleBishopUnMove(Board* board, int from, int to, int capture){
    if (capture){
        uint64_t occupied_squares = board->getOccupiedSquares();
        addCapturePiece(board, board->current_attack_set, to, capture, occupied_squares);
        removeBishop(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->bishop ^= SHIFT(to);
        board->other_pieces->bishop |= SHIFT(from);
        blockRays(board, from);
        addDiags(board->other_attack_set, from, board->getOccupiedSquares());
    }
    else{
        uint64_t occupied_squares = board->getOccupiedSquares();
        removeBishop(board, board->other_attack_set, to, occupied_squares);
        board->other_pieces->bishop ^= SHIFT(to);
        board->other_pieces->bishop |= SHIFT(from);
        blockRays(board, from);
        occupied_squares = board->getOccupiedSquares();
        extendRays(board, to, occupied_squares);
        addDiags(board->other_attack_set, from, occupied_squares);
    }

}

void unmakeMove(Board* board, Move move){
    int from = move.source; 
    int to = move.dest;
    int special = move.special; 
    int capture = move.capture;

    if (special >= N_PROMO){
        if (!board->white_to_move){
            handleWhitePawnUnMove(board, from, to, special, capture);
        }
        else{
            handleBlackPawnUnMove(board, from, to, special, capture);
        }
    }
    else{
        uint64_t shifted = SHIFT(to);
        if (shifted & board->other_pieces->queen){
            handleQueenUnMove(board, from, to, capture);
        }
        else{
            if (shifted & board->other_pieces->bishop){
                handleBishopUnMove(board, from, to, capture);
            }
            else{
                if (shifted & board->other_pieces->knight){
                    handleKnightUnMoves(board, from, to, capture);
                }
                else{
                    if (shifted & board->other_pieces->king){
                        handleKingUnMove(board, from, to, special, capture);
                    }
                    else{
                        if (shifted & board->other_pieces->rook){
                            handleRookUnMoves(board, from, to, capture);
                        }
                        else{
                            if (!board->white_to_move){
                                handleWhitePawnUnMove(board, from, to, special, capture);
                            }
                            else{
                                handleBlackPawnUnMove(board, from, to, special, capture);
                            }
                        }
                    }
                }
            }
        }
    }
    

    board->white_to_move = !board->white_to_move;
    board->setCurrentState();

    /* After turn has already been flipped */
    if (board->white_to_move) {
    }
    else{
        board->turn_number--;
    }
}