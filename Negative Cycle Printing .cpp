//AIA

//using floyed printing neg cycle

const int N = 2e4;
int dis[N];
int relaxtant[N]; // it is like parent[N] array

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;
        vector<tuple<int,int,int>>edges;

        for(int i=0;i<m;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                edges.push_back({x,y,w});
        }
        int take;

        for(int i=1;i<n+1;i++)
        {
                take = -1;
                for(auto &[u,v,w]:edges)
                {
                        if(dis[v]>dis[u]+w)
                        {
                                dis[v] = dis[u]+w;
                                take = v;
                                relaxtant[v] = u;
                        }
                }
        }

        if(take==-1)
        {
                cout<<"NO"<<endl;
                return 0;
        }

        cout<<"YES"<<endl;

        int v = relaxtant[take];



        //The followings is very important
        for(int i=1;i<n+1;i++)
        {
                 v = relaxtant[v];            // if there is a negative cycle eventually v will trace back to it ,, even there exits a positive cycly it wont matter relaxtant wont trace to it
                                              //it will eventually fall into the negetive cycle

        }


        vector<int>ans;

        for(int u = v ; ; u = relaxtant[u])
        {
                ans.push_back(u);
                if(u==v && ans.size()>1)
                {
                        break;
                }
        }

        reverse(ans.begin(),ans.end());

        for(auto x : ans)
        {
                cout<<x<<" ";
        }
        cout<<endl;

        return 0;

}
