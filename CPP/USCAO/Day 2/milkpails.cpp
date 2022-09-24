#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    int one, two, total;
    cin >> one >> two >> total;
    stack<int> test; // Current possibilities
    test.push(0);
    int maximum = 0;
    while (test.size() > 0)
    {
        int temp = test.top();
        test.pop();
        maximum = max(maximum, temp);
        if (maximum == total) // If current possibility is equal to total capacity, we can stop
        {
            cout << maximum << endl;
            return 1;
        }
        if (temp + one <= total) // One possible way
        {
            test.push(temp + one);
        }
        if (temp + two <= total) // Another possible way
        {
            test.push(temp + two);
        }
    }
    cout << maximum << endl;
    return maximum;
}