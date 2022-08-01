#include <iostream>
#include <stack>
#include <set>
#include <vector>
using namespace std;

int main()
{
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    vector<int> enter(26, -1);
    vector<int> leave(26, -1);
    string n;
    cin >> n;
    int count = 0;
    for (int i = 0; i < 52; ++i)
    {
        if (enter[n[i] - 'A'] == -1)
            enter[n[i] - 'A'] = i;
        else
            leave[n[i] - 'A'] = i;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (enter[i] < enter[j] && enter[j] < leave[i] && leave[i] < leave[j])
                count++;
        }
    }
    cout << count;
}