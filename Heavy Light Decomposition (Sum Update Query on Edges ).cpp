//Arfatul Islam Asif

//Edges are basically like Vextex ;
// Lets say there is an edges directed away from root as [1-2] , we will store its value on ara[2] ; which means edge er value down vertex e thakbe [look down from root]

//This supports Range update , which euler tour doesnt

//The technique is All heavy path er node gula visit hobe consecutive time eeee
//So segment tree based on visit time will provide query ans for two vertex who are on same Heavy Path


const int N = 2e5+100;
vector<pair<int,int>>graph[N];
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
        int lazy;
} Tree[4*N] ;
int ara[N];
int tin[N]; // most important array , in this array vertex on same heavy chain will have consecutive visiting time , [for vertex no it will give visiting no ] [ segment tree is built on visiting no]
            // tin[v]  = v visiting time
int tout[N];
int vis_tim_vertex[N];  // visiting time dile vertex no return korbe [for build() in segment tree ]
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
                if(child.first==par)
                {
                        continue;
                }

                ara[child.first] = child.second; // ekhane value rakhlam  [ara[1] = 0]  cause all edges values are stored at the ara[down vertex] [ara[down-vertex]-ara[1] will give the path sum]
                dfs(child.first,s,lev+1);
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
                if(child.first==par)
                {
                        continue;
                }

                dfs1(child.first , s);

                subtree[s] += subtree[child.first];

                if(subtree[child.first]>subtree[graph[s][0].first])
                {
                        swap(child.first ,graph[s][0].first); // &child pathate hobe for swap operation
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
                if(child.first==par)
                {
                        continue;
                }

                if(child.first ==graph[s][0].first )
                {
                        nxt[child.first ] = nxt[s]; // heavy child gulake ekta dsu chain he haralam , nxt[child] = chain er up most vertex return korbe
                }
                else
                {
                        nxt[child.first ] = child.first;
                }

                dfs_hld(child.first ,s);

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

        Tree[node].val = Tree[node*2].val + Tree[node*2+1].val;
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

        Tree[node].val = Tree[node*2].val + Tree[node*2+1].val;

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

        return x+y;
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
                res += query(1,1,n, tin[nxt[u]] , tin[u]);
                u = up[nxt[u]][0]; //next heavy chain e jump
        }

        res += query(1,1, n , tin[l]+1 , tin[u]); // l excluded , cause its not vertex rather it is edge sum query and each edge value are stored at down vertex of the edge [root theke takale down jedike]

        return res;
}

int sum_query_hld(int u,int v)
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

        return x+y; // l is already excluded
}


void update_up(int l,int u,int val) // l is ancestor of u
{
        while(nxt[u]!=nxt[l])
        {
                update(1,1,n,tin[nxt[u]],tin[u],val);
                u = up[nxt[u]][0];
        }
        update(1,1,n,tin[l]+1,tin[u],val); // l is excluded
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

//        update_up(l,l,-val); // l is excluded already

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


        for(int i=0;i<n-1;i++)
        {
                int x,y,w;
                cin>>x>>y>>w;
                graph[x].push_back({y,w});
                graph[y].push_back({x,w});
        }

        hld();

        int q;
        cin>>q;

        cout<<"Ans to the queries: "<<endl;

        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int u,v,x;
                        cin>>u>>v>>x;
                        update_query_hld(u,v,x);
                }
                else
                {
                        int u, v;
                        cin>>u>>v;
                        cout<<sum_query_hld(u,v)<<endl;
                }
        }

        return 0;



}


/*

12

1 2 1
1 3 2
3 4 3
3 5 4
4 8 5
4 9 6
2 6 7
2 7 8
7 10 9
7 11 10
10 12 11

16
2 3 3
2 4 4
2 3 4
2 12 10
2 12 9
1 2 3 1
2 3 7
2 3 7
1 9 1 100
2 2 3
2 1 5
1 6 2 100
2 3 6
1 2 11 100
2 6 11
2 11 6

Ans to the queries:
0
0
3
11
40
13
13
105
107
212
325
325



*/
