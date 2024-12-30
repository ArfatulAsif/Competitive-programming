
// This is similar to maximum flow algorithms.
// In maximum flow algorithms, in each iteration, we used to find an augmenting path using DFS/BFS and then perform flow augmentation through its edges

// But in Minimum cost maximum flow algorithm,
// In each iteration, instead of finding just an augmenting path, we will find minimum cost augmenting path.  [minimum cost augmenting path = cost of sending each unit of flow through this path is minimum among all the remaining augmenting paths]

// So, for MCMF, in each iteration, we will use Dijkstra to find minimum cost augmenting path, then do flow augmentation through it's edges.
// And that's it.




// Adjusting Dijkstra to accomodate negative edges:
// For max flow algorithms we consider edges in reverse to undo flow if needed. In this case, we are gonna have to undo the cost too. That's why for reverse edge, cost is negative "graph[v].push_back({u, (int)graph[u].size()-1, 0, -cost, -id});"
// Also, for some problems cost of edges might be given negative in the input.
// As we know dijkstra algorithm does not works for negative edges, we need to make adjustment to the edge weight's so that they become non-negative. 
// We shall use the same techniques that is used in johnson's algorithm for all pair shortest path in O(V^2 log V + VE)  [https://github.com/ArfatulAsif/Competitive-programming/blob/main/Johnson%E2%80%99s%20algorithm%20for%20All-pairs%20shortest%20paths.cpp]
// Using a bellman-ford to shift edges , new weight = w(u, v) + h[u] - h[v]. in this case u = source
// Here the potential function h[] is used to "normalize" the graph by shifting the edge weights in such a way that all edges have non-negative weights.
// Then perform Repeated Dijkstra
// After each Dijkstra retrieve distance(u,v) = dijkstra(u, v) + h[v] - h[u]. u = source.
// Here distance(source,sink) = minimum cost of sending 1 unit of flow from source to sink
// Then update the potential function h[]. And repeat Dijkstra untill no augmenting path found/target_flow achieved.







// Property of this code:
// Works for both directed, undirected and with negative cost (in the input) too.
// Complexity: O(min(E^2 *V log V, E logV * flow))
// This code does not works if there is a negative cycle in the input.  [that's why It Normally does not work for Maximum Cost maximum Flow, as taking -cost with edges might form negative cycles]




const int N = 1000;

struct MCMF
{

	struct edge
	{
		int v; 			// to
		int rev; 		//Reverse edge index in graph[v]
		int residual_capacity;  // Residual capacity of the edge
		int cost;               // Cost per unit of flow through the edge
		int edge_id;            // Edge ID (optional, if needed)
	};

	vector<edge>graph[N];

	int n;
	int source, sink;

	vector<int> dist;
	vector<int>h; // potential array

	vector<pair<int,int>> parent; //  parent[v] = {u, rev} = {parent node u, parent node u's index in graph[v]}


	MCMF(int _n)
	{
		n = _n+1;
	}

	// This is for directed, for undirected make sure to include edges in both direction  addEdge(u,v) and addEdge(v,u).
	void addEdge(int u, int v, int capacity, int cost, int id = -1)
	{
		graph[u].push_back({v, (int)graph[v].size(), capacity, cost, id});
		graph[v].push_back({u, (int)graph[u].size()-1, 0, -cost, -id});
	}


	bool BellmanFord()
	{
		dist.assign(n, inf);
		dist[source] = 0;
		vector<pair<int,edge>>AllEdges; // {u, edge(v,rev, residual_capacity, cost, id)}

		for(int i=0;i<n;i++)  // vertex,  i < n because we already increased n by 1.
		{
			for(auto &e: graph[i])
			{
				AllEdges.push_back({i, e}); 
			}
		}

		bool flag = true;

		for(int i=0;i<n-1; i++) // number of vertices, for zero based graph, i < n
		{
			flag = false;

			for(auto &e: AllEdges)
			{
				int u = e.first;
				auto &[v, rev, residual_capacity, cost, id] = e.second;

				if(dist[v] > dist[u]+cost && residual_capacity>0)
				{
					dist[v] = dist[u]+cost;
					flag = true;
				}

			}

			if(flag == false)
			{
				break;
			}
		}

		for(auto &e: AllEdges)
		{
			int u = e.first;
			auto &[v, rev, residual_capacity, cost, id] = e.second;

			if(dist[v] > dist[u]+cost && residual_capacity>0)
			{
				dist[v] = dist[u]+cost;

				return false; // neg cycle exists
			}

		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				h[i] = dist[i]; // taking the initial potential function
			}
		}


