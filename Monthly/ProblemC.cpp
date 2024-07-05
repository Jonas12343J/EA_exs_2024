#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

int rows;
int columns;
int startX;
int startY;
int endX;
int endY;
int numCovers;
int pathLength;
int dfsCounter;
int manholeCounter;

vector<vector<char>> maze;
vector<vector<int>> neighbors;
vector<int> manholes;
vector<bool> visited;
vector<int> low;
vector<int> dfs;
vector<int> manholeGraph;

pair<pair<int, int>, pair<int, int>> bridge;

stack<int> path;

//int targetManholes;

bool indexOK(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < columns && maze[r][c] != '#';
}

void findBridges() {
    stack<pair<int, pair<int, int>>> stk;
    

    stk.push({endX*columns + endY, {endX*columns + endY, -1}});

    bool pathComplete = false;
    bool bridgeFound = false;

    while (!stk.empty()) {
        auto &top = stk.top();
        int current = top.first;
        int parent = top.second.first;
        //int &state = current.second.second;
        
        // if (state == -1){ // Initial call


        
        if (!visited[current]) {
            
            visited[current] = true;
            dfs[current] = low[current] = ++dfsCounter;

            int currentY = current % columns;
            int currentX = (current - currentY) / columns;

            if(!pathComplete) {
                path.push(current);
            } 
            if (maze[currentX][currentY] == 'M') {
                manholeGraph[current] = 1;
            } else if (maze[currentX][currentY] == 'E') {
                manholeGraph[current] = -1;
            } else if (maze[currentX][currentY] == 'D') {
                pathComplete = true;
            }

            

            //state = 0;
        }

        bool pathFound = true;

        for (int neighbor : neighbors[current]) {
            if (neighbor == parent) continue; // Skip parent
            if (!visited[neighbor]) {
                stk.push({neighbor, {current, -1}}); // Recurse for child
                pathFound = false;
                break;
            } else {
                low[current] = min(low[current], dfs[neighbor]);
            }
        }


        if(pathFound) {
            if (parent != current) {
                if (manholeGraph[current] == -1) {
                    manholeGraph[parent] = -1;
                } else if (manholeGraph[parent] != -1) {
                    manholeGraph[parent] += manholeGraph[current];
                }

                if (low[current] > dfs[parent] && !bridgeFound) {

                    /*
                    // Print bridge added
                    cout << "Bridge: (" << p / m << ", " << p % m << ") - (" << u / m << ", "
                            << u % m << ")\n";
                    // Print manhole covering
                    cout << "Manhole covering: " << manhole_covering[p] << "\n";
                    */

                    if ((manholes.size() - manholeGraph[current]) <= numCovers) {
                        
                        int parentY = parent % columns;
                        int parentX = (parent - parentY) / columns;
                        int currentY = current % columns;
                        int currentX = (current - currentY) / columns;

                        bridge = {{parentX, parentY}, {currentX, currentY}};

                        neighbors[parent].erase(remove(neighbors[parent].begin(), neighbors[parent].end(), current), neighbors[parent].end());
                        neighbors[current].erase(remove(neighbors[current].begin(), neighbors[current].end(), parent), neighbors[current].end());
                        // Find the manholes in the current component of the flood gate
                        //cout << "Flood gate: " << parentX << " " << parentY << " " << currentX << " " << currentY << " manholes: " << manholeGraph[current] << "\n";
                        //return;
                        bridgeFound = true;
                    }
                }
                low[parent] = min(low[parent], low[current]);
            }

            if(!pathComplete) {
                path.pop();
            }

            stk.pop();
        }
    }    
}

void findManholes(int i, int j)
{
    int id = i*columns + j;
    if (visited[id])
    {
        return;
    }

    visited[id] = true;

    if(maze[i][j] == 'M')
    {
        manholes.erase(remove(manholes.begin(), manholes.end(), i * columns + j), manholes.end());
        //cout << "found manholes " << i << " " << j << endl;
    }

    //iterate trough neighbors
    for (int k = 0; k < neighbors[id].size(); k++)
    {
        int neighbor = neighbors[id][k];
        int y = neighbor % columns;
        int x = (neighbor - y) / columns;

        if(!visited[neighbor])
        {
            findManholes(x, y);
        }
    }
}

int main() {
    int numTestCases;
    cin >> numTestCases;

    for (int k = 0; k < numTestCases; k++)
    {
        cin >> rows >> columns;

        //targetManholes = 0;

        maze.resize(rows, vector<char>(columns));
        neighbors.resize(rows * columns);
        visited.resize(rows * columns, false);
        low.resize(rows * columns);
        dfs.resize(rows * columns);
        manholeGraph.resize(rows * columns);

        dfsCounter = 0;
        manholeCounter = 0;
        //pathLength = 0;

        char input;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cin >> input;
                maze[i][j] = input;
                /*
                if (input != '#')
                {
                    int id = i * columns + j;

                    if (j != 0 && maze[i][j-1] != '#')
                    {
                        neighbors[id].push_back(i * columns + j - 1);
                        neighbors[i * columns + j - 1].push_back(id);
                    }

                    if(i != 0 && maze[i-1][j] != '#')
                    {
                        neighbors[id].push_back((i-1) * columns + j);
                        neighbors[(i-1) * columns + j].push_back(id);
                    }
                }
                */

                if(input == 'D')
                {
                    startX = i;
                    startY = j;
                } else if(input == 'E')
                {
                    endX = i;
                    endY = j;
                } else if (input == 'M')
                {
                    manholeCounter++;
                    manholes.push_back(i * columns + j);
                }

                if (indexOK(i, j)) {
                    int node = i*columns + j;

                    // Check the left neighbor
                    if (j > 0 && indexOK(i, j - 1)) {
                        int leftNeighbor = i * columns + j - 1;
                        neighbors[node].push_back(leftNeighbor);
                        neighbors[leftNeighbor].push_back(node);
                    }

                    // Check the upper neighbor
                    if (i > 0 && indexOK(i - 1, j)) {
                        int upperNeighbor = (i-1) * columns + j;
                        neighbors[node].push_back(upperNeighbor);
                        neighbors[upperNeighbor].push_back(node);
                    }
                }

            }
            
        }
        
        cin >> numCovers;

        findBridges();

        cout << bridge.first.first << " " << bridge.first.second << " " << bridge.second.first << " " << bridge.second.second << "\n";

        int indice = bridge.first.first*columns + bridge.first.second;


        //cout << manholeCounter << " vs " << manholeGraph[indice] << endl;

        visited.clear();
        visited.resize(rows * columns, false);
        findManholes(bridge.second.first, bridge.second.second);
        cout << manholes.size() << endl;

        for (int i = 0; i < manholes.size(); i++)
        {
            int y = manholes[i] % columns;
            int x = (manholes[i] - y) / columns;
            cout << x << " " << y << endl;
        }

        
        cout << path.size() << "\n";
        while (!path.empty()) {
            int pathY = path.top() % columns;
            int pathX = (path.top() - pathY) / columns;

            cout << pathX << " " << pathY << "\n";
            path.pop();
        }

        maze.clear();
        neighbors.clear();
        manholes.clear();
        visited.clear();
        low.clear();
        dfs.clear();
        manholeGraph.clear();

    }
}