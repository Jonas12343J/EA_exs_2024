#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> neighbours;
vector<int> visited;
int best;

int coutNeighbours(int member, int nodeCount)
{
    for (int j = member; j < visited.size(); j++) {
        if (visited[j] == 0) {
            nodeCount++;
        }
    }
    return nodeCount;
}

void social(int nodeCount, int currentNode)
{
    if (nodeCount > best)
        best = nodeCount;

    if (coutNeighbours(currentNode, nodeCount) <= best)
        return;


    for (int i = currentNode + 1; i < neighbours.size(); i++)
    {
        if (neighbours[currentNode][i])
            visited[i]++;
    }

    for (int i = currentNode + 1; i < neighbours.size(); i++)
    {
        if (!visited[i])
            social(nodeCount + 1, i);
    }

    for (int i = currentNode + 1; i < neighbours.size(); i++)
    {
        if (neighbours[currentNode][i])
            visited[i]--;
    }
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        best = -1;
        neighbours.resize(n, vector<int>(n, 0));
        visited.resize(n, 0);
        for (int i = 0; i < m; ++i)
        {
            int memberA, memberB;
            cin >> memberA >> memberB;

            neighbours[memberA][memberB] = 1;
            neighbours[memberB][memberA] = 1;
        }

        for(int i = 0; i < n; i++){
            social(1, i);
        }
            

        cout << best << endl;

        neighbours.clear();
        visited.clear();
    }
}