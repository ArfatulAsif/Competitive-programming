

=========================================Euler Tour Array Building =======================
==========================================================================================

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
const int N = 1e5;
vector<int>graph[N];
bool vis[N];
vector<pair<int,int>>ET1; //ET on Edge
vector<int>ET2; // ET on Vertex
vector<int>ET3; // ET for LCA


void dfs(int s)
{
        vis[s] = true;
        ET2.push_back(s);
        ET3.push_back(s);
        for(auto child : graph[s])
        {
                if(vis[child])
                {
                        continue;
                }

                ET1.push_back({s,child});
                dfs(child);

                ET1.push_back({child,s});

                ET3.push_back(s);
        }
        ET2.push_back(s);

}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }
        dfs(1);

        cout<<"---------- "<<"ET on Edge "<<"------"<<endl;
        cout<<ET1.size()<<endl;
        for(int i=0;i<ET1.size();i++)
        {
                cout<<"["<<ET1[i].first<<"-"<<ET1[i].second<<"] ";
        }
        cout<<endl;

        cout<<"---------- "<<"ET on Vertex "<<"------"<<endl;
        cout<<ET2.size()<<endl;
        for(int i=0;i<ET2.size();i++)
        {
                cout<<ET2[i]<<" ";
        }
        cout<<endl;

        cout<<"---------- "<<"ET for LCA "<<"------"<<endl;
        cout<<ET3.size()<<endl;
        for(int i=0;i<ET3.size();i++)
        {
                cout<<ET3[i]<<" ";
        }
        cout<<endl;


	return 0;




}

/*
5
1 2
2 3
2 4
1 5


O/P:

---------- ET on Edge ------
8
[1-2] [2-3] [3-2] [2-4] [4-2] [2-1] [1-5] [5-1]

---------- ET on Vertex ------
10
1 2 3 3 4 4 2 5 5 1

---------- ET for LCA ------
9
1 2 3 2 4 2 1 5 1




10
1 2
2 3
2 4
2 5
4 6
4 7
1 8
8 9
8 10

O/P:



---------- ET on Edge ------
18
[1-2] [2-3] [3-2] [2-4] [4-6] [6-4] [4-7] [7-4] [4-2] [2-5] [5-2] [2-1] [1-8] [8-9] [9-8] [8-10] [10-8] [8-1]
---------- ET on Vertex ------
20
1 2 3 3 4 6 6 7 7 4 5 5 2 8 9 9 10 10 8 1
---------- ET for LCA ------
19
1 2 3 2 4 6 4 7 4 2 5 2 1 8 9 8 10 8 1

*/





==========================================TYPE - 01====================================
EULER TOUR ON EDGEs
=======================================================================================
=======================================================================================
=======================================================================================




=======================================Subtree Sum Query(u) [Sum of all the edges of subtree of u] ==========
=============================================================================================================

//Edge: Subtree Sum Query(U)

// Technique is described below
// [1-2] [2-3] [3-2] [2-4] [4-6] [6-4] [4-7] [7-4] [4-2] [2-5] [5-2] [2-1] [1-8] [8-9] [9-8] [8-10] [10-8] [8-1]
// if we want to Subtree_Sum_Query(2) :
//         We find where 2 appears first time at the first position in the pairs which is pos: 2
//         We find where 2 appears Last time at the second position in the pairs which is pos: 11
// Now Subtree_Sum_Query(2) = (Query(1,1,n, 2 , 11)/2) [Why divide by 2 , cause we shall count twice each internal edges ,in a subtree(u-v),(v-u)]


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

const int N = 1e5;
vector<pair<int,int>>graph[N];
vector<pair<int,int>>ET1;
bool vis[N];
vector<pair<int,int>>p(N,{0,0}); // (p[v].first = v first appear at the first position in the pairs) , (p[v].second = v Last appear at the second position of the pairs)
bool vis1[N]; // for keeping track v first appear at the first position in the pairs
map<pair<int,int>,int>Edge_id;
int ara[2*N]; // For Segment tree ET1 er size can be 2*N
int Tree[8*N]; // Segment tree (8N hobe )

