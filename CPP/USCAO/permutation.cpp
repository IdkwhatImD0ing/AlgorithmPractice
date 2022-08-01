#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int myints[] = {3, 3, 3, 4};

    std::sort(myints, myints + 3);

    std::cout << "The 3! possible permutations with 3 elements:\n";
    do
    {
        std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';
    } while (std::next_permutation(myints, myints + 4));

    std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';

    return 0;
}