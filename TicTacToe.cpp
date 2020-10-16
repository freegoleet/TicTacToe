// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define HUMAN 1 
#define COMPUTER 2 

#define SIDE 3

#define COMPUTERMOVE 'X' 
#define HUMANMOVE 'O' 
#define EMPTY '_'

struct Move 
{
    int row, col;
};  

int turn = COMPUTER;

int choice;

bool bMovesLeft(char board[SIDE][SIDE]) {
    for (int row = 0; row < SIDE; row++)
        for (int col = 0; col < SIDE; col++)
            if (board[row][col] == EMPTY)
                return true;
        
    return false;
}

int evaluate(char b[SIDE][SIDE]) {
    for (int row = 0; row < SIDE; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == COMPUTERMOVE)
                return +10;
            if (b[row][0] == HUMANMOVE)
                return -10;
        }
    }

    for (int col = 0; col < SIDE; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == COMPUTERMOVE)
                return +10;
            if (b[0][col] == HUMANMOVE)
                return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == COMPUTERMOVE)
            return +10;
        if (b[0][0] == HUMANMOVE)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == COMPUTERMOVE)
            return +10;
        if (b[0][2] == HUMANMOVE)
            return -10;
    }
    return 0;
}

int minimax(char board[SIDE][SIDE], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10)
        return score;

    if (score == -10)
        return score;

    if (!bMovesLeft(board))
        return 0;

    if (isMax) {
        int bestScore = -1000;

        for (int row = 0; row < SIDE; row++) {
            for (int col = 0; col < SIDE; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = COMPUTERMOVE;

                    bestScore = std::max(bestScore, minimax(board, depth + 1, isMax));

                    board[row][col] = EMPTY;
                }
            }
        }
        return bestScore;
    }

    else {
        int bestScore = 1000;

        for (int row = 0; row < SIDE; row++) {
            for (int col = 0; col < SIDE; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = HUMANMOVE;

                    bestScore = std::min(bestScore, minimax(board, depth + 1, !isMax));

                    board[row][col] = EMPTY;

                }
            }
        }
        return bestScore;
    }
}

Move findBestMove(char board[SIDE][SIDE]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int row = 0; row < SIDE; row++) {
        for (int col = 0; col < SIDE; col++) {
            if (board[row][col] == EMPTY) {
                board[row][col] = COMPUTERMOVE;

                int moveVal = minimax(board, 0, false);

                board[row][col] = EMPTY;
                

                if (moveVal > bestVal) {
                    bestMove.row = row;
                    bestMove.col = col;
                    bestVal = moveVal;
                }
            }
        }
    }
    std::printf("\nThe position of the best Move is: Row %d Col %d\n\n", bestMove.row, bestMove.col);

    board[bestMove.row][bestMove.col] = COMPUTERMOVE;
    turn = HUMAN;
    return bestMove;
}


Move getHumanMove(char board[SIDE][SIDE]) {
    
    Move humanMove;
    std::cout << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1: humanMove.row = 0; humanMove.col = 0; break;
    case 2: humanMove.row = 0; humanMove.col = 1; break;
    case 3: humanMove.row = 0; humanMove.col = 2; break;
    case 4: humanMove.row = 1; humanMove.col = 0; break;
    case 5: humanMove.row = 1; humanMove.col = 1; break;
    case 6: humanMove.row = 1; humanMove.col = 2; break;
    case 7: humanMove.row = 2; humanMove.col = 0; break;
    case 8: humanMove.row = 2; humanMove.col = 1; break;
    case 9: humanMove.row = 2; humanMove.col = 2; break;
    default:
        std::cout << "Invalid Move";
    }

    if (board[humanMove.row][humanMove.col] != EMPTY) {
        printf("Invalid move, try again.\n");
        getHumanMove(board);
    }
    else {
        board[humanMove.row][humanMove.col] = HUMANMOVE;
        turn = COMPUTER;
        
        return humanMove;
    }

    return humanMove;
}

void drawBoard(char board[SIDE][SIDE]) {
    for (int row = 0; row < SIDE; row++) {
        std::cout << "\n " << char(board[row][0]) << " | " << char(board[row][1]) << " | " << char(board[row][2]);

        if (row != 2)
            std::cout << "\n---|---|---\n";
    }
}

int main() {
    char board[SIDE][SIDE] = {
    { '_', '_', '_' },
    { '_', '_', '_' },
    { '_', '_', '_' }
    };

    int done;


    printf("Human vs. Tic Tac Toe minimax\n");
    printf("You will be player against the computer as 'O'\n");

    done = 0;

    drawBoard(board);

    do {

        if (turn == HUMAN)
            getHumanMove(board);
        else
            findBestMove(board);

        done = evaluate(board);
        drawBoard(board);

        if (!bMovesLeft) {
            printf("\n draw \n");
            break;
        }

        if (done == 10 || done == -10) break;

    } while (done == 0);

    if (done == 10)
        printf("\nComputer won!\n");
    else
        printf("\nHuman won!\n");

    return 0;
}