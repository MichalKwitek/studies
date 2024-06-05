#include <iostream>
#include<string>
#include<vector>
#include <queue>
using namespace std;

#define RED 1
#define BLUE -1

const int dx[] = { 0, 1, 1, 0, -1, -1 };
const int dy[] = { -1, -1, 0, 1, 1, 0 };

struct Coord {
    int row;
    int col;
    bool operator==(const Coord& other) const {
        return row == other.row && col == other.col;
    }
};

void countPawns(string& s, int& redCounter, int& blueCounter) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] == 'r') redCounter++;
        else if (s[i] == 'b') blueCounter++;
}

void addPawns(vector<vector<int>>& board, string& s, bool& isUpperPart) {
    vector<int> line;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '<') {
            switch (s.at(i + 2)) {
            case 'r':
                line.insert(line.begin(), 1);
                break;
            case 'b':
                line.insert(line.begin(), -1);
                break;
            case ' ':
                line.insert(line.begin(), 0);
                break;
            }
        }
    }
    if (isUpperPart) {
        board.push_back({ line[line.size() - 1] });
        for (int i = 0; i < line.size() - 1; i++) {
            board[i].insert(board[i].begin(), line[i]);
        }
    }
    else {
        int j = 0;
        for (int i = board.size() - line.size(); i < board.size(); i++) {
            board[i].insert(board[i].begin(), line[j]);
            j++;
        }
    }
}

bool isValid(vector<vector<bool>>& visited, int& row, int& col) {
    if (row < 0 || col < 0 || row >= visited.size() || col >= visited.size())
        return false;
    if (visited[row][col])
        return false;
    return true;
}

void BFS(vector<vector<int>>& board, vector<vector<bool>>& visited, int row, int col, int& player, bool& found)
{
    Coord initial;
    initial.row = row;
    initial.col = col;
    queue<Coord> q;
    q.push(initial);

    while (!q.empty()) {
        Coord curr = q.front();
        q.pop();
        int row = curr.row;
        int col = curr.col;

        if (!isValid(visited, row, col) || board[row][col] != player)
            continue;

        visited[row][col] = true;

        if (((col == board.size() - 1) && board[row][col] == 1) || ((row == board.size() - 1) && board[row][col] == -1)) {
            found = true;
            return;
        }

        for (int dir = 0; dir < 6; dir++) {
            Coord next;
            next.row = row + dx[dir];
            next.col = col + dy[dir];
            if (isValid(visited, next.row, next.col) && board[next.row][next.col] == player)
                q.push(next);
        }
    }
    return;
}

bool checkWin(vector<vector<int>>& board, int player) {
    vector<vector<bool>> visited(board.size(), vector<bool>(board.size(), false));
    bool found = false;
    if (player == RED) {
        for (int i = 0; i < board.size(); i++) {
            if (!visited[i][0] && board[i][0] == 1)
                BFS(board, visited, i, 0, player, found);
            if (found) break;
        }
    }
    if (player == BLUE) {
        for (int i = 0; i < board.size(); i++) {
            if (!visited[0][i] && board[0][i] == -1)
                BFS(board, visited, 0, i, player, found);
            if (found) break;
        }
    }
    return found;
}

bool checkIntegrity(vector<vector<int>> board, int& player)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == player)
            {
                board[i][j] = 0;

                if (!checkWin(board, player))
                    return true;

                board[i][j] = player;
            }
        }
    }
    return false;
}

bool IsWinningFirstTurnObligatory(vector<vector<int>> board, int& player, int& row, int& col)
{
    board[row][col] = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = player;
                if (!checkWin(board, player))
                    return false;
                board[i][j] = 0;
            }
        }
    }
    return true;
}

