
//Just copy this and move on to the solution 

const int N = 1e6;
bool sieve[N];
int lp[N];
int k;


void pre()
{
        for(int i=0;i<N;i++)
        {
                sieve[i] = true;
        }
        for(int i=2;i<N;i++)
        {
                if(sieve[i])
                {
                        lp[i] = i;
                        for(int j=i+i;j<N;j+=i)
                        {
                                sieve[j] = false;
                                if(lp[j]==0)
                                {
                                        lp[j] = i;
                                }
                        }
                }
        }
}

map<int,int>fact(int n)
{
        map<int,int>m;

        while(n>1)
        {
                int a = lp[n];
                m[a]++;
                n/=lp[n];
        }
        if(n>1)
        {
                m[n]++;
        }

        return m;

}


int32_t main()
{

        pre(); // Remember to declare this in the main function


        int n;
        cin>>n;

        map<int,int>m;
        m = fact(n);

        for(auto x: m)
        {
                cout<<x.first<<" "<<x.second<<endl;
        }




}
