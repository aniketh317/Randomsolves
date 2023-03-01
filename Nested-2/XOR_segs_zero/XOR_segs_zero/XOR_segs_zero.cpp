// XOR_segs_zero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define N 1000000007
using namespace std;
class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int siz = nums.size();

        vector<vector<int>>ele(k);//ele[z] will have the elements at pos i st. i%k == z
        for (int i = 0; i < siz; i++)
            ele[i % k].push_back(nums[i]);
        for (vector<int>& vec : ele)
            sort(vec.begin(), vec.end());
        vector<vector<int>>dp(k, vector<int>(1024));//Since all numbers are within 1<<10, their xor is also within 1<<10
        /*dp[z][r] denotes the min number of changes to get xor = r over positions with (i%k) <= z*/
        for (int z = 0; z < 1024; z++)
        {
            int n = ele[0].size();
            int j = 0;
            int min = n;//May be all have to be changed to get this xor sum over pos i st i%k == 0
            for (; j < n; j++)
            {
                int k = j;
                while (j + 1 < n && ele[0][j + 1] == ele[0][k])
                    j++;
                if (ele[0][k] == z)
                    min = n - (j - k + 1);
            }
            dp[0][z] = min;
        }
        for (int r = 1; r < k; r++)
        {
            int m = N;
            for (int z = 0; z < 1024; z++)
                m = m < dp[r - 1][z] ? m : dp[r - 1][z];

            for (int z = 0; z < 1024; z++)
            {
                int n = ele[r].size(); //n <= (siz/k)+1
                int j = 0;
                int min = m + ele[r].size();//case where all of the values in ele[r] have to be changed
                for (; j < n; j++)
                {
                    int k = j;
                    while (j + 1 < n && ele[r][j + 1] == ele[r][k])
                        j++;
                    int numc = n - (j - k + 1);//number of elemnts with pos i , st. i%k == r to be changed to ele[r][k]
                    int t = z ^ ele[r][k];//xor sum rest
                    min = min < dp[r - 1][t] + numc ? min : dp[r - 1][t] + numc;
                }
                dp[r][z] = min;
            }
        }
        return dp[k - 1][0];
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 26,19,19,28,13,14,6,25,28,19,0,15,25,11 };
    int k = 3;
    int ret = sol.minChanges(nums, k);
    cout << "Min Number of changes for xor of all k segs to be zero : " << ret << endl;
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
