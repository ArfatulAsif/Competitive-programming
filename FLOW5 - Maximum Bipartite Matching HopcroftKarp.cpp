
    
// It has time complexity of O(E*√V). Which is extremely fast
// Recommended for regular use
// Here is the resource for Hopcroft-Karp:  https://brilliant.org/wiki/hopcroft-karp/
// By the was I did not understand how this algo works, I just use this template directly [21-12-2024]

	
const int N = 3e5 + 9;

struct HopcroftKarp
{
        int left_size, right_size;
        vector<int> left_i_is_connected_to_right;
        vector<int> right_i_is_connected_to_left;
        vector<int> level;
        vector<vector<int>> graph;

        HopcroftKarp(int _n, int _m)
        {
                left_size = _n;
                right_size = _m;
                int p = _n + _m + 1;
                graph.resize(p);
                left_i_is_connected_to_right.resize(p, 0);
                right_i_is_connected_to_left.resize(p, 0);
                level.resize(p, 0);
        }

        void addEdge(int u, int v)
        {
                graph[u].push_back(v + left_size); // right vertex is increased by left_size here..
        }

        bool bfs()
        {
                queue<int> q;

                for (int u = 1; u <= left_size; u++)
                {
                        if (!left_i_is_connected_to_right[u])
                        {
                                level[u] = 0;
                                q.push(u);
                        }
                        else
                        {
                                level[u] = inf;
                        }
                }

                level[0] = inf;

                while (!q.empty())
                {
                        int u = q.front();
                        q.pop();

                        for (auto v : graph[u])
                        {
                                if (level[right_i_is_connected_to_left[v]] == inf)
                                {
                                        level[right_i_is_connected_to_left[v]] = level[u] + 1;
                                        q.push(right_i_is_connected_to_left[v]);
                                }
                        }
                }

                return level[0] != inf;
        }

        bool dfs(int u)
        {
                if (!u)
                {
                        return true;
                }

                for (auto v : graph[u])
                {
                        if (level[right_i_is_connected_to_left[v]] == level[u] + 1 && dfs(right_i_is_connected_to_left[v]))
                        {
                                left_i_is_connected_to_right[u] = v;
                                right_i_is_connected_to_left[v] = u;
                                return true;
                        }
                }

                level[u] = inf;

                return false;
        }

        int MaximumBipartiteMatching()
        {
                int ans = 0;

                while (bfs())
                {
                        for (int u = 1; u <= left_size; u++)
                        {
                                if (!left_i_is_connected_to_right[u] && dfs(u))
                                {
                                        ans++;
                                }
                        }
                }

                return ans;
        }

        vector<pair<int, int>> GetMatchingEdges()
        {
                vector<pair<int, int>> matching;

                for (int u = 1; u <= left_size; u++)
                {
                        if (left_i_is_connected_to_right[u])
                        {
                                matching.push_back({u, left_i_is_connected_to_right[u] - left_size}); // subtract left_size to get original right-side vertex
                        }
                }

                return matching;
        }
};



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int left_size, right_size, edges;

        cin >> left_size >> right_size >> edges;

        HopcroftKarp HK(left_size, right_size);

        for (int i = 0; i < edges; i++)
        {
                int u, v;
                cin >> u >> v;

                HK.addEdge(u, v);
        }

        cout << HK.MaximumBipartiteMatching() << endl;

        vector<pair<int, int>> matching = HK.GetMatchingEdges();

        for (auto x : matching)
        {
                cout << x.first << " " << x.second << endl;
        }

        return 0;
}

//  https://cses.fi/problemset/task/1696/
