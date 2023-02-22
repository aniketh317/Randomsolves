// array_restore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
typedef long long ll;
#define M 1000000007
using namespace std;

class Solution {
public:
    int numberOfArrays(string s, int k) {
        int n = s.size();
        if (k < 10)
        {
            for (int i = 0; i < n; i++)
            {
                int d = s[i] - '0';
                if (d > k)
                    return 0;
            }
            return 1;
        }
        if (int(s[0] - '0') == 0)
            return 0;
        vector<int>dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; i++)
        {
            bool flag = true;
            ll l = 1;
            ll num = s[i] - '0';
            int j = i;
            for (; j > 0 && num <= k; j--)
            {
                if (int(s[j] - '0') != 0)
                    dp[i] = (dp[i] + dp[j - 1]) % M;
                if (l <= 100000000000)
                    l = l * 10;
                else
                {
                    flag = false;
                    break;
                }

                num += (s[j - 1] - '0') * l;
            }
            if (flag && num <= k)
                dp[i] = (dp[i] + 1) % M;
        }
        return dp[n - 1];
    }
};
int main()
{
    Solution sol;
    string s = "1317";
    int k = 2000;
    int ret = sol.numberOfArrays(s, k);
    cout << "Number of ways to restore : " << ret << endl;
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
