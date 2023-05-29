//=============================== DSU On Tree O(n log^2 n) ===========================

// =========== How many vertex in the subtree of v has the color c , Query(v,c) ===========


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


vector<pair<int,int>> Query[N];
int ans[N];






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

        if(bigchild != -1)
        {
                swap(cnt[s] , cnt[bigchild]) ; // this swap operation is O(1) [all stl container swap is O(1)]

                //this part is the brain of the whole algorithm .
                //Here cnt[s] will gain cnt[bigchild]'s info in O(1) and cnt[bigchild] will contain cnt[s] [which means cnt[bigchild] will be empty]
        }

        cnt[s][col[s]]++;

        for(auto child: graph[s])
        {
                if(child==par || child == bigchild) // we have copied big child's info in O(1) , and rest are copied manually , it is not possible to copy rest of them without manual process
                {
                        continue;
                }
                for(auto x : cnt[child])
                {
                        cnt[s][x.first] += x.second;
                }
        }



        //query for vertex s should be answered here , cause after each recursion call cnt[bigchild] would be cleared

        for(auto x : Query[s])
        {
                ans[x.second] = cnt[s][x.first];
        }




}


void dsu_on_tree()
{
        dfs1(1,1);
        dfs(1,1);
}











//https://codeforces.com/blog/entry/44351

//map<int, int> *cnt[maxn]; //We declare pointer of map cause


//void dfs(int v, int p){
//    int mx = -1, bigChild = -1;
//    for(auto u : g[v])
//       if(u != p){
//           dfs(u, v);
//           if(sz[u] > mx)
//               mx = sz[u], bigChild = u;
//       }
//    if(bigChild != -1)
//        cnt[v] = cnt[bigChild]; // Since cnt[v] is a pointer , this operation is O(1) [ assigning address of cnt[bigchild] to cnt[v] is O(1) ] [ remember any change in cnt[v] will result change in cnt[bigchild] , so cnt bigchild won't provide correct answer]
//    else
//        cnt[v] = new map<int, int> (); // constructor of map , else cnt[v] is a NULL
//    (*cnt[v])[ col[v] ] ++;
//    for(auto u : g[v])
//       if(u != p && u != bigChild){
//           for(auto x : *cnt[u])
//               (*cnt[v])[x.first] += x.second;
//       }
//
//       //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
//       // answer of the queries should be done here
//
//}
//









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


        cout<<"Answer to each Queries :"<<endl;
        for(int i=0;i<no;i++)
        {
                cout<<ans[i]<<endl;
        }



        return 0;






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


Answer to each Queries :
3
1
1
3
2
3
1
2


*/


