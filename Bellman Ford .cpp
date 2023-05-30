
int inf = 1e18;

struct edge
{
        int x;
        int y;
        int w;
};


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;
        vector<edge>edges;

        for(int i=0;i<m;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                edges.push_back({x,y,w});
        }

        vector<int>dis(n+1,inf);

        dis[0] = 0;
        dis[1] = 0; // distant of source is 0 . very important

        vector<int>par(n+4,-1);

        bool neg_cycle = false;

        for(int i=0;i<n;i++)
        {
                for(int j=0;j<m;j++)
                {
                        int u = edges[j].x;
                        int v = edges[j].y;
                        int w = edges[j].w;
                        if(dis[u]<inf)
                        {
                                if( dis[u]+w < dis[v])
                                {
                                        if(i==n-1)
                                        {
                                                neg_cycle = true;
                                        }
                                        dis[v] = min(dis[v] , dis[u]+w);
                                        par[v] = u;
                                }

                        }
                }
        }


//        vector<int>path;
//
//        int v = n;
//
//        while(v!=-1) // path printing
//        {
//                path.push_back(v);
//                v = par[v];
//        }
//
//        reverse(path.begin() , path.end());
//
//        for(auto x : path)
//        {
//                cout<<x<<" ";
//        }
//        cout<<endl;

        if(neg_cycle)
        {
                cout<<"Neg cycle is present"<<endl;
        }
        else
        {
                cout<<"No neg cycle"<<endl;
        }

        return 0;



}
