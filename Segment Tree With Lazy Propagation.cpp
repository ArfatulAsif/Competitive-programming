//Arfatul Islam Asif

//Sum update Query 

const int N = 1e5+100;

struct node
{
        int val;
        int lazy;

} Tree[4*N];

int ara[N];


void propagate(int node,int lo,int hi)
{
        int temp = Tree[node].lazy;

        Tree[node*2].lazy += temp;
        Tree[node*2+1].lazy += temp;
        Tree[node].lazy = 0;

        int mid = (lo+hi)>>1;

        Tree[node*2].val += (mid-lo+1)*temp;  // lazy pawar sathe sathei  sob node e add  kore disi , tai query korar somoy node er Lazy add korte hobe na
        Tree[node*2+1].val +=(hi-(mid+1)+1)*temp; // // lazy pawar sathe sathei sob node e add  kore disi , tai query korar somoy node er Lazy add korte hobe na
}


void build(int node,int lo,int hi)
{
        if(lo==hi)
        {
                Tree[node].val = ara[lo];
                return;
        }

        int mid = (lo+hi)>>1;

        build(node*2,lo,mid);
        build(node*2+1 , mid+1,hi);

        Tree[node].val = Tree[node*2].val + Tree[node*2+1].val;
}

void update(int node,int lo,int hi,int i,int j , int val)
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
                Tree[node].lazy += val;
                Tree[node].val += (hi-lo+1)*val; // ekhanei sob node e add  kore disi , tai query korar somoy node er Lazy add korte hobe na

                return;
        }

        int mid = (lo+hi)>>1;
        update(node*2,lo,mid,i,j,val);
        update(node*2+1,mid+1,hi,i,j,val);

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


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
                cin>>ara[i];
        }

        build(1,1,n);

        int q;
        cin>>q;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int i,j,x;
                        cin>>i>>j>>x;
                        update(1,1,n,i,j,x);
                }
                else
                {
                        int i,j;
                        cin>>i>>j;
                        cout<<query(1,1,n,i,j)<<endl;

                }
        }

        return 0;




}

/*

10

1 2 3 4 5 6 7 8 9 10

8
2 2 4
2 1 4
1 2 5 1
2 2 4
1 4 10 10
2 5 7
1 5 5 100
2 5 5

*/
