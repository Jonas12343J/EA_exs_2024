#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> people;
    
    int input, nGuests, value;

    while (cin >> input)
    {
        int success = 0;
        nGuests = input;
        cin >> input;

        while (input != 0)
        {
            people.push_back(input);
            cin >> input;
        }
        sort(people.begin(), people.end());

        // Sets preenchidos
        for(int i = 0; i < people.size(); ++i) {
            int ptrStart = i+1;
            int ptrEnd = people.size() - 1;

            while (ptrStart < ptrEnd) {
                if (people[ptrStart] + people[i] + people[ptrEnd] == 0)
                {
                    success = 1;
                    break;
                }
                else if (people[ptrStart] + people[i] + people[ptrEnd] < 0)
                {
                    ptrStart++;
                }
                else
                {
                    ptrEnd--;
                }
            }
        }
        
        if (success)
            cout << "Fair" << endl;
        else
            cout << "Rigged" << endl;
        // reset sets
        people.clear();
    }
}
