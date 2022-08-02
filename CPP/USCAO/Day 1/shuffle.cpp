#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int main() // Bovine Shuffle
{
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> id(n, 0);

    unordered_map<int, int> reverseMap; // Reverse movements

    for (int i = 0; i < n; i++) // Stores all movements
    {
        int temp;
        cin >> temp;
        reverseMap[temp - 1] = i;
    }

    for (int i = 0; i < n; i++) // Stores cow Ids
    {
        cin >> id[i];
    }

    for (int i = 0; i < 3; i++) // 3 Shuffles
    {
        vector<int> temp(n, 0);
        for (auto it : reverseMap) // Shuffles
        {
            temp[it.second] = id[it.first];
        }

        id = temp; // New Positions
    }

    for (int i = 0; i < n; i++)
    {
        cout << id[i] << endl;
    }
}