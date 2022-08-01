#include <iostream>
using namespace std;
int main()
{
    int a = 0, max = 0, c = 0;
    cin >> a;
    int b[a][3] = {0};
    for (int i = 0; i < a; i++)
    {
        cin >> b[i][0] >> b[i][1] >> b[i][2];
    }
    for (int i = 0; i <= 1000; i++)
    {
        c = 0;
        for (int j = 0; j < a; j++)
        {
            if (b[j][0] <= i && b[j][1] >= i)
            {
                c += b[j][2];
            }
        }
        if (c > max)
        {
            max = c;
        }
    }
    cout << max;
}