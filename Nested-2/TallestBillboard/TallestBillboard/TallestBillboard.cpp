// TallestBillboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int siz = rods.size();
        vector<vector<int>>dp(20, vector<int>(10001, -1));//dp[i][diff] denotes max sum of s1, s2 when s1-s2 = diff, s2-s1 = diff,diff+5000 upto i
        dp[0][rods[0]] = rods[0];
        dp[0][5000 + rods[0]] = rods[0];
        dp[0][0] = 0;
        for (int i = 1; i < siz; i++)
        {
            int m1 = dp[i - 1][0];
            int m2 = (dp[i - 1][rods[i]] != -1) ? dp[i - 1][rods[i]] + rods[i] : -1;
            int m3 = (dp[i - 1][5000 + rods[i]] != -1) ? dp[i - 1][5000 + rods[i]] + rods[i] : -1;
            int m = (m1 > m2) ? m1 : m2;
            m = (m > m3) ? m : m3;
            dp[i][0] = m;
            for (int j = 1; j <= 5000; j++)
            {
                int m1 = dp[i - 1][j];
                int m2 = -1;
                int m3 = -1;
                if (j >= rods[i])
                    m2 = (dp[i - 1][j - rods[i]] != -1) ? dp[i - 1][j - rods[i]] + rods[i] : -1;
                else
                    m2 = (dp[i - 1][-j + rods[i] + 5000] != -1) ? dp[i - 1][-j + rods[i]+5000] + rods[i] : -1;
                if (j + rods[i] <= 5000)
                    m3 = (dp[i - 1][j + rods[i]] != -1) ? dp[i - 1][j + rods[i]] + rods[i] : -1;
                int m = (m1 > m2) ? m1 : m2;
                m = (m > m3) ? m : m3;
                dp[i][j] = m;

                m1 = dp[i - 1][5000 + j];
                m2 = -1;
                m3 = -1;
                if (rods[i] + j <= 5000)
                    m2 = (dp[i - 1][5000 + j + rods[i]] != -1) ? dp[i - 1][5000 + j + rods[i]] + rods[i] : -1;
                if (rods[i] - j >= 0)
                    m3 = (dp[i - 1][rods[i] - j] != -1) ? dp[i - 1][rods[i] - j] + rods[i] : -1;
                else
                    m3 = (dp[i - 1][-rods[i] + j + 5000] != -1) ? dp[i - 1][-rods[i] + j + 5000] + rods[i] : -1;

                m = (m1 > m2) ? m1 : m2;
                m = (m > m3) ? m : m3;
                dp[i][5000 + j] = m;
            }
        }
        return (dp[siz - 1][0] != -1) ? dp[siz - 1][0] >> 1 : 0;
    }
};
int main()
{
    Solution sol;
    vector<int>rods{ 1,2,3,6 };
    int ret = sol.tallestBillboard(rods);
    std::cout << "Tallest board : " << ret << endl;
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
