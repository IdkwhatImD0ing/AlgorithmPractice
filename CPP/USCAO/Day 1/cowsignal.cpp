#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<char>> output;

int main()
{
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);
    int m, n, k;
    cin >> m >> n >> k;
    for (int i = 0; i < m; i++)
    {
        vector<char> line;
        for (int j = 0; j < n; j++)
        {
            char temp;
            cin >> temp;

            for (int length = 0; length < k; length++)
            {
                line.push_back(temp);
            }
        }
        for (int length = 0; length < k; length++)
        {
            output.push_back(line);
        }
    }

    for (int i = 0; i < k * m; i++)
    {
        for (int j = 0; j < k * n; j++)
        {
            cout << output[i][j];
        }
        cout << endl;
    }
}