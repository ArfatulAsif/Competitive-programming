

const int N = 1e5+100;
vector<int>graph[N];
bool vis[N];
int din[N];
int dout[N];
int tin = 0;
const int L = log2(N);
int up[N][L+1];

void dfs(int s,int par)
{
        vis[s] = true;
        din[s] = tin++;

        up[s][0] = par;

        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[ up[s][i-1] ][i-1]; // Here is the binary lifting is occuring try for this graph ( 1->2 , 2->3 , 3->4 , 4->5,5->6,6->7,7->8,8->9,9->10) then s = 10 er jonno eta draw kore buja
        }


        for(auto child : graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dfs(child,s);
        }
        dout[s] = tin++;
}

bool is_ancestor(int u,int v) // u is ancestor of v
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
                if(!is_ancestor(up[u][i] ,v))  // ancestor na hole jump dissi                                [up[1][0] = 1 na hole ei part kaj korbe na]
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
        int n,m;
        cin>>n>>m;

        for(int i=0;i<m;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        dfs(1,1); // parent of 1 should be 1 i.e. up[1][0] = 1;

        int q;
        cin>>q;
        while(q--)
        {
                int u,v;
                cin>>u>>v;
                cout<<lca(u,v)<<endl;
        }




}




/*
7 6
1 2
1 3
2 4
2 5
3 6
3 7
5
4 5
5 6
7 2
6 7
6 3


o/p
2
1
1
3
3

*/
