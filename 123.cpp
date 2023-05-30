//Apprentice
//New kid on the block
//AIAsif try's "A new beginning"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
const int N = 2e5+100;
int BIT[N];
int n;

void update(int x,int val)
{
        for(; x<=n ; x+= (x&-x))
        {
                BIT[x]+=val;
        }
        return;
}

int query(int x)
{
        int sum = 0;
        for(;x>0;x-=(x&-x))
        {
                sum+= BIT[x];
        }
        return sum;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int q;
        cin>>n>>q;
        for(int i=1;i<=n;i++) // BIT should be 1 based index
        {
                int a;
                cin>>a;
                update(i,a);
        }

        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int b,c;
                        cin>>b>>c;
                        int val = query(b)-query(b-1);
                        update(b,-val);
                        update(b,c);
                }
                else
                {
                        int l,r;
                        cin>>l>>r;

                        cout<<query(r)-query(l-1)<<endl;
                }
        }

        return 0;






}
