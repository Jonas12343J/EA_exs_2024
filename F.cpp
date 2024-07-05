#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> objects;

void guards(int range)
{
    int nGuards = 1;
    int pos = objects[0] + range;

    for (int i = 2; i < objects.size(); ++i)
    {
        if (objects[i] > pos + range)
        {
            nGuards++;
            pos = objects[i] + range;
        }
    }

    cout << nGuards << endl;
}

int main()
{
    int nTesteCases;
    cin >> nTesteCases;
    for (int i = 0; i < nTesteCases; ++i)
    {
        int nValuables, range, pos;
        cin >> nValuables >> range;

        for (int j = 0; j < nValuables; ++j)
        {
            cin >> pos;
            objects.push_back(pos);
        }

        sort(objects.begin(), objects.end());

        guards(range);

        objects.clear();
    }
}