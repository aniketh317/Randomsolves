// max_score_from_mul.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>>dp;//dp[i][j] -- max product sum for the subproblem, in which nums starts from i and j multipliers have been consumed 
    vector<vector<bool>>isc;//isc[i][j] - true meands dp[i][j] has been computed
    vector<int>num;
    vector<int>mul;
    void topdown(int i, int j)
    {
        /*calculates dp[i][j].. invoked only when not memoized*/
        isc[i][j] = true;
        int msiz = mul.size();
        int nsiz = num.size();
        if (j == msiz)
            dp[i][j] = 0;
        else
        {
            if (i + 1 < nsiz)
            {
                if (!isc[i + 1][j + 1])
                    topdown(i + 1, j + 1);
                dp[i][j] = num[i] * mul[j] + dp[i + 1][j + 1];
                if (!isc[i][j + 1])
                    topdown(i, j + 1);
                int siz = num.size();
                int val = num[siz - 1 - (j - i)] * mul[j] + dp[i][j + 1];//j>=i
                dp[i][j] = (dp[i][j] < val) ? val : dp[i][j];
            }
            else
                dp[i][j] = num[i] * mul[j];
        }
        return;
    }
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        dp.clear();
        isc.clear();
        num = nums;
        mul = multipliers;
        int nsiz = nums.size();
        int msiz = multipliers.size();
        dp.resize(nsiz, vector<int>(msiz + 1, 0));
        isc.resize(nsiz, vector<bool>(msiz + 1, 0));
        topdown(0, 0);
        return dp[0][0];
    }
};

int main()
{
    vector<int>nums{ 1,2,3 };
    vector<int>multipliers{ 3,2,1 };
    Solution sol;
    int ret = sol.maximumScore(nums, multipliers);
    cout << "Maximum product Score : " << ret << endl;
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
