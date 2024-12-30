// This is essentailly Ford-Fulkerson Using BFS

// In just Ford-Fulkerson with DFS, the time complexity is O(E * max_flow), because DFS is not guaranteed to find the shortest augmenting path. 
// It could take a very long path through the network, reducing residual flow very slowly. 
// For instance, if DFS always explores the deepest possible path (even if that path is long or inefficient), the number of iterations could become very large.
// That's why the total number of augmenting paths to grow significantly, and is not proportional to O(E). In worse case it is proportional to O(max flow).
// So time complexity becomes, (number of augmenting paths * complexity in each DFS) = O( max flow * (V+E)), how ever normally E is dominant, so O( max_flow * E) = O(E*max_flow) 


// In Ford-Fulkerson with BFS or Edmonds-Karp algorithm, the time complexity is O(V * E^2).
// Because BFS guarantees that we always find a "short" augmenting path with respect to the number of edges, which leads to a more efficient increase in flow.
// So number of augmenting path becomes proportional to O(E).
// So time complexity becomes, (number of augmenting paths * complexity in each BFS) = O( E * (V+E)) = O( EV + E^2), as normally E is dominant, this is considered O(V*E^2)


const int N = 1000;

struct edge
{
	int v; 			// to
	int rev; 		//Reverse edge index in graph[v]
	int residual_capacity;  // Residual capacity of the edge
	int edge_id;            // Edge ID (optional, if needed)
};

vector<edge>graph[N];


// This is for directed, for undirected make sure to include edges in both direction  addEdge(u,v,c) and addEdge(v,u,c).
void addEdge(int u, int v, int capacity, int id = -1)
{
	graph[u].push_back({v, (int)graph[v].size(), capacity, id});
	graph[v].push_back({u, (int)graph[u].size()-1, 0, -id});
}

int bfs(int source, int sink, vector<pair<int,int>> &parent)
{
	for(int i=0;i<N;i++)
	{
		parent[i] = {-1, -1};
	}

	vector<bool>visited(N, false);

	visited[source] = true;
	queue<int>q;
	q.push(source);

	int flow = INT_MAX;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for(auto &[v, rev, residual_capacity, id] : graph[u])
		{
			if(visited[v] || residual_capacity == 0)
			{
				continue;
			}

			flow = min(flow, residual_capacity);

			parent[v] = {u,rev};  // rev contains index of u in graph[v]
			
			visited[v] = true;

			if(v == sink)
			{
				return flow;
			}

			q.push(v);



		}
	}

	return 0; // no augmenting path
}


int Edmonds_Karp(int source, int sink)
{
	int max_flow = 0;

	vector<pair<int,int>>parent(N, {-1,-1});  // parent[v] = {u, rev}, where rev contains index of u in graph[v]

	while(true)
	{
		int flow = bfs(source, sink, parent);

		if(flow == 0)
		{
			break;
		}

		max_flow += flow;

		int v = sink;

		while(v != source)
		{
			int u = parent[v].first;
			int rev = parent[v].second;

			graph[v][rev].residual_capacity += flow;
			graph[u][graph[v][rev].rev].residual_capacity -= flow;

			v = parent[v].first;
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
        	int u,v,w;
        	cin>>u>>v>>w;

        	addEdge(u,v,w);
        }

        cout<<Edmonds_Karp(1,n)<<endl;

}
// https://cses.fi/problemset/task/1694/
