// Numbers_with_rep_digits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        vector<int>dig;
        int k = n;
        while (n > 0)
        {
            dig.push_back(n % 10);
            n = n / 10;
        }
        int N = dig.size();
        if (N == 1)
            return 0;
        vector<vector<int>>nPr(11, vector<int>(11, 1));//nPr[i][j] = iPj
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= N; j++)
                nPr[i][j] = nPr[i][j - 1] * (i - j + 1);
        }
        int num = 0;//Number of numbers with no repeated digits
        for (int i = 1; i < N; i++)
            num += (nPr[10][i] - nPr[9][i - 1]);
        set<int>S;
        set<int>::iterator itr;
        bool flag = true;
        for (int i = N - 1; i >= 0; i--)
        {
            int d = dig[i];
            int jst = (i == N - 1) ? 1 : 0;
            for (int j = jst; j < d; j++)
            {
                itr = S.find(j);
                if (itr == S.end())
                    num += nPr[10 - N + i][i];
            }
            itr = S.find(d);
            if (itr != S.end())
            {
                flag = false;
                break;
            }
            S.insert(d);
        }
        if (flag)
            num++;
        return k - num;
    }
};

int main()
{
    Solution sol;
    int n = 11;
    int ret = sol.numDupDigitsAtMostN(n);
    std::cout << "Number of numbers with atleast one repeated digit : " << ret << endl;
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
