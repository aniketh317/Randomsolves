// Great_partitions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#define M 1000000007

using namespace std;
typedef long long ll;

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        ll sum = 0;
        int siz = nums.size();
        int val = (k << 1);
        for (int i = 0; i < siz; i++)
        {
            sum += nums[i];
            if (sum >= val)
                break;
        }
        if (sum < val)
            return 0;
        
        vector<ll>dpu(k, 0);
        if (nums[0] < k)
            dpu[nums[0]] = 1;
        dpu[0] = 1;//Empty subset
        for (int i = 1; i < siz; i++)
        {
            vector<ll>temp = dpu;//Copy constructor
            for (int z = 0; z < k; z++)
            {
                if (z - nums[i] >= 0)
                    temp[z] = (temp[z] + dpu[z - nums[i]]) % M;
            }
            dpu = temp;
        }
        ll nump = 1;//To hold Number of partitions mod M
        while (siz > 0)
        {
            nump <<= 1;
            nump = nump % M;
            siz--;
        }
        ll numi = 0;//Number of undesired paritiotions
        for (int z = 0; z < k; z++)
            numi = (numi + dpu[z]) % M;
        numi <<= 1;
        numi = numi % M;
        ll ret = nump - numi;
        if (ret < 0)
            ret += M;
        
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int>nums{ 6,6 };
    int k = 2;
    int ret = sol.countPartitions(nums, k);
    std::cout << "Number of Great Partitions: " << ret << endl;
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
