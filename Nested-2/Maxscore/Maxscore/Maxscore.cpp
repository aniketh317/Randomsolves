// Maxscore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define M 1000000007
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        vector<ll>dp1(n1 + 1, 0);
        vector<ll>dp2(n2 + 1, 0);

        n1--;
        n2--;

        while (n1 >= 0 && n2 >= 0)
        {
            if (nums1[n1] > nums2[n2])
            {
                dp1[n1] = dp1[n1 + 1] + nums1[n1];
                n1--;
            }
            else if (nums1[n1] < nums2[n2])
            {
                dp2[n2] = dp2[n2 + 1] + nums2[n2];
                n2--;
            }
            else
            {
                ll m = dp1[n1 + 1] > dp2[n2 + 1] ? dp1[n1 + 1] : dp2[n2 + 1];
                dp1[n1] = m + nums1[n1];
                dp2[n2] = m + nums2[n2];
                n1--;
                n2--;
            }
        }
        while (n1 >= 0)
        {
            dp1[n1] = dp1[n1 + 1] + nums1[n1];
            n1--;
        }
        while (n2 >= 0)
        {
            dp2[n2] = dp2[n2 + 1] + nums2[n2];
            n2--;
        }
        ll M1 = dp1[0] % M;
        ll M2 = dp2[0] % M;
        return (dp1[0] > dp2[0]) ? M1 : M2;
    }
};

int main()
{
    Solution sol;
    vector<int>nums1{ 2,4,5,8,10 };
    vector<int>nums2{ 4,6,8,9 };
    int ret = sol.maxSum(nums1, nums2);
    cout << "Max Sum mod M : " << ret << endl;
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
