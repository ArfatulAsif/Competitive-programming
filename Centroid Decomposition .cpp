//IN path queries where we have to consider n^2 path , we use centroid decomposition(nlogn) .

================================================================        =======================================


//How many paths length = k   



const int N = 5e4+10;

class CentroidDecomposition
{
private:
        int n,k;
        set<int>graph[N];  // many implementation uses 2d vector and isRemoved array , I however think using set is way simplier

        int cnt[N];

        int subtree[N];

        int mx_depth;

public:


        int ans;



        CentroidDecomposition(int n,int k)
        {
                this->n = n;
                this->k = k;
                ans = 0;

        }

        void addEdge(int u,int v)
        {
                graph[u].insert(v);
                graph[v].insert(u);
        }

        int dfs(int s,int p)
        {
                subtree[s] = 1;
                for(auto child : graph[s])
                {
                        if(child == p )
                        {
                                continue;
                        }
                        subtree[s] += dfs(child,s);
                }
                return subtree[s];
        }

        int centroid(int s,int p,int n)
        {
                for(auto child : graph[s])
                {
                        if(child==p)
                        {
                                continue;
                        }
                        if(subtree[child]>n/2)
                        {
                                return centroid(child,s,n);
                        }
                }
                return s;
        }

        void build(int s,int p)
        {
                int n = dfs(s,p);
                int c = centroid(s,p,n);

                vector<int>temp(graph[c].begin() , graph[c].end());

                do_for_centroid(c);

                for(auto child : temp)
                {
                        graph[child].erase(c);
                        graph[c].erase(child);

                        build(child , c);
                }


        }

        void do_for_centroid(int c)
        {
                mx_depth = 0;

                cnt[0] = 1;

                for(auto child : graph[c])
                {
                        dfs2(child,c,1 , false); // we store ans  in this step :
                        dfs2(child,c,1,true);  // in order to avoid recalculation , we store cnt[] after ans has been store for this path
                }




                for(int i=0;i<=mx_depth;i++) // (logn)
                {
                        cnt[i] = 0;
                }

        }


        void dfs2(int s,int p , int depth , bool storeValue)
        {
                if(k-depth<0)
                {
                        return;
                }

                mx_depth = max(mx_depth , depth);

                if(storeValue==false)
                {
                        ans += cnt[k-depth];
                }
                else if(storeValue)
                {
                        cnt[depth]++;
                }

                for(auto child : graph[s])
                {
                        if(child == p)
                        {
                                continue;
                        }
                        dfs2(child,s,depth+1,storeValue);
                }
        }


};


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,k;
        cin>>n>>k;

        CentroidDecomposition cd(n,k);

        for(int i=0;i<n-1;i++)
        {
                int u,v;
                cin>>u>>v;

                cd.addEdge(u,v);
        }


        cd.build(1,0);


        cout<<cd.ans<<endl;


        return 0;





}


=================================================================  ==========================================
//Closest Red vertex 

const int inf = 1e9;

class CentroidDecomposition
{
private:
        const static int N = 1e5+5;
public:
        set<int>graph[N];

        map<int,int>dis[N];

        int subtree[N];
        int parent[N];
        int ans[N];

        CentroidDecomposition(int n)
        {
                for(int i=0;i<=n;i++)
                {
                        graph[i].clear();
                        subtree[i] = 0;
                        parent[i] = 0;
                        ans[i] = inf;
                }
        }
        void addEdge(int x,int y)
        {
                graph[x].insert(y);
                graph[y].insert(x);
        }
        int dfs(int s,int p)
        {
                subtree[s] = 1;
                for(auto child : graph[s])
                {
                        if(child==p)
                        {
                                continue;
                        }
                        subtree[s]+=dfs(child,s);
                }
                return subtree[s];
        }
        int centroid(int s,int p,int n)
        {
                for(auto child: graph[s])
                {
                        if(child==p)
                        {
                                continue;
                        }
                        if(subtree[child]>n/2)
                        {
                                return centroid(child,s,n);
                        }
                }
                return s;
        }

        void dfs2(int s,int p,int c,int d) // build distances
        {
                dis[c][s] = d;
                for(auto child : graph[s])
                {
                        if(child==p)
                        {
                                continue;
                        }
                        dfs2(child,s,c,d+1);
                }
        }

        void build(int s,int p)
        {
                int n = dfs(s,p);
                int c = centroid(s,p,n);

                if(p==-1)
                {
                        p = c;
                }
                parent[c] = p;

                dfs2(c,p,c,0);

                vector<int>temp(graph[c].begin() , graph[c].end());

                for(auto child : temp)
                {
                        graph[c].erase(child);
                        graph[child].erase(c);
                        build(child,c);
                }
        }

        void modify(int s)
        {
                for(int v = s ; v!=0 ; v = parent[v])
                {
                        ans[v] = min(ans[v] , dis[v][s]);
                }
        }
        int query(int s)
        {
                int mn = inf;
                for(int v=s ; v!=0 ; v = parent[v])
                {
                        mn = min(mn , ans[v]+dis[v][s]);
                }

                return mn;
        }


};

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int n,q;
        cin>>n>>q;


        CentroidDecomposition cd(n);

        for(int i=0;i<n-1;i++)
        {
                int u,v;
                cin>>u>>v;
                cd.addEdge(u,v);
        }

        cd.build(1,0);

        cd.modify(1); // make 1 red

        while(q--)
        {
                int a , v;
                cin>>a>>v;
                if(a==1)
                {
                        cd.modify(v);
                }
                else
                {
                        cout<<cd.query(v)<<endl;
                }
        }




}
