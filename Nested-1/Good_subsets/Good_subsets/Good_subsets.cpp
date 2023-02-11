// Good_subsets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define M 1000000007
using namespace std;

class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        /*10 prime numbers upto 30, without 1*/
        sort(nums.begin(), nums.end());
        vector<int>ncount(31, 0);
        int siz = nums.size();
        for (int i = 0; i < siz; i++)
        {
            int count = 1;
            while ((i + 1) < siz && (nums[i] == nums[i + 1]))
            {
                i++;
                count++;
            }
            ncount[nums[i]] = count;
        }
        vector<int>primes{ 2,3,5,7,11,13,17,19,23,29 };
        int psiz = primes.size();

        map<int, long long>dp;
        vector<int>nums2(31, 0);//Factors stored in bit mask manner(numbers with >1  power of prime factor are not considered)
        vector<bool>isvalid(31, false);
        for (int i = 1; i <= 30; i++)
        {
            bool poss = true;
            int val = i;
            int st = 0;
            for (int j = 0; j < psiz && poss; j++)
            {
                int z = 0;
                while (val % primes[j] == 0)
                {
                    val = val / primes[j];
                    z++;
                }
                if (z > 1)
                    poss = false;
                else if (z == 1)
                    st |= (1 << j);
            }
            nums2[i] = (st);
            isvalid[i] = poss;
        }
        for (int k = 0; k < (1 << psiz); k++)
            dp[k] = 0;

        dp[0] = 1;
        for (int k = 0; k < ncount[1]; k++)
            dp[0] = (dp[0] * 2) % M;
        siz = nums2.size();
        vector<vector<map<int, long long>::iterator>>source(31);// source[i]: Iterator nodes of Bit-mask subsets that can pair up with nums2[i]
        vector<vector<map<int, long long>::iterator>>target(31);//target[i]: Iterator nodes of Bit-mask subsets asresult of nums2[i], and bitmsak of source[i]
        for (int i = 1; i <= 30; i++)
        {
            for (int j = 0; j < (1 << psiz); j++)
            {
                if (!(j & nums2[i]))
                {
                    source[i].push_back(dp.find(j));
                    target[i].push_back(dp.find(nums2[i] | j));
                }
            }
            target[i].push_back(dp.find(nums2[i]));
        }
        for (int i = 2; i <= 30; i++)
        {
            if (isvalid[i])
            {
                int sz = source[i].size();
                for (int j = 0; j < sz; j++)
                    target[i][j]->second = (target[i][j]->second + ((ncount[i] * source[i][j]->second) % M)) % M;

            }
        }

        long long ret = 0;
        for (int j = 1; j < (1 << psiz); j++)
            ret = (ret + dp[j]) % M;

        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 5,10,1,26,24,21,24,23,11,12,27,4,17,16,2,6,1,1,6,8,13,30,24,20,2,19 };
    int ret = sol.numberOfGoodSubsets(nums);
    cout << "Number of Good subsets : " << ret << endl;
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
