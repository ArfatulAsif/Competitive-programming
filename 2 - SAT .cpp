
using namespace std;
using namespace __gnu_pbds;

// 2- SAT
// a = a and -a = a+n edge; // n being the number of variable in the satishfibility


const int N = 2e5+10;
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

void reset(int n)
{
        for(int i=0;i<=2*n;i++)
        {
                graph[i].clear();
                Rgraph[i].clear();
                vis1[i] = false;
                vis2[i] = false;
                SCC[i] = 0;
                assignment[i] = false;
        }
        forder.clear();
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


        int t;
        cin>>t;
        for(int tt = 1; tt<=t; tt++)
        {
                int n,m;
                cin>>n>>m;


                reset(m);// use this for test case



                int a[n+1];
                int b[n+1];

                for(int i=0;i<n;i++)
                {
                        cin>>a[i]>>b[i];

                }




                for(int i=0;i<n;i++)
                {
                        if(a[i]>0 && b[i]> 0) // (a v b) = (-a -> b)^(-b -> a)
                        {
                                addedge(a[i]+m , b[i]); // (-a -> b)
                                addRedge(a[i]+m , b[i]);
                                addedge(b[i]+m , a[i]); //(-b -> a)
                                addRedge(b[i]+m , a[i]);

                        }
                        else if(a[i]>0 && b[i]<0) // (a v -b) = (-a -> -b)^(b -> a)
                        {
                                addedge(a[i]+m , m-b[i]); // (-a -> -b)
                                addRedge(a[i]+m , m-b[i]);
                                addedge(-b[i], a[i]); // (b -> a)
                                addRedge(-b[i] , a[i]);
                        }
                        else if(a[i]<0 && b[i]>0) // (-a v b) = (a -> b)^(-b -> -a)
                        {
                                addedge(-a[i] , b[i]); // (a -> b)
                                addRedge(-a[i] , b[i]);
                                addedge(b[i]+m, m-a[i]); // (-b -> -a)
                                addRedge(b[i]+m , m-a[i]);
                        }
                        else   //(-a v -b) = (a -> -b)^(b -> -a)
                        {
                                addedge(-a[i] , m-b[i]); // (a -> -b)
                                addRedge(-a[i] , m-b[i]);
                                addedge(-b[i] , m-a[i]); // (b -> -a)
                                addRedge(-b[i] , m-a[i]);
                        }

                }

                for(int i=1;i<=2*m;i++)
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


                for(int i=1;i<=m;i++)
                {

                        if(SCC[i]==SCC[i+m])
                        {
                                ans = false;
                        }
                        assignment[i] = SCC[i+m]<SCC[i]; // ( -x -> x) hole x = true  else (x -> -x) hole x = false [(-x -> x) is true for x = true] 
                }


                if(ans==false)
                {
                        cout<<"Case "<<tt<<": No"<<endl;
                        continue;
                }

                cout<<"Case "<<tt<<": Yes"<<endl;

                vector<int>res;

                for(int i=1;i<=m;i++)
                {
                        if(assignment[i])
                        {
                                res.push_back(i);
                        }
                }


                cout<<res.size()<<" ";

                for(auto x : res)
                {
                        cout<<x<<" ";
                }
                cout<<endl;







        }





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

