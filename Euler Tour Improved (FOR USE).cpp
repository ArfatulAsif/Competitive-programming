https://codeforces.com/gym/102625/problem/H

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

const int N = 1e5+100;
vector<int>graph[N];
bool vis[N];
int vis_time_vertex[N];
int in[N];
int out[N];
int tim;

void dfs(int s)
{
        vis[s] = true;
        in[s] = ++tim;
        vis_time_vertex[tim] = s; // ET array  [Instead for 2*n , IT runs for O(n) time]
        
        for(auto child : graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dfs(child);
        }
        out[s] = tim;
}


int Tree[4*N];

void update(int node ,int lo ,int hi ,int pos ,int val)
{
        if(lo==hi)
        {
                Tree[node] = val;
                return;
        }

        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                update(node*2 , lo, mid , pos,val);
        }
        else 
        {
                update(node*2+1 , mid+1 , hi , pos ,val);
        }

        Tree[node] = max(Tree[node*2] , Tree[node*2+1]);
}


int query(int node, int lo ,int hi,int i,int j)
{
        if(hi<i || lo>j)
        {
                return -1;
        }
        
        if(lo>=i && hi <= j)
        {
                return Tree[node];
        }

        int mid = (lo+hi)>>1;
        int x = query(node*2 , lo , mid , i , j);
        int y = query(node*2+1 , mid+1 , hi, i, j);

        return max(x,y);
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,q;
        cin>>n>>q;
        vector<int>v;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
        }

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }


        dfs(1);

        for(int i=1;i<=n;i++)
        {
                update(1,1,n,i , v[vis_time_vertex[i]-1]);
        }

        while(q--)
        {
                int tt;
                cin>>tt;
                int node1;
                cin>>node1;
                vector<pair<int,int>>p;

                bool flag = false;

                for(int i=0;i<tt-1;i++)
                {
                        int v;
                        cin>>v;

                        if(in[v]<in[node1] && out[v] >= out[node1])
                        {
                                flag = true;
                        }

                        if(in[v]>in[node1]  && out[v] <= out[node1] )
                        {
                                 p.push_back({in[v] , out[v]});
                        }
                }

                if(flag)
                {
                        cout<<-1<<endl;
                        continue;
                }

                sort(p.begin() , p.end());
                int mx = -1;

                int cur = in[node1];

                for(int i=0;i<p.size();i++)
                {
                        mx = max(mx , query(1,1,n, cur+1 ,p[i].first-1));
                        
                        cur = max(cur,p[i].second);
                }

                mx = max(mx , query(1,1,n,cur+1 , out[node1]));


                cout<<mx<<endl;

                
        }



}
