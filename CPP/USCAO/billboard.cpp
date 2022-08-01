#include <iostream>

using namespace std;
int main()
{
    // freopen("billboard.in", "r", stdin);
    //  freopen ("billboard.out","w",stdout);
    //  m is mower
    int mx1 = 0;
    int mx2 = 0;
    int my1 = 0;
    int my2 = 0;
    // f is cow feed
    int fx1, fx2, fy1, fy2;
    int a[2000][2000];
    cin >> mx1;
    cin >> my1;
    cin >> mx2;
    cin >> my2;
    cin >> fx1;
    cin >> fy1;
    cin >> fx2;
    cin >> fy2;
    mx1 += 1000;
    my1 += 1000;
    mx2 += 1000;
    my2 += 1000;
    fx1 += 1000;
    fx2 += 1000;
    fx2 += 1000;
    fy2 += 1000;
    for (int x = mx1; x < mx2; x++)
    {
        for (int y = my1; y < my2; y++)
        {
            a[x][y] = 1;
        }
    }
    for (int x = fx1; x < fx2; x++)
    {
        for (int y = fy1; y < fy2; y++)
        {
            a[x][y] = 0;
        }
    }
    int minx, miny, maxx, maxy = 0;
    bool minxfound, minyfound = false;
    for (int x = 0; x < 2000; x++)
    {
        for (int y = 0; y < 2000; y++)
        {
            if (a[x][y] == 1)
            {
                if (minxfound == false)
                {
                    minxfound = true;
                    minx = x;
                }
                else
                {
                    maxx = x;
                }
            }
        }
    }
    for (int x = 0; x < 2000; x++)
    {
        for (int y = 0; y < 2000; y++)
        {
            if (a[x][y] == 1)
            {
                if (minyfound == false)
                {
                    minyfound = true;
                    miny = y;
                }
                else
                {
                    maxy = y;
                }
            }
        }
    }
    int ans = (maxy - miny) * (maxx - minx);
    cout << ans;
}