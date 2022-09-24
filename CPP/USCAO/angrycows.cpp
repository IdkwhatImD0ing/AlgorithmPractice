#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> bales;

int exploded_num(int start, int direction)
{
    int radius = 1;
    int prev = start;
    while (true)
    {
        int next = prev;
        // Get the furthest explosion index without exceeding the current radius
        while (
            next + direction >= 0 && next + direction < N && abs(bales[next + direction] - bales[prev]) <= radius)
        {
            next += direction;
        }

        // We didn't find a new haybale, so the chain explosion is over
        if (next == prev)
        {
            break;
        }

        // Update our previous explosion and increment radius
        prev = next;
        radius++;
    }
    return abs(prev - start);
}

int main()
{
    // freopen("angry.in", "r", stdin);
    // freopen("angry.out", "w", stdout);

    cin >> N;
    bales.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> bales[i];
    }

    sort(bales.begin(), bales.end());
    int max_exploded = 0;
    for (int i = 0; i < N; i++)
    {
        // Get the number of exploded bales for the left & right side
        max_exploded = max(
            max_exploded, exploded_num(i, -1) + exploded_num(i, 1) + 1);
    }
    cout << max_exploded << endl;
}
