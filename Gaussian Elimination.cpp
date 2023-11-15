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


const double eps = 1e-9;

int Gauss(vector<vector<double>> a, vector<double> &ans)
{
        int n = (int)a.size(), m = (int)a[0].size() - 1;
        vector<int> pos(m, -1);
        double det = 1;
        int rank = 0;


        for (int col = 0, row = 0; col < m && row < n; ++col)
        {
                int mx = row;
                for (int i = row; i < n; i++)
                {
                        if (fabs(a[i][col]) > fabs(a[mx][col]))
                        {
                                mx = i;
                        }
                                
                }
                        
                if (fabs(a[mx][col]) < eps)
                {
                        det = 0;
                        continue;
                }
                for (int i = col; i <= m; i++)
                {
                        swap(a[row][i], a[mx][i]);
                }
                        
                if (row != mx)
                {
                        det = -det;
                }
                       
                det *= a[row][col];
                pos[col] = row;
                for (int i = 0; i < n; i++)
                {
                        if (i != row && fabs(a[i][col]) > eps)
                        {
                                double c = a[i][col] / a[row][col];
                                for (int j = col; j <= m; j++)
                                {
                                        a[i][j] -= a[row][j] * c;
                                }
                                        
                        }
                }
                ++row;
                ++rank;
        }
        ans.assign(m, 0);
        for (int i = 0; i < m; i++)
        {
                if (pos[i] != -1)
                {
                        ans[i] = a[pos[i]][m] / a[pos[i]][i];
                }
                        
        }
        for (int i = 0; i < n; i++)
        {
                double sum = 0;
                for (int j = 0; j < m; j++)
                {
                        sum += ans[j] * a[i][j];
                }
                       
                if (fabs(sum - a[i][m]) > eps)
                {
                        return -1; // no solution
                }
                        
        }
        for (int i = 0; i < m; i++)
        {
                if (pos[i] == -1)
                {
                        return 2; // infinte solutions
                }
                        
        }
                
        return 1;                 // unique solution
}




int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int n, m;
        cin >> n >> m;
        
        vector<vector<double>> v(n);
        for (int i = 0; i < n; i++)
        {
                for (int j = 0; j <= m; j++) // m-th colunm contain the value of constant
                {
                        double x;
                        cin >> x;
                        v[i].push_back(x);
                }
        }
        vector<double> ans;

        int k = Gauss(v, ans);

        if (k)
        {
                for (int i = 0; i < n; i++)
                {
                        cout << fixed << setprecision(5) << ans[i] << ' ';
                }
                        
        }  
        else
        {
                 cout << "no solution"<<endl;
        }
               
        return 0;


}
