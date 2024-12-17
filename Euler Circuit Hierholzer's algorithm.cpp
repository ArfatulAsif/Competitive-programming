// Hierholzer's Algorithm. Sort of like DFS on EDGES
 
const int N = 2e5+10;
vector<pair<int,int>>graph[N]; // {vertex no, edge no}
vector<int>path;
bool vis_edge[N]; // edge visited
int degree[N];
 
 
void dfs_edge(int s)
{
	while(!graph[s].empty())
	{
		auto [child, idx] = graph[s].back();
		graph[s].pop_back();
 
		if(vis_edge[idx])
		{
			continue;
		}
 
		vis_edge[idx] = true;
 
		dfs_edge(child);
	}
 
	path.push_back(s);
}
 
      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
 
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=m;i++)
        {
        	int a,b;
        	cin>>a>>b;
        	graph[a].push_back({b,i});
        	graph[b].push_back({a,i});
        	degree[a]++;
        	degree[b]++;
        }
 
        for(int i=1;i<=n;i++)
        {
        	if(degree[i]%2==1)
        	{
        		cout<<"IMPOSSIBLE"<<endl;
        		return 0;
        	}
        }
 
        dfs_edge(1);
 
        if(path.size() != m+1)
        {
        	cout<<"IMPOSSIBLE";  // disconnected graph
        }
        else 
        {
        	for(auto x : path)
        	{
        		cout<<x<<" ";
        	}
        }
 
        cout<<endl;
 
 
 
}

// CSES : Mail Delivery