const int L = log2(N);
int up[N][L+1]; // For LCA
int din[N];
int dout[N];
int tim;




void dfs(int s,int par)
{
        vis[s] = true;
        din[s] = tim++;
        up[s][0] = par;
        for(int i=1;i<=L;i++) // store LCA
        {
                up[s][i] = up[up[s][i-1]][i-1];
        }
        for(auto child : graph[s])
        {
                if(vis[child.first])
                {
                        continue;
                }
                ET1.push_back({s,child.first});

                ara[ET1.size()-1] = child.second; // remember ET1 ke 1 based korar jonno {0,0} push koresi tai ET1.size()-1

                Edge_id[{s,child.first}] = ET1.size()-1;

                dfs(child.first , s);

                ET1.push_back({child.first,s});

                ara[ET1.size()-1] = child.second;

                Edge_id[{child.first,s}] = ET1.size()-1;

        }
        dout[s] = tim++;
}

bool is_ancestor(int u,int v)
{
        return (din[u]<=din[v] && dout[u]>=dout[v]);
}

int lca(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return u;
        }
        if(is_ancestor(v,u))
        {
                return v;
        }
        for(int i=L;i>=0;i--)
        {
                if(!is_ancestor(up[u][i] , v))
                {
                        u = up[u][i];
                }
        }
        return up[u][0];
}


void build(int node , int lo ,int hi)
{
        if(lo==hi)
        {
               Tree[node] = ara[lo];
               return;
        }
        int mid = (lo+hi)>>1;

        build(node*2,lo , mid);
        build(node*2+1,mid+1,hi);

        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

void update(int node ,int lo,int hi,int pos,int val)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo] = val; // if add then Tree[node] = ara[lo] +=val

                return;
        }
        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                update(node*2,lo,mid,pos,val);
        }
        else
        {
                update(node*2+1,mid+1,hi,pos,val);
        }
        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

int query(int node ,int lo,int hi,int i,int j)
{
        if(j<lo || i>hi)
        {
                return 0;
        }
        if(lo>=i && hi<=j)
        {
                return Tree[node];
        }
        int mid = (lo+hi)>>1;

        int x = query(node*2,lo,mid,i,j);
        int y = query(node*2+1,mid+1,hi,i,j);

        return x+y;
}

int Subtree_sum_query(int u)
{
        return query(1,1,ET1.size()-1,p[u].first,p[u].second)/2; // remember to divide by 2
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }

        ET1.push_back({-1,-1}); // to make ET1 1 based rather than 0 for segment tree

        dfs(1,1);

        for(int i=1;i<ET1.size();i++)
        {
                if(vis1[ET1[i].first]==false)
                {
                        p[ET1[i].first].first = i;
                        vis1[ET1[i].first] = true;
                }

                p[ET1[i].second].second = i; // p[v].second = v appears Last at the second position in the pairs


        }

        build(1,1,ET1.size()-1);


        int q;
        cin>>q;
        cout<<"SubTree Sum queries: "<<endl;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1) // update query
                {
                        int u,v,w;
                        cin>>u>>v>>w;
                        // (u - v) edge er value update
                        if(is_ancestor(u,v)) // if in tree u is closes to root
                        {
                                update(1,1,ET1.size()-1 , Edge_id[{u,v}] , w);
                                update(1,1,ET1.size()-1 , Edge_id[{v,u}] , w); // in Edge sum query we would have used -w
                        }
                        else  // if in tree v is closes to root
                        {
                                update(1,1,ET1.size()-1 , Edge_id[{v,u}] , w);
                                update(1,1,ET1.size()-1 , Edge_id[{u,v}] , w); // in Edge sum query we would have used -w
                        }

                }
                else
                {
                        int u;
                        cin>>u;
                        cout<<Subtree_sum_query(u)<<endl;

                }



        }





	return 0;






}


/*

10
1 2 2
2 3 9
2 4 7
2 5 11
4 6 9
4 7 4
1 8 2
8 9 7
8 10 3

12
2 2
2 4
2 1
2 8
2 6
2 7
1 2 5 100
2 2
1 4 2 200
2 2
1 8 1 500
2 1



O/P:
SubTree Sum Query :
40
13
54
10
0 // Leaf er Edge Subtree Sum Query = 0
0 // Leaf er Edge Subtree Sum Query = 0
129
322
834

*/






