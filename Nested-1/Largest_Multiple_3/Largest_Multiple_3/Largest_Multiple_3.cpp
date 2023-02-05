// Largest_Multiple_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        vector<vector<int>>dp(3, vector<int>(10, 0));//dp[i][j] indicates no. of j's the largest string upto now, which leaves reminder i
        vector<int>count(3, 0);
        int rem = digits[0] % 3;
        count[rem] = 1;
        dp[rem][digits[0]] = 1;
        int siz = digits.size();
        for (int i = 1; i < siz; i++)
        {
            vector<vector<int>>temp = dp;
            vector<int>tcount = count;
            int rem = digits[i] % 3;
            for (int j = 0; j < 3; j++)
            {
                if (count[j] > 0 || j == 0)
                {
                    bool igt = false;//Is the string obtained from longest for j combined with this digit is larger 
                    int rem2 = (rem + j) % 3;
                    if (tcount[rem2] < count[j] + 1)
                        igt = true;
                    else if (tcount[rem2] == count[j] + 1)
                    {
                        for (int k = 9; k >= 0; k--)
                        {
                            int val = dp[j][k] + ((digits[i] == k) ? 1 : 0);
                            if (val > temp[rem2][k])
                                igt = true;
                            if (val != temp[rem2][k])
                                break;
                        }
                    }
                    if (igt)
                    {
                        for (int k = 9; k >= 0; k--)
                        {
                            int val = dp[j][k] + ((digits[i] == k) ? 1 : 0);
                            temp[rem2][k] = val;
                        }
                        tcount[rem2] = count[j] + 1;
                    }
                }
            }
            dp = temp;
            count = tcount;
        }
        string ret = "";
        if (count[0] > 0)
        {
            bool flag = false;
            for (int k = 9; k > 0; k--)
            {
                for (int l = 0; l < dp[0][k]; l++)
                {
                    ret += (k + '0');
                    flag = true;
                }
            }
            if (flag)
            {
                for (int l = 0; l < dp[0][0]; l++)
                    ret += (0 + '0');
            }
            else if (dp[0][0] > 0)
                ret += (0 + '0');
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int>digits{ 1,1,1,2 };
    string ret = sol.largestMultipleOfThree(digits);
    cout << "Longest 3 divisible string: " << ret << endl;
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
