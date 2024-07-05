#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> neighbours;
vector<int> visited;

void check_trains() {
    for (int i = 0; i < neighbours.size(); i++) {
        for (int j = 0; j < neighbours[i].size(); j++) {
            // temp: posiçao do vizinho no visited
            int temp = neighbours[i][j] - 1;
           
            if (visited[i] != -1) { // nao visitado
                if (visited[temp] == -1) {
                    if (visited[i] == 0)
                        visited[temp] = 1;
                    else
                        visited[temp] = 0;
                }
            } else {
                if (visited[temp] == -1) {
                    visited[i] = 0;
                    visited[temp] = 1;
                } else {
                    if (visited[temp] == 0)
                        visited[i] = 1;
                    else
                        visited[i] = 0;
                }
            }
            
        }
    }
}

int validate() {
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < neighbours[i].size(); j++) {
            int temp = neighbours[i][j] - 1;
            if (visited[i] == visited[temp])
                return 0;
        }
    }

    return 1;
}

int main()
{
    int n, m;
    
    while(cin >> n >> m) {
        neighbours.resize(n);
        visited.resize(n, -1);

        for (int i = 0; i < m; i++) {
            int ID1, ID2;
            cin >> ID1 >> ID2;
            neighbours[ID1-1].push_back(ID2);
            neighbours[ID2-1].push_back(ID1);
        }

        visited[0] = 0;

        check_trains();

        int result = validate();
        
        neighbours.clear();
        visited.clear();

        cout << (result == 1 ? "NOT SURE" : "NO") << endl;
    }
}