
// Finding all pair shortest path using Repeated dijkstra from each vertex to all other.
// But the thing is dijkstra does not works for negative edges. So,
// Using a bellman-ford edge shifting techniques , new weight = w(u, v) + h[u] - h[v], we transform the graph in a way so that weight becomes non-negative weight.
// Here the potential function h[] is used to "normalize" the graph by shifting the edge weights in such a way that all edges have non-negative weights. 
// Finally we after performing dijkstra from each vertex u, we find distance(u,v) = dijkstra(u, v) + h[v] - h[u].



// Remember it does not works for graph with negative cycle.


const int N = 1e5+10;

vector<pair<int,int>> graph[N], altered_graph[N];

int dist[N];
int vis[N];

void dijkstra(int ss, int V) 
{
        for (int i = 0; i < V; i++) 
        {
                dist[i] = inf;
                vis[i] = false;
        }

        dist[ss] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, ss});

        while (!pq.empty()) 
        {
                int father = pq.top().second;
                pq.pop();

                if (vis[father]) continue;
                vis[father] = true;

                for (auto child : altered_graph[father]) 
                {
                        int v = child.first;
                        int vw = child.second;
                        if (vis[v]) continue;
                        if (dist[v] > dist[father] + vw) 
                        {
                                dist[v] = dist[father] + vw;
                                pq.push({dist[v], v});
                        }
                }
        }
}

vector<int> bellmanFord(int V) 
{
        vector<int> dist(V, inf);
        dist[V - 1] = 0;

        for (int i = 0; i < V - 1; i++) 
        {
                for (int u = 0; u < V; u++) 
                {
                        for (auto edge : graph[u]) 
                        {
                                int v = edge.first;
                                int weight = edge.second;
                                if (dist[u] != inf && dist[u] + weight < dist[v]) 
                                {
                                        dist[v] = dist[u] + weight;
                                }
                        }
                }
        }

        for (int u = 0; u < V; u++) {
                for (auto edge : graph[u]) {
                        int v = edge.first;
                        int weight = edge.second;
                        if (dist[u] != inf && dist[u] + weight < dist[v]) 
                        {
                                cout << "Negative weight cycle detected!" << endl;
                                exit(0);
                        }
                }
        }

        return dist;
}

void johnsonAlgorithm(int V) {
        for (int i = 0; i < V; i++) 
        {
                graph[V].push_back({i, 0});
        }

        vector<int> h = bellmanFord(V + 1); // The potential function h[] is used to "normalize" the graph by shifting the edge weights in such a way that all edges have non-negative weights

        for (int i = 0; i < V; i++) 
        {
                for (auto& edge : graph[i])
                 {
                        int v = edge.first;
                        int weight = edge.second;
                        altered_graph[i].push_back({v, weight + h[i] - h[v]});
                }
        }

        for (int u = 0; u < V; u++) 
        {
                cout << "Shortest Distance from vertex " << u << ":"<<endl;
                dijkstra(u, V);

                

                for (int v = 0; v < V; v++) 
                {
                        cout<<"Vertex: "<<v<<" dist: ";

                        if(dist[v]==inf)
                        {
                                cout<<"INF"<<endl;
                                continue;
                        }
                        cout << dist[v] + h[v] - h[u] << endl;
                }
                cout << endl;
        }
}

int32_t main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        
        vector<vector<int>> input = {
                {0, -5, 2, 3},
                {0, 0, 4, 0},
                {0, 0, 0, 1},
                {0, 0, 0, 0}
        };

        for (int i = 0; i < 4; i++) 
        {
                for (int j = 0; j < 4; j++) 
                {
                        if (input[i][j] != 0) 
                        {
                                graph[i].push_back({j, input[i][j]});
                        }
                }
        }

        johnsonAlgorithm(4);

        return 0;
}