=======================================Edge Sum Query(u,v) [Sum of all the edges from u to v] ============
=============================================================================================================


//Edge Sum Query(U,V)

// Technique is described below
// [1-2] [2-3] [3-2] [2-4] [4-6] [6-4] [4-7] [7-4] [4-2] [2-5] [5-2] [2-1] [1-8] [8-9] [9-8] [8-10] [10-8] [8-1]
// if we want to Sum_Query(6,8) :
//     We first find LCA(6,8) = 1 now Sum_query(6,8) = Query(1,6)+Query(1,8) , remember left e jeta root er kase seta thakbe
//     For Query(1,6) :
//         We find where 1 appears first time at the first position in the pairs which is pos: 1
//         We find where 6 appears first time at the second position in the pairs which is pos: 5
//     For Query(1,8) :
//         We find where 1 appears first time at the first position in the pairs which is pos: 1
//         We find where 8 appears first time at the second position in the pairs which is pos : 13
//     So now it is Sum_query(6,8) = Query(1,5) + Query(1,13)



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

const int N = 1e5;
vector<pair<int,int>>graph[N];
vector<pair<int,int>>ET1;
bool vis[N];
vector<pair<int,int>>p(N,{0,0}); // (p[v].first = v first appear at the first position in the pairs) , (p[v].second = v first appear at the second position of the pairs)
bool vis1[N]; // for keeping track v first appear at the first position in the pairs
bool vis2[N]; // for keeping track v first appear at the second position of the pairs
map<pair<int,int>,int>Edge_id;
int ara[2*N]; // For Segment tree
int Tree[8*N]; // Segment tree (2*(4*N)

const int L = log2(N);
int up[N][L+1]; // For LCA
int din[N];
int dout[N];
int tim;




void dfs(int s,int par)
{
        vis[s] = true;
        din[s] = tim++;
        up[s][0] = par;
        for(int i=1;i<=L;i++) // store LCA
        {
                up[s][i] = up[up[s][i-1]][i-1];
        }
        for(auto child : graph[s])
        {
                if(vis[child.first])
                {
                        continue;
                }
                ET1.push_back({s,child.first});

                ara[ET1.size()-1] = child.second; // remember ET1 ke 1 based korar jonno {-1,-1} push koresi

                Edge_id[{s,child.first}] = ET1.size()-1;

                dfs(child.first , s);

                ET1.push_back({child.first,s});

                ara[ET1.size()-1] = -child.second; // Internal  node gula -+ hoye jawar jonno Segment tree Te

                Edge_id[{child.first,s}] = ET1.size()-1;

        }
        dout[s] = tim++;
}

bool is_ancestor(int u,int v)
{
        return (din[u]<=din[v] && dout[u]>=dout[v]);
}

int lca(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return u;
        }
        if(is_ancestor(v,u))
        {
                return v;
        }
        for(int i=L;i>=0;i--)
        {
                if(!is_ancestor(up[u][i] , v))
                {
                        u = up[u][i];
                }
        }
        return up[u][0];
}


void build(int node , int lo ,int hi)
{
        if(lo==hi)
        {
               Tree[node] = ara[lo];
               return;
        }
        int mid = (lo+hi)>>1;
        build(node*2,lo , mid);
        build(node*2+1,mid+1,hi);

        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

void update(int node ,int lo,int hi,int pos,int val)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo] = val; // if add then Tree[node] = ara[lo] +=val

                return;
        }
        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                update(node*2,lo,mid,pos,val);
        }
        else
        {
                update(node*2+1,mid+1,hi,pos,val);
        }
        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

int query(int node ,int lo,int hi,int i,int j)
{
        if(j<lo || i>hi)
        {
                return 0;
        }
        if(lo>=i && hi<=j)
        {
                return Tree[node];
        }
        int mid = (lo+hi)>>1;

        int x = query(node*2,lo,mid,i,j);
        int y = query(node*2+1,mid+1,hi,i,j);

        return x+y;
}

