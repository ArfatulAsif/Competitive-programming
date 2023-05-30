=========================== LONGEST PATH IN DAG ===============
================================================================
IT is a NP HARD For normall undirected graph
================================================================

// LONGEST PATH in a undirected graph or NON DAG graph is a NP-Hard problem
// however Longest Path in a DAG is O(V+E) problem using topo sort
//using normall dijkstra in a LONgest path in a graph problem wont work , cause it is a NP HARD PROBLEM

// Modified dijkstra is a OK on DAG

// best is using topo Sort + O(V+E) approach


// LONGEST PATH IN A DAG
// Using topo sort  O(V+E) formula


const int inf = 1e18;
const int N = 1e5+100;
vector<int>graph[N];
int in[N];
vector<int>dis(N,-inf);
int parent[N];

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
                in[y]++;
        }
        queue<int>q;

        for(int i=1;i<=n;i++)
        {
                if(in[i]==0)
                {
                        q.push(i);
                }
        }
        vector<int>topo;
        while(!q.empty())
        {
                int father = q.front();
                topo.push_back(father);
                q.pop();


                for(auto child: graph[father])
                {
                        in[child]--;
                        if(in[child]==0)
                        {
                                q.push(child);
                        }
                }
        }

        dis[1] = 0;

        for(auto s : topo)
        {
                if(dis[s]!=-inf)
                {
                        for(auto child: graph[s])
                        {
                                if(dis[child]<dis[s]+1)
                                {
                                        parent[child] = s;
                                        dis[child] = dis[s]+1;
                                }
                        }
                }
        }



        if(dis[n]==-inf)
        {
                cout<<"IMPOSSIBLE"<<endl;
                return 0;
        }



        int v = n;

        vector<int>ans;

        while(v!=0)
        {
                ans.push_back(v);
                v = parent[v];
        }
        reverse(ans.begin(),ans.end());

        cout<<ans.size()<<endl;

        for(auto x : ans)
        {
                cout<<x<<" ";
        }
        cout<<endl;


}
