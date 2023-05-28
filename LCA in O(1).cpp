

// ============= Euler Tour type -  03 ========== LCA in O(1) ============

// ET3 = 1 2 3 2 4 6 4 7 4 2 5 2 1 8 9 8 10 8 1

// in this tour technique (child - father - child) is always maintained , so between 2 child , their father shall be present (not grand father though)
// So query(u,v) means :
//                u first appear in ET3 and v first appear in ET3 er moddhe jetar depth lowest setai LCA ;
//                we find this using sparse table O(1) , segment tree O(logn)


const int N = 1e5;
vector<int>graph[N];
vector<int>ET3;
vector<int>p(N,-1); //p[v] = v first appear in ET3;
bool vis[N];
int dept[N];
const int L = log2(N);
int st[N][L+1];
int Log2[N];

void dfs(int s)
{
        vis[s] = true;
        ET3.push_back(s);
        for(auto child: graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dept[child] = dept[s]+1;

                dfs(child);

                ET3.push_back(s);
        }
}

void pre()
{
        Log2[0] = 0;
        Log2[1] = 0;
        Log2[2] = 1;
        for(int i=3;i<N;i++)
        {
                Log2[i] = Log2[i/2]+1;
        }
}

void sparse_table()
{
        for(int i=0;i<ET3.size();i++)
        {
                st[i][0] = ET3[i];
        }

        int l = Log2[ET3.size()];

        for(int i=1;i<=l;i++)
        {
                for(int j=0;j+(1<<i)<=ET3.size();j++) // j+(1<<i)-1<ET3.size()
                {
                        int a = st[j][i-1];

                        int b = st[j+(1<<(i-1))][i-1];

                        //Sort of like dp
                        //instead of storing the minimum , We are storing the Vertex with minimum detph

                        if(dept[a]<dept[b])
                        {
                                st[j][i] = a;
                        }
                        else
                        {
                                st[j][i] = b;
                        }
                }
        }
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        pre();


        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        dfs(1);

        for(int i=0;i<ET3.size();i++)
        {
                if(p[ET3[i]]==-1)
                {
                        p[ET3[i]] = i;
                }
        }

        sparse_table();


        int q;
        cin>>q;


        cout<<"LCAs : "<<endl;
        while(q--)
        {
                int u,v;
                cin>>u>>v;


                int a = min(p[v],p[u]); // p[u] first pos of u , p[v] first pos of v in ET3;
                int b = max(p[v],p[u]);

                int i = Log2[b-a+1];

                int vertex1 = st[a][i];
                int vertex2 = st[b-(1<<i)+1][i];

                if(dept[vertex1]<dept[vertex2])
                {
                        cout<<vertex1<<endl;
                }
                else
                {
                        cout<<vertex2<<endl;
                }


        }



        return 0;




}
/*

10
1 2
2 3
2 4
2 5
4 6
4 7
1 8
8 9
8 10

6
1 8
8 7
6 7
10 9
3 4
3 5

O/P:

LCAs :
1
1
4
8
2
2




*/

