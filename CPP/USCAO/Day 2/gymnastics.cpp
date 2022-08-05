#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int main()
{
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> rankings;

    vector<vector<bool>> consistent(k, vector<bool>(k, true));

    for (int i = 0; i < n; i++)
    {
        vector<int> tempVector;
        for (int j = 0; j < k; j++)
        {
            int temp;
            cin >> temp;
            tempVector.push_back(temp);
        }
        rankings.push_back(tempVector);
    }

    // Finding consistent pairs
    for (int i = 1; i < k + 1; i++)
    {
        for (int j = 1; j < k + 1; j++)
        {
            // Going through all rankings
            if (i == j) // Cant compare with self
            {
                continue;
            }
            for (int x = 0; x < rankings.size(); x++)
            {
                vector<int> temp = rankings[x];
                int index1 = find(temp.begin(), temp.end(), i) - temp.begin();
                int index2 = find(temp.begin(), temp.end(), j) - temp.begin();
                if (index1 < index2) // Consistent
                {
                    continue;
                }
                else
                {
                    consistent[i - 1][j - 1] = false;
                }
            }
        }
    }

    // Checking for remaining consistent pairs
    int remainder = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i == j) // Self always true
            {
                continue;
            }
            if (consistent[i][j])
            {
                remainder++;
            }
        }
    }

    cout << remainder << endl;
}