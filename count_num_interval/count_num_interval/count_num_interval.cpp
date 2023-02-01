// count_num_interval.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class CountIntervals {
    set<pair<int, int>> st;
    int cnt;
public:
    CountIntervals() {
        cnt = 0;
    }

    void add(int left, int right) {
        auto it = st.upper_bound({ left, INT_MIN });

        if (it != st.begin() && (--it)->second < left) {
            ++it;
        }

        while (it != st.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);

            cnt -= (it->second - it->first + 1);
            it = st.erase(it);
        }

        st.insert({ left, right });
        cnt += (right - left + 1);
    }

    int count() {
        return cnt;
    }
};
int main()
{
    std::cout << "Hello World!\n";
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
