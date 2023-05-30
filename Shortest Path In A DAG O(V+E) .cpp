
======================SHORTEST  PATH IN A DAG ========== O(V+E)


const int inf = 1e18;
const int N = 1e5+100;
vector<pair<int,int>>graph[N];
int in[N];
vector<int>dis(N,inf);
int parent[N];

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
                        in[child.first]--;
                        if(in[child.first]==0)
                        {
                                q.push(child.first);
                        }
                }
        }

        dis[1] = 0;

        for(auto s : topo)
        {
                if(dis[s]!=inf)
                {
                        for(auto child: graph[s])
                        {
                                if(dis[child.first]>dis[s]+child.second)
                                {
                                        parent[child.first] = s;
                                        dis[child.first] = dis[s]+child.second;
                                }
                        }
                }
        }



        if(dis[n]==inf)
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


        cout<<"dis[n] " <<dis[n]<<endl;

        cout<<ans.size()<<endl;

        for(auto x : ans)
        {
                cout<<x<<" ";
        }
        cout<<endl;


}


/*
5 5
1 2 2
2 5 2
1 3 2
3 4 2
4 5 2
*/
