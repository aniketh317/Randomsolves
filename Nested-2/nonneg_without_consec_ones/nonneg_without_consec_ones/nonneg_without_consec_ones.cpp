// nonneg_without_consec_ones.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int findIntegers(int n) {
        vector<int>bits;
        int m = n;
        int num = 0;
        while (m > 0)
        {
            if (m % 2 == 1)
                bits.push_back(1);
            else
                bits.push_back(0);
            num++;
            m >>= 1;
        }
        bool flag = false;
        int i;
        for (i = num - 2; i >= 0 && !flag; i--)
        {
            if (bits[i + 1] == 1 && bits[i] == 1)
            {
                bits[i] = 0;
                flag = true;
            }
        }
        if (flag)
        {
            for (; i >= 0; i--)
                bits[i] = (bits[i + 1] == 1) ? 0 : 1;
        }
        /*num is the number of bits in n*/
        vector<int>z(num + 1);//z[i] indicates number of numbers without consecutive ones upto (1<<i)-1
        z[0] = 1;
        z[1] = 2;
        for (int i = 2; i <= num; i++)
            z[i] = z[i - 2] + z[i - 1];
        int sum = (bits[0] == 1) ? z[1] : z[0];
        for (int i = num - 1; i > 0; i--)
        {
            if (bits[i] == 1)
                sum += z[i];
        }
        return sum;
    }
};
int main()
{
    Solution sol;
    int n = 6;
    int ret = sol.findIntegers(n);
    cout << "Number of desired integers : " << ret << endl;
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
