#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main(int argc, char const *argv[])
{
    queue<int> books;
    unordered_set<int> bookNumbers;
    int n, num;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        books.push(num);
        bookNumbers.insert(num);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        int count = 0;
        if (bookNumbers.count(num) > 0)
        {
            while (true)
            {
                int temp = books.front();
                bookNumbers.erase(temp);
                books.pop();
                count++;
                if (temp == num)
                {
                    break;
                }
            }
        }
        cout << count << " ";
    }
    return 0;
}
