#include "AI.h"
#include <climits>

Move AI::find_move (Board & obj) {
       Move mv = maxim(obj, ply_count - 1, true);
    //    cout << i << " - " << j << " - ";
    //    cout << "( " << mv.x  << ", " << mv.y <<" )"<< endl;
       return mv;
}
Move AI::maxim (Board & obj, int depth, bool minFlag) {
    Move best = {-1, -1, minFlag ? INT_MAX : INT_MIN};
    if(depth < 0) return best;
    if (depth == 0) {
        // evaluate all possible nodes and return the optimum move....
        for (int i = 0; i < obj.size(); i++) {
            for (int j = 0; j < obj.size(); j++) {
                // cout << i << endl;
                if (obj.get(i, j) != '-') continue;
                Move mv = {i, j, minFlag ? INT_MAX : INT_MIN};
                obj.mark_board(mv);

                // evaluate the board state....
                mv.eval_value = AI_EVAL(obj, minFlag);// evaluates the board based on defined heuristics
                if (comp(mv, best, minFlag)) {
                    if (mv.eval_value == best.eval_value) {
                        ((rand() % 16) == 1) ? best = mv : best;
                    }
                    else best = mv;
                    // cout << i << " - " << j << " - ";
                    // cout << "( " << best.x  << ", " << best.y <<" )"<< endl;
                }
                //delete the move and try the next one....
                mv.x = i; mv.y = j;
                obj.demark_board(mv);
            }
        }
    }
    else { // if depth is greater than 0...
        for (int i = 0; i < obj.size(); i++) {
            for (int j = 0; j < obj.size(); j++) {
                // cout << i << endl;
                if (obj.get(i, j) != '-') continue;
                Move mv = {i, j, minFlag ? INT_MAX : INT_MIN};
                // cout << i << " - " << j << " - ";
                // cout << "( " << mv.x  << ", " << mv.y <<" )"<< endl;
                obj.mark_board(mv);
                mv.eval_value = AI_EVAL(obj, minFlag);

                if (isWinMove(mv, minFlag)) { // returns true if the move makes the AI win the game...
                    obj.demark_board(mv); // this moves wins the game so no need to check the other moves...
                    return mv;
                }

                mv = maxim(obj, depth - 1, !minFlag);
                if (comp(mv, best, minFlag)) { // if true, the current move is equal or better than the current best....
                    if (mv.eval_value == best.eval_value) {
                        ((rand() % 16) == 1 )? best = mv : best;
                    }
                    else best = mv;
                }

                mv.x = i; mv.y = j;
                obj.demark_board(mv);
            }
        }
    }
    return best;
}
bool AI::isWinMove (const Move & mv, const bool minFlag) {
    if (minFlag) {
        if (mv.eval_value < -300) return true;
    }
    else {
        if (mv.eval_value > 300) return true;
    }
    return false;
}
int AI:: AI_EVAL (Board & obj, bool minFlag) {
    // return the number of sequential Xs in the array...
    int evaluation = 0;
    for (int i = 0; i < obj.size(); i++) {
        for (int j = 0; j <  obj.size(); j++) {
            if (obj.get(i, j) == X) {
                evaluation += eval_helper(obj.check_east(i, j, X));
                evaluation += eval_helper(obj.check_SE(i, j, X));
                evaluation += eval_helper(obj.check_south(i, j, X));
                evaluation += eval_helper(obj.check_SW(i, j, X));
            }
            else if (obj.get(i,j) == O) {
                evaluation -= eval_helper(obj.check_east(i, j, O));
                evaluation -= eval_helper(obj.check_SE(i, j, O));
                evaluation -= eval_helper(obj.check_south(i, j, O));
                evaluation -= eval_helper(obj.check_SW(i, j, O));
            }
        }
    }
    return evaluation;
}
int AI::eval_helper(int rank) {
    // Must be hard coded for now........
    switch (rank) {
        case 4: return 10000;
        case 3: return 10;
        case 2: return 5;
        case 1: return 2;
        default: return 0;
    }
}
bool AI::comp (const Move & mv, const Move & best, bool minFlag) {
    if (minFlag) {
        if (mv.eval_value <= best.eval_value) return true;
    }
    else {
        if (mv.eval_value >= best.eval_value) return true;
    }
    return false;
}