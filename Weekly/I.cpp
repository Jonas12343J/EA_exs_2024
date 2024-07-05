#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

// Que conexões existem entre nós
vector<vector<int>> connections;

// Quanto custa ir de um nó para outro
vector<vector<int>> cost;

vector<int> visited;

// Priority queue ordered by first element (min)
priority_queue<pair<int,int> , vector<pair<int,int>>, greater<pair<int,int>>> pq;

int best = INT_MAX;

// Dijkstra algorithm
int travel_dijkstra(int finish, int current) {
    if (current == finish) {
        //cout << "Chegou" << endl;
        best = min(best, pq.top().first);
        return best;
    }

    //cout << "start" << endl;
    pq.pop();
    //cout << "apagou" << endl;

    for (int j = 0; j < connections[current].size(); j++) {
        //cout << "for: " << current << endl;

        // Por na fila de prioridade o custo dos nós que são conexões + o valor da ligação anterior
        pair temp = make_pair(cost[current][connections[current][j]] + visited[current], connections[current][j]);
        //cout << "temp: " << temp.first << " " << temp.second << endl;
        pq.push(temp);

    }

    // Visitar o nó com menor custo !pq.empty() && 
    while (visited[pq.top().second] < pq.top().first) {
        //cout << "inuteis" << endl;
        pq.pop();
    }

    //cout << "saiu do while" << endl;
    
    visited[pq.top().second] = pq.top().first;
    travel_dijkstra(finish, pq.top().second);

    return best;

}

int main() {
    int n, finish;
    while (cin >> n >> finish) {
        connections.resize(n);
        cost.resize(n, vector<int>(n,  0));
        visited.resize(n, INT_MAX);

        int input;

        for (int i = 0; i < n; i++) {
            int ID;
            cin >> ID;
            ID--;
            for (int j = 0; j < n; j++) {
                cin >> input;
                if (input > 0) {
                    connections[ID].push_back(j);
                }
                cost[ID][j] = input;
            }
        }

        pq.push(make_pair(0, 0));
        visited[0] = 0;

/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < connections[i].size(); j++) {
                cout << connections[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << cost[i][j] << " ";
            }
            cout << endl;
        }
*/

        cout << travel_dijkstra(finish - 1, 0) << endl;

        connections.clear();
        cost.clear();
        visited.clear();
    }
}