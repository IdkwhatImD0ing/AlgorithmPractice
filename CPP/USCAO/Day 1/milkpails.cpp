#include <cstdio>
#include <algorithm>
using namespace std;

void pour(int &c1, int &m1, int &c2, int &m2)
{
    int amt = min(m1, c2 - m2); // See which contains the smallest amount of milk, container 1 or empty space in container 2
    m1 -= amt;
    m2 += amt;
}

int main()
{
    freopen("mixmilk.in", "r", stdin);
    freopen("mixmilk.out", "w", stdout);
    int c1, c2, c3;
    int m1, m2, m3;
    scanf("%d %d", &c1, &m1); // 3 Input
    scanf("%d %d", &c2, &m2);
    scanf("%d %d", &c3, &m3);

    for (int i = 0; i < 33; i++) // 99 Pours
    {
        pour(c1, m1, c2, m2);
        pour(c2, m2, c3, m3);
        pour(c3, m3, c1, m1);
    }
    pour(c1, m1, c2, m2); // Last pour

    printf("%d\n%d\n%d\n", m1, m2, m3);
}