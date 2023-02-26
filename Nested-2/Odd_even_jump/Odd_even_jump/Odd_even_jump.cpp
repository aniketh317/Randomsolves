// Odd_even_jump.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include <vector>
using namespace std;
struct cust1 {
    int val;//dummy values
    int ind;//dummy valus
    cust1(int v=-1, int i=-1):val(v), ind(i){}
    bool operator < (const cust1 &rhs) const
    {
        return (val < rhs.val) || (val == rhs.val && ind < rhs.ind);
    }
    bool operator >=(const cust1& rhs) const
    {
        return !(operator<(rhs));
    }
};

struct cust2 {
    int val;//dummy values
    int ind;//dummy valus
    cust2(int v = -1, int i = -1) :val(v), ind(i) {}
    bool operator < (const cust2& rhs) const
    {
        return (val > rhs.val) || (val == rhs.val && ind < rhs.ind);
    }
    bool operator >=(const cust2& rhs) const
    {
        return !(operator<(rhs));
    }
};


class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int siz = arr.size();
        vector<int>onxt(siz, -1);//next jump from this index in case of odd jump, -1 means no jump
        vector<int>enxt(siz, -1);//next jump from this index in case of even jump, -1 means no jump
        vector<bool>even(siz, false);//whether starting from even jump, end can be reached
        vector<bool>odd(siz, false);//whether startibg from odd jump, end can be reached
        even[siz - 1] = true;
        odd[siz - 1] = true;
        
        set<cust1>S1;
        S1.insert(cust1(arr[siz - 1], siz - 1));
        set<cust2>S2;
        S2.insert(cust2(arr[siz - 1], siz - 1));
        
        for (int i = siz - 1; i >= 0; i--)
        {
            cust1 C1(arr[i], i);
            set<cust1>::iterator itr1 = S1.lower_bound(C1);
            if (itr1 != S1.end() && even[itr1->ind])
                odd[i] = true;
            cust2 C2(arr[i], i);
            set<cust2>::iterator itr2 = S2.lower_bound(C2);
            if (itr2 != S2.end() && odd[itr2->ind])
                even[i] = true;
            S1.insert(C1);
            S2.insert(C2);
        }
        int num = 0;//Number of good indices
        for (int i = 0; i < siz; i++)
            num += (odd[i]) ? 1 : 0;

        return num;
    }
};
int main()
{
    Solution sol;
    vector<int>nums{ 10,13,12,14,15 };
    int ret = sol.oddEvenJumps(nums);
    cout << "Number of good indices : " << ret << endl;
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