bool checkNaive(vector<vector<int>>& board, int& player, int moves, bool& victoryIsPossible)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = player;

                if (checkWin(board, player))
                {
                    if (moves == 1)
                    {
                        board[i][j] = 0;
                        victoryIsPossible = true;
                        return victoryIsPossible;
                    }
                    else { // sprawdź czy jest takie pole że położenie na nim pionka nie spowoduje zwycięstwa
                        if (IsWinningFirstTurnObligatory(board, player, i, j)) {
                            board[i][j] = 0;
                            victoryIsPossible = false;
                            return victoryIsPossible;
                        }
                    }
                }

                if (moves > 1) // jak moves = 2 to wykona się jeszcze raz
                    checkNaive(board, player, moves - 1, victoryIsPossible);
                if (victoryIsPossible == true)
                {
                    board[i][j] = 0;
                    return victoryIsPossible;
                }

                board[i][j] = 0;
            }
        }
    }
    return victoryIsPossible;
}

bool initialiseNaive(vector<vector<int>>& board, int& redCounter, int& blueCounter, int& pawnCounter, int& voidCounter, int player, int moves)
{
    if (checkWin(board, RED))
        return false;
    else if (checkWin(board, BLUE))
        return false;

    int currentPlayer = 0;
    if (redCounter == blueCounter)
        currentPlayer = 1;
    else if (redCounter > blueCounter)
        currentPlayer = -1;

    int depth = 0;
    if (currentPlayer == player)
        depth = 1 + 2 * (moves - 1);
    else {
        depth = 2 + 2 * (moves - 1);
    }

    if (voidCounter < depth)
        return false;
    if (player == 1 && redCounter < (board.size() - moves))
        return false;
    if (player == -1 && blueCounter < (board.size() - moves))
        return false;

    bool victoryIsPossible = false;
    victoryIsPossible = checkNaive(board, player, moves, victoryIsPossible);
    return victoryIsPossible;
}

bool check1Case(vector<vector<int>>& board, int& player)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = player;

                if (checkWin(board, player))
                {
                    board[i][j] = 0;
                    return true;
                }

                board[i][j] = 0;
            }
        }
    }
    return false;
}

bool check2Case(vector<vector<int>>& board, int& player)
{
    int enemyMoves = 1;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = player;

                if (checkWin(board, player))
                {
                    if (enemyMoves > 0)
                    {
                        board[i][j] = 0;
                        enemyMoves--;
                    }
                    else
                    {
                        board[i][j] = 0;
                        return true;
                    }
                }

                board[i][j] = 0;
            }
        }
    }
    return false;
}

bool check3Case(vector<vector<int>>& board, int& player)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = player;

                if (!checkWin(board, player))
                    if (check2Case(board, player))
                    {
                        board[i][j] = 0;
                        return true;
                    }

                board[i][j] = 0;
            }
        }
    }
    return false;
}

bool check4Case(vector<vector<int>>& board, int& player)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = -1 * player;

                if (!check3Case(board, player))
                {
                    board[i][j] = 0;
                    return false;
                }

                board[i][j] = 0;
            }
        }
    }
    return true;
}

bool initialisePerfect(vector<vector<int>>& board, int& redCounter, int& blueCounter, int& pawnCounter, int& voidCounter, int player, int moves)
{
    if (checkWin(board, RED))
        return false;
    else if (checkWin(board, BLUE))
        return false;

    int currentPlayer = 0;
    if (redCounter == blueCounter)
        currentPlayer = 1;
    else if (redCounter > blueCounter)
        currentPlayer = -1;

    int depth = 0;
    if (currentPlayer == player)
        depth = 1 + 2 * (moves - 1);
    else {
        depth = 2 + 2 * (moves - 1);
    }

    if (voidCounter < depth)
        return false;
    if (player == 1 && redCounter < (board.size() - moves))
        return false;
    if (player == -1 && blueCounter < (board.size() - moves))
        return false;

    if (depth == 1)
    {
        if (check1Case(board, player))
            return true;
    }
    else if (depth == 2)
    {
        if (check2Case(board, player))
            return true;
    }
    else if (depth == 3)
    {
        if (check3Case(board, player))
            return true;
    }
    else if (depth == 4)
    {
        if (check4Case(board, player))
            return true;
    }
    return false;
}

