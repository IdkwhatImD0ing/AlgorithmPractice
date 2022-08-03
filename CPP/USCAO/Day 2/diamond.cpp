#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() // Diamond Collector
{
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> diamonds(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> diamonds[i];
    }
    sort(diamonds.begin(), diamonds.end()); // Sorts all diamonds
    int maximum = 0;
    for (int i = 0; i < n; i++) // For all diamonds
    {
        int local_max = 0;
        for (int j = i; j < n; j++) // Finds all diamonds within range
        {
            if (diamonds[j] <= diamonds[i] + k)
            {
                local_max++;
            }
        }
        maximum = max(maximum, local_max); // Finds the maximum possible diamonds in bag
    }

    cout << maximum << endl;
}