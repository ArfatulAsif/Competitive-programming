https://leetcode.com/discuss/study-guide/2347639/A-comprehensive-guide-and-template-for-monotonic-stack-based-problems


https://leetcode.com/discuss/study-guide/2703748/Monotonic-stack-study-summary [For Topic Wise]
1. Next greater / lesser problem , Previous greater / lesser problem:
2. Construct binary tree from given array
3. Subsequece problem[Very Important]
5. Subarray problem [Very Very Important , counting sub array with maximum , minimum property]
6. monotonic queue together with binary search
7. Monotonic stack but manily compare current with top of stack then determine whether add or not current
10. Sort subarry / remove subarry in order to make whole array ascending


===================== 1.Next Greater =================
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

//Next Greater Element 
//Monotonic non-increasing stack 

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
        }
        vector<int>nxtGreater(n,-1); // keep the indices
        
        stack<int>s;
        
        for(int i=0;i<n;i++)
        {
                while(!s.empty() && v[s.top()]<v[i])
                {
                        nxtGreater[s.top()] = i;
                        s.pop();
                }
                s.push(i);
        }

        for(int i=0;i<n;i++)
        {
                cout<<nxtGreater[i]<<" ";
        }
        cout<<endl;



}



=========================== 2. Previous Greater ==============
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

//Previous Greater Element
//Monotonic strickly decreasing stack

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
        }

        vector<int>prevGreater(n,-1);//keeps the indexes

        stack<int>st;

        for(int i=0;i<n;i++)
        {
                while(!st.empty() && v[st.top()]<= v[i])
                {
                        st.pop();
                }

                if(!st.empty())
                {
                        prevGreater[i] = st.top();
                }
                st.push(i);
        }

        for(int i=0;i<n;i++)
        {
                cout<<prevGreater[i]<<" ";
        }
        cout<<endl;


}



================================== 3. Next Smaller (strictly smaller) ==========

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

//Next Smaller Element
//Monotonic non-decreasing stack

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
        }

        vector<int>nxtSmaller(n,-1); // indexes

        stack<int>st;

        for(int i=0;i<n;i++)
        {
                while(!st.empty() && v[st.top()]> v[i])
                {
                        
                        nxtSmaller[st.top()] = i;
                        st.pop();
                }
                st.push(i);
        }

        for(int i=0;i<n;i++)
        {
                cout<<nxtSmaller[i]<<" ";
        }
        cout<<endl;

}




============================= 4. Previous Smaller (strictly smaller) ========

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

//Previous smaller element
//Monotonic increasing stack

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
        }

        vector<int>prevSmaller(n,-1); //indexes

        stack<int>st;
        for(int i=0;i<n;i++)
        {
                while(!st.empty() && v[st.top()]>=v[i])
                {
                        st.pop();
                }
                if(!st.empty())
                {
                        prevSmaller[i] = st.top();
                }
                st.push(i);
        }

        for(int i=0;i<n;i++)
        {
                cout<<prevSmaller[i]<<" ";
        }
        cout<<endl;



}











========================= 5. Minimum element in a window, using deque ==================





// Minimum element in a window, using deque



// https://cses.fi/problemset/task/3221/


const int N = 1e7+5;

int ara[N];




int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,k;
        cin>>n>>k;

        int x,a,b,c;

        cin>>x>>a>>b>>c;

        ara[0] = x;

        for(int i=1;i<n;i++)
        {
                x = (a*1LL*x+b)%c;

                ara[i] = x;
        }

        deque<int>d;

        int i=0,j=0;

        int Xor=0;

        while(j<n)
        {
                if(j-i+1 < k)
                {
                        while(!d.empty() && ara[d.back()] >= ara[j])
                        {
                                d.pop_back();
                        }

                        d.push_back(j);

                        j++;
                }

                else 
                {
                        while(!d.empty() && ara[d.back()] >= ara[j])
                        {
                                d.pop_back();
                        }

                        d.push_back(j);

                        Xor ^= ara[d.front()];   // Minimum element in the k-length window


                        while( !d.empty() && i >= d.front())
                        {
                                d.pop_front();
                        }

                        i++,j++;
                }
        }


        cout<<Xor<<endl;



        

}














