// inc_quad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++)
            nums[i]--;

        vector<vector<int>>ls(nums.size(), vector<int>(nums.size(), 0));
        for (int j = 0; j < nums.size(); j++)
        {
            for (int i = 0; i < j; i++)
            {
                if (nums[i] < nums[j])
                    ls[j][nums[i]] = 1;
            }

            for (int n = 1; n < nums.size(); n++)
                ls[j][n] += ls[j][n - 1];
        }
        vector<vector<int>>ls2(nums.size(), vector<int>(nums.size(), 0));
        for (int k = 0; k < nums.size(); k++)
        {
            for (int j = 0; j < k; j++)
            {
                if (nums[j] > nums[k])
                    ls2[k][nums[j]] = ls[j][nums[k]];
            }
            for (int n = 1; n < nums.size(); n++)
                ls2[k][n] += ls2[k][n - 1];
        }

        ll ret = 0;
        
        for (int k = 0; k < nums.size(); k++)
        {
            for (int l = k + 1; l < nums.size(); l++)
            {
                if (nums[k] < nums[l])
                    ret += ls2[k][nums[l]];
            }
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 1,2,3,4};
    int ret = sol.countQuadruplets(nums);
    cout << "Number of desired quadruples: " << ret << endl;
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
