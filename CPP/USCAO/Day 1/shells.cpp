#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int pos[3] = {0, 1, 2};
int points[3] = {0, 0, 0};

int main()
{
    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w", stdout);
    int a = 0;
    cin >> a;

    int first = 0;
    int second = 0;
    int guess = 0;
    for (int i = 0; i < a; i++)
    {
        cin >> first;
        cin >> second;
        cin >> guess;
        first -= 1; // The input is from 1-3 whereas our array uses 0-2;
        second -= 1;
        guess -= 1;
        for (int j = 0; j < 3; j++)
        {
            if (pos[j] == first) // Performs the swaps
            {
                pos[j] = second;
            }
            else if (pos[j] == second)
            {
                pos[j] = first;
            }
            if (pos[j] == guess) // Checks for guess
            {
                points[j]++;
            }
        }
    }

    cout << max({points[0], points[1], points[2]}) << endl;
    return 1;
}