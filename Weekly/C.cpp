#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

vector<vector<int>> pairs;
vector<bool> nodes; // visitado
vector<int> neighboors;

int best;
int k;

void buildNetwork(int len, int depth)
{
    if (len >= best)
        return;

    if (depth == nodes.size())
    {
        best = len;
        return;
    }

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i] && neighboors[i] < k)
        {
            for (int j = 0; j < nodes.size(); ++j)
            {
                if (!nodes[j] && pairs[i][j] != 0)
                {
                    ++neighboors[i];
                    ++neighboors[j];
                    nodes[j] = true;
                    // chamada recursiva
                    buildNetwork(len + pairs[i][j], depth + 1);
                    nodes[j] = false;
                    --neighboors[i];
                    --neighboors[j];
                }
            }
        }
    }
}

int main()
{
    int n, m;

    while (cin >> n)
    {
        cin >> m >> k;

        int point1, point2, cost;

        pairs.resize(0);
        pairs.resize(n, vector<int>(n, 0));
        nodes.resize(n, false);
        nodes[0] = true;

        neighboors.resize(n, 0);

        for (int i = 0; i < m; ++i)
        {
            cin >> point1 >> point2 >> cost;

            pairs[point1 - 1][point2 - 1] = pairs[point2 - 1][point1 - 1] = cost;
        }
        nodes[0] = true;

        best = INT_MAX;

        buildNetwork(0, 1);

        cout << (best < INT_MAX && best >= 0 ? to_string(best) : "NO WAY!") << endl;
    }
}