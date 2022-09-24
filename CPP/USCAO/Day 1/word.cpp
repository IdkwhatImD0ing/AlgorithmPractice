#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() // Word Processor
{

    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    int currLength = 0;
    for (int i = 0; i < n; i++) // Brute force each word and check length
    {
        string word;
        cin >> word;

        if (currLength + word.size() <= k)
        {
            if (currLength != 0)
            {
                cout << " ";
            }
            cout << word;
            currLength += word.size();
        }
        else
        {
            currLength = word.size();
            cout << endl;
            cout << word;
        }
    }
    cout << endl;
}