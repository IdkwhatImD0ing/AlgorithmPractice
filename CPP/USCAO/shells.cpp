#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    string as;
    // freopen("shell.in","r",stdin);
    // freopen("shell.out", "w", stdout);
    int a = 0;
    cin >> a;
    vector<int> res{1, 2, 3};
    int pos[3] = {1, 2, 3};
    int first = 0;
    int second = 0;
    int guess = 0;
    for (int i = 0; i < a; i++)
    {
        cin >> first;
        cin >> second;
        cin >> guess;
        int temp = pos[first];
        pos[first] = pos[second];
        pos[second] = temp;
        res.push_back(pos[guess]);
    }
    int temp;
    cout << (max(max(count(res.begin(), res.end(), 1), count(res.begin(), res.end(), 2)), count(res.begin(), res.end(), 3))) - 1 << endl;
    return 1;
}