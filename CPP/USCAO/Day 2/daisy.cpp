#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int total = 0;

    vector<int> flowers(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> flowers[i];
    }
    for (int i = 0; i < n; i++) // Go though all pairs
    {
        for (int j = i; j < n; j++)
        {
            vector<int> temp(&flowers[i], &flowers[j + 1]); // Sub Vector

            double average = accumulate(temp.begin(), temp.end(), 0.0) / temp.size(); // Find average

            if (find(temp.begin(), temp.end(), average) != temp.end()) // Check if average inside sub vector
            {
                total++;
            }
        }
    }
    cout << total << endl;
    return total;
}