#include <iostream>
#include <algorithm>

using namespace std;

int n;
pair<int, int> cows[3000];
int pAbove[3000][3000];
int pBelow[3000][3000];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> cows[i].first >> cows[i].second;
    }

    sort(cows, cows + n);

    for (int i = 0; i < n; i++) // Generate the prefix sum array
    {
        for (int j = 0; j < n; j++)
        {
            pAbove[i][j + 1] = pAbove[i][j];
            pBelow[i][j + 1] = pBelow[i][j];

            if (cows[j].second >= cows[i].second)
            {
                pAbove[i][j + 1]++;
            }
            if (cows[j].second <= cows[i].second)
            {
                pBelow[i][j + 1]++;
            }
        }
    }

    long long total = 0;

    for (int i = 0; i < n; i++) // Line Sweep algorithm
    {
        for (int j = i; j < n; j++)
        {
            if (cows[j].second > cows[i].second)
            {
                total += (pAbove[j][j + 1] - pAbove[j][i]) * (pBelow[i][j + 1] - pBelow[i][i]);
            }
            else
            {
                total += (pBelow[j][j + 1] - pBelow[j][i]) * (pAbove[i][j + 1] - pAbove[i][i]);
            }
        }
    }

    cout << total + 1 << endl;
}