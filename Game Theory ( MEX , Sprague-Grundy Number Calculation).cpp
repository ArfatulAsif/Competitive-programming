https://lightoj.com/problem/partitioning-game


// Add some code//Intermediary
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

const int N = 1e4+100;
int dp[N];
int calculateMex(unordered_set<int> &s)
{
        int mex = 0;
        while(s.find(mex)!=s.end())
        {
                mex++;
        }
        return mex;
}

int grundy(int n) //depending on the problem this function can be very different ....... Look at the light oj various Sprague-Grundy Number problems 
{
        if(n<3)
        {
                dp[n] = 0;
                return 0;
        }
        if(dp[n]!=-1)
        {
                return dp[n];
        }

        int left = n/2;

        if(n%2==0)
        {
                left--;
        }

        unordered_set<int>s;

        for(int i=1;i<=left;i++)
        {
                s.insert(grundy(i)^grundy(n-i));
        }

        dp[n] = calculateMex(s);

        return dp[n];
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int t;
        cin>>t;

        memset(dp,-1,sizeof(dp));

        for(int tt=1;tt<=t;tt++)
        {
                int n;
                cin>>n;

                int Xor = 0;

                for(int i=0;i<n;i++)
                {
                        int a;
                        cin>>a;

                        Xor ^= grundy(a);
                }

                cout<<"Case "<<tt<<": "<<((Xor)?"Alice":"Bob")<<endl;
        }

        return 0;


}
