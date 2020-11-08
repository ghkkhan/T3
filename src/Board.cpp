#include "Board.h"

// constructs the board object, initializes the board and sets turn to Player 1.
Board::Board (size_t size, int vic_num) {
    for (int i = 0; i < size; i++) {
        vector<char> temp(size, '-');
        board.push_back(temp);
    }
    turn = PLAYER_1;
    vic_number = vic_num;
}

void Board::mark_board(Move & mv) {
    // cout << "( " << mv.x  << ", " << mv.y <<" )"<< endl;
    // marks a '-' to either an X or O...
    // the mv should always be validated since this function assumes it is.
    if ( turn == PLAYER_1) {
        board[mv.x][mv.y] = X;
        turn = PLAYER_2;
    }
    else {
        turn = PLAYER_1;
        board[mv.x][mv.y] = O;
    }
}

void Board::gods_mark(int i, int j, char a) {
     board[i][j] = a;
}

//resets the board posiion back to default... used in algorithms rather than the actual game...
void Board::demark_board(Move & mv) {
    if ( turn == PLAYER_1 )  turn = PLAYER_2;
    else    turn = PLAYER_1;
    board[mv.x][mv.y] = '-';
}

char check_helper(int a) {
    if (a == PLAYER_1) return O;
    return X;
}

bool Board::check_victory_condition () {
    // only need to check 4 direc<tions...
    // EAST, SOUTH-EAST, SOUTH, SOUTH-WEST
    for (int i = 0; i < ( board).size(); i++) {
        for (int j = 0; j < ( board)[0].size(); j++) {
            if ( board[i][j] == '-') continue;
            if(check_east(i, j, check_helper(turn)) >= vic_number) return true;
            if (check_SE(i, j, check_helper(turn)) >= vic_number) return true;
            if (check_south(i, j, check_helper(turn)) >= vic_number) return true;
            if (check_SW(i, j, check_helper(turn)) >= vic_number) return true;
        }
    }
    return false;
}

// Begining of the misceleneous checks... They just check if a 4 in a 
// row exists in the specified direction... not much comments because its all copy of one anotehr

int Board::check_east(int i, int j, char a) {
    for (int k = 0; k < vic_number; k++) {
        if ( board[i][j+k] != a) return k;
        if (j + k + 1 >= board[i].size()) return k + 1;
    
    }
    return  vic_number;
}
int Board::check_SE(int i, int j, char a) {
    for (int k = 0; k < ( vic_number); k++) {
        if ((board[i + k][j + k]) != a) return k;
        if ((j + k + 1) >= board[i].size() || (i + k + 1) >= board.size()) return k + 1;
    }
    return  vic_number;
}

int Board::check_south(int i, int j, char a) {


    for (int k = 0; k < ( vic_number); k++) {
        if (board[i + k][j] != a) return k;
        if ((i + k + 1) >= board.size()) return k + 1;
    }
    return  vic_number;
}

int Board::check_SW(int i, int j, char a) {
    for (int k = 0; k < vic_number; k++) {
        if (board[i + k][j - k] != a ) return k;
        if ((i + k + 1) >= board.size() || (j - k - 1) < 0) return k + 1;
    }
    return  vic_number;
}
// ************************************************************************************* END OF Misc Checkers

void Board::print () {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}