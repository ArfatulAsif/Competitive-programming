
const int N = 1e5;
vector<int>graph[N];
bool vis[N];
vector<int>parent(N,-1);
int dis[N];
int low[N];
set<int>AP;

void dfs(int s , int time = 0)
{
        time++;
        vis[s] = true;
        dis[s] = low[s] = time;
        int childno = 0;
        for(auto child : graph[s])
        {
                if(parent[s]==child)
                {
                        continue;
                }
                if(vis[child])
                {
                        low[s] = min(low[s],dis[child]);
                        continue;
                }
                childno++;
                parent[child] = s;
                dfs(child, time);
                low[s] = min(low[s],low[child]);

                if(parent[s]!=-1 && dis[s]<=low[child]) // make sure s is not the root
                {
                        AP.insert(s);
                }
        }
        if(s==0 && childno>1) // handling the root case
        {
                AP.insert(s);
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
        dfs(0);
        for(auto x : AP)
        {
                cout<<x<<" ";
        }
        cout<<endl;

        return 0;






}