int main()
{
    string line = "Hello";
    while (getline(cin, line)) {

        // wczytywanie inputu
        if (line.find("---") != string::npos) {
            vector<vector<int>> board;
            int pawnCounter = 0;
            int redCounter = 0;
            int blueCounter = 0;
            int voidCounter = 0;
            bool boardIsCorrect = true;
            bool isUpperPart = true;
            while (line.at(0) != '<') {
                getline(cin, line);
                if (line.find('<') != string::npos) {
                    countPawns(line, redCounter, blueCounter);
                    addPawns(board, line, isUpperPart);
                }
            }
            isUpperPart = false;
            for (int i = 0; i < board.size(); i++) {
                getline(cin, line);
                countPawns(line, redCounter, blueCounter);
                addPawns(board, line, isUpperPart);
            }
            pawnCounter = redCounter + blueCounter;
            voidCounter = board.size() * board.size() - pawnCounter;
            if (blueCounter > redCounter || redCounter > (blueCounter + 1))
                boardIsCorrect = false;

            // operacje na inpucie
            int k = 4; int whoWon = 0;
            while (getline(cin, line) && !line.empty()) {
                k--;
                if (line == "BOARD_SIZE")
                    cout << board.size() << endl;
                else if (line == "PAWNS_NUMBER")
                    cout << pawnCounter << endl;
                else if (line == "IS_BOARD_CORRECT") {
                    if (boardIsCorrect)
                        cout << "YES" << endl;
                    else cout << "NO" << endl;
                }
                else if (line == "IS_GAME_OVER") {
                    if (checkWin(board, RED) && boardIsCorrect)
                        cout << "YES RED" << endl;
                    else if (checkWin(board, BLUE) && boardIsCorrect)
                        cout << "YES BLUE" << endl;
                    else cout << "NO" << endl;
                }
                else if (line == "IS_BOARD_POSSIBLE") {
                    if (boardIsCorrect) {
                        bool isGameOver = false;
                        if (checkWin(board, RED) || checkWin(board, BLUE))
                            isGameOver = true;
                        int lastPlayer;
                        if (redCounter > blueCounter)
                            lastPlayer = RED;
                        else lastPlayer = BLUE;
                        if (isGameOver && checkWin(board, lastPlayer)) {
                            if (checkIntegrity(board, lastPlayer))
                                cout << "YES" << endl;
                            else cout << "NO" << endl;
                        }
                        else if (!isGameOver)
                            cout << "YES" << endl;
                        else  cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
                    if (boardIsCorrect) {
                        if (initialiseNaive(board, redCounter, blueCounter, pawnCounter, voidCounter, RED, 1))
                            cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                    if (boardIsCorrect) {
                        if (initialiseNaive(board, redCounter, blueCounter, pawnCounter, voidCounter, RED, 2))
                            cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
                    if (boardIsCorrect) {
                        if (initialiseNaive(board, redCounter, blueCounter, pawnCounter, voidCounter, BLUE, 1))
                            cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
                    if (boardIsCorrect) {
                        if (initialiseNaive(board, redCounter, blueCounter, pawnCounter, voidCounter, BLUE, 2))
                            cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
                    if (boardIsCorrect && whoWon != BLUE) {
                        if (initialisePerfect(board, redCounter, blueCounter, pawnCounter, voidCounter, RED, 1))
                        {
                            cout << "YES" << endl;
                            whoWon = RED;
                        }
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
                    if (boardIsCorrect && whoWon != BLUE) {
                        if (initialisePerfect(board, redCounter, blueCounter, pawnCounter, voidCounter, RED, 2))
                        {
                            cout << "YES" << endl;
                            whoWon = RED;
                        }
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
                    if (boardIsCorrect && whoWon != RED) {
                        if (initialisePerfect(board, redCounter, blueCounter, pawnCounter, voidCounter, BLUE, 1))
                        {
                            cout << "YES" << endl;
                            whoWon = BLUE;
                        }
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else if (line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
                    if (boardIsCorrect && whoWon != RED) {
                        if (initialisePerfect(board, redCounter, blueCounter, pawnCounter, voidCounter, BLUE, 2))
                        {
                            cout << "YES" << endl;
                            whoWon = BLUE;
                        }
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                if (k == 0) break;
            }
        }
    }
}