#include <iostream>
#include <vector>
#include <istream>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> neighbors;
vector<int> visited;
vector<int> low;
vector<int> num;

// -----------------------------------
int articulation_points(int u, int parent, int depth, int &count)
{
    visited[u] = 1;
    low[u] = num[u] = depth;
    int children = 0;
    bool is_articulation = false;

    for (int v : neighbors[u])
    {
        if (v == parent)
            continue;

        if (!visited[v])
        {
            children++;
            articulation_points(v, u, depth + 1, count);
            low[u] = min(low[u], low[v]);

            if (low[v] >= num[u])
                is_articulation = true;
        }
        else
        {
            low[u] = min(low[u], num[v]);
        }
    }

    if ((parent == -1 && children > 1) || (parent != -1 && is_articulation))
    {
        count++;
    }

    return count;
}
// -----------------------------------

int main()
{
    int n;

    while ((cin >> n) && (n != 0))
    {
        neighbors.resize(n);
        visited.resize(n, 0);
        low.resize(n, 0);
        num.resize(n, 0);

        cin.ignore(32767, '\n');

        string line;

        while (getline(cin, line))
        {
            istringstream iss(line);
            int x, y;
            iss >> x;

            if (x == 0)
                break;

            while (iss >> y)
            {
                neighbors[x - 1].push_back(y - 1);
                neighbors[y - 1].push_back(x - 1);
            }
        }


        int count = 0;
        cout << articulation_points(0, -1, 0, count) << endl;

        visited.clear();
        low.clear();
        num.clear();
        neighbors.clear();
    }
}