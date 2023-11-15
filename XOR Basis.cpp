// Intermediary
// Young kid on the block
// AIAsif try's Continuing the journey
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>


Basis: A set B of vectors in a vector space V is called a basis (pl.: bases) if every element of V may be written in a unique way as a finite linear combination of elements of B. The coefficients of this linear combination are referred to as components or coordinates of the vector with respect to B. The elements of a basis are called basis vectors.

class Basis
{
        vector<int> a;

public:
        void insert(int x)
        {
                for (auto &i : a)
                
                        x = min(x, x ^ i); //for row echelon form get the smallest bit which is not equals to 0 means this bit is controlled by this
                if (!x)
                        return;
                for (auto &i : a)
                        if ((i ^ x) < i)
                                i ^= x;
                a.push_back(x);
                sort(a.begin(), a.end());
        }
        bool can(int x)
        {
                for (auto &i : a)
                        x = min(x, x ^ i);
                return !x;
        }
        int maxxor(int x = 0)
        {
                for (auto &i : a)
                        x = max(x, x ^ i);
                return x;
        }
        int minxor(int x = 0) // always returning zero . If you are not considering empty set then take care of it...
        {
                for (auto &i : a)
                        x = min(x, x ^ i);
                return x;
        }
        int kth(int k) //1st is 0 . which means empty set is also coounted .. if you don't want to count empty set then take care of the condition whether zero can be made using existing 
        { // 1st is 0
                int sz = (int)a.size();
                if (k > (1LL << sz))
                        return -1;
                k--;
                int ans = 0;
                for (int i = 0; i < sz; i++)
                        if (k >> i & 1)
                                ans ^= a[i];
                return ans;
        }

} t;

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                t.insert(a);
        }


        cout<<t.maxxor()<<endl;


        return 0;
}
