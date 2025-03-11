// Mobius inclusion exclusion

// Finding the number of co-primes pairs


   
const int N = 1e6+100;
int cnt[N];
bool sieve[N];
int mobius[N];
int D[N];
int arr[N];

void pre()
{
        memset(sieve, true, sizeof(sieve));

        for(int i=2;i<N;i++)
        {
                if(sieve[i])
                {
                        cnt[i] = 1;

                        for(int j=i+i;j<N;j += i)
                        {
                                sieve[j] = false;

                                if(cnt[j] == -1)
                                {
                                        continue;
                                }

                                cnt[j]++;

                                if(j % (i*i) ==0)
                                {
                                        cnt[j] = -1;
                                }
                        }
                }
        }

        mobius[1] = 1;
        mobius[2] = -1;

        for(int i=3;i<N;i++)
        {
                if(cnt[i]==-1)
                {
                        mobius[i] = 0;
                }
                else if(cnt[i]%2==0)
                {
                        mobius[i] = 1;
                }
                else 
                {
                        mobius[i] = -1;
                }
        }


}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        vector<int>v;
        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
                arr[a]++;
        }

        pre();

        for(int d = N-50; d >= 1; d--)
        {
                int count = 0;
                for(int i = d; i<N; i += d)
                {
                        count += arr[i];
                }

                D[d] = count;
        }


        int ans = n*(n-1);
        ans /= 2;

        for(int i=2;i<N;i++)
        {
                ans += mobius[i]* (D[i]*(D[i]-1))/2; // Here mobius[i] works as a sign for inclusion exclusion.

                
        }

        cout<<ans<<endl;



}
