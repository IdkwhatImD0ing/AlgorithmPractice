#include <map>
#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int location;
    char direction;
    int n;
    cin >> n;
    int minimum = INT_MAX;
    map<int, char> m;
    for (size_t i = 0; i < n; i++)
    {
        cin >> direction;
        cin >> location;
        m[location] = direction;
    }
    for (auto cow : m) // Assume Bessie at location of cow
    {
        int liars = 0;
        for (auto other : m) // Check all other cows if they are liars.
        {
            if (other.first < cow.first && other.second == 'L')
            {
                liars++;
            }
            else if (other.first > cow.first && other.second == 'G')
            {
                liars++;
            }
        }
        minimum = min(minimum, liars);
    }

    cout << minimum << endl;
}