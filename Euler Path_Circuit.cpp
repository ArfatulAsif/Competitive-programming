Euler Path/Circuit : Visit all edges excatly once.

Hamilton Path/Circuit: Visit all vertex excatly once.

[Finding hamilton path/circuit is an NP - Complete problem]

Euler Path/Circuit Undirected:
1.Euler Circuit: All vertices must have an even degree. 
2.Euler Path: Exactly two vertices must have an odd degree (the path starts at one and ends at the other).


Euler Path/Circuit Directed:
1. Euler Circuit: The graph must be strongly connected, and for every vertex, the in-degree must equal the out-degree.

2. Euler Path: The graph must be connected, Exactly one vertex must have out-degree - in-degree = 1 and exactly one vertex must have in-degree - out-degree = 1. All other vertices must have in-degree = out-degree.




Hierholzer's algorithm For Undirected:


// https://www.youtube.com/watch?v=8MpoO2zA2l4  [This video is for directed. But just remember that, instead of removing outdegree by 1, we will remove an edge. See the implementation of how we remove an edge.
// Hierholzer's algorithm
// Euler path/circuit in a undirected graph



	
// https://cses.fi/problemset/task/1691
	
const int N = 2e5+100;
set<int>graph[N];
int degree[N];
vector<int>path;
bool vis[N];

void modified_dfs(int s)
{

	while(!graph[s].empty()) // this is just to make sure if out[s], or out_degree of s becomes 0, we add it to path[] or solution, like stated in the heirhozler algoritm.
	{
		int v = *graph[s].begin();  // For undirected graph, we consider each edge as an out_edge, so we remove it from count, so that we can get out[s] = 0 and add s to path

		graph[s].erase(v);  // this is removing [s - v] edge from count
		graph[v].erase(s);  // this is removing [s - v] edge from count

		modified_dfs(v);
	}

	path.push_back(s);


}
      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n,m;
        cin>>n>>m;

        for(int i=0;i<m;i++)
        {
        	int a,b;
        	cin>>a>>b;
        	graph[a].insert(b);
        	graph[b].insert(a);
        	degree[a]++;
        	degree[b]++;
        }

        bool ok = true;

        for(int i=1;i<=n;i++)
        {
        	if(degree[i]%2!=0)
        	{
        		ok = false;
        		break;
        	}
        }

        if(!ok)
        {
        	cout<<"IMPOSSIBLE"<<endl;
        	return 0;
        }


        
        modified_dfs(1); // As we ensured it is euler circuit, that means if it starts from 1, it will end at 1.

        // For euler path, we need to find start_vertex and end_vertex (two vertex with odd degree)

        if(path.size()!= m+1)
        {
        	cout<<"IMPOSSIBLE"<<endl;
        	return 0;
        }

        reverse(path.begin(),path.end());

        for(auto x : path)
        {
        	cout<<x<<" ";
        }
        cout<<endl;





}




Hierholzer's algorithm For Directed:

 
// https://www.youtube.com/watch?v=8MpoO2zA2l4
// Hierholzer's algorithm
// Euler path in a directed graph


https://cses.fi/problemset/task/1693/

const int N = 2e5+100;
vector<int>graph[N];
int in[N];
int out[N];
vector<int>path;
bool vis[N];
 
void modified_dfs(int s)
{
 
	while(!graph[s].empty()) // this is just to make sure if out[s], or out_degree of s becomes 0, we add it to path[] or solution, like stated in the heirhozler algoritm
	{
		int v = graph[s].back();
		graph[s].pop_back();
		modified_dfs(v);
	}
 
	path.push_back(s);
 
 
}
      
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);
 
        int n,m;
        cin>>n>>m;
 
        for(int i=0;i<m;i++)
        {
        	int a,b;
        	cin>>a>>b;
        	graph[a].push_back(b);
        	out[a]++;
        	in[b]++;
        }
 
        bool ok = true;
 
        for(int i=2;i<n;i++)
        {
        	if(in[i]!=out[i])
        	{
        		ok = false;
        		break;
        	}
        }
 
        if(!ok)
        {
        	cout<<"IMPOSSIBLE"<<endl;
        	return 0;
        }
 
 
        if((out[1]-in[1]) != 1 && (in[n]-out[n]) != 1) // For 1, out - in = 1 and For n, in - out = 1. This will ensure that euler path will exits that starts at 1 and ends n. Note: If euler circuit exists, this means that it will stats and ends at the same node, so it is not going to work for 1 to n.
        {
        	cout<<"IMPOSSIBLE"<<endl;
        	return 0;
        }
 
        modified_dfs(1);
 
        if(path.size()!= m+1)
        {
        	cout<<"IMPOSSIBLE"<<endl;
        	return 0;
        }
 
        reverse(path.begin(),path.end());
 
        for(auto x : path)
        {
        	cout<<x<<" ";
        }
        cout<<endl;
 
}
