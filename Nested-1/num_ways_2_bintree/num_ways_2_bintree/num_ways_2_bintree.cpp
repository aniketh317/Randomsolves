// num_ways_2_bintree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
typedef long long ll;
#define M 1000000007
using namespace std;

class Solution {
private:
    void ncr_calc(vector<vector<ll>>&nCr, int n)
    {
        nCr.resize(n + 1, vector<ll>(n + 1, 1));//nCr[i][j] = iCj
        vector<ll>inv(n + 1, 1);//stores inv[i] = (i! mod M)^-1 under the field.
        vector<ll>fact(n + 1);//fact[i] = i!
        fact[0] = 1;
        for (int i = 1; i <= n; i++)
            fact[i] = (i * fact[i - 1]) % M;

        for (int i = 1; i <= n; i++)
        {
            int k = M - 2;
            ll j = fact[i];
            ll res = 1;
            while (k > 0)
            {
                if (k % 2 == 1)
                    res = (res * j) % M;
                j = (j * j) % M;
                k >>= 1;
            }
            inv[i] = res;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
                nCr[i][j] = (((fact[i] * inv[i - j]) % M) * inv[j]) % M;
        }
    }

    ll rec(vector<vector<ll>>&nCr,vector<int>& num)
    {
        if (num.size() == 0 || num.size() == 1)
            return 1;
        int root = num[0];
        vector<int>left;
        vector<int>right;
        for (int i = 1; i < num.size(); i++)
        {
            if (num[i] < root)
                left.push_back(num[i]);
            else
                right.push_back(num[i]);
        }
        int l = left.size();
        int r = right.size();
        ll res = (((rec(nCr, left) * rec(nCr, right)) % M) * nCr[l + r][l]) % M;
        return res;
    }
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        vector<vector<ll>>nCr;
        ncr_calc(nCr,n);
        return rec(nCr, nums) - 1;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 3,4,5,1,2 };
    int ret = sol.numOfWays(nums);
    cout << "Number of permutations that result in same BST : " << ret << endl;
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
