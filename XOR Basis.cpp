https://codeforces.com/gym/102625/problem/J

//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

class XorBasis
{
public:
        vector<int>basis;
        int N = 0;
        int temp = 0;

        void add(int x)
        {
                N++;
                temp |= x;

                for(auto &it : basis)
                {
                        x = min(x,x^it);
                }
                if(x==0)
                {
                        return;
                }
                for(auto &it : basis)
                {
                        if((it^x)<it)
                        {
                                it ^= x;
                        }
                }
                basis.push_back(x);
                sort(basis.begin() , basis.end());
        }

        int size()
        {
                return basis.size();
        }

        void clear()
        {
                basis.clear();
                N = 0;
                temp = 0;
        }

        bool possible(int x)
        {
                for(auto &it : basis)
                {
                        x = min(x, x^it);
                }
                return x==0;
        }

        int maxXor(int x=0)
        {
                for(auto &it : basis)
                {
                        x = max(x, x^it);
                }
                return x;
        }

        int minXor(int x = 0)
        {
                for(auto &it : basis)
                {
                        x = min(x, x^it);
                }
                return x;
        }

        int cntXor(int x)
        {
                if(possible(x)==false)
                {
                        return 0LL;
                }
                return (1LL<<(N-size()));
        }

        int sumOfAll()
        {
                int ans = temp*(1LL<<(N-1));
                return ans;
        }

        int kth(int k)
        {
                int sz = size();

                if(k> (1LL<<sz))
                {
                        return -1;
                }
                k--;
                int ans = 0;
                for(int i=0;i<sz;i++)
                {
                        if(k>>i & 1)
                        {
                                ans ^= basis[i];
                        }

                }
                return ans;
        }


};      

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        XorBasis xb;

        int q;
        cin>>q;

        while(q--)
        {
                int a , n;
                cin>>a>>n;

                if(a==1)
                {
                        xb.add(n);
                }
                else 
                {
                        cout<<xb.kth(n)<<endl;
                }
        }

        return 0;


}
