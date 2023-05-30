

// Printing cycle in a directed graph

// Round trip 1 was on undirected graph , but here round trip 2 is on directed graph so normal dfs visit one time wont work
// visited but not returned , thats our target

const int N = 1e5+100;
int vis[N];
vector<int>graph[N];
int Time[N];
bool ok;
bool flag;
vector<int>ans;
int parent[N];
int start,finish;

void dfs(int s,int tim)
{
        vis[s] = 1;
        Time[s] = tim++;
        for(auto child: graph[s])
        {
                if(vis[child]==0 )
                {
                        parent[child] = s;
                        dfs(child,tim);
                        if(ok)
                        {
                                return;
                        }
                }
                if(vis[child]==1)
                {

                        start = s;
                        finish = child;
                        ok = true;
                        flag = true;
                        return;
                }

        }

        vis[s] = 2;


}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;

        for(int i=0;i<m;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
        }


        for(int i=1;i<=n;i++)
        {
                if(vis[i]==false)
                {
                        dfs(i,0);
                        if(flag)
                        {
                                break;
                        }
                }
        }


        if(flag)
        {

                ans.push_back(finish);

                while(finish!=start)
                {
                        ans.push_back(start);
                        start = parent[start];
                }

                ans.push_back(finish);

                reverse(ans.begin(),ans.end());


               cout<<ans.size()<<endl;

               for(auto x : ans)
               {
                       cout<<x<<" ";
               }
               cout<<endl;

               return 0;


        }



        cout<<"IMPOSSIBLE"<<endl;

        return 0;





}
