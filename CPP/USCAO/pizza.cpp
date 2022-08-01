#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    double dx = -15 / 6;
    double dy = -20 / 8;
    double dz = -25 / 10;
    for (int i = 0; i < n; i++)
    {
        unsigned long number = 0;
        cin >> number;
        int x = (number / 10) - 1;
        number -= x * 10;
        int y = (number / 8) - 1;
        number -= y * 8;
        int z = (number / 6) + 1;
        cout << 2.5 * (z * 6 + y * 8 + x * 10) << endl;
    }
}