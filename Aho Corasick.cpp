// Motto : longest suffix that ends at i which is also a prefix
=============================================================== Aho Corasic =============================================


// 1.Finding The occarance of all pattern in a text in O(text.size()) time.


const int ALPH = 52;
const int N = 5e5;
map<char,int>node[N];  // it is equal to [[  int node[N][ALPH]  ]]; Trie er moto
const int root = 0;
int avail = 0;

//Suffix Link or Failure Link
int fail[N];
int nxtWord[N];
int wordId[N];


void ini()
{
        for(int i=0;i<=avail;i++)
        {
                node[i].clear();
        }
        avail = 0;
}

int insertTrie(const string &s , int idx)
{
        int cur = root;
        for(int i=0;i<s.size();i++)
        {
                if(node[cur][s[i]]==0)
                {
                        avail++;
                        node[cur][s[i]] = avail;
                        fail[avail] = 0;
                        nxtWord[avail] = 0;
                        wordId[avail] = -1;

                }
                cur = node[cur][s[i]];
        }
        if(wordId[cur]==-1)
        {
                wordId[cur] = idx;
        }
        return wordId[cur];
}


void computeFailureLinkBFS() // OR suffix link
{
        queue<int>q;
        for(auto x : node[root])
        {
                q.push(x.second); // root er child node er No.
        }
        while(!q.empty())
        {
                int u = q.front();
                q.pop();
                for(auto [ch , v] : node[u]) // v = child node . ch = transition character
                {
                        int f = fail[u]; // parent er fail link e gelam : jate sekan theke check korbo node ch e Transition hoy naki

                        while(node[f][ch]==0 && f!=0) // jotokkon porjonto f No. node theke ch Transition exit's na kore totokkon failure link e jump kortei thakbo . f = 0 hoyegele off
                        {
                                f = fail[f];
                        }

                        fail[v] = node[f][ch]; // jodi node[f][ch] ch na thake tahole auto f =  0 zero assign(ie. root ) map er karone

                        if(wordId[fail[v]] !=-1)
                        {
                                nxtWord[v] = fail[v];
                        }
                        else
                        {
                                nxtWord[v] = nxtWord[fail[v]];
                        }

                        q.push(v);

                }
        }
}


vector<vector<int>> match(const string &text , int q)
{
        vector<vector<int>> ret(q);

        int cur = root;

        for(int i=0;i<text.size();i++)
        {
                while(node[cur][text[i]]==0 && cur!=0)
                {
                        cur = fail[cur];
                }
                cur = node[cur][text[i]];

                int u = cur;

                while(u!=0)
                {
                        if(wordId[u]!=-1)
                        {
                                ret[wordId[u]].push_back(i);
                        }
                        u = nxtWord[u];
                }
        }
        return ret;
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int t;
        cin>>t;

        while(t--)
        {
                ini();
                string text;
                cin>>text;
                int n;
                cin>>n;
                vector<int>id;
                for(int i=0;i<n;i++)
                {
                        string s;
                        cin>>s;
                        id.push_back(insertTrie(s,i));
                }
                computeFailureLinkBFS();

                auto matching = match(text,n);

                for(int i=0;i<n;i++)
                {
                        cout<<"yn"[matching[id[i]].empty()]<<endl;   //matching[id[i]] id[i] erokom likte hobe . etar modde all occarance pawa jabe
                }
        }

        return 0;



}
