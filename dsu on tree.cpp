//=============================== DSU On Tree O(n log^2 n) ===========================

// =========== Which color in the subtree of v has appeared the most  , Query(v) ===========


//Intermediary
//Young kid on the block
//AIAsif try's "Continuing the journey"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int N = 2e5+100;
vector<int>graph[N];
int subtree[N];
int col[N];
map<int,int> cnt[N];

int mx_color[N]; // mx_color[v] will return the color which has appeared the most in the subtree of v ;



void dfs1(int s,int par)
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


void dfs(int s,int par)
{
        int mx = -1;
        int bigchild = -1;

        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                dfs(child,s);

                if(mx<subtree[child])
                {
                        mx = subtree[child];
                        bigchild = child;
                }
        }

        int cur_max = -1;

        if(bigchild != -1)
        {
                cur_max = mx_color[bigchild];

                swap(cnt[s] , cnt[bigchild]) ; // this swap operation is O(1) [all stl container swap is O(1)]

                //this part is the brain of the whole algorithm .
                //Here cnt[s] will gain cnt[bigchild]'s info in O(1) and cnt[bigchild] will contain cnt[s] [which means cnt[bigchild] will be empty]
        }

        cnt[s][col[s]]++;

        if(cnt[s][cur_max]  < cnt[s][col[s]])
        {
                cur_max = col[s];
        }

        for(auto child: graph[s])
        {
                if(child==par || child == bigchild) // we have copied big child's info in O(1) , and rest are copied manually , it is not possible to copy rest of them without manual process
                {
                        continue;
                }
                for(auto x : cnt[child])
                {
                        cnt[s][x.first] += x.second;

                        if(cnt[s][cur_max]  < cnt[s][x.first])
                        {
                                cur_max = x.first;
                        }
                }
        }



        //query for vertex s should be answered here , cause after each recursion call cnt[bigchild] would be cleared


        mx_color[s] = cur_max;




}

void dsu_on_tree()
{
        dfs1(1,1);
        dfs(1,1);
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



        int no = 0;



        dsu_on_tree();


        cout<<"Answer to each Queries :"<<endl;

        int q;
        cin>>q;
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


Answer to each Queries :
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