int sum_query(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return query(1,1,ET1.size()-1 , p[u].first , p[v].second);
        }
        if(is_ancestor(v,u))
        {
                return query(1,1,ET1.size()-1 , p[v].first , p[u].second);
        }
        int l = lca(u,v);
        // (l,u)

        int sum1 = query(1,1,ET1.size()-1 , p[l].first , p[u].second); // l first appear in the first pos of the pairs ---- u first appear first at the second pos in the pairs
        // (l,v)
        int sum2 = query(1,1,ET1.size()-1 , p[l].first , p[v].second); // l first appear in the first pos of the pairs ---- v first appear first at the second pos in the pairs

        return sum1+sum2;

}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }

        ET1.push_back({-1,-1}); // to make ET1 1 based rather than 0 for segment tree

        dfs(1,1);

        for(int i=1;i<ET1.size();i++)
        {
                if(vis1[ET1[i].first]==false)
                {
                        p[ET1[i].first].first = i;
                        vis1[ET1[i].first] = true;
                }
                if(vis2[ET1[i].second]==false)
                {
                        p[ET1[i].second].second = i;
                        vis2[ET1[i].second]= true;
                }
        }

        build(1,1,ET1.size()-1);


        int q;
        cin>>q;
        cout<<"Sum queries: "<<endl;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1) // update query
                {
                        int u,v,w;
                        cin>>u>>v>>w;
                        // (u - v) edge er value update
                        if(is_ancestor(u,v)) // if in tree u is closes to root
                        {
                                update(1,1,ET1.size()-1 , Edge_id[{u,v}] , w);
                                update(1,1,ET1.size()-1 , Edge_id[{v,u}] , -w);
                        }
                        else  // if in tree v is closes to root
                        {
                                update(1,1,ET1.size()-1 , Edge_id[{v,u}] , w);
                                update(1,1,ET1.size()-1 , Edge_id[{u,v}] , -w);
                        }

                }
                else
                {
                        int u,v;
                        cin>>u>>v;
                        cout<<sum_query(u,v)<<endl;
                }



        }





	return 0;






}


/*

10
1 2 2
2 3 9
2 4 7
2 5 11
4 6 9
4 7 4
1 8 2
8 9 7
8 10 3

14
2 6 7
2 7 9
2 1 10
2 9 10
2 3 10
2 2 3
2 1 5
1 2 5 100
2 3 5
1 4 2 200
2 6 7
2 6 5
1 8 1 500
2 5 8



O/P:
13
22
5
10
16
9
13
109
13
309
602

*/





==========================================TYPE - 02====================================
EULER TOUR ON VERTEXs
=======================================================================================
=======================================================================================
=======================================================================================



=======================================Subtree Sum Query(u) [Sum of all the vertex of the subtree of u] ============
====================================================================================================================

//Vertex: Subtree Sum Query
// ET2 array
// 1 2 3 3 4 6 6 7 7 4 5 5 2 8 9 9 10 10 8 1
// Lets say subtree_sum_query(2) :
//          we find first pos of 2 : 2
//          we find last pos (2nd pos) of 2 : 13
// so return Query(1,1,n,2,13) / 2 [divide by 2 cause each vertex is appeared twice]


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
const int N = 1e5;
vector<int>graph[N];
bool vis[N];
vector<int>ET2; // ET on Vertex
int tim;
int din[N];
int dout[N];
const int L = log2(N);
int up[N][L+1];

vector<pair<int,int>>p(N,{0,0}); // p[v].first  = v appear for the first time in ET2 and p[v].second = v appear for the last time(which is essentially 2nd time) in ET2
bool vis1[N];

int ara[2*N];
int Tree[8*N];


void dfs(int s,int par)
{
        vis[s] = true;
        up[s][0] = par;
        din[s] = tim++;
        ET2.push_back(s);

        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[ up[s][i-1] ][i-1];
        }
        for(auto child: graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dfs(child,s);
        }

        dout[s] = tim++;
        ET2.push_back(s);


}

