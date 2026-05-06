#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int row, int col, vector<vector<char>> &board, int n)
{
    for (int j = 0; j < col; j++)
    {
        if (board[row][j] == 'Q')
        {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    return true;
}

void solve(vector<vector<char>> &board, vector<vector<string>> &ans, int col, int n)
{
    if (col == n)
    {
        vector<string> temp;
        for (int i = 0; i < n; i++)
        {
            string row(board[i].begin(), board[i].end());
            temp.push_back(row);
        }
        ans.push_back(temp);
    }

    for (int row = 0; row < n; row++)
    {
        if (isSafe(row, col, board, n))
        {
            board[row][col] = 'Q';
            solve(board, ans, col + 1, n);
            board[row][col] = '.';
        }
    }
}

vector<vector<string>> nQueens(int n)
{
    vector<vector<string>> ans;
    vector<vector<char>> board(n, vector<char>(n, '.'));

    solve(board, ans, 0, n);
    return ans;
}

int main()
{
    int n;
    cout << "Enter the dimensions of the chess board: ";
    cin >> n;

    vector<vector<string>> res = nQueens(n);

    for (auto &board : res)
    {
        for (auto &row : board)
        {
            cout << row << "\n";
        }
        cout << "\n";
    }

    return 0;
}