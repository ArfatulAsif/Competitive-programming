

//Using binary lifting find sum of value from vertex U to V in a tree

//NO updates



const int N = 1e5+10;
vector<pair<int,int>>graph[N];
bool vis[N];
const int L = log2(N);
int up[N][L+1];
int sum[N];
int din[N];
int dout[N];
int tin;
int tout;

void dfs(int s,int par)
{
        vis[s] = true;
        up[s][0] = par;

        din[s] = tin++;
        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[ up[s][i-1] ][i-1];
        }

        for(auto child : graph[s])
        {
                if(vis[child.first])
                {
                        continue;
                }

                sum[child.first] = sum[s] + child.second; // here storing prefix sum

                dfs(child.first,s);
        }
        dout[s] = tout++;
}

bool is_ancestor(int u,int v)
{
        if(din[u]<=din[v] && dout[u]>=dout[v])
        {
                return true;
        }
        return false;
}

int lca(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return u;
        }
        if(is_ancestor(v,u))
        {
                return v;
        }
        for(int i=L;i>=0;i--)
        {
                if(!is_ancestor(up[u][i] , v))
                {
                        u = up[u][i];
                }
        }
        return up[u][0];
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }

        dfs(1,1);

        int q;
        cin>>q;
        while(q--)
        {
                int u,v;
                cin>>u>>v;

                int l = lca(u,v);

                if(l==u || l==v)
                {
                        cout<<abs(sum[u]-sum[v])<<endl;
                }
                else
                {
                        cout<<abs(sum[l]-sum[u])+abs(sum[v]-sum[l])<<endl;
                }
        }


        return 0;




}



/*
13
1 2 2
1 4 7
2 3 8
3 8 9
3 7 7
7 9 6
7 10 5
4 6 10
4 5 9
5 11 11
11 12 3
11 13 12
5
9 11
11 6
2 3
9 10
8 5


o/p

50
30
8
11
35

*/
