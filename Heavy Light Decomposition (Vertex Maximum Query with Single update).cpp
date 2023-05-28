
//Arfatul Islam Asif


//The technique is All heavy path er node gula visit hobe consecutive time eeee
//So segment tree based on visit time will provide query ans for two vertex who are on same Heavy Path


const int N = 2e5+100;
vector<int>graph[N];
int level[N];


//LCA Part
const int L = log2(N);
int lca_din[N];
int lca_dout[N];
int up[N][L+1];
int tim_lca;




//SEGMENT Tree Part
int n; // to be taken input as no of vertex
struct node
{
        int val;
        int lazy;  // used the same tamplate as Range update [so thats why we kept the lazy] [although it is easily do able without lazy]
} Tree[4*N] ;
int ara[N];
int tin[N]; // most important array , in this array vertex on same heavy chain will have consecutive visiting time , [for vertex no it will give visiting no ] [ segment tree is built on visiting no]
            // tin[v]  = v visiting time
int tout[N];
int vis_tim_vertex[N];  // visiting time dile vertex no. return korbe [for build() in segment tree ]
int nxt[N]; //for DSU part
int subtree[N];
int tim;




//LCA

void dfs(int s,int par,int lev)
{
        lca_din[s] = tim_lca++;
        up[s][0] = par;
        level[s] = lev;

        for(int i=1;i<=L;i++)
        {
                up[s][i] = up[up[s][i-1]][i-1];
        }

        for(auto child: graph[s])
        {
                if(child==par)
                {
                        continue;
                }
                dfs(child,s,lev+1);
        }
        lca_dout[s] = tim_lca++;

}

