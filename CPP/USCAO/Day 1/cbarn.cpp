#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{ // Circular Barn
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> pos(n, 0);
    int cows = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> pos[i];
        cows += pos[i];
    }

    int out = INT32_MAX;
    for (int i = 0; i < n; i++) // Brute force trying out all doors
    {
        int remaining = cows;
        int distance = 0;
        for (int j = 0; j < n; j++) // For each door, go through all other rooms
        {
            remaining -= pos[(i + j) % n]; // Question states that all cows walk through the door then go circular, so we simply subtract the number of cows in the room from the remaining cows
            distance += remaining;         // The remaining cows all walk 1 distance each, so we add them all up
        }
        out = min(out, distance); // Keep track of the minimum distance
    }

    cout << out << endl;
}