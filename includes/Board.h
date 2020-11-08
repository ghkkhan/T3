#include <vector>
#include <iostream>
using namespace std;

#define PLAYER_1 0
#define PLAYER_2 1
#define X 'X' 
#define O 'O'

typedef vector<vector<char>> Board_t;

struct Move {
    int x, y; // x and y column of the move in the table... indexed from 0
    int eval_value; // value of the move according to the eval functions and the context of the board...
};


class Board {
private:
    int vic_number, turn;
    Board_t board;
public:
    Board (size_t size, int vic_num);
    int trn() { return turn;}
    int size() {return board.size();}
    int vic() {return vic_number;}
    int get(int i, int j) { return board[i][j];}
    void mark_board (Move & mv);
    void gods_mark(int i, int j, char a);
    void demark_board (Move & mv);
    bool check_victory_condition ();
        // some misceleneous functions (helper functions to check_victory_condition + AI) 
        int check_east (int i, int j, char);
        int check_SE (int i, int j, char);
        int check_south (int i, int j, char);
        int check_SW (int i, int j, char);
    void print ();
};

