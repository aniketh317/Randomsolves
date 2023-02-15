// substring_with_largest_var.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int largestVariance(string &s) {
        int siz = s.size();
        int M = -2;
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (i != j)
                {
                    vector<int>ci_j(siz, 0);//i will be logged as 1, j will be logged as -1
                    for (int n = 0; n < siz; n++)
                    {
                        if (int(s[n] - 'a') == i)
                            ci_j[n] = 1;
                        else if (int(s[n] - 'a') == j)
                            ci_j[n] = -1;
                    }
                    bool f = false;//whther a subarray with all 1s and no -1 found
                    bool f_1 = false;//whether a subarray with 1s and atleast one -1 found
                    
                    int maxf = 0;//maximum subarray sum with all 1s ending at current n
                    int maxf_1 = 0;//maximum subarray sum with 1s and atleast one -1 ending at current n
                    int max = 0;//maximum sub array sum found so far, with atleast one -1
                    for (int n = 0; n < siz; n++)
                    {
                        if (ci_j[n] == 1)
                        {
                            if (f_1)
                            {
                                maxf_1 += 1;
                                max = (max < maxf_1) ? maxf_1 : max;
                            }
                            maxf++;
                            f = true;
                        }

                        else if (ci_j[n] == -1)
                        {
                            if (f)
                                max = (max < maxf - 1) ? maxf - 1 : max;
                            maxf_1 = ((maxf_1 - 1) > -1) ? (maxf_1 - 1) : -1;
                            if (f)
                                maxf_1 = (maxf - 1 > maxf_1) ? maxf - 1 : maxf_1;
                            maxf = 0;
                            f_1 = true;
                            f = false;
                        }
                    }
                    M = (max > M) ? max : M;
                }
            }
        }
        return M;
    }
};

int main()
{
    Solution sol;
    string s = "aababbb";
    int ret = sol.largestVariance(s);
    cout << "Substring with Largest Variance : " << ret << endl;
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
