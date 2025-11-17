#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Player {
private:
    std::string name;
    char mark;

public:
    Player(const std::string& name, char mark) : name(name), mark(mark) {}

    const std::string& getName() const {
        return name;
    }

    char getMark() const {
        return mark;
    }
};

class Board {
private:
    static constexpr int SIZE = 3;
    std::vector<std::vector<char>> grid;
    int movesMade;

public:
    Board() : grid(SIZE, std::vector<char>(SIZE, ' ')), movesMade(0) {}

    void display() const {
        std::cout << "\n  1 2 3\n";
        std::cout << " -----\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << i + 1 << "|";
            for (int j = 0; j < SIZE; ++j) {
                std::cout << grid[i][j] << (j == SIZE - 1 ? "" : "|");
            }
            std::cout << "|\n";
            std::cout << " -----\n";
        }
        std::cout << "\n";
    }

    bool isValidMove(int row, int col) const {
        int r = row - 1;
        int c = col - 1;

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            std::cout << "Invalid coordinates. Use 1–3.\n";
            return false;
        }
        if (grid[r][c] != ' ') {
            std::cout << "Spot already taken.\n";
            return false;
        }
        return true;
    }

    void placeMark(int row, int col, char mark) {
        grid[row - 1][col - 1] = mark;
        movesMade++;
    }

    bool isFull() const {
        return movesMade == SIZE * SIZE;
    }

    bool checkWin(char mark) const {
        for (int i = 0; i < SIZE; ++i) {
            if (grid[i][0] == mark && grid[i][1] == mark && grid[i][2] == mark)
                return true;
            if (grid[0][i] == mark && grid[1][i] == mark && grid[2][i] == mark)
                return true;
        }

        if (grid[0][0] == mark && grid[1][1] == mark && grid[2][2] == mark)
            return true;

        if (grid[0][2] == mark && grid[1][1] == mark && grid[2][0] == mark)
            return true;

        return false;
    }
};

class Game {
private:
    Board board;
    Player playerX;
    Player playerO;
    Player* currentPlayer;

public:
    Game() : playerX("Player X", 'X'), playerO("Player O", 'O') {
        currentPlayer = &playerX;
        std::cout << "--- Tic-Tac-Toe Game ---\n";
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == &playerX ? &playerO : &playerX);
    }

    void run() {
        bool gameOver = false;

        while (!gameOver) {
            board.display();

            int row, col;
            std::cout << currentPlayer->getName()
                      << " (" << currentPlayer->getMark()
                      << "), enter your move (row col): ";

            while (!(std::cin >> row >> col) || !board.isValidMove(row, col)) {
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Enter numbers only: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    std::cout << "Try again (row col): ";
                }
            }

            board.placeMark(row, col, currentPlayer->getMark());

            if (board.checkWin(currentPlayer->getMark())) {
                board.display();
                std::cout << "\n*** " << currentPlayer->getName() << " wins! ***\n";
                gameOver = true;
            } 
            else if (board.isFull()) {
                board.display();
                std::cout << "\n*** It's a Draw! ***\n";
                gameOver = true;
            } 
            else {
                switchPlayer();
            }
        }
    }
};

int main() {
    Game ticTacToe;
    ticTacToe.run();
    return 0;
}