bool is_ancestor(int u,int v)
{
        return (din[u]<=din[v] && dout[u]>=dout[v]);
}

int lca(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return u;
        }
        if(is_ancestor(v,u))
        {
                return v;
        }
        for(int i = L ;i>=0;i--)
        {
                if(!is_ancestor(up[u][i] , v))
                {
                        u = up[u][i];
                }
        }
        return up[u][0];
}

void build(int node,int lo ,int hi)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo];
                return;
        }
        int mid = (lo+hi)>>1;

        build(node*2,lo,mid);
        build(node*2+1,mid+1,hi);

        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

void update(int node,int lo,int hi,int pos,int val)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo] = val; // if add then += val
                return;
        }
        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                update(node*2,lo,mid,pos,val);
        }
        else
        {
                update(node*2+1,mid+1,hi,pos,val);
        }
        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

int query(int node,int lo,int hi,int i,int j)
{

        if(hi<i || lo>j)
        {
                return 0;
        }
        if(lo>=i && hi <=j)
        {
                return Tree[node];
        }

        int mid = (lo+hi)>>1;

        int x = query(node*2,lo,mid, i ,j );

        int y = query(node*2+1,mid+1,hi,i,j);

        return x+y;
}

int Subtree_sum_query(int u)
{

        return query(1,1,ET2.size()-1 , p[u].first , p[u].second )/2; // why divide by 2 , cause each vertex between them appear twice

}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        int v[n+5];
        v[0] = 0;
        for(int i=1;i<=n;i++)
        {
                cin>>v[i]; // value on each vertex
        }
        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        ET2.push_back(0); // to make ET2 1 based for segment tree

        dfs(1,1);

        for(int i=1;i<ET2.size();i++)
        {
                ara[i] = v[ET2[i]]; // prottek node er jonno ET2 er sequence wise node value rakha
        }



        for(int i=1;i<ET2.size();i++)
        {

                if(vis1[ET2[i]]==false)
                {
                        vis1[ET2[i]] = true;
                        p[ET2[i]].first = i;
                }
                else
                {
                        p[ET2[i]].second = i;
                }
        }

        build(1,1,ET2.size()-1);

        int q;
        cin>>q;
        cout<<"Subtree Sum Query: "<<endl;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int u,w;
                        cin>>u>>w;

                        update(1,1,ET2.size()-1 , p[u].first , w );
                        update(1,1,ET2.size()-1 , p[u].second , w);
                }
                else
                {
                        int u;
                        cin>>u;
                        cout<<Subtree_sum_query(u)<<endl;



                }
        }


        return 0;


}

/*

10
7 3 6 11 10 13 9 13 16 3
1 2
2 3
2 4
2 5
4 6
4 7
1 8
8 9
8 10

11
2 2
2 1
2 8
2 6
2 7
1 2 100
2 1
2 2
1 9 200
2 8
2 1

O/P:
Subtree Sum Query:
52
91
32
13
9
188
149
216
372

*/





=======================================Vertex Sum Query(u,v) [Sum of all the vertex value from u to v] =============
====================================================================================================================

//Vertex: Vertex Sum Query(U,V)
// ET2 array
// 1 2 3 3 4 6 6 7 7 4 5 5 2 8 9 9 10 10 8 1
// vertex_sum_query(6,5) :
//                 LCA(6,5) = 2 :
//                 vertex_sum_query(6,5) = query(2,6)+query(2,5)-query(2,2)
// look , (2-appear first time) ar (6- appear first time) er maje ET2 array te thaka 3 3 4 6 6 , er maje 3 -3 6 -6 cancell out so thake [2 4 6]
// similarly (2-appear first time) ar (5-appear first time) er maje ET2 array te thake 3 3 4 6 6 7 7 4  er maje 3 -3 4 6 -6 7 -7 -4  cancell out so thake [2 5]

//thats how it works


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
const int N = 1e5;
vector<int>graph[N];
bool vis[N];
vector<int>ET2; // ET on Vertex
int tim;
int din[N];
int dout[N];
const int L = log2(N);
int up[N][L+1];

