=============================== 1D BIT ===========

===================== 1.Point update - Range Query(sum)========


const int N = 2e5+100;
int BIT[N];
int n;

void update(int x,int val)
{
        for(; x<=n ; x+= (x&-x))
        {
                BIT[x]+=val;
        }
        return;
}

int query(int x)
{
        int sum = 0;
        for(;  x>0 ;  x-=(x&-x))
        {
                sum+= BIT[x];
        }
        return sum;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int q;
        cin>>n>>q;
        for(int i=1;i<=n;i++) // BIT should be 1 based index
        {
                int a;
                cin>>a;
                update(i,a);
        }

        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int b,c;
                        cin>>b>>c;
                        int val = query(b)-query(b-1);
                        update(b,-val);
                        update(b,c); //point update
                }
                else
                {
                        int l,r;
                        cin>>l>>r;

                        cout<<query(r)-query(l-1)<<endl;  //Range Query
                }
        }

        return 0;


}

====================================================

======================  2.Range Update - point Query(sum) ==========

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

const int N = 2e5+10;
int BIT[N];

void update(int x,int num)
{
        for(; x<N ; x+=(x&-x))
        {
                BIT[x]+=num;
        }
}

void Update(int l,int r,int num)
{
        update(l,num);
        update(r+1,-num);
}

int PointQuery(int x) // 1 based
{
        int ans = 0;
        for(; x>0 ; x-=(x&-x))
        {
                ans += BIT[x];
        }
        return ans;
}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
                int a;
                cin>>a;
                Update(i,i,a);
        }

        int q;
        cin>>q;

        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int l,r,val;
                        cin>>l>>r>>val;
                        Update(l,r,val);
                }
                else 
                {
                        int pos; // 1 based
                        cin>>pos;
                        cout<<PointQuery(pos)<<endl;
                }
        }

        return 0;


}

I/O

5
0 0 0 0 0
4
1 3 5 2
2 5
1 1 4 4
2 4

O/P
2
6

======================================================================

========================3.Range Update - Range Query(sum) ================

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

const int N = 2e5+100;
int BIT1[N];
int BIT2[N];

void update(int BIT[] , int x , int num)
{
        for(;x<N; x += (x&-x))
        {
                BIT[x] += num;
        }
}

void RangeUpdate(int l,int r,int num) // You have to use this method : cant use these above
{
        update(BIT1 , l , num);
        update(BIT1, r+1, -num);
        update(BIT2 , l , num*(l-1));
        update(BIT2,r+1,-num*r);
}

int query(int BIT[] ,int x)
{
        int sum = 0;
        for(;x>0;x-=(x&-x))
        {
                sum += BIT[x];
        }
        return sum;
}

int PrefixSum(int i)
{
        return query(BIT1,i)*i-query(BIT2 , i); // For explainantion check cp algo
}

int RangeQuery(int l,int r) // You have to use this method : cant use other above
{
        return PrefixSum(r)-PrefixSum(l-1);
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
                int a;
                cin>>a;
                RangeUpdate(i,i,a);
        }

        int q;
        cin>>q;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int l,r,val;
                        cin>>l>>r>>val;
                        RangeUpdate(l,r,val);
                }
                else 
                {
                        int l,r;
                        cin>>l>>r;
                        cout<<RangeQuery(l,r)<<endl;
                }
        }


}

I/O

7
1 2 3 4 5 6 7
4
1 3 5 2
2 2 4
1 2 6 1
2 3 6

O/P

13
28

====================================================================

============== Range Update - Range Query (xor) ==============

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


const int N = 2e5+100;
int BIT1[N];
int BIT2[N];

void update(int BIT[] , int x , int num)
{
        for(;x<N; x += (x&-x))
        {
                BIT[x] ^= num;
        }
}

void RangeUpdate(int l,int r,int num) // You have to use this method : cant use these above
{
        update(BIT1 , l ,  num);
        update(BIT1 , r+1, num);
        update(BIT2 , l ,  num*((l-1)&1) ); //While modifing Range Sum Query BIT :  num*(l-1) means num appears (l-1) times . So for Range Xor Query if (l-1) is even then xor = 0 . if (l-1) is odd then xor = num
        update(BIT2 , r+1, num*(r&1)); //While modifing Range Sum Query BIT :  num*r means num appears r times . So for Range Xor Query if r is even then xor = 0 . if r is odd then xor = num
}

int query(int BIT[] ,int x)
{
        int sum = 0;
        for(;x>0;x-=(x&-x))
        {
                sum ^= BIT[x];
        }
        return sum;
}

int PrefixXor(int i)
{
        return query(BIT1,i)*(i&1)^query(BIT2 , i);  //In Range Sum Query BIT . query(BIT1,i)*i meant query(BIT1,i) appeared i times . So for Range Xor BIT we just need to check whether i is odd or even like before
}

int RangeQuery(int l,int r) // You have to use this method : cant use other above
{
        return PrefixXor(r)^PrefixXor(l-1);
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
                int a;
                cin>>a;
                RangeUpdate(i,i,a);
        }

        int q;
        cin>>q;
        while(q--)
        {
                int a;
                cin>>a;
                if(a==1)
                {
                        int l,r,val;
                        cin>>l>>r>>val;
                        RangeUpdate(l,r,val);
                }
                else 
                {
                        int l,r;
                        cin>>l>>r;
                        cout<<RangeQuery(l,r)<<endl;
                }
        }


}

I/O
7
1 2 3 4 5 6 7
4
1 3 5 2
2 2 4
1 2 6 1
2 3 6

O/P
5
6

=================================================



