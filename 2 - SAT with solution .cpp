
// 2- SAT
// a = a and -a = a+n edge; // here n being the number of variable 

const int N = 1e5;
vector<int>graph[N];
vector<int>Rgraph[N];
vector<int>forder;
bool vis1[N];
bool vis2[N];
int SCC[N];
vector<bool>assignment(N , false);
 
void addedge(int a,int b)
{
        graph[a].push_back(b);
}
void addRedge(int a,int b)
{
        Rgraph[b].push_back(a);
}
 
void dfs1(int s)
{
        vis1[s] = true;
        for(auto child:graph[s])
        {
                if(vis1[child])
                {
                        continue;
                }
                dfs1(child);
        }
        forder.push_back(s);
}
 
void dfs2(int s,int sccno)
{
        vis2[s] = true;
        SCC[s] = sccno;
        for(auto child : Rgraph[s])
        {
                if(vis2[child])
                {
                        continue;
                }
                dfs2(child,sccno);
        }
}
 
 
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
 
        int n ;// number of variable
        cin>>n;
        int m; // number of clause
        cin>>m;
 
        int a[m]; // first element of clause
        int b[m]; // second element of clause
 
        for(int i=0;i<m;i++)
        {
                cin>>a[i];
        }
        for(int i=0;i<m;i++)
        {
                cin>>b[i];
        }
 
        for(int i=0;i<m;i++)
        {
                if(a[i]>0 && b[i]> 0) // (a v b) = (-a -> b)^(-b -> a)
                {
                        addedge(a[i]+n , b[i]); // (-a -> b)
                        addRedge(a[i]+n , b[i]);
                        addedge(b[i]+n , a[i]); //(-b -> a)
                        addRedge(b[i]+n , a[i]);
 
                }
                else if(a[i]>0 && b[i]<0) // (a v -b) = (-a -> -b)^(b -> a)
                {
                        addedge(a[i]+n , n-b[i]); // (-a -> -b)
                        addRedge(a[i]+n , n-b[i]);
                        addedge(-b[i], a[i]); // (b -> a)
                        addRedge(-b[i] , a[i]);
                }
                else if(a[i]<0 && b[i]>0) // (-a v b) = (a -> b)^(-b -> -a)
                {
                        addedge(-a[i] , b[i]); // (a -> b)
                        addRedge(-a[i] , b[i]);
                        addedge(b[i]+n, n-a[i]); // (-b -> -a)
                        addRedge(b[i]+n , n-a[i]);
                }
                else   //(-a v -b) = (a -> -b)^(b -> -a)
                {
                        addedge(-a[i] , n-b[i]); // (a -> -b)
                        addRedge(-a[i] , n-b[i]);
                        addedge(-b[i] , n-a[i]); // (b -> -a)
                        addRedge(-b[i] , n-a[i]);
                }
        }
 
        for(int i=1;i<=2*n;i++)
        {
                if(vis1[i]==false)
                {
                        dfs1(i);
                }
        }
 
        reverse(forder.begin(),forder.end());
        int cnt=0;
        for(auto x : forder)
        {
                if(vis2[x]==false)
                {
                        cnt++;
                        dfs2(x,cnt);
                }
        }
 
 
        bool ans = true;
 
 
        for(int i=1;i<=n;i++)
        {
 
                if(SCC[i]==SCC[i+n])
                {
                        ans = false;
                }
                assignment[i] = SCC[i+n]<SCC[i]; // ( -x -> x) hole x = true  else (x -> -x) hole x = false [for testing build a truth table]
        }
 
 
 
        if(ans==false)
        {
                cout<<"The given expression is NOT satisfiable."<<endl;
                return 0;
        }
 
 
        cout<<("The given expression is satisfiable.")<<endl;
 
 
        cout<<"The solution: "<<endl;
        for(int i=1;i<=n;i++)
        {
                cout<<assignment[i]<<" ";
        }
        cout<<endl;
 
 
 
 
 
        return 0;
 
 
 
 
 
 
}
 
/*
 
5 7
1 -2 -1 3 -3 -4 -3
2 3 -2 4 5 -5 4
 
output : The given expression is satisfiable
 
The solution:
1 0 0 1 0
 
 
2 4
1 -1 1 -1
2 2 -2 -2
 
output : The given expression is NOT satisfiable
 
*/
 
 
