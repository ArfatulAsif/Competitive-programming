//================================ DSU On Tree O(n logn ) ===============================

// =========== How many vertex in the subtree of v has the color c , Query(v,c) ===========


// https://codeforces.com/blog/entry/44351
// from this blog I have also learned [3. heavy-light decomposition style ] but I didn't find it very interesting
// Use this method  [2. easy to code ]
// only improvement is using swap( ) instead of pointer  and vector<int> *vec[N]


const int N = 2e5+100;
vector<int>graph[N];
int col[N];
int subtree[N];
int cnt[N];
vector<int> vec[N] ; //vec[v] will contain all the vertex of the subtree of v



vector<pair<int,int>>Query[N];
int ans[N];

void dfs1(int s ,int par)
{
        subtree[s] = 1;
        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                dfs1(child,s);
                subtree[s] += subtree[child];
        }
}


void dfs(int s,int par,bool keep)
{
        int mx = -1;
        int bigchild = -1;

        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                if(mx<subtree[child])
                {
                        mx = subtree[child];
                        bigchild = child;
                }
        }


        //it doesn't matter if we send bigchild first or small child first

        for(auto child: graph[s])
        {
                if(child==par || child==bigchild)
                {
                        continue;
                }
                dfs(child,s,false);
        }
        if(bigchild!=-1)
        {
                dfs(bigchild,s,true);

                swap(vec[s] , vec[bigchild]); // This operation is O(1) ; this will transfer all the vertex of bigchild's subtree to S in O(1)
                // after this vec[bigchild] will be cleared as vec[s] was empty


        }

        cnt[col[s]]++;

        vec[s].push_back(s);

        // Think about this : let say For a node S , bigchild is already counted and result are stored in cnt[bigchild] . and for All small child cnt[small] are cleared before in the Backtracking call .

        // cnt[small] are cleared  in the last two line starting from if(keep==false) in the backtracking call .

        // That's why we are gonna count cnt[small] here For the node S .

        for(auto child: graph[s])
        {
                if(child == par || child==bigchild)
                {
                        continue;
                }
                for(auto x : vec[child]) // light child's subtree is being counted manually
                {
                        cnt[col[x]]++;

                        vec[s].push_back(x);  //all the vertex's of the subtree of the light vertex's are being push in vec[s]
                }
        }


        //answer to all the queries should be stored
        for(auto x : Query[s])
        {
                ans[x.second] = cnt[x.first];
        }



        if(keep == false) // if S itself a light vertex for it's parent . then it need to be cleared . so that in the backtracking call when counting cnt[] for it parent it remain clear
        {
                for(auto x : vec[s])
                {
                        cnt[col[x]]--;
                }
        }



}

void dsu_on_tree()
{
        dfs1(1,1);

        dfs(1,1,0);
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        for(int i=1;i<=n;i++)
        {
                cin>>col[i];
        }

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }
        int q;
        cin>>q;
        int no = 0;
        while(q--)
        {
                int v,c;
                cin>>v>>c;
                Query[v].push_back({c,no});
                no++;
        }

        dsu_on_tree();


        cout<<"Answer to the Queries :"<<endl;
        for(int i=0;i<no;i++)
        {
                cout<<ans[i]<<endl;
        }



}

/*

14
5 7 5 1 3 9 4 3 1 2 4 4 9 9

1 2
1 3
2 4
2 5
2 6
4 13
4 14
3 8
3 7
8 10
7 9
9 11
9 12

8

2 9
8 2
1 7
1 4
1 5
3 4
3 3
4 9

Answer to the Queries :
3
1
1
3
2
3
1
2


*/







//=============================== DSU On Tree O(nlogn) ===========================

// =========== Which color in the subtree of v has appeared the most  , Query(v) [if there multiple ans print any] ===========


// https://codeforces.com/blog/entry/44351
// from this blog I have also learned [3. heavy-light decomposition style ] but I didn't find it very interesting
// Use this method  [2. easy to code ]
// only improvement is using swap( ) instead of pointer  and vector<int> *vec[N]



const int N = 2e5+100;
vector<int>graph[N];
int col[N];
int subtree[N];
int cnt[N];
vector<int> vec[N] ; //vec[v] will contain all the vertex of the subtree of v


int mx_color[N]; // mx_color[v] will contain the color which has appeared the most in the subtree of v

void dfs1(int s ,int par)
{
        subtree[s] = 1;
        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                dfs1(child,s);
                subtree[s] += subtree[child];
        }
}


void dfs(int s,int par,bool keep)
{
        int mx = -1;
        int bigchild = -1;

        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                if(mx<subtree[child])
                {
                        mx = subtree[child];
                        bigchild = child;
                }
        }


        //it doesn't matter if we send bigchild first or smallchild first

        for(auto child: graph[s])
        {
                if(child==par || child==bigchild)
                {
                        continue;
                }

                dfs(child,s,false);

        }

        int cur_max = -1;

        if(bigchild !=-1 )
        {


                dfs(bigchild,s,true);

                cur_max = mx_color[bigchild];

                swap(vec[s] , vec[bigchild]); // This operation is O(1) ; this will transfer all the vertex of bigchild's subtree to S in O(1)
                // after this vec[bigchild] will be cleared as vec[s] was empty

        }

        cnt[col[s]]++;


        if(cur_max ==-1)
        {
                cur_max = col[s];
        }
        else if(cnt[cur_max]<cnt[col[s]])
        {
                cur_max = col[s];
        }


        vec[s].push_back(s);

        // Think about this : let say For a node S , bigchild is already counted and result are stored in cnt[bigchild] . and for All small child cnt[small] are cleared before in the Backtracking call .

        // cnt[small] are cleared  in the last two line starting from if(keep==false) in the backtracking call .

        // That's why we are gonna count cnt[small] here For the node S .

        for(auto child: graph[s])
        {
                if(child == par || child ==bigchild)
                {
                        continue;
                }
                for(auto x : vec[child]) // light child's subtree is being counted manually
                {
                        cnt[col[x]]++;


                        if(cnt[cur_max]<cnt[col[x]])
                        {
                                cur_max = col[x];
                        }

                        vec[s].push_back(x);  //all the vertex's of the subtree of the light vertex's are being push in vec[s]
                }
        }


        //answer to all the queries should be stored



        mx_color[s] = cur_max;




        if(keep == false) // if S itself a light vertex for it's parent . then it need to be cleared . so that in the backtracking call when counting cnt[] for it parent it remain clear
        {
                for(auto x : vec[s])
                {
                        cnt[col[x]]--;
                }
        }



}

void dsu_on_tree()
{
        dfs1(1,1);

        dfs(1,1,0);
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        for(int i=1;i<=n;i++)
        {
                cin>>col[i];
        }

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }


        dsu_on_tree();


        int q;
        cin>>q;


        cout<<"Answer to the Queries :"<<endl;

        while(q--)
        {
                int v;
                cin>>v;

                cout<<mx_color[v]<<endl;
        }


}

/*

14
5 7 5 1 3 9 4 3 1 2 4 4 9 9

1 2
1 3
2 4
2 5
2 6
4 13
4 14
3 8
3 7
8 10
7 9
9 11
9 12

14

1
2
3
4
5
6
7
8
9
10
11
12
13
14


Answer to the Queries :
4
9
4
9
3
9
4
2
4
2
4
4
9
9



*/



