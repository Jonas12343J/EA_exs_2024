#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> matriz;


int func(int rows, int columns)
{


    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            matriz[i][j] = matriz[i][j] + max(matriz[i-1][j], matriz[i-1][j-1]);
        }
    }

    int max = 0;
    for (int j = 1; j < columns; ++j) {
        if (max < matriz[rows - 1][j])
            max = matriz[rows - 1][j];
    }
    return max;
}

int main()
{
    int n, nRows;

    cin >> n;

    // O(n)
    for (int i = 0; i < n; ++i)
    {
        cin >> nRows;

        matriz.resize(nRows + 1, vector<int>(nRows + 1));

        for (int i = 1; i < matriz.size(); ++i)
        {
            for (int j = 1; j < matriz[i].size(); ++j)
            {
                if (i >= j)
                {
                    cin >> matriz[i][j];
                }
            }
        }

        cout << func(matriz.size(), matriz[0].size()) << endl;

        matriz.clear();
    }
}