//all Numbers are distinct thats why ordered_set and MO's algorithm works  . Else use MergeSort Tree


//spoj mkth number soln : TLE (but should works on faster judge)



const int N = 1e5+10;
const int M = 5000+10;

int ans[M];


struct Query
{
    int l, r, k ,  idx;

};

int block;

bool cmp(Query a, Query b)
{
        if(a.l/block == b.l/block)
        {
                return a.r<b.r;
        }
        return (a.l/block)<(b.l/block);
}

vector<Query>Q;


//All NUMBERS are different thats why this solution works using Ordered_SET

void results(vector<int> &v , int m)
{

        block = sqrt(v.size()+0.0);  // USE block = 666; way faster

        sort(Q.begin() , Q.end() , cmp);

        int currL = 0;
        int currR = 0;



        ordered_set S;

        for(int i=0;i<m;i++)
        {
                int L = Q[i].l;
                int R = Q[i].r;
                int k = Q[i].k;
                int idx = Q[i].idx;

                while(currL>L)
                {
                        S.insert(v[currL-1]);
                        currL--;
                }
                while(currR<=R)
                {
                        S.insert(v[currR]);
                        currR++;
                }

                while(currL<L)
                {
                        int a = v[currL];
                        S.erase(a);
                        currL++;
                }

                while(currR>R+1)
                {
                        int a = v[currR-1];
                        S.erase(a);
                        currR--;
                }


                ans[idx] = *S.find_by_order(k-1); // 0 based bole k-1 will refer to k-th

        }


}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;

        vector<int>v;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
        }

        for(int g=0;g<m;g++)
        {
                int i,j,k;
                cin>>i>>j>>k;
                Q.push_back({i-1,j-1,k,g});
        }

        results(v,m);

        for(int i=0;i<m;i++)
        {
                cout<<ans[i]<<endl;
        }





}
