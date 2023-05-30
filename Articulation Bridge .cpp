
const int N = 1e5;
vector<int>graph[N];
bool vis[N];
vector<int>parent(N,-1);
int dis[N];
int low[N];
set<pair<int,int>>bridge;

void dfs(int s , int time = 0)
{
        time++;
        vis[s] = true;
        dis[s] = low[s] = time;
        for(auto child : graph[s])
        {
                if(parent[s]==child)
                {
                        continue;
                }
                if(vis[child])
                {
                        low[s] = min(low[s],dis[child]); // backedge checking
                        continue;
                }
                parent[child] = s;
                dfs(child, time);
                low[s] = min(low[s],low[child]);

                if(dis[s]<low[child]) // make sure s is not the root
                {
                        bridge.insert({s,child});
                }
        }

        return;
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
        for(int i=0;i<n;i++)
        {
                if(!vis[i])
                {
                        dfs(i);
                }
        }
        for(auto x : bridge)
        {
                cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<endl;

        return 0;






}
