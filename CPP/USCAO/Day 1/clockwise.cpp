#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() // Clockwise Fence
{
    int n;
    cin >> n;
    char prev;

    for (int i = 0; i < n; i++)
    {
        int rightTurn = 0, leftTurn = 0;
        string a;
        cin >> a;
        prev = a[0];
        for (int j = 1; j < a.size(); j++) // Bruteforce see what direction
        {
            char next = a[j];
            if (prev == 'N')
            {
                if (next == 'W')
                {
                    leftTurn++;
                }
                else if (next == 'E')
                {
                    rightTurn++;
                }
            }
            else if (prev == 'E')
            {
                if (next == 'N')
                {
                    leftTurn++;
                }
                else if (next == 'S')
                {
                    rightTurn++;
                }
            }
            else if (prev == 'S')
            {
                if (next == 'E')
                {
                    leftTurn++;
                }
                else if (next == 'W')
                {
                    rightTurn++;
                }
            }
            else if (prev == 'W')
            {
                if (next == 'S')
                {
                    leftTurn++;
                }
                else if (next == 'N')
                {
                    rightTurn++;
                }
            }

            prev = next;
        }
        if (rightTurn > leftTurn) // If more right turns circle goes towards right so CW
        {
            cout << "CW" << endl;
        }
        else if (leftTurn > rightTurn) // If more left turns circle goes towards left so CCW
        {
            cout << "CCW" << endl;
        }
        else // If equal number of turns circle is in a straight line, eg should never happen
        {
            cout << "NONE" << endl;
        }
    }
}