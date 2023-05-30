//Arfatul Islam Asif 
//This programme can be used for both finding SCC's and converting a directed graph to DAG 

const int N = 1000;
vector<int>graph[N];
vector<int>Rgraph[N];
bool vis1[N];
bool vis2[N];
int group_id[N];
vector<int>forder;

void dfs1(int s)
{
        vis1[s] = true;
        for(auto child : graph[s])
        {
                if(vis1[child])
                {
                        continue;
                }
                dfs1(child);
        }
        forder.push_back(s);
}
void dfs2(int s , int no)
{
        vis2[s] = true;
        group_id[s] = no;
        for(auto child : Rgraph[s])
        {
                if(vis2[child])
                {
                        continue;
                }
                dfs2(child , no);
        }
        return;
}




int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n,m;
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
                int x,y;
                cin>>x>>y;
                graph[x].push_back(y);
                Rgraph[y].push_back(x);
        }
        for(int i=0;i<n;i++)
        {
                if(vis1[i]==false)
                {
                        dfs1(i);
                }
        }
        reverse(forder.begin() , forder.end());
        int no = 1;
        for(auto x : forder)
        {
                if(vis2[x]==false)
                {
                        dfs2(x , no);
                        no++;
                }
        }
        vector<int>DAG[N];
        //SCC to DAG convertion
        for(int i=0;i<n;i++)
        {
                for(auto child : graph[i])
                {
                        if(group_id[i]!=group_id[child])
                        {
                                DAG[group_id[i]].push_back(group_id[child]);
                        }
                }
        }

        for(int i = 1;i<no;i++)
        {
                cout<<i<<": ";
                for(int j=0;j<DAG[i].size();j++) //Printing DAG's adjacency list
                {
                        cout<<DAG[i][j]<<" ";
                }
                cout<<endl;
        }


        return 0;




}

/*
7 8
0 1
1 2
2 0
2 3
3 4
4 5
5 6
6 4


*/
