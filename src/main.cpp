// #include "Board.h"
#include "AI.h"
#include <unistd.h>

int main() {
    Board main_board(6, 4);
    AI Ai;
    Move mv;
    while(main_board.check_victory_condition() == false) {
        if(main_board.trn() == PLAYER_1) {
            cout << "Player's turn: Please enter a move..." << endl;
            cin >> mv.y >> mv.x;
        }
        else {
            //AI's turn...
            cout << "The AI is thinking..." << endl;
            mv = Ai.find_move(main_board);  
        }
        main_board.mark_board(mv);
        main_board.print();
    }
}