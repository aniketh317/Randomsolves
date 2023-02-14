// count_spl_int.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countSpecialNumbers(int n) {
        int dig = 0;
        int k = n;
        vector<int>digits;//Digits in the number
        while (k > 0)
        {
            digits.push_back(k % 10);
            k = k / 10;
            dig++;
        }
        reverse(digits.begin(), digits.end());
        vector<vector<int>>nPr(11, vector<int>(11, 1));//nPr[i][j] = iPj 
        for (int i = 2; i <= 10; i++)
        {
            nPr[i][i] = nPr[i - 1][i - 1] * i;
            for (int j = i - 1; j >= 0; j--)
                nPr[i][j] = nPr[i][j + 1] / (i - j);
        }
        int count = 0;
        for (int i = 1; i < dig; i++)
            count += (nPr[10][i] - nPr[9][i - 1]);

        set<int>fill;//Numbers filled up
        for (int i = 0; i < dig; i++)
        {
            int v = digits[i];//The digit in ith(0-indexed) position starting from left
            for (int j = 0; j < v; j++)
            {
                if ((i == 0 && j == 0) || (fill.find(j) != fill.end()))
                    continue;
                if (10 - i - 1 > 0)
                    count += nPr[10 - i - 1][dig - i - 1];
            }
            if (fill.find(v) != fill.end())
                break;

            fill.insert(v);
            if (i == dig - 1)
                count++;
        }
        return count;
    }
};

int main()
{
    Solution sol;
    int n = 135;
    int ret = sol.countSpecialNumbers(n);
    cout << "Number of special numbers : " << ret << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
