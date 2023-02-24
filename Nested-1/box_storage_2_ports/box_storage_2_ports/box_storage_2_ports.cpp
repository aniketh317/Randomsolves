// box_storage_2_ports.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#define M 1000000007
#define VI vector<int>

using namespace std;
typedef long long ll;

struct seg_tree{
    struct seg_node {
        int L;//Left end-point of range
        int R;//Right end-point of range
        int left = -1;//index of the left child(-1 means no child)
        int right = -1;// index of the right child(-1 means no child)
        int lub = 0;//lazy update value to be trickled down at the appr. moment
        int rval = 0;//range-value(minimum for the range)
        seg_node(int l, int r) :L(l), R(r) {}
    };
    int N;
    vector<seg_node>T;//T[ind].rval to indicate the minimum of all the elements covered by the interval, with lub's below this
    //this node trickled down to the array elements(invariant after range-update/range-query)
    seg_tree(vector<int>& A):N(A.size())
    {
        int siz = 0;
        queue<int>Q;
        T.emplace_back(0, N - 1);
        Q.push(0);
        while (!Q.empty())
        {
            int c = Q.front();
            Q.pop();
            int l = T[c].L;
            int r = T[c].R;

            if (l == r)
                T[c].rval = A[l];

            else
            {
                T.emplace_back(l, (l + r) / 2);//Half-interval 1
                siz++;
                T[c].left = siz;
                Q.push(siz);

                T.emplace_back(((l + r) / 2) + 1, r);//Half-interval 2
                siz++;
                T[c].right = siz;
                Q.push(siz);
            }
        }
        for (int i = siz; i >= 0; i--)
        {
            if (T[i].L != T[i].R)
                T[i].rval = (T[T[i].left].rval < T[T[i].right].rval) ? (T[T[i].left].rval) : (T[T[i].right].rval);
        }
    }

    int updnode(int ind, int l, int r, int val)
    {
        /*Recursive call for lazy updates */
        /*[l,r] will always intersect with T[ind]'s range*/
        if (T[ind].L == l && T[ind].R == r)
        {
            T[ind].lub += val;
            return T[ind].rval + T[ind].lub;
        }
        
        int left = T[ind].left;
        int right = T[ind].right;
        int lr;
        int rr;
        if (T[left].L <= l && l <= T[left].R)
        {
            int r2 = (T[left].R < r) ? T[left].R : r;
            lr = updnode(left, l, r2, val);
        }
        else
            lr = T[left].rval + T[left].lub;
        if (T[right].L <= r && r <= T[right].R)
        {
            int l2 = (T[right].L > l) ? T[right].L : l;
            rr = updnode(right, l2, r, val);
        }
        else
            rr = T[right].rval + T[right].lub;
        T[ind].rval = (lr < rr) ? lr : rr;
        return T[ind].rval + T[ind].lub;
    }

    int rquery(int ind, int l, int r)
    {
        /*[l,r] will always intersect with T[ind]'s range*/
        if (T[ind].L == l && T[ind].R == r)
            return T[ind].rval + T[ind].lub;

        int left = T[ind].left;
        int right = T[ind].right;
        int lr = M;
        int rr = M;
        if (T[left].L <= l && l <= T[left].R)
        {
            int r2 = (T[left].R < r) ? T[left].R : r;
            lr = rquery(left, l, r2);
        }
        if (T[right].L <= r && r <= T[right].R)
        {
            int l2 = (T[right].L > l) ? T[right].L : l;
            rr = rquery(right, l2, r);
        }
        
        int ret = (lr < rr) ? lr : rr;
        return ret + T[ind].lub;
    }
};



class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        /*0 for port , 1 for weight*/
        int siz = boxes.size();
        vector<int>A(siz, 0);
        A[0] = 2;
        vector<int>dp(A);//dp[i] will contain the total no. trips for best transport for boxes[0..i]
        int back = 0;//j \in [back(incl..) to i] can form the last batch with i(resulting from weight and number constraints)  
        int w = boxes[0][1];//total weight of the batch from back to previous i
        seg_tree T(A);//Invariant property - For every i, on loop end, A[back..i] has (dp[j]+(trips for j..i)) for j = back to i 
        for (int i = 1; i < siz; i++)
        {
            while (back < i && !(w + boxes[i][1] <= maxWeight && (i - back) < maxBoxes))
            {
                w -= boxes[back][1];
                back++;
            }
            w += boxes[i][1];
            if (back < i)
            {
                bool same = (boxes[i][0] == boxes[i - 1][0]);
                T.updnode(0, back, i - 1, same ? 0 : 1);
                int m1 = T.rquery(0, back, i - 1);
                T.updnode(0, i, i, dp[i - 1] + 2);
                dp[i] = (m1 < dp[i - 1] + 2) ? m1 : dp[i - 1] + 2;
            }
            else
            {
                T.updnode(0, i, i, dp[i - 1] + 2);
                dp[i] = dp[i - 1] + 2;
            }
                
        }
        return dp[siz - 1];
    }
};

int main()
{
    Solution sol;
    vector<vector<int>>boxes{ VI{1,4},VI{1,2}, VI{2,1}, VI{2,1}, VI{3,2} , VI{3,4} };
    int portsCount = 3;
    int maxBoxes = 6;
    int maxWeight = 7;
    int ret = sol.boxDelivering(boxes, portsCount, maxBoxes, maxWeight);
    cout << "Minimum number of trips : " << ret << endl;
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
