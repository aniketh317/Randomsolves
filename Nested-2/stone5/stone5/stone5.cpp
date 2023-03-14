// stone5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const& a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    int max(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = (ret > bit[r]) ? ret : bit[r];
        return ret;
    }

    void update(int idx, int val) {
        /*Works because there is only one update to idx, which increases the value of the element*/
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = (bit[idx] > val) ? bit[idx] : val;
    }
};
class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int vz = stoneValue.size();
        vector<int>csv(vz, 0);

        vector<FenwickTree>ftf(vz, vz + 1);//Forward Fenwick tree, ftf[i] Max fenwick tree for (dp[i,l]+csv[i+l-1]-csv[i-1]) 
        vector<FenwickTree>ftb(vz, vz + 1);//Backward Fenwick tree, ftb[i] Max fenwick tree for (dp[i-l+1,l]+csv[i]-csv[i-l]) 

        for (int i = 0; i < vz; i++)
        {
            ftf[i].update(1, stoneValue[i]);
            ftb[i].update(1, stoneValue[i]);
        }
        vector<vector<int>>dp(vz, vector<int>(vz + 1, 0));
        csv[0] = stoneValue[0];
        for (int i = 1; i < vz; i++)
            csv[i] = stoneValue[i] + csv[i - 1];
        for (int l = 2; l <= vz; l++)
        {
            for (int i = 0; i <= vz - l; i++)
            {
                int max = 0;
                int s2 = 0;
                if (i > 0)
                    s2 = csv[i - 1];
                int vr = csv[i + l - 1] - s2;//Total Value of the range
                
                /*Get last index j, from i, st. csv[j]-s2 <= (vr/2)*/
                int sval = (vr >> 1) + s2;
                if (csv[i] <= sval)
                {
                    int lo = i;
                    int hi = i + l - 1;
                    while (lo < hi)
                    {
                        int mid = (lo + hi + 1) >> 1;
                        if (csv[mid] <= sval)
                            lo = mid;
                        else
                            hi = mid - 1;
                    }
                    max = ftf[i].max(hi - i + 1);
                }
                
                /*Get first index j, from i st. csv[j]-s2>=((vr+1)/2)*/
                sval = ((vr + 1) >> 1) + s2;
                if (csv[i + l - 1] >= sval)
                {
                    int lo = i;
                    int hi = i + l - 1;
                    while (lo < hi)
                    {
                        int mid = (lo + hi) >> 1;
                        if (csv[mid] < sval)
                            lo = mid + 1;
                        else
                            hi = mid;
                    }
                    int ind = hi + 1;
                    int z = ftb[i + l - 1].max(i + l - ind);
                    max = max > z ? max : z;
                }

                dp[i][l] = max;
                ftf[i].update(l, max + vr);
                ftb[i + l - 1].update(l, max + vr);
            }
        }
        return dp[0][vz];
    }
};

int main()
{
    Solution sol;
    vector<int>stoneValue{ 98,77,24,49,6,12,2,44,51,96 };
    int ret = sol.stoneGameV(stoneValue);
    std::cout << "Max score : " << ret << endl;
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
