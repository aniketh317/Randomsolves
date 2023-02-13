// closest_subseeq_sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 1000000007
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        /*NP hard*/
        int siz = nums.size();
        int sz1 = siz >> 1;
        int sz2 = siz - sz1;
        int minabs = MAX;
        vector<int>s1((1 << sz1), 0);//sums of all subsets in the first half
        for (int i = 1; i < (1 << sz1); i++)
        {
            int v = i & (-i);
            int lk = 0;
            while ((1 << lk) != v)
                lk++;
            s1[i] = s1[i - v] + nums[lk];
        }
        sort(s1.begin(), s1.end());//sort in increasing order

        vector<int>s2((1 << sz2), 0);//sums of all subsets in the second half
        for (int i = 0; i < (1 << sz2); i++)
        {
            if (i != 0)
            {
                int v = i & (-i);
                int lk = 0;
                while ((1 << lk) != v)
                    lk++;
                s2[i] = s2[i - v] + nums[lk + sz1];
            }
            auto a = lower_bound(s1.begin(), s1.end(), goal - s2[i]);//smallest element greater than or equal to goal-s1[i]
            if (a != s1.end())
                minabs = (minabs > ((*a) + s2[i]) - goal) ? ((*a) + s2[i]) - goal : minabs;
            auto b = lower_bound(s1.rbegin(), s1.rend(), goal-s2[i], greater<int>());////largest element smaller than or equal to goal-s1[i]
            if (b != s1.rend())
                minabs = (minabs > goal - ((*b) + s2[i])) ? goal - ((*b) + s2[i]) : minabs;
        }
        return minabs;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 5,-7,3,5 };
    int goal = 6;
    int ret = sol.minAbsDifference(nums, goal);
    cout << "Cloest Subseqence sum : " << ret << endl;
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
