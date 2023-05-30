
const int N = 10000;
vector<int>graph[N];
int low[N];
int dis[N];
vector<int>par(N,-1);
bool vis[N];
vector<pair<int,int>>p[N];
int no = 1;

void dfs(int s, stack<pair<int,int>> &st , int time)
{
        time++;
        vis[s] = true;
        low[s] = dis[s] = time;
        int childno = 0;
        for(auto child : graph[s])
        {
                if(par[s]==child)
                {
                        continue;
                }
                if(vis[child])
                {
                        low[s] = min(low[s] , dis[child]);
                        if(dis[child]<dis[s])
                        {
                                st.push({s,child});
                        }
                        continue;
                }
                par[child] = s;
                childno++;

                st.push({s,child});

                dfs(child,st,time);
                low[s] = min(low[s] , low[child]);


                if((par[s]==-1 && childno>1) || (par[s]!=-1 && dis[s]<=low[child]) )
                {
                        while(st.top().first!=s || st.top().second!= child)
                        {
                                p[no].push_back({st.top().first ,st.top().second });
                                st.pop();
                        }
                        p[no].push_back({st.top().first ,st.top().second });
                        st.pop();
                        no++;
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
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }
        stack<pair<int,int>>st;
        for(int i=0;i<n;i++)
        {
                if(vis[i]==false)
                {
                        dfs(i,st,0);
                }
                bool flag = false;
                while(!st.empty())
                {
                        flag = true;
                        p[no].push_back({st.top().first ,st.top().second });
                        st.pop();
                }
                if(flag)
                {
                        no++;
                }
        }

        cout<<"-------------"<<endl;
        for(int i=1;i<N;i++)
        {
                if(p[i].size()==0)
                {
                        break;
                }
                cout<<"BCC NO: "<<i<<":"<<endl;
                for(int j=0;j<p[i].size();j++)
                {
                        cout<<p[i][j].first<<"-"<<p[i][j].second<<" ";
                }
                cout<<endl;
        }



        return 0;


}

/*
geeksforgeeks
12 28
0 1
1 0
1 2
2 1
1 3
3 1
2 3
3 2
2 4
4 2
3 4
4 3
1 5
5 1
0 6
6 0
5 6
6 5
5 7
7 5
5 8
8 5
7 8
8 7
8 9
9 8
10 11
11 10
*/

/* hackerearth
6 6
0 3
3 2
2 5
2 4
5 4
1 4

*/
