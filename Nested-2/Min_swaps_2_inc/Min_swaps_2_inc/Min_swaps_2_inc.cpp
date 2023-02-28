// Min_swaps_2_inc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#define M 1000000007
using namespace std;
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int siz = nums1.size();
        vector<vector<int>>dp(siz, vector<int>(2, M));//dp[i][0] -- min swaps to get increasing without the last one swapped
        //dp[i][1] -- min swaps to get increasing with the last one swapped
        dp[0][0] = 0;
        dp[0][1] = 1;
        for (int i = 1; i < siz; i++)
        {
            int m1 = M;
            int m2 = M;
            if (nums1[i - 1] < nums1[i] && nums2[i - 1] < nums2[i] && dp[i - 1][0] != M)
                m1 = dp[i - 1][0];
            if (nums2[i - 1] < nums1[i] && nums1[i - 1] < nums2[i] && dp[i - 1][1] != M)
                m2 = dp[i - 1][1];
            dp[i][0] = (m1 < m2) ? m1 : m2;
            m1 = M;
            m2 = M;
            if (nums1[i - 1] < nums2[i] && nums2[i - 1] < nums1[i] && dp[i - 1][0] != M)
                m1 = dp[i - 1][0] + 1;
            if (nums2[i - 1] < nums2[i] && nums1[i - 1] < nums1[i] && dp[i - 1][1] != M)
                m2 = dp[i - 1][1] + 1;
            dp[i][1] = (m1 < m2) ? m1 : m2;
        }
        return (dp[siz - 1][0] < dp[siz - 1][1]) ? dp[siz - 1][0] : dp[siz - 1][1];
    }
};

int main()
{
    Solution sol;
    vector<int>nums1{ 1,3,5,4 };
    vector<int>nums2{ 1,2,3,7 };
    int ret = sol.minSwap(nums1, nums2);
    cout << "Min number of swaps : " << ret << endl;
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
