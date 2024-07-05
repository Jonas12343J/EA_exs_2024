#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pizzas;
vector<vector<bool>> table;

void cooker()
{
    for (int i = 0; i < pizzas.size(); ++i)
        table[i][0] = true;

    for (int i = 1; i < table.size(); ++i)
    {
        for (int j = 1; j < table[0].size(); ++j)
        {
            if (pizzas[i] > j)
            {
                table[i][j] = table[i - 1][j];
            }
            else
            {
                table[i][j] = table[i - 1][j] || table[i - 1][j - pizzas[i]];
            }
        }
    }
}

int main()
{
    int n;

    while (cin >> n)
    {
        int sum = 0;
        pizzas.resize(n + 1, 0);

        for (int i = 0; i < n; ++i)
        {
            cin >> pizzas[i+1];
            sum += pizzas[i+1];
        }

        table.resize(n + 1, vector<bool>(sum / 2 + 1, false));

        cooker();
        

        // cout << sum << endl;
        for (int i = table[0].size() - 1; i > -1; --i)
        {
            if (table[n][i])
            {
                cout << (sum) - (2 * i) << endl;
                break;
            }
        }

        pizzas.clear();
        table.clear();
    }
}