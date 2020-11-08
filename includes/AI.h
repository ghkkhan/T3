/* Define declarations and typedefs */
#include "Board.h"

class AI {
private:
    char ply_count = 4; // depth of the AI's analysis

    Move maxim (Board & obj, int depth, bool minFlag);
    int AI_EVAL(Board & obj, bool minFlag);
    int eval_helper(int score);
    bool comp (const Move & a, const Move & b, bool minFlag);
    bool isWinMove(const Move & a, const bool minFlag);
public:

    Move find_move (Board & obj);
    
};