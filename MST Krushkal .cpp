
const int N = 1e5;
int parent[N];
int sz[N];
vector<pair<int, pair<int,int>>>edge;
vector<pair<pair<int,int> , int>>MST;
int mstCost = 0;


void make(int v)
{
        parent[v] = v;
        sz[v] = 1;
}

int find(int v)
{
        if(v==parent[v])
        {
                return v;
        }
        return parent[v] = find(parent[v]);
}

void Union(int a,int b)
{
        a = find(a);
        b = find(b);
        if(a!=b)
        {
                if(sz[a]<sz[b])
                {
                        swap(a,b);
                }
                parent[b] = a;
                sz[a] += sz[b];
        }
}

void Krushkal()
{
        for(auto x : edge)
        {
                int w = x.first;
                int u = x.second.first;
                int v = x.second.second;
                if(find(u)!=find(v))
                {
                        MST.push_back({{u , v} , w });
                        mstCost += w;
                        Union(u,v);
                }
        }
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                edge.push_back({w , { x , y }});
        }
        sort(edge.begin() , edge.end());
        for(int i=1;i<=n;i++) // 1 based
        {
                make(i);
        }
        Krushkal();

        cout<<"----------"<<endl;
        cout<<mstCost<<endl;

        for(auto x : MST)
        {
                cout<<x.first.first<<" "<<x.first.second<<" "<<x.second<<endl;
        }

        return 0;



}

/*
6 9
5 4 9
1 4 1
5 1 4
4 3 5
4 2 3
1 2 2
3 2 3
3 6 8
2 6 7

*/
