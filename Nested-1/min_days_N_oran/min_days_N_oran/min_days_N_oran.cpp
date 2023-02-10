// min_days_N_oran.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
using namespace std;
class Solution {
private:
    map<int, int>lkp;
public:
    int minDays(int n) {
        int min = 1000;
        if (n == 1 || n == 0)
            return n;
        /*  (N/a)/b = (N/b)/a = (N/ab). where the division results are rounded down integer values, so some O(log_3(n)*log_2(n)) values explored at the most*/
        int n_2 = n / 2;
        int n_3 = n / 3;
        map<int, int>::iterator itr;
        
        itr = lkp.find(n_2);
        int v1 = 1 + n % 2 + ((itr == lkp.end()) ? minDays(n_2) : (itr->second));

        itr = lkp.find(n_3);
        int v2 = 1 + n % 3 + ((itr == lkp.end()) ? minDays(n_3) : (itr->second));

        min = (min > v1) ? v1 : min;
        min = (min > v2) ? v2 : min;
        lkp[n] = min;
        return min;
    }
};

int main()
{
    int n = 10;
    Solution sol;
    int ret = sol.minDays(n);
    cout << "Number of days: " << ret << endl;
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
