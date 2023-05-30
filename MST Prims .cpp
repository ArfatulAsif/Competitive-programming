
const int N = 1e5;
int inf = 1e18;
vector<pair<int,int>>graph[N];
vector<int>key(N , inf);
vector<int>parent(N,-1);
int mstCost = 0;
int vis[N];

void Prims(int s)
{
        priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > pq;
        key[s] = 0;
        pq.push({0,s});
        parent[s] = -1;
        while(!pq.empty())
        {
                int father = pq.top().second;

                if(vis[father]==false)
                {
                        mstCost += pq.top().first;
                        vis[father] = true;
                }

                pq.pop();
                for(auto child : graph[father])
                {
                        if(vis[child.first])
                        {
                                continue;
                        }
                        if(child.second < key[child.first]) // Note e leka ase why , tar por oo fresh mind a 2,1 ta mST draw kore buja jay . Try the graph attach below
                        {
                                key[child.first] = child.second;
                                parent[child.first] = father;
                                pq.push({child.second , child.first});
                        }
                }
        }
        return;
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
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }
        Prims(1);
        cout<<"------"<<endl;
        cout<<mstCost<<endl;
        for(int i=1;i<=n;i++)
        {
                if(parent[i]==-1)
                {
                        continue;
                }
                cout<<i<<" "<<parent[i]<<endl;
        }

        return 0;


}


/*
4 5
1 2 2
1 3 7
2 3 6
1 4 5
4 3 1

*/
