#include "MoveAnalyzer.h"

int MoveAnalyzer::evaluateBoard()
{
    const auto board = m_manager.getBoard();
    int score = 0;
    int pieceValue = 0;

    for (int i = 0; i < BOARD_SIZE; i++) 
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] == nullptr) continue;
        bool isWhite = board[i][j]->isWhite();
        char pieceType = std::tolower(board[i][j]->getPiece());
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
