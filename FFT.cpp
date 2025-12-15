//https://cses.fi/problemset/task/2111

// This implementation is based on Sohag vai's


const double PI = acos(-1);

struct base
{
        double a, b;
        base(double a = 0, double b = 0) : a(a), b(b)
        {

        }
        const base operator + (const base &c) const
        {
                
                return base( a +c.a, b + c.b);


        }
        const base operator - (const base &c) const
        {

                return base(a -c.a, b - c.b);
        }
        const base operator * (const base &c) const
        {
                return base(a *c.a - b * c.b, a * c.b + b * c.a);

        }
};

void fft(vector<base> &p, bool inv = 0)
{
        int n = p.size(), i = 0;

        for(int j = 1; j < n - 1; ++j)
        {
                for(int k = n >> 1; k > (i ^= k); k >>= 1);

                if(j < i) swap(p[i], p[j]);
        }
        for(int l = 1, m; (m = l << 1) <= n; l <<= 1)
        {
                double ang = 2 * PI / m;

                base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;

                for(int i = 0, j, k; i < n; i += m)
                {
                        for(w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn)
                        {
                                base t = w * p[j + l];

                                p[j + l] = p[j] - t;

                                p[j] = p[j] + t;
                        }
                }
        }
        if(inv)
                for(int i = 0; i < n; ++i) p[i].a/= n,  p[i].b/= n;
}

vector<long long> multiply(vector<int> &a, vector<int> &b)
{
        int n = a.size(), m = b.size(), t = n + m - 1, sz = 1;

        while(sz < t) sz <<= 1;

        vector<base> x(sz), y(sz), z(sz);

        for(int i = 0 ; i < sz; ++i)
        {
                x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);

                y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);

        }
        
        fft(x), fft(y);

        for(int i = 0; i < sz; ++i) z[i] = x[i] * y[i];


        fft(z, 1);


        vector<long long> ret(sz);


        for(int i = 0; i < sz; ++i) ret[i] = (long long) round(z[i].a);


        while((int)ret.size() > 1 && ret.back() == 0) ret.pop_back();


        return ret;

        
}






int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int k,n,m;
        cin>>k>>n>>m;

        vector<int> a(k+1), b(k+1);

        for(int i=0;i<n;i++)
        {
                int x;
                cin>>x;

                a[x]++;
        }


        for(int i=0;i<m;i++)
        {
                int x;
                cin>>x;

                b[x]++;
        }


        auto res = multiply(a,b);



        for(int i=2;i<=2*k;i++)
        {
                cout<<res[i]<<" ";
        }


        cout<<endl;










}
