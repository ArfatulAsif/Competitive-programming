
/* Hungarian Algorithm:
   - Complexity: O(V^3), optimized for both minimum and maximum cost maximum matching.
   - Minimum Cost Maximum Matching: Uses original costs. [ Also set, c[i][j] = inf]
   - Maximum Cost Maximum Matching: Negates the costs and returns the negated result. [ add_edge(u, v, -cost) and cout<<(-M.WeightedBipartiteMatching())<<endl] And [c[i][j] = 0]
   - Works for 1-indexed input. Both left and right is 1 based, no need to do v += left_size */

// I didn't understand the algorithm, but I can use it.


const int N = 509;

struct Hungarian 
{
        int c[N][N], fx[N], fy[N], d[N];

        int left_i_connected_to_right[N]; 
        int right_i_connected_to_left[N];

        int arg[N], trace[N];
        queue<int> q;
        int start, finish, n;

        Hungarian() {}

        Hungarian(int n1, int n2): n(max(n1, n2)) 
        {
                for (int i = 1; i <= n; ++i) 
                {
                        fy[i] = left_i_connected_to_right[i] = right_i_connected_to_left[i] = 0;
                        
                        for (int j = 1; j <= n; ++j) 
                        {
                                c[i][j] = 0; // Set to 0 for maximum cost matching
                        }
                }
        }

        void add_edge(int u, int v, int cost) 
        {
                c[u][v] = min(c[u][v], cost);
        }

        inline int getC(int u, int v) 
        {
                return c[u][v] - fx[u] - fy[v];
        }

        void initBFS() 
        {
                while (!q.empty()) q.pop();
                q.push(start);
                
                for (int i = 0; i <= n; ++i) trace[i] = 0;
                
                for (int v = 1; v <= n; ++v) 
                {
                        d[v] = getC(start, v);
                        arg[v] = start;
                }
                finish = 0;
        }

        void findAugPath() 
        {
                while (!q.empty()) 
                {
                        int u = q.front();
                        q.pop();
                        for (int v = 1; v <= n; ++v) 
                        {
                                if (!trace[v])
                                {
                                        int w = getC(u, v);
                                        if (!w) 
                                        {
                                                trace[v] = u;
                                                if (!right_i_connected_to_left[v]) 
                                                {
                                                        finish = v;
                                                        return;
                                                }
                                                q.push(right_i_connected_to_left[v]);
                                        }
                                        if (d[v] > w) 
                                        {
                                                d[v] = w;
                                                arg[v] = u;
                                        }
                                }
                        }
                }
        }

        void subX_addY() 
        {
                int delta = inf;
                for (int v = 1; v <= n; ++v) 
                {
                        if (!trace[v] && d[v] < delta) 
                        {
                                delta = d[v];
                        }
                }

                fx[start] += delta;

                for (int v = 1; v <= n; ++v) 
                {
                        if (trace[v]) 
                        {
                                int u = right_i_connected_to_left[v];
                                fy[v] -= delta;
                                fx[u] += delta;
                        } 
                        else 
                        {
                                d[v] -= delta;
                        }
                }
                for (int v = 1; v <= n; ++v) 
                {
                        if (!trace[v] && !d[v]) 
                        {
                                trace[v] = arg[v];
                                if (!right_i_connected_to_left[v]) 
                                {
                                        finish = v;
                                        return;
                                }
                                q.push(right_i_connected_to_left[v]);
                        }
                }
        }

        void Enlarge() 
        {
                do {
                        int u = trace[finish];
                        int next = left_i_connected_to_right[u];
                        left_i_connected_to_right[u] = finish;
                        right_i_connected_to_left[finish] = u;
                        finish = next;
                } while (finish);
        }

        int WeightedBipartiteMatching() 
        {
                for (int u = 1; u <= n; ++u) 
                {
                        fx[u] = c[u][1];
                        for (int v = 1; v <= n; ++v) 
                        {
                                fx[u] = min(fx[u], c[u][v]);
                        }
                }
                for (int v = 1; v <= n; ++v) 
                {
                        fy[v] = c[1][v] - fx[1];

                        for (int u = 1; u <= n; ++u) 
                        {
                                fy[v] = min(fy[v], c[u][v] - fx[u]);
                        }
                }
                for (int u = 1; u <= n; ++u) 
                {
                        start = u;
                        initBFS();
                        while (!finish) 
                        {
                                findAugPath();
                                if (!finish) subX_addY();
                        }
                        Enlarge();
                }
                int ans = 0;
                for (int i = 1; i <= n; ++i) 
                {
                        if (c[i][left_i_connected_to_right[i]] != inf) ans += c[i][left_i_connected_to_right[i]];
                        else left_i_connected_to_right[i] = 0;
                }
                return ans;
        }


        vector<pair<int,int>>  FindBipartiteMatching(int left_size, int right_size)
        {
                vector<pair<int,int>>matching;
                
                for(int i=1;i<=left_size;i++)
                {
                        if(left_i_connected_to_right[i]!=0)
                        {
                                matching.push_back({i,left_i_connected_to_right[i]});
                        }
                }

                // Or we can use below part, either one is fine.
                // for(int i=1;i<=right_size;i++)
                // {
                //      if(right_i_connected_to_left[i] != 0) 
                //      {
                //              matching.push_back({right_i_connected_to_left[i], i});
                //      }
                // }

                return matching;
        }
};




int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int t;
        cin>>t;
        for(int tt=1;tt<=t;tt++)
        {
                int n;
                cin>>n;
                
                int left_size, right_size;

                left_size = right_size = n;

                Hungarian M(left_size,right_size);

                vector<int>v1,v2;
                for(int i=0;i<n;i++)
                {
                        int a;
                        cin>>a;
                        v1.push_back(a);
                }

                for(int i=0;i<n;i++)
                {
                        int a;
                        cin>>a;
                        v2.push_back(a);
                }

                for(int i=0;i<n;i++)
                {
                        for(int j=0;j<n;j++)
                        {
                                if(v1[i]>v2[j])
                                {
                                        M.add_edge(i+1,j+1, -2); // -cost, so that it becomes maximum cost maximum bipartite matching . For minimum cost, dont negate
                                }
                                if(v1[i] == v2[j])
                                {
                                        M.add_edge(i+1,j+1,-1);
                                }
                        }
                }


                cout<<"Case "<<tt<<": "<<-M.WeightedBipartiteMatching()<<endl;  // maximum cost bipartite matching
        }

}

// https://lightoj.com/problem/karate-competition
