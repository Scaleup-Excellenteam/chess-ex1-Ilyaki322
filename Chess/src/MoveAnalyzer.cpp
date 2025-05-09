#include "MoveAnalyzer.h"
#include <limits>
#include <algorithm>

#undef min
#undef max

std::pair<coords, coords> MoveAnalyzer::findBestMove(bool isWhite)
{
    std::pair<coords, coords> bestMove;

    /*
    * We generate all moves, and for each move apply minimax.
    */
    int bestValue = (isWhite) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    std::vector<std::vector<std::pair<coords, coords>>> allMoves = m_manager.getAllMoves(isWhite);

    for (const auto& i : allMoves) {
        for (auto& move : i) {
            m_manager.playMove2(move.first, move.second);
            int boardValue = minmax(m_depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), !isWhite);
            m_manager.undoLastMove2();

            if ((isWhite && boardValue > bestValue) || (!isWhite && boardValue < bestValue)) {
                bestValue = boardValue;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

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
                break;
            }
            case 'r': {
                pieceValue = isWhite ? 500 : -500;
                break;
            }
            case 'n': {
                pieceValue = isWhite ? 320 : -320;
                break;
            }
            case 'b': {
                pieceValue = isWhite ? 330 : -330;
                break;
            }
            case 'q': {
                pieceValue = isWhite ? 900 : -900;
                break;
            }
            case 'k': {
                pieceValue = isWhite ? 2000 : -2000;
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
