// min_incompatibilty.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define M 1000000000
using namespace std;
class Solution {
private:
    vector<int>dp;//dp[i] denotes the minuimum incompatibilty for subset with bit mask == i
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        /*k equal sized partitions required*/
        dp.clear();
        map<int, int>count;
        sort(nums.begin(), nums.end());
        int nsiz = nums.size();
        dp.resize(1 << nsiz, M);
        dp[0] = 0;
        if (nsiz % k != 0)
            return -1;
        int r = nsiz / k;
        for (int n = 0; n < nsiz; n++)
        {
            map<int, int>::iterator itr;
            itr = count.find(nums[n]);
            int val;
            if (itr != count.end())
            {
                itr->second++;
                val = itr->second;
            }
            else
            {
                count[nums[n]] = 1;
                val = 1;
            }
            if (val > k)
                return -1;
        }
        map<int, int>lkp;
        for (int i = 0; i < nsiz; i++)
            lkp[1 << i] = i;
        set<int>rsiz;//all r sized subsets
        vector<pair<int, int>>csub(1 << nsiz, make_pair(0, 0));//<Number of 1s in each subset, incompatibilty>
        for (int i = 1; i < (1 << nsiz); i++)
        {
            int k2 = i & (-i);
            int z1 = lkp[k2];
            int j = i ^ k2;
            csub[i].first = csub[j].first + 1;
            if (j != 0)
            {
                int val = (j & (-j));
                int z2 = lkp[val];
                csub[i].second = csub[j].second + (nums[z2] - nums[z1]);
            }
            if (csub[i].first == r)
            {
                int st = i;
                bool flag = true;
                int prev = M;
                while (st != 0 && flag)
                {
                    j = st & (-st);
                    st = st ^ j;
                    int val = nums[lkp[j]];
                    flag = (val != prev);
                    prev = val;
                }
                if(flag)
                    rsiz.insert(i);
            }
        }
        int mic = M;//min incompatibilty
        int mu = (1 << nsiz) - 1;
        if (k == 2)
        {
            for (int z : rsiz)
            {
                int comp = mu ^ z;
                set<int>::iterator itr = rsiz.find(comp);
                if (itr != rsiz.end())
                    mic = (mic < csub[z].second + csub[comp].second) ? mic : csub[z].second + csub[comp].second;
            }
        }
        else
        {
            for (int i = 1; i <= mu; i++)
            {
                if (csub[i].first % r == 0)
                {
                    for (int z : rsiz)
                    {
                        if ((z | i) == i)
                            dp[i] = dp[i] < dp[z ^ i] + csub[z].second ? dp[i] : dp[z ^ i] + csub[z].second;
                    }
                }
            }
            mic = dp[mu];
        }
        return mic;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 10,4,4,2,11,10,8,9,1,2,2,10 };
    int k = 4;
    int ret = sol.minimumIncompatibility(nums, k);
    cout << "Minimum incompatibilty : " << ret << endl;
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
