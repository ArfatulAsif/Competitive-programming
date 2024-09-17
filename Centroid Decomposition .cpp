//IN path queries where we have to consider n^2 path , we use centroid decomposition(nlogn) .

================================================================        =======================================

//How many paths length = k   

const int N = 2e5 + 100;

class CentroidDecomposition {
private:
    int n, k;
    set<int> graph[N];
    int cnt[N];    // cnt[i] = number of i-length path from the centroid/root
    int subtree[N];
    int mx_depth;
    int parent[N];

public:
    long long int ans; // ans = total count of exactly k-length paths

    CentroidDecomposition() {
        this->n = 0;
        this->k = 0;
    }

    void addEdge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }
            if (subtree[child] > n / 2) {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p, int k) {
        this->k = k;
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        vector<int> temp(graph[c].begin(), graph[c].end());

        do_for_centroid(c);

        for (auto child: temp) {
            graph[c].erase(child); // tearing apart the graph
            graph[child].erase(c);
            build(child, c, k);
        }
    }

    void do_for_centroid(int c) { // Here, we will calculate how many paths that contain the centroid C
        cnt[0] = 1; // for computation, we consider Centroid to Centroid, zero length path

        mx_depth = 0;

        for (auto child: graph[c]) {
            // current depth = 1, since they are children
            dfs2(child, c, 1, true);  // flag = true, means compute k-length path for this subtree.
            dfs2(child, c, 1, false); // flag = false means calculate cnt[i], for each i-length path from the centroid to subtree node.

            // For each child, we get a different subtree,
            // We know that if we go from one subtree node to another subtree node, we must visit the centroid.
            // Since we are calculating the k-length path that goes through the centroid, we must process each subtree differently.
            // Also, to avoid recomputation, we must use two different dfs2() calls, so that for each i, we don't count cnt[k-i] of the same subtree, which wouldn't visit through the centroid.
        }

        for (int i = 0; i <= mx_depth + 1; i++) {
            cnt[i] = 0; // clearing
        }
    }

    void dfs2(int s, int p, int depth, bool flag) {
        if (k - depth < 0) {
            return;
        }

        if (flag) { // calculate k-length path
            ans += cnt[k - depth];  // from all the visited different subtrees, we get the count of k-depth path,
                                    // from this subtree we take the current path, whose length is depth, so total length of each path = k - depth + depth = k
        } else { // flag = false
            cnt[depth]++;
        }

        mx_depth = max(depth, mx_depth);

        for (auto child: graph[s]) {
            if (child == p) {
                continue;
            }

            dfs2(child, s, depth + 1, flag);
        }
    }

} CD;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        CD.addEdge(a, b);
    }

    CD.build(1, 1, k);

    cout << CD.ans << endl;
}

------------------ Faster -------------------


        
// use processed[i] to mark which node is already removed, like this implementation        
        
const int N = 2e5 + 100;

class CentroidDecomposition {
private:
    int n, k;
    vector<int> graph[N];
    bool processed[N]; // processed[i] = i-th node has been removed from the graph
    int cnt[N];    // cnt[i] = number of i-length paths from the centroid/root
    int subtree[N];
    int mx_depth;
    int parent[N];

public:
    long long int ans; // ans = total count of exactly k-length paths

    CentroidDecomposition() {
        this->n = 0;
        this->k = 0;
        fill(processed, processed + N, false);
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int dfs(int s, int p) {
        subtree[s] = 1;
        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }
            subtree[s] += dfs(child, s);
        }
        return subtree[s];
    }

    int centroid(int s, int p, int n) {
        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }
            if (subtree[child] > n / 2) {
                return centroid(child, s, n);
            }
        }
        return s;
    }

    void build(int s, int p, int k) {
        this->k = k;
        int n = dfs(s, p);
        int c = centroid(s, p, n);

        processed[c] = true;

        do_for_centroid(c);

        for (auto child : graph[c]) {
            if (processed[child]) {
                continue;
            }
            build(child, c, k);
        }
    }

    void do_for_centroid(int c) { // Calculate how many paths contain the centroid C
        cnt[0] = 1; // for computation, we consider Centroid to Centroid, zero length path

        mx_depth = 0;

        for (auto child : graph[c]) {
            if (processed[child]) {
                continue;
            }

            // Current depth = 1, since they are children
            dfs2(child, c, 1, true);  // flag = true, compute k-length path for this subtree.
            dfs2(child, c, 1, false); // flag = false, calculate cnt[i], for each i-length path from centroid to subtree node.

            // For each child, we get a different subtree.
            // We know that if we go from one subtree node to another subtree node, we must visit the centroid.
            // Since we are calculating the k-length path that goes through the centroid, we must process each subtree differently.
            // To avoid recomputation, we use two different dfs2() calls.
        }

        for (int i = 0; i <= mx_depth + 1; i++) {
            cnt[i] = 0; // Clearing
        }
    }

    void dfs2(int s, int p, int depth, bool flag) {
        if (k - depth < 0) {
            return;
        }

        if (flag) { // Calculate k-length path
            ans += cnt[k - depth];  // From all the visited different subtrees, we get the count of k-depth path,
                                    // from this subtree we take the current path, whose length is depth, so total length of each path = k - depth + depth = k
        } else { // flag = false
            cnt[depth]++;
        }

        mx_depth = max(depth, mx_depth);

        for (auto child : graph[s]) {
            if (child == p || processed[child]) {
                continue;
            }

            dfs2(child, s, depth + 1, flag);
        }
    }
} CD;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        CD.addEdge(a, b);
    }

    CD.build(1, 1, k);

    cout << CD.ans << endl;
}

        

=================================================================  ==========================================
//Closest Red vertex : https://codeforces.com/contest/342/problem/E

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
