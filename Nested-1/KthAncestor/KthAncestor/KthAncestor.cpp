// KthAncestor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class TreeAncestor {
private:
    vector<vector<int>>G;//Adjacency graph(edges only to children, so directed in this sense)
    vector<vector<int>>kpar;//For getting kth ancestor kpar[n][k] is 2^k th ancestor of n

    void rec_fill(int n)
    {
        for (int z : G[n])
        {
            kpar[z][0] = n;
            for (int j = 1; j < kpar[z].size(); j++)
            {
                if (kpar[z][j - 1] != -1)
                {
                    int kp = kpar[kpar[z][j - 1]][j - 1];
                    kpar[z][j] = kp;
                    if (kp == -1)
                        break;
                }
                else
                    break;
            }
            rec_fill(z);
        }
    }
public:
    TreeAncestor(int n, vector<int>& parent) {
        G.resize(n);
        for (int i = 1; i < n; i++)
            G[parent[i]].push_back(i);
        kpar.resize(n);
        int lgl = 0;
        int l = 1;
        while (l < n)
        {
            l <<= 1;
            lgl++;
        }
        lgl++;
        for (auto& z : kpar)
            z.resize(lgl, -1);//Setting the default kth ances to -1
        rec_fill(0);
    }

    int getKthAncestor(int node, int k) {
        int cur = node;
        int j = 0;
        while (k > 0)
        {
            if (k % 2 == 1)
                cur = kpar[cur][j];
            j++;
            k >>= 1;
            if (cur == -1)
                break;
        }
        return cur;
    }
};

int main()
{
    vector<int>par{ -1, 0, 0, 1, 1, 2, 2 };
    TreeAncestor sol(7, par);
    int v1 = sol.getKthAncestor(3, 1);
    int v2 = sol.getKthAncestor(5, 2);
    int v3 = sol.getKthAncestor(6, 3);
    std::cout << "v1 : " << v1 << "\nv2 : " << v2 << "\nv3 : " << v3 << endl;
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
