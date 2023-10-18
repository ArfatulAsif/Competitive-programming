
========================== 2D BIT =================

========================== Single Cell update - GRID Query (SUM)  =======


//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

//https://www.spoj.com/problems/MATSUM/

const int N = 1030;
int GRID[N][N];
int BIT[N][N];

void update(int x,int y,int num)
{
        for( ; x<N ; x += (x&-x))
        {
                int col = y;
                for( ; col<N ; col += (col&-col))
                {
                       
                        BIT[x][col] +=num;
                }
               
        }
}

int query(int x,int y)
{
        int ans = 0;
        for(;x>0 ; x-= (x&-x))
        {
                int col = y;
                for(;col>0 ; col -=(col&-col))
                {
                        ans += BIT[x][col];
                }
        }

        return ans;
}

int Query(int x1,int  y1 , int x2,int y2)
{
      
        int ans = query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);

        return ans;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        
        int t;
        cin>>t;

        while(t--)
        {
                int n;
                cin>>n;
                
                for(int i=0;i<N;i++)
                {
                        for(int j=0;j<N;j++)
                        {
                                GRID[i][j] = 0;
                                BIT[i][j] = 0;
                        }
                }

                while(true)
                {
                        string s;
                        cin>>s;
                        if(s=="END")
                        {
                                break;
                        }
                        if(s=="SET")
                        {
                                int x,y,num;
                                cin>>x>>y>>num;
                                x++;
                                y++;
                                update(x,y,-GRID[x][y]); //clear previous
                                update(x,y,num);
                                GRID[x][y] = num;
                               
                                
                        }
                        else 
                        {
                                int x1,y1,x2,y2;
                                cin>>x1>>y1>>x2>>y2;
                                x1++;
                                y1++;
                                x2++;
                                y2++;

                                cout<<Query(x1,y1,x2,y2)<<endl;
                        }

                }
        }

        return 0;


}



============================== 2. Grid Update - Grid Query (SUM) ===========

// Copied From Shohag vai template

//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int N = 1010;

struct BIT2D
{
        long long M[N][N][2], A[N][N][2];
        BIT2D()
        {
                memset(M, 0, sizeof M);
                memset(A, 0, sizeof A);
        }
        void upd2(long long t[N][N][2], int x, int y, long long mul, long long add)
        {
                for (int i = x; i < N; i += i & -i)
                {
                        for (int j = y; j < N; j += j & -j)
                        {
                                t[i][j][0] += mul;
                                t[i][j][1] += add;
                        }
                }
        }
        void upd1(int x, int y1, int y2, long long mul, long long add)
        {
                upd2(M, x, y1, mul, -mul * (y1 - 1));
                upd2(M, x, y2, -mul, mul * y2);
                upd2(A, x, y1, add, -add * (y1 - 1));
                upd2(A, x, y2, -add, add * y2);
        }
        void GridUpdate(int x1, int y1, int x2, int y2, long long val)
        {
                upd1(x1, y1, y2, val, -val * (x1 - 1));
                upd1(x2, y1, y2, -val, val * x2);
        }
        long long query2(long long t[N][N][2], int x, int y)
        {
                long long mul = 0, add = 0;
                for (int i = y; i > 0; i -= i & -i)
                {
                        mul += t[x][i][0];
                        add += t[x][i][1];
                }
                return mul * y + add;
        }
        long long query1(int x, int y)
        {
                long long mul = 0, add = 0;
                for (int i = x; i > 0; i -= i & -i)
                {
                        mul += query2(M, i, y);
                        add += query2(A, i, y);
                }
                return mul * x + add;
        }
        long long GridQuery(int x1, int y1, int x2, int y2)
        {
                return query1(x2, y2) - query1(x1 - 1, y2) - query1(x2, y1 - 1) + query1(x1 - 1, y1 - 1);
        }
};
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        BIT2D t;

        int n, m;
        cin >> n >> m;


        for (int i = 1; i <= n; i++)
        {
                for (int j = 1; j <= m; j++)
                {
                        int k;
                        cin >> k;
                        t.GridUpdate(i, j, i, j, k);
                }
        }
        int q;
        cin >> q;
        while (q--)
        {
                int ty, x1, y1, x2, y2;
                cin >> ty;
                if (ty == 1)
                {
                        long long val;
                        cin >> x1 >> y1 >> x2 >> y2 >> val;
                        t.GridUpdate(x1, y1, x2, y2, val); // add val from top-left(x1, y1) to bottom-right (x2, y2);
                }
                else
                {
                        cin >> x1 >> y1 >> x2 >> y2;
                        cout << t.GridQuery(x1, y1, x2, y2) << '\n'; // output sum from top-left(x1, y1) to bottom-right (x2, y2);
                }
        }
        return 0;
}

====================================================================


========================= Grid Update - Grid Query (XOR) =========

//Modified Grid Update - Grid Query (sum) : shohag vai template

//Intermediary
//Young kid on the block
//AIAsif try's Continuing the journey
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int N = 1010;

struct BIT2D
{
        long long M[N][N][2], A[N][N][2];
        BIT2D()
        {
                memset(M, 0, sizeof M);
                memset(A, 0, sizeof A);
        }
        void upd2(long long t[N][N][2], int x, int y, long long mul, long long add)
        {
                for (int i = x; i < N; i += i & -i)
                {
                        for (int j = y; j < N; j += j & -j)
                        {
                                t[i][j][0] ^= mul;
                                t[i][j][1] ^= add;
                        }
                }
        }
        void upd1(int x, int y1, int y2, long long mul, long long add)
        {
                upd2(M, x, y1, mul, mul * ((y1 - 1)&1));
                upd2(M, x, y2, mul, mul * (y2&1));
                upd2(A, x, y1, add, add * ((y1 - 1)&1));
                upd2(A, x, y2, add, add * (y2&1));
        }
        void GridUpdate(int x1, int y1, int x2, int y2, long long val)
        {
                upd1(x1, y1, y2, val, val * ((x1 - 1)&1));
                upd1(x2, y1, y2, val, val * (x2&1));
        }
        long long query2(long long t[N][N][2], int x, int y)
        {
                long long mul = 0, add = 0;
                for (int i = y; i > 0; i -= i & -i)
                {
                        mul ^= t[x][i][0];
                        add ^= t[x][i][1];
                }
                return mul * (y&1) ^ add;
        }
        long long query1(int x, int y)
        {
                long long mul = 0, add = 0;
                for (int i = x; i > 0; i -= i & -i)
                {
                        mul ^= query2(M, i, y);
                        add ^= query2(A, i, y);
                }
                return mul * (x&1) ^ add;
        }
        long long GridQuery(int x1, int y1, int x2, int y2)
        {
              
                return query1(x2, y2) ^ query1(x1 - 1, y2) ^ query1(x2, y1 - 1) ^ query1(x1 - 1, y1 - 1);
        }
}T;
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;

        //BIT2D T; Since N*N is quite bigger and inside struct don't declare like this

        while(m--)
        {
                int a;
                cin>>a;
                if(a==2)
                {
                        int x1,y1,x2,y2,val;
                        cin>>x1>>y1>>x2>>y2>>val;

                        T.GridUpdate(x1,y1,x2,y2,val);
                }
                else 
                {
                        int x1,y1,x2,y2;
                        cin>>x1>>y1>>x2>>y2;

                        cout<<T.GridQuery(x1,y1,x2,y2)<<endl;

                }
        }


        return 0;

       
}
https://codeforces.com/contest/341/problem/D



