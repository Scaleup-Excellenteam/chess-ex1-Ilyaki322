#include "MoveAnalyzer.h"
#include <limits>
#include <algorithm>

#undef min
#undef max

/*
* Finds the best move using minmax algorithm, more info on the algo in minmax func documentation.
* Commented code is version without forced prio queue, gives the best move right away.
* 
* @param isWhite - color for who to find best move
* @returns std::pair<coords,coords> for the best move.
*/
std::pair<coords, coords> MoveAnalyzer::findBestMove(bool isWhite)
{
    if (m_manager.getTurnCounter() < 4) {
        return m_starter[m_manager.getTurnCounter()];
    }

    //std::pair<coords, coords> bestMove;
    //int bestValue = (isWhite) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    /*
    * We generate all moves, and for each move apply minmax.
    */
    std::vector<std::vector<std::pair<coords, coords>>> allMoves = m_manager.getAllMoves(isWhite);

    for (const auto& i : allMoves) {
        for (auto& move : i) {
            m_manager.playMove2(move.first, move.second);
            int boardValue = minmax(m_depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !isWhite);
            m_manager.undoLastMove2();

            /*if ((iswhite && boardvalue > bestvalue) || (!iswhite && boardvalue < bestvalue)) {
                bestvalue = boardvalue;
                bestmove = move;
            }*/

            if (!isWhite) boardValue *= -1;
            m_queue.push({ move.first, move.second, boardValue });
        }
    }

    auto best = m_queue.pop();
    return { best.start, best.target };
    //return bestMove;
}


/*
* The minmax algorithm will get a board position, and recusivly play all possible moves,
* and on those moves will apply minmax, up to depth.
* for each move it will evaluate the board and return a value,
* overall this will return a move that has the highest value.
*
* The algorithm also uses alpha beta pruning:
* minmax plays both black and white moves, so
* it will 'cut' and stop the recursion if it finds moves that are better for the opponent,
* it assumes the opponent will make the best move for them, and so we reduce the number
* of positions we need to check.
* for example: if we look at 3 different moves, and on the first the evaluation favours
* the enemy, then if on the second move we find a lower evaluation, we will skip the entire recursion
* of that move.
*/
int MoveAnalyzer::minmax(int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0)
        return evaluateBoard();

    std::vector<std::vector<std::pair<coords, coords>>> allMoves = m_manager.getAllMoves(maximizingPlayer);

    if (isGameOver(allMoves))
        depth = 1;


    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& i : allMoves) {
            for (const auto& move : i) {

                m_manager.playMove2(move.first, move.second);
                int eval = minmax(depth - 1, alpha, beta, false);
                m_manager.undoLastMove2();

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    return maxEval;
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& i : allMoves) {
            for (const auto& move : i) {

                m_manager.playMove2(move.first, move.second);
                int eval = minmax(depth - 1, alpha, beta, true);
                m_manager.undoLastMove2();

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    return minEval;
                }
            }
        }
        return minEval;
    }
}


/*
* goes through the board position, and calculates
* a value for it.
* negative means the position favors the enemy,
* positive means the position favors the Player.
* will calculate based on Piece values and the Tables.
*/
int MoveAnalyzer::evaluateBoard()
{
    const auto board = m_manager.getBoard();
    int score = 0;
    int pieceValue = 0;

    for (int i = 0; i < BOARD_SIZE; i++) 
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] == nullptr) continue;
        bool isWhite = board[i][j]->isWhite();
        char pieceType = (char)(std::tolower(board[i][j]->getPiece()));
            switch (pieceType) {
            case 'p': {
                pieceValue = isWhite ? 100 : -100;
                pieceValue += isWhite ? whitePawnTable[j + i * BOARD_SIZE] : -blackPawnTable[j + i * BOARD_SIZE];
                break;
            }
            case 'r': {
                pieceValue = isWhite ? 500 : -500;
                pieceValue += isWhite ? whiteRookTable[j + i * BOARD_SIZE] : -blackRookTable[j + i * BOARD_SIZE];
                break;
            }
            case 'n': {
                pieceValue = isWhite ? 320 : -320;
                pieceValue += isWhite ? whiteKnightTable[j + i * BOARD_SIZE] : -blackKnightTable[j + i * BOARD_SIZE];
                break;
            }
            case 'b': {
                pieceValue = isWhite ? 330 : -330;
                pieceValue += isWhite ? whiteBishopTable[j + i * BOARD_SIZE] : -blackBishopTable[j + i * BOARD_SIZE];
                break;
            }
            case 'q': {
                pieceValue = isWhite ? 900 : -900;
                pieceValue += isWhite ? whiteQueenTable[j + i * BOARD_SIZE] : -blackQueenTable[j + i * BOARD_SIZE];
                break;
            }
            case 'k': {
                pieceValue = isWhite ? 2000 : -2000;
                pieceValue += isWhite ? whiteKingTableMidgame[j + i * BOARD_SIZE] : -blackKingTableMidgame[j + i * BOARD_SIZE];
                break;
            }
            }

        score += pieceValue;
    }
    return score;
}

bool MoveAnalyzer::isGameOver(std::vector<std::vector<std::pair<coords, coords>>>& allMoves)
{
    for (const auto& i : allMoves)
        if (!i.empty()) return false;
    return true;
}