vector<pair<int,int>>p(N,{0,0}); // p[v].first  = v appear for the first time in ET2 and p[v].second = v appear for the last time(which is essentially 2nd time) in ET2
bool vis1[N];

int ara[2*N];
int Tree[8*N];


void dfs(int s,int par)
{
        vis[s] = true;
        up[s][0] = par;
        din[s] = tim++;
        ET2.push_back(s);

        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[ up[s][i-1] ][i-1];
        }
        for(auto child: graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dfs(child,s);
        }

        dout[s] = tim++;
        ET2.push_back(s);


}

bool is_ancestor(int u,int v)
{
        return (din[u]<=din[v] && dout[u]>=dout[v]);
}

int lca(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return u;
        }
        if(is_ancestor(v,u))
        {
                return v;
        }
        for(int i = L ;i>=0;i--)
        {
                if(!is_ancestor(up[u][i] , v))
                {
                        u = up[u][i];
                }
        }
        return up[u][0];
}

void build(int node,int lo ,int hi)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo];
                return;
        }
        int mid = (lo+hi)>>1;

        build(node*2,lo,mid);
        build(node*2+1,mid+1,hi);

        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

void update(int node,int lo,int hi,int pos,int val)
{
        if(lo==hi)
        {
                Tree[node] = ara[lo] = val; // if add then += val
                return;
        }
        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                update(node*2,lo,mid,pos,val);
        }
        else
        {
                update(node*2+1,mid+1,hi,pos,val);
        }
        Tree[node] = Tree[node*2]+Tree[node*2+1];
}

int query(int node,int lo,int hi,int i,int j)
{

        if(hi<i || lo>j)
        {
                return 0;
        }
        if(lo>=i && hi <=j)
        {
                return Tree[node];
        }

        int mid = (lo+hi)>>1;

        int x = query(node*2,lo,mid, i ,j );

        int y = query(node*2+1,mid+1,hi,i,j);

        return x+y;
}

int Vertex_sum_query(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return query(1,1,ET2.size()-1,p[u].first , p[v].first);
        }
        if(is_ancestor(v,u))
        {
                return query(1,1,ET2.size()-1, p[v].first , p[u].first);
        }

        int l = lca(u,v);

        int x = query(1,1,ET2.size()-1,p[l].first,p[u].first);
        int y = query(1,1,ET2.size()-1,p[l].first,p[v].first);
        int ans = x+y - query(1,1,ET2.size()-1,p[l].first , p[l].first); // lca two time count hoye jabe bole , since it is vertex . [in edge query eta hoy na]

        return ans;
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        int v[n+5];
        v[0] = 0;
        for(int i=1;i<=n;i++)
        {
                cin>>v[i]; // value on each vertex
        }
        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        ET2.push_back(0); // to make ET2 1 based for segment tree

        dfs(1,1);


        for(int i=1;i<ET2.size();i++)
        {

                if(vis1[ET2[i]]==false)
                {
                        vis1[ET2[i]] = true;
                        p[ET2[i]].first = i;
                }
                else
                {
                        p[ET2[i]].second = i;
                }
        }

        for(int i=1;i<=n;i++)
        {
                ara[p[i].first] = v[i];
                ara[p[i].second] = -v[i];
        }

        build(1,1,ET2.size()-1);

        int q;
        cin>>q;
        cout<<"Vertex Sum Query: "<<endl;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int u,w;
                        cin>>u>>w;

                        update(1,1,ET2.size()-1 , p[u].first , w );
                        update(1,1,ET2.size()-1 , p[u].second , -w);
                }
                else
                {
                        int u,v;
                        cin>>u>>v;
                        cout<<Vertex_sum_query(u,v)<<endl;



                }
        }


        return 0;


}

/*

10
7 3 6 11 10 13 9 13 16 3
1 2
2 3
2 4
2 5
4 6
4 7
1 8
8 9
8 10

10
2 4 8
2 3 3
2 3 10
2 7 9
2 7 1
1 4 100
1 2 200
2 6 8
1 9 100
2 9 10



O/P:
Vertex Sum query :
34
6
32
59
30
333
116

*/




