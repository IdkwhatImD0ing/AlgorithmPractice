#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    char answer[9];
    char guess[9];
    map<char, int> correct;
    map<char, int> guessNumner;
    int readIn;
    for (int i = 0; i < 9; i++)
    {
        cin >> answer[i];
    }
    for (int i = 0; i < 9; i++)
    {
        cin >> guess[i];
    }
    cout << guess << endl;
    cout << "Split" << endl;
    cout << answer << endl;
}