bool is_ancestor(int u,int v)
{
        return (lca_din[u]<=lca_din[v] && lca_dout[u]>=lca_dout[v]);
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




//Heavy edge on graph[s][0]

void dfs1(int s, int par)
{

        subtree[s] = 1;

        for(auto &child : graph[s]) // & child pathate hobe
        {
                if(child==par)
                {
                        continue;
                }

                dfs1(child,s);

                subtree[s] += subtree[child];

                if(subtree[child]>subtree[graph[s][0]])
                {
                        swap(child,graph[s][0]); // &child pathate hobe for swap operation
                }

        }

}




//Heavy light decomposition er DSU part
void dfs_hld(int s,int par)
{

        tin[s] = ++tim;
        vis_tim_vertex[tim] = s;

        for(auto child : graph[s])
        {
                if(child==par)
                {
                        continue;
                }

                if(child==graph[s][0])
                {
                        nxt[child] = nxt[s]; // heavy child gulake ekta dsu chain he haralam , nxt[child] = chain er up most vertex return korbe
                }
                else
                {
                        nxt[child] = child;
                }

                dfs_hld(child,s);

        }
        tout[s] = tim;
}







void propagate(int node ,int lo,int hi)
{
        int temp = Tree[node].lazy;

        Tree[node*2].lazy += temp;
        Tree[node*2+1].lazy += temp;

        int mid = (lo+hi)>>1;

        Tree[node*2].val += (mid-lo+1)*temp;  // lazy pawar sathey sathey value node e add kore dilam jate query er somoy add kora na lage
        Tree[node*2+1].val += (hi-(mid+1)+1)*temp; // lazy pawar sathey sathey value node e add kore dilam jate query er somoy add kora na lage

        Tree[node].lazy = 0;
}


void build(int node,int lo,int hi) // indexing visiting time diye
{
        if(lo==hi)
        {
                Tree[node].val = ara[vis_tim_vertex[lo]]; // lo th time e je vertex visit hobe te holo vis_tim_vertex[lo]
                return;
        }

        int mid = (lo+hi)>>1;

        build(node*2,lo,mid);
        build(node*2+1,mid+1,hi);

        Tree[node].val = max(Tree[node*2].val , Tree[node*2+1].val );
}


void update(int node,int lo,int hi,int i,int j ,int val)
{
        if(Tree[node].lazy>0)
        {
                propagate(node,lo,hi);
        }
        if(hi<i || lo>j)
        {
                return;
        }
        if(lo>=i && hi<=j)
        {
                Tree[node].val += (hi-lo+1)*val;
                Tree[node].lazy += val;
                return;
        }

        int mid = (lo+hi)>>1;

        update(node*2 , lo , mid , i, j,val);
        update(node*2+1 , mid+1 , hi, i, j, val);

        Tree[node].val = max(Tree[node*2].val , Tree[node*2+1].val );

}

int query(int node,int lo,int hi,int i,int j)
{
        if(Tree[node].lazy>0)
        {
                propagate(node,lo,hi);
        }
        if(hi<i || lo>j)
        {
                return 0;
        }
        if(lo>=i && hi<=j)
        {
                return Tree[node].val;
        }

        int mid = (lo+hi)>>1;

        int x = query(node*2,lo,mid,i,j);
        int y = query(node*2+1,mid+1,hi,i,j);

        return max(x,y);
}





//Queries  Started

int dist(int u,int v) // given unweighted edges
{
        return level[u]+level[v] - 2*level[lca(u,v)];
}




int query_up(int l,int u) // l is ancestor of u
{
        int res = 0;
        while(nxt[u]!=nxt[l])
        {
                res = max(res,query(1,1,n, tin[nxt[u]] , tin[u]));
                u = up[nxt[u]][0]; //next heavy chain e jump
        }

        res = max(res , query(1,1, n , tin[l] , tin[u]) ); // l included

        return res;
}

int maximum_query_hld(int u,int v)
{
        if(is_ancestor(u,v))
        {
                return query_up(u,v);
        }
        if(is_ancestor(v,u))
        {
                return query_up(v,u);
        }

        int l = lca(u,v);
        int x = query_up(l,u);
        int y = query_up(l,v);

        return max(x , y);
}


void update_up(int l,int u,int val) // l is ancestor of u
{
        while(nxt[u]!=nxt[l])
        {
                update(1,1,n,tin[nxt[u]],tin[u],val);
                u = up[nxt[u]][0];
        }
        update(1,1,n,tin[l],tin[u],val); // including l
}

void update_query_hld(int u,int v,int val) // u to v er path e thaka sob vertex er value er sathe val add
{
        if(is_ancestor(u,v))
        {
                update_up(u,v,val);
                return;
        }
        if(is_ancestor(v,u))
        {
                update_up(v,u,val);
                return;
        }
        int l = lca(u,v);
        update_up(l,u,val);
        update_up(l,v,val);

        update_up(l,l,-val); // l updated twice thats why ekber minus

}


void hld()
{
        dfs(1,1,1); // for LCA up[1][0] = 1; for is_ancestor to work properly

        dfs1(1,0);

        dfs_hld(1,0);

        build(1,1,n);
}





int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        cin>>n;




        for(int i=1;i<=n;i++)
        {
                cin>>ara[i];
        }

        for(int i=0;i<n-1;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                graph[y].push_back(x);
        }

        hld();



        int q;
        cin>>q;

        cout<<"Answer to the queries : "<<endl;

        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int u,x;
                        cin>>u>>x;
                        int val = maximum_query_hld(u,u);
                        update_query_hld(u,u,-val); //clearing
                        update_query_hld(u,u,x);

                }
                else
                {
                        int u, v;
                        cin>>u>>v;
                        cout<<maximum_query_hld(u,v)<<endl;
                }
        }


        return 0;



}


/*

12

4 10 9 6 7 6 4 1 3 2 7 9

1 2
1 3
3 4
3 5
4 8
4 9
2 6
2 7
7 10
7 11
10 12


8
2 1 7
2 5 12
1 2 5
2 5 12
2 8 9
1 3 100
2 12 11
2 7 5

Ans to the queries:

10
10
9
6
9
100


*/



==================================== Thanks to =============================================
https://github.com/Ashishgup1/Competitive-Coding/blob/master/Heavy%20Light%20Decomposition%20(HLD).cpp
============================================================================================
