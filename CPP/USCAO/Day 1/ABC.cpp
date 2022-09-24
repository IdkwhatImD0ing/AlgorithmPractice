#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;
typedef unordered_map<int, int> umap;

vector<int> list;
umap myMap;

int main() // Do you know your ABCs
{
    for (int i = 0; i < 7; i++) // Input
    {
        int temp;
        cin >> temp;
        list.push_back(temp);
        myMap[temp]++;
    }

    for (int i = 0; i < list.size(); i++) // Disgusting brute force, try every possible triplet for ABC
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            for (int k = j + 1; k < list.size(); k++)
            {
                umap temp = myMap;
                int A = list[i];
                int B = list[j];
                int C = list[k];
                temp[A]--;
                temp[B]--;
                temp[C]--;
                if (temp[A + B] == 0 || temp[A + C] == 0 || temp[B + C] == 0 || temp[A + B + C] == 0) // If any of the four are missing, it's not correct
                {
                    continue;
                }
                temp[A + B]--;                                                    // Remove A+B
                if (temp[A + C] == 0 || temp[B + C] == 0 || temp[A + B + C] == 0) // If any of the three are missing, it's not correct
                {
                    continue;
                }
                temp[A + C]--;                                // Remove A+C
                if (temp[B + C] == 0 || temp[A + B + C] == 0) // If any of the two are missing, it's not correct
                {
                    continue;
                }
                temp[B + C]--;            // Remove B+C
                if (temp[A + B + C] == 0) // If A+B+C is missing, it's not correct
                {
                    continue;
                }
                int output[3] = {A, B, C}; // Wasted 5 minutes debugging when it turned output supposed to be sorted.
                sort(output, output + 3);
                cout << output[0] << " " << output[1] << " " << output[2] << endl;
                return 1;
            }
        }
    }
}