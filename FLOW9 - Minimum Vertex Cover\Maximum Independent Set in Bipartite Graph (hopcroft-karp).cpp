
// Complexity of this code is O(E*√V).

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

        vector<pair<int,char>> FindMinimumVertexCover()
        {
        	vector<pair<int,char>> min_vertex_cover;
        	vector<bool> visited_left(left_size+1);
        	vector<bool> visited_right(right_size+1);

        	queue<int>q;

        	for(int i=1;i <= left_size; i++)
        	{
        		if(!left_i_is_connected_to_right[i]) // selecting unmatched vertices from left side. [unmatched: those vertices that are not end points of matching edges]
        		{
        			visited_left[i] = true;
        			q.push(i);
        		}
        	}

        	while(!q.empty())
        	{
        		int left = q.front();
        		q.pop();

        		for(auto v : graph[left])
        		{
        			if(v <= left_size) // v is not a right vertex
        			{
        				continue;
        			}

        			int right = v - left_size;

        			// left -------unmatched_edge-------> right. 
        			if(visited_right[right] == false)
        			{
        				visited_right[right] = true;

        				int matched_left = right_i_is_connected_to_left[right+left_size];

        				// matched_left <---------matched_edge----------right.
        				if(matched_left!=0 && visited_left[matched_left] == false)
        				{
        					visited_left[matched_left] = true;
        					q.push(matched_left);
        				}

        			}

        		}
        	}


        	// Taking unmarked vertices from left
        	for(int i=1;i<=left_size;i++)
        	{
        		if(visited_left[i]==false)
        		{
        			min_vertex_cover.push_back({i, 'L'});
        		}
        	}


        	// Taking marked vertices from right
        	for(int i=1;i<=right_size;i++)
        	{
        		if(visited_right[i] == true)
        		{
        			min_vertex_cover.push_back({i,'R'});
        		}
        	}

        	return min_vertex_cover;
        }

        vector<pair<int,char>> FindMaximumIndependentSet()
        {
        	vector<pair<int,char>> max_independent_set;
        	vector<bool> visited_left(left_size+1);
        	vector<bool> visited_right(right_size+1);

        	queue<int>q;

        	for(int i=1;i <= left_size; i++)
        	{
        		if(!left_i_is_connected_to_right[i]) // selecting unmatched vertices from left side. [unmatched: those vertices that are not end points of matching edges]
        		{
        			visited_left[i] = true;
        			q.push(i);
        		}
        	}

        	while(!q.empty())
        	{
        		int left = q.front();
        		q.pop();

        		for(auto v : graph[left])
        		{
        			if(v <= left_size) // v is not a right vertex
        			{
        				continue;
        			}

        			int right = v - left_size;

        			// left -------unmatched_edge-------> right. 
        			if(visited_right[right] == false)
        			{
        				visited_right[right] = true;

        				int matched_left = right_i_is_connected_to_left[right+left_size];

        				// matched_left <---------matched_edge----------right.
        				if(matched_left!=0 && visited_left[matched_left] == false)
        				{
        					visited_left[matched_left] = true;
        					q.push(matched_left);
        				}

        			}

        		}
        	}


        	//Exact opposite of Minimum Vertex Cover

        	// Taking marked vertices from left
        	for(int i=1;i<=left_size;i++)
        	{
        		if(visited_left[i]==true)
        		{
        			max_independent_set.push_back({i, 'L'});
        		}
        	}


        	// Taking unmarked vertices from right
        	for(int i=1;i<=right_size;i++)
        	{
        		if(visited_right[i] == false)
        		{
        			max_independent_set.push_back({i,'R'});
        		}
        	}

        	return max_independent_set;
        }
};


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int left_size, right_size, edges;

        cin>>left_size>>right_size>>edges;


        HopcroftKarp HK(left_size,right_size);

        for(int i=0;i<edges;i++)
        {
        	int u,v;
        	cin>>u>>v;

        	HK.addEdge(u,v);

        }


        HK.MaximumBipartiteMatching(); // we need to call it First.......

        vector<pair<int,char>> min_vertex_cover = HK.FindMinimumVertexCover();

        for(auto x : min_vertex_cover)
        {
        	cout<<x.second<<" "<<x.first<<endl;
        }

}



/*
input:
5 4 9
1 1
2 1
2 2
3 2
4 1
4 3
4 4
5 3
5 4

output:
L 4
L 5
R 1
R 2
*/        
        
// Or solve this problem :https://leetcode.com/problems/maximum-students-taking-exam/description/
