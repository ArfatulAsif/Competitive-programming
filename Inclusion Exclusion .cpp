// excellent problem on  inclusion exclusion
// Nailed By me ,,, only only meee

Solution of the Problem is given below 
https://codeforces.com/contest/1295/problem/D


const int N = 1e6;
bool sieve[N];
vector<int>prime;

void pre()
{
        memset(sieve , true, sizeof(sieve));

        for(int i=2;i<N;i++)
        {
                if(sieve[i])
                {
                        for(int j=2;i*j<N;j++)
                        {
                                sieve[i*j] = false;
                        }
                }
        }
        for(int i=2;i<N;i++)
        {
                if(sieve[i])
                {
                        prime.push_back(i);
                }
        }
}

map<int,int> fact(int n)
{
        map<int,int>m;

        for(int i=0;i<prime.size();i++)
        {
                while(n%prime[i]==0)
                {
                        m[prime[i]]++;
                        n/=prime[i];
                }
        }
        if(n>1)
        {
                m[n]++;
        }

        return m;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        pre();

        int t;
        cin>>t;

        while(t--)
        {
                int a,m;
                cin>>a>>m;

                int test = __gcd(a,m);

                map<int,int>fact1;
                map<int,int>fact2;

                fact1 = fact(m);

                fact2 = fact(test);

                if(test!=1)
                {
                        for(auto x : fact2)
                        {
                                fact1[x.first]-=x.second;
                        }
                }


                vector<int>v;

                for(auto x : fact1)
                {
                        if(x.second!=0)
                        {
                                v.push_back(x.first);
                        }
                }

                int ans = (a+m-1)/test - (a-1)/test ;

                for(int i=1;i<(1<<v.size()); i++)
                {
                        int num = __builtin_popcountll(i);

                        int mul = 1;

                        for(int j=0;j<20;j++)
                        {
                                if(i&(1<<j))
                                {
                                        mul *= v[j];
                                }
                        }
                        if(num%2==0)
                        {
                                mul *= test;
                                ans += (a+m-1)/mul - (a-1)/mul;
                        }
                        else
                        {
                                mul *= test;
                                ans -= (a+m-1)/mul - (a-1)/mul;
                        }
                }

                cout<<ans<<endl;

        }

        return 0;


}
