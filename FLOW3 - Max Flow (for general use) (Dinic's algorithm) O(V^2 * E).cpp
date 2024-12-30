// Use this code for finding max flow
// The time complexity is O(V^2 * E). Which is most practicall, as normally number of vertices V are less than edges.

// Using a BFS to build a level graph, then iterate over it multiple times using DFS. and repeat it (one BFS, multiple DFS).
// Level Graphs and Blocking Flows: By focusing only on augmenting paths in the current level graph , Dinic minimizes redundant or unnecessary path exploration. This reduces the total number of augmentations compared to Edmonds-Karp, which may repeatedly explore longer paths.
// Once a blocking flow is found, it saturates (residual capacity = 0) multiple paths simultaneously, reducing future work.
// That's why it is more efficient than Edmonds-Karp.


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

      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
        	int u,v,c;
        	cin>>u>>v>>c;
        	addEdge(u,v,c);
        }

        cout<<Dinic(1,n)<<endl;

}
