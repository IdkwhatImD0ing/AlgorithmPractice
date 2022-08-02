#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("lostcow.in", "r", stdin);
    freopen("lostcow.out", "w", stdout);
    int x, y;
    cin >> x >> y;

    int nextPos = 1;
    int distanceTraveled = 0;

    while (true)
    {
        if (nextPos > 0 && y - x > 0 && y - x <= nextPos) // If cow position is in the positive direction and below next position
        {
            distanceTraveled += abs(x - y);
            break;
        }
        else if (nextPos < 0 && y - x < 0 && y - x >= nextPos) // If cow position is in the negative direction and above next position
        {
            distanceTraveled += abs(x - y);
            break;
        }

        else // If disntance is not far enough to reach cow
        {
            distanceTraveled += abs(2 * abs(nextPos));
        }

        nextPos *= -2;
    }
    cout << distanceTraveled << endl;
    return 1;
}