==========================================TYPE - 03====================================
EULER TOUR ON FOR LCA O(1)
=======================================================================================
=======================================================================================
=======================================================================================



// ============= Euler Tour type -  03 ========== LCA in O(1) ============

// ET3 = 1 2 3 2 4 6 4 7 4 2 5 2 1 8 9 8 10 8 1

// in this tour technique (child - father - child) is always maintained , so between 2 child , their father shall be present (not grand father though)
// So query(u,v) means :
//                u first appear in ET3 and v first appear in ET3 er moddhe jetar depth lowest setai LCA ;
//                we find this using sparse table O(1) , segment tree O(logn)





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
const int N = 1e5;
vector<int>graph[N];
vector<int>ET3;
vector<int>p(N,-1); //p[v] = v first appear in ET3;
bool vis[N];
int dept[N];
const int L = log2(N);
int st[N][L+1];
int Log2[N];

void dfs(int s)
{
        vis[s] = true;
        ET3.push_back(s);
        for(auto child: graph[s])
        {
                if(vis[child])
                {
                        continue;
                }
                dept[child] = dept[s]+1;

                dfs(child);

                ET3.push_back(s);
        }
}

void pre()
{
        Log2[0] = 0;
        Log2[1] = 0;
        Log2[2] = 1;
        for(int i=3;i<N;i++)
        {
                Log2[i] = Log2[i/2]+1;
        }
}

void sparse_table()
{
        for(int i=0;i<ET3.size();i++)
        {
                st[i][0] = ET3[i];
        }

        int l = Log2[ET3.size()];

        for(int i=1;i<=l;i++)
        {
                for(int j=0;j+(1<<i)<=ET3.size();j++) // j+(1<<i)-1<ET3.size()
                {
                        int a = st[j][i-1];

                        int b = st[j+(1<<(i-1))][i-1];

                        //Sort of like dp
                        //instead of storing the minimum , We are storing the Vertex with minimum detph

                        if(dept[a]<dept[b])
                        {
                                st[j][i] = a;
                        }
                        else
                        {
                                st[j][i] = b;
                        }
                }
        }
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        pre();


        int n;
        cin>>n;
        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        dfs(1);

        for(int i=0;i<ET3.size();i++)
        {
                if(p[ET3[i]]==-1)
                {
                        p[ET3[i]] = i;
                }
        }

        sparse_table();


        int q;
        cin>>q;


        cout<<"LCAs : "<<endl;
        while(q--)
        {
                int u,v;
                cin>>u>>v;


                int a = min(p[v],p[u]); // p[u] first pos of u , p[v] first pos of v in ET3;
                int b = max(p[v],p[u]);

                int i = Log2[b-a+1];

                int vertex1 = st[a][i];
                int vertex2 = st[b-(1<<i)+1][i];

                if(dept[vertex1]<dept[vertex2])
                {
                        cout<<vertex1<<endl;
                }
                else
                {
                        cout<<vertex2<<endl;
                }


        }



        return 0;




}
/*

10
1 2
2 3
2 4
2 5
4 6
4 7
1 8
8 9
8 10

6
1 8
8 7
6 7
10 9
3 4
3 5

O/P:

LCAs :
1
1
4
8
2
2




*/









================================================================================================
================================================================================================
================================================================================================
================================================================================================
================================================================================================
=========================THE END================================================================
================================================================================================
================================================================================================
================================================================================================
================================================================================================
================================================================================================


================================Euler Tour =================================
https://codeforces.com/blog/entry/18369
============================================================================


===================== Summing what I know about Euler Tour ===================


Type - 01 : Tour on Edge
================================
1.Edge update query (done)
2.Subtree Edges sum. (done)
3.Edge sum query in the form of Q(U,V) sum from U to V edges (done)



Type - 02 : Tour on Vertex
=================================
1.Vertex update query(done)
2.Subtree sum Query(done)
3.Vertex sum query in the form of Q(U,V) sum from U to V vertex .(done)


Type - 03 : 1.For finding LCA in both O(logn)segment tree and O(1)sparse table time.(done)
=================================











Re Rooting and Minimum Query are Left to Learn later on



