
//TOPO SORT

const int N = 1e5+100;
vector<int>graph[N];
bool vis[N];
int in[N];

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
                in[y]++;
        }
        queue<int>q;
        for(int i=1;i<=n;i++)
        {
                if(in[i]==0)
                {
                    q.push(i);
                }
        }
        vector<int>ans;
        while(!q.empty())
        {
                int father = q.front();
                vis[father] = true;
                ans.push_back(father);
                q.pop();
                for(auto child : graph[father])
                {
                        if(vis[child])
                        {
                                continue;
                        }
                        in[child]--;
                        if(in[child]==0)
                        {
                                q.push(child);
                                vis[child] = true;
                        }
                }
        }


        for(int i=1;i<=n;i++)
        {
                if(vis[i]==false)
                {
                        cout<<"IMPOSSIBLE"<<endl;
                        return 0;
                }
        }


        for(auto x : ans)
        {
                cout<<x<<" ";
        }
        cout<<endl;

        return 0;






}
