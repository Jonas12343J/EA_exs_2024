#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

vector<vector<int>> neighbors;
vector<pair<int, int>> coordinates;
vector<int> connected;
vector<int> set;
vector<int> rankVect;

double myPow(int a, int b) {
    double result = 1;

    return ((a-b)*(a-b));
}

double euclidean_distance(int a, int b) {
    int x1 = coordinates[a].first;
    int y1 = coordinates[a].second;
    int x2 = coordinates[b].first;
    int y2 = coordinates[b].second;

    return sqrt(myPow(x1, x2) + myPow(y1, y2));
}

void makeSet(int n) {
    set.resize(n);
    rankVect.resize(n);

    for (int i = 0; i < n; i++) {
        set[i] = i;
        rankVect[i] = 0;
    }
}

int findSet(int i) {
    if (set[i] != i) {
        set[i] = findSet(set[i]);    
    }
    return set[i];
}

void unionSet(int i, int j) {
    int x = findSet(i);
    int y = findSet(j);

    if (x != y) {
        if (rankVect[x] > rankVect[y]) {
            set[y] = x;
        } else {
            set[x] = y;

            if (rankVect[x] == rankVect[y]) {
                rankVect[y]++;
            }
        }
    }
}

double cableNeeded() {
    vector<pair<double, pair<int, int>>> edges;

    for (int i = 0; i < neighbors.size(); i++) {
        for (int j = 0; j < neighbors[i].size(); j++) {
            edges.push_back(make_pair(euclidean_distance(i, neighbors[i][j]), make_pair(i, neighbors[i][j])));
        }
    }

    sort(edges.begin(), edges.end());

    double total = 0;

    makeSet(neighbors.size());

    for (int i = 0; i < edges.size(); i++) {
        int x = edges[i].second.first;
        int y = edges[i].second.second;

        if (findSet(x) != findSet(y)) {
            unionSet(x, y);
            total += euclidean_distance(x, y);
        }
    }

    return total;
}


int main() {
    int n;
    
    while (cin >> n) {

        neighbors.resize(n);
        coordinates.resize(n);
        connected.resize(n, 0);

        for (int i = 0; i < n; i++) {
            int x, y;
            
            cin >> x >> y;

            coordinates[i] = make_pair(x, y);
        }
        int m;

        cin >> m;

        for (int i = 0; i < m; i++) {
            int a, b;

            cin >> a >> b;
            a--;
            b--;

            neighbors[a].push_back(b);
            neighbors[b].push_back(a);

            connected[a]++;
            connected[b]++;
        }

        cout << fixed;
        cout.precision(2);

        cout << cableNeeded() << endl;

        neighbors.clear();
        coordinates.clear();
        connected.clear();
    }
}