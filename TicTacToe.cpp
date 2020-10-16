#include <iostream>
#include <time.h>

#define HUMAN 1 
#define COMPUTER 2 

#define SIDE 3

#define MAXMOVE 'X' 
#define MINMOVE 'O' 
#define EMPTY '_'

struct Move 
{
    int row, col;
};  

int turn;
int COMPUTERMOVE;
int HUMANMOVE;


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
            if (b[row][0] == MAXMOVE)
                return +10;
            if (b[row][0] == MINMOVE)
                return -10;
        }
    }

    for (int col = 0; col < SIDE; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == MAXMOVE)
                return +10;
            if (b[0][col] == MINMOVE)
                return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == MAXMOVE)
            return +10;
        if (b[0][0] == MINMOVE)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == MAXMOVE)
            return +10;
        if (b[0][2] == MINMOVE)
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
                    board[row][col] = MAXMOVE;

                    bestScore = std::max(bestScore, minimax(board, depth + 1, !isMax));

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
                    board[row][col] = MINMOVE;

                    bestScore = std::min(bestScore, minimax(board, depth + 1, !isMax));

                    board[row][col] = EMPTY;

                }
            }
        }
        return bestScore;
    }
}

Move findBestMove(char board[SIDE][SIDE]) {
    int bestVal = 1000;
    bool isMax = true;
    if (COMPUTERMOVE == MAXMOVE) {
        bestVal = -1000;
        isMax = false;
    }

    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int row = 0; row < SIDE; row++) {
        for (int col = 0; col < SIDE; col++) {
            if (board[row][col] == EMPTY) {
                board[row][col] = COMPUTERMOVE;

                int moveVal = minimax(board, 0, isMax);

                board[row][col] = EMPTY;
                
                if (COMPUTERMOVE == MAXMOVE) {
                    if (moveVal > bestVal) {
                        bestMove.row = row;
                        bestMove.col = col;
                        bestVal = moveVal;
                    }
                }
                else {
                    if (moveVal < bestVal) {
                        bestMove.row = row;
                        bestMove.col = col;
                        bestVal = moveVal;
                    }
                }
            }
        }
    }

    board[bestMove.row][bestMove.col] = COMPUTERMOVE;
    turn = HUMAN;
    return bestMove;
}


Move getHumanMove(char board[SIDE][SIDE]) {
    
    Move humanMove;
    std::cout << std::endl;
    std::cout << "Your input: ";
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
    std::cout << "\n\n_____________\n\n";
}

int main() {
    char board[SIDE][SIDE] = {
    { '_', '_', '_' },
    { '_', '_', '_' },
    { '_', '_', '_' }
    };

    srand(time(0));
    int done;
    int firstTurn = rand() % 2 + 1;
    turn = firstTurn;

    if (firstTurn == COMPUTER) {
        COMPUTERMOVE = MAXMOVE;
        HUMANMOVE = MINMOVE;
    }
    else {
        COMPUTERMOVE = MINMOVE;
        HUMANMOVE = MAXMOVE;
    }


    printf("Human vs. Tic Tac Toe minimax\n");
    printf("You will be playing against the computer as '%c'\n", HUMANMOVE);
    printf("The computer will be playing as '%c'\n", COMPUTERMOVE);
    printf("Controls are: \n 1 - 2 - 3 \n 4 - 5 - 6 \n 7 - 8 - 9 \n");
    if(HUMANMOVE == MAXMOVE) drawBoard(board);

    done = 0;

    std::cout << std::endl;

    do {

        if (turn == HUMAN)
            getHumanMove(board);
        else {
            findBestMove(board);
            drawBoard(board);
        }

        done = evaluate(board);

        if (bMovesLeft(board) == false) {
            drawBoard(board);
            printf("\n Draw! \n");
            break;
        }

        if (done == 10 || done == -10) break;

    } while (done == 0);

    drawBoard(board);
    if (done == 10)
        printf("\%c won!\n", MAXMOVE);
    else if (done == -10)
        printf("\%c won!\n", MINMOVE);

    return 0;
}