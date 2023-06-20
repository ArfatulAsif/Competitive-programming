//Intermediary
//Young kid on the block
//AIAsif try's "Continuing the journey"

//concept is using segment tree , where each node will store indexes in sorted order : kind of like MergeSort

//K-th minimum in Range :

const int N = 1e5+10;

vector<int>Tree[4*N]; // each node will store (indexes) in sorted order
vector<pair<int,int>>A;


void build(int node,int lo,int hi)
{
        if(lo==hi)
        {
                Tree[node].push_back(A[lo].second); // indexex will be stored at every node in sorted order
                return;
        }

        int mid = (lo+hi)>>1;

        build(node*2,lo,mid);
        build(node*2+1 , mid+1,hi);

        merge(Tree[node*2].begin() , Tree[node*2].end() , Tree[node*2+1].begin() , Tree[node*2+1].end() , back_inserter(Tree[node])); // this merge fuction works excatly like merge in mergeSort [watch gfg]


}

int query(int node ,int lo,int hi,int i,int j,int k)
{
        if(lo==hi)
        {
                return Tree[node][0];
        }
        int mid = (lo+hi)>>1;

        int a = lower_bound(Tree[node*2].begin() , Tree[node*2].end() , i)-Tree[node*2].begin();
        int b = upper_bound(Tree[node*2].begin() , Tree[node*2].end() , j)-Tree[node*2].begin();

        int M = b-a; // [i:j] range er moddhe koyta indexes ase in Tree[node*2] Tee

        if(M>=k)
        {
                //Tree[node*2] tee thaka indexes er songkha greater than K hoy taile k-th minimum er index will exits here
                return query(node*2 , lo , mid , i , j , k);
        }
        else
        {
                //let say k = 6 and M = 4 :
                //er ortho hocce [i:j] range er 4 ta indexes exists kore Tree[node*2] te

                // baki 2 ta indexes exits here : k-M

                //Keep in mind that elements at the right childs > elements at the left childs . thats why we have to pass k-M here to get k-th minimum number er index

                return query(node*2+1 , mid+1 , hi , i , j , k-M);
        }


}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n , q;
        cin>>n>>q;

        vector<int>v;
        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
        }

        for(int i=0;i<n;i++)
        {
                A.push_back({v[i] , i}); // indexes are  0-based
        }

        sort(A.begin() , A.end()); // according to first element Indexes will be sorted too

        build(1,0,n-1);

        while(q--)
        {
                int i,j,k;
                cin>>i>>j>>k; //i,j 1-based

                int kthminimumdx = query(1,0,n-1,i-1,j-1,k);  // pass 0-based

                cout<<v[kthminimumdx]<<endl;
        }

        return 0;






}