		return dist[sink] != inf; // reachable
	}

	// Use Dijkstra to find minimum cost augmenting path
	bool Dijkstra()
	{
		parent.assign(n, {-1,-1});
		dist.assign(n, inf);

		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

		dist[source] = 0;

		pq.push({0, source});

		while(!pq.empty())
		{
			int u = pq.top().second;
			int u_cost = pq.top().first;  // cost of 1 unit of flow from source to u
			pq.pop();

			if(u_cost != dist[u])
			{
				continue;
			}

			for(auto &[v, rev, residual_capacity, cost, id]: graph[u])
			{
				int adjusted_weight = cost + h[u] - h[v];  // this is always non_negative, even if h[u] or h[v] is negative.

				if(dist[v] > dist[u]+adjusted_weight && residual_capacity > 0)
				{
					dist[v] = dist[u]+adjusted_weight;
					parent[v] = {u, rev}; // {u, position of u in graph[v]}
					pq.push({dist[v], v});
				}
			}
		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				dist[i] += h[i]-h[source]; // retriving the true distance = dijkstra[u,v] + h[v] - h[u]
			}
		}

		for(int i=0;i<n;i++)
		{
			if(dist[i] < inf)
			{
				h[i] = dist[i]; // setting new potential value, as after using each augmenting path, some edges residual_capacity could becomes 0, and we might not be able to use these
				// that's why we need new potential values
			}
		}

		return dist[sink] != inf; // sink is reachable, which means in this iteration augmenting path is found. Not reachable means no more augmenting path remains.
	}

	// Solve the Min-Cost Max-Flow problem
	pair<int,int> MinimumCostMaximumFlow(int _source, int _sink, int target_flow = inf)
	{
		source = _source;
		sink = _sink;

		int total_flow_sent = 0;
		int total_cost = 0;

		h.assign(n, 0);

		if(!BellmanFord())  // using bellman-Ford for adjusting weight to accomodate negative neg weight edges
		{
			return {inf,inf}; // Either sink is not reachable or negative cycle exists
		}

		while( total_flow_sent < target_flow)
		{
			if(!Dijkstra()) // Use Dijkstra to find shortest augmenting path
			{
				// If no augmenting pathfound
				break;
			}


	                int v = sink;
	                int augmenting_path_flow = inf;
	                int cost_per_unit_of_flow_from_source_to_sink = dist[sink];
	 	         
	                while(v != source)
	                {
	                	int u = parent[v].first;
	                	int rev = parent[v].second;	

	                	int idx_of_v_in_u = graph[v][rev].rev;

	                	int residual_capacity = graph[u][idx_of_v_in_u].residual_capacity;
	                	
	                	augmenting_path_flow = min(augmenting_path_flow, residual_capacity);
	 
	                        v = parent[v].first;
	                        
	                }
	                            
	 	                	 
	 		//adjust the residual capacity 

	                v = sink;	                
	                while(v != source)
	                {
	                	int u = parent[v].first;
	                	int rev = parent[v].second;	

	                	int idx_of_v_in_u = graph[v][rev].rev;

	                	graph[u][idx_of_v_in_u].residual_capacity -= augmenting_path_flow;
	                	graph[v][rev].residual_capacity += augmenting_path_flow;

	                        v = parent[v].first;
	                        
	                }


	                if(total_flow_sent + augmenting_path_flow >= target_flow)
	                {
	                        int take = target_flow - total_flow_sent;
	                        total_cost += (take*cost_per_unit_of_flow_from_source_to_sink);
	                        total_flow_sent = target_flow;
	                        break;
	                }
	                else 
	                {
	                        total_flow_sent += augmenting_path_flow;

	                        total_cost += (augmenting_path_flow*cost_per_unit_of_flow_from_source_to_sink);
	                }

		}


		if(total_flow_sent < target_flow)
		{
			return {inf, inf};
		}


		return {total_flow_sent, total_cost};
	}


};

      

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m,k;
        cin>>n>>m>>k;

        MCMF mcmf(n);

        for(int i=0;i<m;i++)
        {
        	int u,v,c,cost;
        	cin>>u>>v>>c>>cost;

        	mcmf.addEdge(u,v,c,cost);  // if undirect then add mcmf.addEdge(v,u,c,cost) too
        }



        int ans = mcmf.MinimumCostMaximumFlow(1,n,k).second;

        if(ans == inf)
        {
        	cout<<-1<<endl;
        }
        else 
        {
        	cout<<ans<<endl;
        }

}

// https://cses.fi/problemset/task/2121/
