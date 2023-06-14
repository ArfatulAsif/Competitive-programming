//Intermediary
//Young kid on the block
//AIAsif try's "Continuing the journey"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>




vector<vector<int>>Multiply (vector<vector<int>> &one , vector<vector<int>> &two) //pass them as reference to save time
{
        vector<vector<int>>res;
        int D = one.size();
        for(int i=0;i<D;i++)
        {
                vector<int>temp;
                for(int j=0;j<D;j++)
                {
                        int cnt = 0;
                        for(int k=0;k<D;k++)
                        {
                                cnt += one[i][k]*two[k][j];
                        }
                        temp.push_back(cnt);
                }
                res.push_back(temp);
        }
        return res;

}




vector<vector<int>> Mat_Ex(vector<vector<int>> Mat , int b)  //don't pass Mat as reference
{
        vector<vector<int>> ans
                {
                        {1,0},
                        {0,1}
                }; //Identity Matrix {Adjust its dimension according to Mat

        while(b>0)
        {
                if(b&1)
                {
                        ans = Multiply(ans,Mat);
                }
                Mat = Multiply(Mat,Mat);
                b>>=1;
        }

        return ans;

}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        // For finding nth fibbonacci
        vector<vector<int>>Mat{
                {1,1},
                {1,0}
                };

        int n;

        cin>>n;   //n>2

        cout<<Mat_Ex(Mat , n-2)[0][0]<<endl;


        return 0;


}
