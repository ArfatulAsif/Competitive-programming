
===================================== Dijkstra ===========================
https://ideone.com/FLsyXI
==========================================================================
//Intermediary
//Young kid on the block
//AIAsif try's "Continuing the journey"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int N = 1e5+10;
vector<pair<int,int>>graph[N];
const int inf = 1e18;
bool vis[N];
int dist[N];


void dijkstra(int ss)
{
        dist[ss] = 0;
        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> >pq;
        pq.push({0,ss});

        while(!pq.empty())
        {

                int father = pq.top().second;

                 pq.pop();


                //This line is very important for time saving
                if(vis[father])
                {

                        continue;
                }

                vis[father] = true;


                for(auto child : graph[father])
                {
                        int v = child.first;
                        int vw = child.second;
                        if(vis[v])
                        {
                                continue;
                        }
                        if(dist[v]>dist[father]+vw)
                        {
                                dist[v] = dist[father]+vw;
                                pq.push({dist[v] , v});
                        }
                }
        }


}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;

        for(int i=0;i<m;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
        }
        for(int i=0;i<N;i++)
        {
                dist[i] = inf;
        }

        dijkstra(1);

        for(int i=1;i<=n;i++)
        {
                cout<<dist[i]<<" ";
        }
        cout<<endl;

        return 0;




}
