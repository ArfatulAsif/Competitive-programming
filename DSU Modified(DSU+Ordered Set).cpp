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

//https://codeforces.com/gym/102625/problem/G


//Modified dsu
//dsu + ordered set
//    [ u -- v  edge]  lets say I want to get the size of [left part of u in the component tree and right part of v in the same component tree] 


const int N = 2e5+100;
vector<int>graph[N];
int in[N];
int out[N];
int tim;

void dfs(int s , int p)
{
        in[s] = tim++;

        for(auto child : graph[s])
        {
                if(child==p)
                {
                        continue;
                }
                dfs(child,s);
        }

        out[s] = tim;
}


int parent[N];
ordered_set sz[N];

void make(int v)
{
        parent[v] = v;
        sz[v].insert(in[v]);
}

int Find(int v)
{
        if(v==parent[v])
        {
                return v;
        }

        return parent[v] = Find(parent[v]);
}

void Union(int a,int b)
{
        a = Find(a);
        b = Find(b);

        if(a!=b)
        {
                if(sz[a].size()<sz[b].size())
                {
                        swap(a,b);
                }

                for(auto x : sz[b])
                {
                        sz[a].insert(x);
                }

                parent[b] = a;
        }
}


pair<int,int> left_right_size(int u,int v)
{
        bool flag = false;
        if(in[u]>in[v]) 
        {
                flag = true;
                swap(u,v);
        } // u age dukbe

        u = Find(u);

        int a = sz[u].order_of_key(out[v]) - sz[u].order_of_key(in[v]);  // This represent same component e v er subtree size . ba right part er size 
        int b = sz[u].size()-a ; // this represent the component size of u or left part 

        if(flag)
        {
                return {b,a}; // b hocche u er diker size and a hocche v er diker size 
        }
        else 
        {
                return {a,b}; // a hocce u er diker size and b hocce v er diker size 
        }

}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        vector<array<int,4>>edges;

        set<int>s;

        for(int i=1;i<n;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                edges.push_back({i,x,y,w});
                graph[x].push_back(y);
                graph[y].push_back(x);

                s.insert(w);
        }

        dfs(1,0);

        sort(edges.begin() , edges.end() , [&](auto a, auto b){return a[3]<b[3]; });

        for(int i=1;i<=n;i++)
        {
                make(i);
        }

        int l = 0;

        int mx = 0;
        
        vector<int>ans(n+1);

        for(auto w : s)
        {
                int r = l;

                while(r+1<edges.size()  && edges[r+1][3] == w)
                {
                        r++;
                }

                for(int i = l; i<= r ; i++)
                {
                        Union(edges[i][1] , edges[i][2]);
                }

                for(int i=l;i<=r;i++)
                {
                        auto take = left_right_size(edges[i][1] , edges[i][2]);

                        int temp = take.first * 2LL * take.second;

                        mx = max(temp,mx);

                        ans[edges[i][0]] = temp;  // edges[i][0] represent id no 
                }

                l = r+1;
        }


        vector<int>res;

        for(int i=1;i<n;i++)
        {
                if(mx == ans[i])
                {
                        res.push_back(i);
                }
        }

        cout<<mx<<" "<<res.size()<<endl;

        for(auto x : res)
        {
                cout<<x<<" ";
        }
        cout<<endl;


        return 0;






}
