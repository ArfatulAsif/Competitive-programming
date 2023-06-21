//Works for non-distinct elements too [unlike mo's algo]

const int M = 5000+100;
const int N = 100000+100;
int arr[N];

struct node
{
        int val;
        node *left;
        node *right;

        node(node *l , node *r , int v)
        {
                left = l;
                right = r;
                val = v;
        }

};

node *version[M];

//initially building an empty segment tree

void build(node *n , int lo,int hi)
{
        if(lo==hi)
        {
                n->val = 0;
                return;
        }
        n->left = new node(NULL,NULL,0);
        n->right = new node(NULL,NULL,0);

        int mid = (lo+hi)>>1;

        build(n->left,lo,mid);
        build(n->right,mid+1,hi);

        n->val = 0;

}

void update(node *prev, node *cur ,int lo,int hi,int pos,int val)
{
        if(pos>hi || pos<lo || lo>hi)
        {
                return;
        }
        if(lo==hi)
        {
                cur->val = prev->val;  //If elements are not distinct , we need to add previous values too : else just cur->val = 1 would works
                cur->val += val;  

                return;
        }
        int mid = (lo+hi)>>1;

        if(pos<=mid)
        {
                cur->right = prev->right;
                cur->left = new node(NULL , NULL,0);
                update(prev->left , cur->left , lo,mid,pos,val);
        }
        else
        {
                cur->left = prev->left;
                cur->right = new node(NULL , NULL,0);
                update(prev->right , cur->right , mid+1,hi,pos,val);
        }

        cur->val = cur->left->val + cur->right->val;


}

int query(node *j , node *i ,int lo,int hi,int k)
{
        if(lo==hi)
        {
                return lo;
        }
        int M = (j->left->val) - (i->left->val);


        int mid = (lo+hi)>>1;


        if(M>=k)
        {
                return query(j->left,i->left,lo,mid,k);
        }
        else
        {
                return query(j->right,i->right,mid+1,hi,k-M);
        }
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;

        version[0] = new node(NULL,NULL,0);


        build(version[0],1,n); // empty segment tree

        vector<int>v;

        for(int i=1;i<=n;i++)
        {
                int a;
                cin>>a;
                arr[i] = a;
                v.push_back(a);
        }
        sort(v.begin(),v.end());

        for(int i=1;i<=n;i++)
        {
                arr[i] = lower_bound(v.begin(),v.end(),arr[i])-v.begin() + 1; // converting all the elements to (0 < arr[i] <= n)
                //Here arr[i] = arr[i]-th element in vector v; //THis makes sure we getting the position rather than the number . This will make sure Histogram fenwick tree < N size
        }

        for(int i=1;i<=n;i++)
        {
                version[i] = new node(NULL,NULL,0); // this line must be here : if we allocate space for versions before here we shall get RUN TIME ERROR due to unused allocations
                update(version[i-1],version[i],1,n,arr[i],1);
        }

        while(m--)
        {
                int l,r,k;
                cin>>l>>r>>k;

                int idx = query(version[r],version[l-1],1,n,k);
                
                
                //(idx - 1)-th element in vector V is the ans : [think the Fenwick tree implementation of Order statistices tree 

                cout<<v[idx-1]<<endl;



        }

        return 0;




}
