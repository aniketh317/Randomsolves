// distrib_integers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<int>sw;//sum of each subset of quantities
    bool recfunc(map<int, int>& M, vector<int>& ind)
    {
        /*
        M-- lookup table for weight to count at this stage
        ind -- vector of indices
        Run-time is of order n*Bell-number(n)(log(m)), n is quantity size
        */
        map<int, int>::iterator itr;
        int isiz = ind.size();
        bool ret = false;
        if (isiz == 0)
            ret = true;
        else if (ind.size() == 1)
        {
            itr = M.lower_bound(sw[1 << ind[0]]);

            if (itr == M.end() || itr->second == 0)
                ret = false;
            else
                ret = true;
        }
        else
        {
            int f = ind[0];
            for (int i = 0; i < (1 << (isiz - 1)) && !ret; i++)
            {
                vector<int>ind2;
                int sub = (1 << f);
                int index = 1;
                int j = i;
                while (j > 0)
                {
                    if (j % 2 == 1)
                        sub |= (1 << ind[index]);
                    j >>= 1;
                    index++;
                }
                int k = ((1 << isiz) - 1) ^ ((i << 1) | 1);
                index = 0;
                while (k > 0)
                {
                    if (k % 2 == 1)
                        ind2.push_back(ind[index]);
                    k >>= 1;
                    index++;
                }
                itr = M.lower_bound(sw[sub]);
                if (itr != M.end() && itr->second > 0)
                {
                    int key = itr->first;
                    int val = itr->second;
                    if (val == 1)
                        M.erase(itr);
                    else
                        itr->second--;
                    ret = recfunc(M, ind2);
                    M[key] = val;
                }
            }
        }
        return ret;
    }
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int siz = nums.size();
        int qsiz = quantity.size();
        
        /*Total quantity of each subset*/
        sw.clear();
        sw.resize(1 << qsiz, 0);
        for (int i = 1; i < (1 << qsiz); i++)
        {
            int k = i & (-i);
            int ind = 0;
            int j = k;
            k >>= 1;
            while (k > 0)
            {
                ind++;
                k >>= 1;
            }
            sw[i] = sw[i ^ j] + quantity[ind];
        }

        sort(nums.begin(), nums.end());
        int i = 0;
        map<int, int>lkp;
        map<int, int>::iterator itr;
        for (; i < siz;)
        {
            int j = i;
            while (i < siz && nums[i] == nums[j])
                i++;
            itr = lkp.find(i - j);
            if (itr == lkp.end())
                lkp[i - j] = 1;
            else
                itr->second++;

        }
        vector<int>ind;
        for (int i = 0; i < qsiz; i++)
            ind.push_back(i);
        return recfunc(lkp, ind);
    }
};

int main()
{
    vector<int>nums{ 1,1,2,2 };
    vector<int>quantity{ 2,2 };
    Solution sol;
    bool ret = sol.canDistribute(nums, quantity);
    cout << "Whether Can distribute : " << ret << endl;
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
