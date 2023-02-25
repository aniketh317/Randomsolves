// sliding_window_max.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int siz = nums.size();
        vector<int>ret;
        deque<pair<int, int>>dq;//(val, index)
        /*pushfront, pushback, popfront, popback are all O(1) amortized operations*/
        dq.push_back(make_pair(nums[0], 0));
        for (int i = 1; i < k; i++)
        {
            while (!dq.empty() && dq.back().first <= nums[i])
                dq.pop_back();
            dq.push_back(make_pair(nums[i], i));
        }
        ret.push_back(dq.front().first);
        for (int i = k; i < siz; i++)
        {
            while (!dq.empty() && dq.back().first <= nums[i])
                dq.pop_back();
            dq.push_back(make_pair(nums[i], i));
            if ((i - dq.front().second) >= k)//Deletion happens only once though
                dq.pop_front();
            ret.push_back(dq.front().first);
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 1,-1 };
    int k = 1;
    vector<int>ret = sol.maxSlidingWindow(nums, k);
    cout << ret[0];
    for (int i = 1; i < ret.size(); i++)
        cout << " , " << ret[i];
    cout << endl;
    return 0;
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