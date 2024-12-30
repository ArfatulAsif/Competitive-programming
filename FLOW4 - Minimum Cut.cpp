// Dinic + Additional BFS to Find Minimum Cut edges

const int N = 1000;

struct edge
{
	int v;                  // to
	int rev;                // Reverse edge index in graph[v]
	int residual_capacity;  // Residual capacity of the edge
	int edge_id;            // Edge ID (optional, if needed)
};

vector<edge> graph[N];
int level[N];
int done[N]; //  done[u] array is to keep track of which edges have already been tried for a given node during a DFS call. This ensures that we don't revisit the same edges unnecessarily and speeds up the process.


// This is for directed, for undirected make sure to include edges in both direction  addEdge(u,v,c) and addEdge(v,u,c).
void addEdge(int u, int v, int capacity, int id = -1)
{
	graph[u].push_back({v, (int)graph[v].size(), capacity, id});
	graph[v].push_back({u, (int)graph[u].size()-1, 0, -id});
}


// BFS to build Level Graph
bool bfs(int source, int sink)
{
	fill(level, level+N, -1);
	level[source] = 0;
	queue<int>q;
	q.push(source);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for(auto &[v, rev, residual_capacity, id]: graph[u])
		{
			if(level[v] != -1 || residual_capacity == 0)
			{
				continue;
			}

			level[v] = level[u] + 1;
			q.push(v);
		}
	}

	return level[sink] != -1;  // sink is reachable = true
}


// DFS to send flow along augmenting paths
int dfs(int u, int sink, int flow)
{
	if(u == sink)
	{
		return flow;
	}

	for(; done[u] < graph[u].size(); done[u]++)
	{
		auto &[v, rev, residual_capacity, id] = graph[u][done[u]];

		if(level[v] == level[u]+1 && residual_capacity > 0) // only traversing trough level graph
		{
			int pathFlow = min(flow, residual_capacity);
			int pushedFlow = dfs(v, sink, pathFlow);

			if(pushedFlow > 0)
			{
				residual_capacity -= pushedFlow;
				graph[v][rev].residual_capacity += pushedFlow;

				return pushedFlow;
			}
		}
	}

	return 0;
}


int Dinic(int source, int sink)
{
	int max_flow = 0;

	while(bfs(source, sink)) // build the level graph
	{
		fill(done, done+N, 0);

		while(true)  // traverse on the same level graph multiple time, which is efficiant than Edmonds-Karp. As we are blocking multiple edges(residual_capacity = 0) using the same level graph.
		{
			int flow = dfs(source, sink, inf);

			if(flow == 0)
			{
				break;
			}

			max_flow += flow;
		}

	}

	return max_flow;
}



// For minimum cut, edges on minimum cut will have residual capacity = 0.
// So if we run a BFS from source and reach vertices through edges that still have residual capacity > 0. We will eventually stop after finding residual capacity = 0 edges.
// Now visited ones are Vs and unvisited once are Vt in a minimum cut X = (Vs, Vt), where Vs includes source and Vt includes sink.


// Finds all reachable nodes from the source in the residual graph after dinic is called
void FindReachable_BFS(int source, vector<bool> &visited)
{
	queue<int>q;
	q.push(source);
	visited[source] = true;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for(auto &[v, rev, residual_capacity, id]: graph[u])
		{
			if(visited[v] == true || residual_capacity == 0)
			{
				continue;
			}

			visited[v] = true;
			q.push(v);
		}
	}
}

vector<pair<int,int>> FindMinCut(int source, int sink)
{
	vector<bool> visited(N, false);

	FindReachable_BFS(source, visited);

	vector<pair<int,int>> Edges;

	for(int u=1; u < N; u++)
	{
		if(visited[u])
		{
			for(auto &[v, rev, residual_capacity, id]: graph[u])
			{
				if(visited[v] == false && residual_capacity == 0)
				{
					Edges.push_back({u,v});
				}
			}
		}
	}

	return Edges;
}


      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;

        map<pair<int,int>, bool> mp;

        for(int i=0;i<m;i++)
        {
        	int u,v;
        	cin>>u>>v;

        	mp[{u,v}] = true;

        	addEdge(u,v,1);
        	addEdge(v,u,1);  // the problem is for undirected
        }

        cout<<Dinic(1,n)<<endl;

        vector<pair<int,int>> Cut_edges = FindMinCut(1, n); 

        
        set<pair<int,int>>ans; // Since this is a undirected flow network, we need to remove all the duplicates , and only consider edges like input

        for(auto x : Cut_edges)
        {
        	if(mp[{x.first, x.second}])
        	{
        		ans.insert({x.first, x.second});
        	}
        	else 
        	{
        		ans.insert({x.second, x.first});
        	}
        }


        for(auto x : ans)
        {
        	cout<<x.first<<" "<<x.second<<endl;
        }


}

// https://cses.fi/problemset/task/1695/
