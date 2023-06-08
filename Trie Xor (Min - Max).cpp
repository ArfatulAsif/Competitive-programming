
// Maximum Xor or Minimum Xor of two numbers in an array Using trie


const int N = 5e6;
int node[N][2]; //remember trie er edge information store kore (NOT node) . [ lets say 1 --> 2 e ekti edge directed , then er information store hobe  cnt[2] Te ::::::::::: ebong 2 =  node[1][] is like 1 = parent[2] er moto in directed tree :: age amra parent diye jump kortm : Now children diye jump]
int root = 0;                 //which means Edge info is actually stored in the 2nd child : and edges er characterictistics is (2 = node[1][]) refers to (1) ---> (2) edge
int avail = 0;
int cnt[N];


void ini()
{
        root = 0;
        avail = 0;
        for(int i=0;i<N;i++)
        {
                cnt[i] = 0;
        }
        node[root][0] = -1;
        node[root][1] = -1;
}

void Insert(int x)
{
        int cur = root;
        for(int i=30;i>=0;i--) // MSB must be at the top 1
        {
                if(x &(1<<i))
                {
                        if(node[cur][1]==-1)
                        {
                                avail++;
                                node[cur][1] = avail;
                                node[avail][0] = -1;
                                node[avail][1] = -1;
                        }
                        cur = node[cur][1];
                }
                else
                {
                        if(node[cur][0]==-1)
                        {
                                avail++;
                                node[cur][0] = avail;
                                node[avail][0] = -1;
                                node[avail][1] = -1;
                        }
                        cur = node[cur][0];
                }
                cnt[cur]++;

        }
}

void Remove(int x)
{
        int cur = root;
        for(int i=30;i>=0;i--) // MSB must be at the top 1
        {
                if(x &(1<<i))
                {
                        cur = node[cur][1];
                }
                else
                {
                        cur = node[cur][0];
                }
                cnt[cur]--;
        }
}

int Max_Xor(int x)
{
        int ans = 0;

        int cur = root;
        for(int i=30;i>=0;i--) // MSB must be at the top 1
        {
                if(x&(1<<i))
                {
                        if(node[cur][0]!=-1 && cnt[node[cur][0]]>0) // ei edge er info is being stored in cur = node[cur][0]
                        {
                                ans |= (1<<i);
                                cur = node[cur][0];
                        }
                        else
                        {
                                cur = node[cur][1]; // alternate will always exits
                        }

                }
                else
                {
                        if(node[cur][1]!=-1 && cnt[node[cur][1]]>0)
                        {
                                ans |= (1<<i);
                                cur = node[cur][1];
                        }
                        else
                        {
                                cur = node[cur][0];// alternate will always exits
                        }
                }
        }

        return ans;
}


int Min_Xor(int x)
{
        int cur =root;
        int ans = 0;

        for(int i=30;i>=0;i--)
        {
                if(x&(1<<i))
                {
                        if(node[cur][1]!=-1 && cnt[node[cur][1]]>0)
                        {
                                cur = node[cur][1];
                        }
                        else
                        {
                                ans |=(1<<i);
                                cur = node[cur][0];
                        }
                }
                else
                {

                        if(node[cur][0]!=-1 && cnt[node[cur][0]]>0)
                        {
                                cur = node[cur][0];
                        }
                        else
                        {
                                ans |=(1<<i);
                                cur = node[cur][1];
                        }
                }
        }

        return ans;
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n; // n>=2
        cin>>n;

        vector<int>v;

        ini();

        //Insert(0); // IN some problem you might need to use this where you have the choice of choosing any number of element : i.e n==1 is allowed

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
                Insert(a);
        }

        int mx = 0;

        for(int i=0;i<n;i++)
        {
                mx = max(mx, Max_Xor(v[i]));
        }

        int mn = INT_MAX;

        for(int i=0;i<n;i++)
        {
                Remove(v[i]); // we need to remove this else v[i]^v[i] = 0 which would be minimum [ this wont be a problem for Max finding ]

                mn = min(mn, Min_Xor(v[i]));

                Insert(v[i]);
        }


        cout<<"Max Xor : "<<mx<<" Min Xor : "<<mn<<endl;


        return 0;








}
