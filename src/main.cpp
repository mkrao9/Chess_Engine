#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../include/board.hpp"
#include "../include/move.hpp"
#include "../include/make_unmake.hpp"
#include "../include/search.hpp"
#include <string>
#include <time.h>

using namespace std;

void printBoard(Board *b);

uint64_t perft(Board* board, uint32_t depth){
    Move ml[256];
    
    if (depth == 0){
        return 1; 
    }

    if (depth == 1){
        return generateAllMoves(board, ml); 
    }
    
    uint64_t nodes = 0; 
    int curr_num_moves = generateAllMoves(board, ml);
    for (int i = 0; i < curr_num_moves; i++){
        int old_ep = board->en_pass_square; 
        int old_moves_since = board->move_since; 
        CastleRights old_castle_rights = board->castle_rights; 
        makeMove(board, ml[i]);
        nodes += perft(board, depth - 1);
        unmakeMove(board, ml[i]); 
        board->en_pass_square = old_ep; 
        board->move_since = old_moves_since;
        board->castle_rights = old_castle_rights;
    }
    return nodes; 
}

uint64_t perft(const char *fen, int depth){
    Board *b = new Board(fen);
    return perft(b, depth);
}

uint64_t perft(int depth){
    Board *b = new Board(); 
    return perft(b, depth);
}


int searchBoard(Board* board, Move* ml, int num_moves, int from, int to, int promo){
    for (int i = 0; i < num_moves; i++){
        if ((ml[i].source == from && ml[i].dest == to) && (!promo || ml[i].special == promo)){
            return i;
        }
    }
    return -1;
}

int getSquare(string input){
    if (isalpha(input[0]) && isdigit(input[1])){
        int col = 7 - (input[0] - 'a');
        int row = input[1] - '1';
        if (col < 0 || row < 0 || row > 7)
            return - 1;
        return 8*row + col;
    }
    return -1;
}




int handleInputMove(Board* b, Move* ml, int num_moves){
    std::string input;
    std::cin >> input;
    int from, to, promo;
    if (input.size() == 4){
        from = getSquare(input.substr(0, 2));
        to = getSquare(input.substr(2, 2));
        if (from == -1 || to == -1){
            cout << "Invalid Move try again" << endl; 
            return -1;
        }
        int mv = searchBoard(b,ml, num_moves, from, to, 0);
        if (mv == -1)
            cout << "Invalid Move try again" << endl; 
        return mv;
    }
    else{
        if (input.size() == 5){
            from = getSquare(input.substr(0, 2));
            to = getSquare(input.substr(2, 2));
            if (from == -1 || to == -1){
                cout << "Invalid Move try again" << endl; 
                return -1;
            }
            char prom = input[4];
            switch (prom){
                case 'Q': 
                case 'q': 
                    promo = 7; 
                    break; 
                case 'N': 
                case 'n': 
                    promo = 4; 
                    break; 
                case 'B': 
                case 'b': 
                    promo = 5;
                    break; 
                case 'R': 
                case 'r': 
                    promo = 6; 
                    break; 
                default:
                    cout << "Invalid Move try again" << endl; 
                    return -1;
            }
            int mv = searchBoard(b,ml, num_moves, from, to, promo);
            if (mv == -1)
                cout << "Invalid Move try again" << endl; 
            return mv;
        }
        cout << "Invalid Move try again" << endl;
        return -1; 
    }
}

//returns whether or not the computer is white
bool getColor(){
    bool is_valid = false; 
    while (!is_valid){
        string input; 
        cout << "Which side do you want? Enter w for white and b for black" << endl;
        cin >> input;
        if (input.compare("w") == 0 || input.compare("W") == 0 || input.compare("white") == 0 || input.compare("WHITE") == 0 || input.compare("White") == 0){
            return false;
        }
        if (input.compare("b") == 0 || input.compare("B") == 0 || input.compare("black") == 0 || input.compare("BLACK") == 0 || input.compare("Black") == 0){
            return true; 
        }
        cout << "Not a valid side selection, try again" << endl;
    }
    
    return false;
}

Move getComputerMove(Board* b, Move* ml, int num_moves){
    return basicSearch(b, 4, ml, num_moves);
}

string moveToUCI(Move move){
    string out = "";
    int fromCol = move.source % 8; 
    int fromRow = move.source / 8; 
    int toCol = move.dest % 8; 
    int toRow = move.dest / 8; 
    out += ((char) (7 - fromCol) + 'a');
    out += ((char) fromRow + '1');
    out += ((char) (7 - toCol) + 'a'); 
    out += ((char) toRow + '1');
    return out;
}

void initializeComputer(){
    initializeZorbistKeys();
}

int main(){

    Move ml[256];    
    Board* b = new Board(); 
    bool is_game = true; 

    initializeComputer();
    srand(time(0));
    bool is_comp_white = getColor();
    while (is_game){
        int num_moves = generateAllMoves(b, ml);
        if (num_moves == 0){
            if (isInCheck(b)){
                string color = b->white_to_move ? "black " : "white ";
                cout << "gg " << color << "wins" << endl;
            }
            else{
                cout << "it's a draw" << endl;
            }
            is_game = false; 
            break;
        }

        if (b->white_to_move == is_comp_white){
            cout << "The computer is moving "; 
            Move mv = getComputerMove(b, ml, num_moves);
            makeMove(b, mv); 
            cout << moveToUCI(mv) << endl;
        }
        else{
            cout << "Enter Move" << endl;
            int index = -1;             
            while (index == -1){
                index = handleInputMove(b, ml, num_moves);
            }
            makeMove(b, ml[index]); 
        }
    }





    return 0;
}