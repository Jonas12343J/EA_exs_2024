#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int chessBoard[400][400] = {};

int countOnes(const vector<vector<int>> &chessBoard, int x)
{
    int cont = 0;
    for (const auto &row : chessBoard)
    {
        cont += count(row.begin(), row.end(), x);
    }
    return cont;
}

int move(int x, int y, int nMoves)
{
    int sum = 0;

    if (chessBoard[x][y] == 0)
    {
        chessBoard[x][y] = 1;
        sum = 1;
    }

    if (nMoves == 0)
        return sum;

    // Recursividade
    // x -> +/- 2 COM y +/- 1
    // x -> +/- 1 COM y +/- 2
    else
    {
        sum += move(x + 2, y - 1, nMoves - 1);
        sum += move(x + 2, y + 1, nMoves - 1);
        sum += move(x - 2, y - 1, nMoves - 1);
        sum += move(x - 2, y + 1, nMoves - 1);
        sum += move(x + 1, y - 2, nMoves - 1);
        sum += move(x + 1, y + 2, nMoves - 1);
        sum += move(x - 1, y - 2, nMoves - 1);
        sum += move(x - 1, y + 2, nMoves - 1);
    }

    return sum;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<vector<int>> chessBoard(400, vector<int>(400, 0));

    int nHorses, count = 0;

    cin >> nHorses;

    for (int i = 0; i < nHorses; ++i)
    {
        int x, y, nMoves;
        cin >> x;
        cin >> y;
        cin >> nMoves;
        x += 200;
        y += 200;

        chessBoard[x][y] = 1;
        count += move(x, y, nMoves);
    }

    cout << count << endl;
}