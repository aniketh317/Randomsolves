// Count_Palindromic_Subsequences.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define M 1000000007
typedef long long ll;
using namespace std;
class Solution {
public:
    int countPalindromes(string &s) {
        int siz = s.size();
        vector<vector<int>>num(siz, vector<int>(10, 0));//num[i][k] gives the number of k's in s[0:i]
        num[0][int(s[0] - '0')] = 1;
        for (int i = 1; i < siz; i++)
        {
            for (int j = 0; j < 10; j++)
                num[i][j] = num[i - 1][j];
            num[i][int(s[i] - '0')]++;
        }

        vector<vector<ll>>dpf(siz, vector<ll>(100, 0));//dpf[i][k] gives the number of subsequences whose decimal rep. is k in s[0:i] 
        //j1j2 is the decimal string for which number of matching subsequences found
        for (int j1 = 0; j1 < 10; j1++)
        {
            for (int j2 = 0; j2 < 10; j2++)
            {
                int k = 10 * j1 + j2;
                for (int i = 1; i < siz; i++)
                    dpf[i][k] = (dpf[i - 1][k] + ((int(s[i] - '0') == j2) ? num[i - 1][j1] : 0)) % M;
            }
        }

        vector<vector<ll>>dpr(siz, vector<ll>(100, 0));//dpr[i][k] gives the number of subsequences whose decimal rep. is k in s[i:siz-1]
        //j1j2 is the decimal string for which number of matching subsequences found
        for (int j1 = 0; j1 < 10; j1++)
        {
            for (int j2 = 0; j2 < 10; j2++)
            {
                int k = 10 * j1 + j2;
                for (int i = siz - 2; i >= 0; i--)
                    dpr[i][k] = (dpr[i + 1][k] + ((int(s[i] - '0') == j1) ? (num[siz - 1][j2] - num[i][j2]) : 0)) % M;
            }
        }

        int count = 0;
        for (int i = 2; i < siz - 2; i++)
        {
            for (int j1 = 0; j1 < 10; j1++)
            {
                for (int j2 = 0; j2 < 10; j2++)
                    count = (count + (dpf[i - 1][10 * j1 + j2] * dpr[i + 1][10 * j2 + j1]) % M) % M;
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;
    string s = "0000000";
    int out = sol.countPalindromes(s);
    cout << "Number of desired palindrome subsequences: " << out << endl;
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
