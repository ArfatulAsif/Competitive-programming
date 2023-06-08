// TRIE : Insert , Remove , Prefix search , String search

const int N = 1e6;
int node[N][26];
int root = 0;
int avail = 0;
int cnt[N];
int is_end[N];

void ini()
{
        root = 0;
        avail = 0;
        for(int i=0;i<26;i++)
        {
                node[root][i] = -1;
        }
}


void Insert(string s)
{

        int cur = root;
        for(int i=0;i<s.size();i++)
        {
                if(node[cur][s[i]-'a']==-1)
                {
                        avail++;

                        node[cur][s[i]-'a'] = avail;

                        is_end[avail] = 0;

                        cnt[avail] = 0;

                        for(int j=0;j<26;j++)
                        {
                                node[avail][j] = -1;
                        }
                }

                cur = node[cur][s[i]-'a'];

                cnt[cur]++;
        }
        is_end[cur]++;
}

void Remove(string s)
{

        int cur = root;

        for(int i=0;i<s.size();i++)
        {

                cur = node[cur][s[i]-'a'];

                cnt[cur]--;
        }
        is_end[cur]--;
}

bool prefix(string s)
{

        int cur = root;
        for(int i=0;i<s.size();i++)
        {
                if(node[cur][s[i]-'a']!=-1 && cnt[node[cur][s[i]-'a'] ]> 0)
                {
                        cur = node[cur][s[i]-'a'];
                }
                else
                {
                        return false;
                }
        }

        return true;
}


bool Search(string s)
{
        int cur = root;
        for(int i=0;i<s.size();i++)
        {
                if(node[cur][s[i]-'a']!=-1 && cnt[node[cur][s[i]-'a'] ]> 0)
                {
                        cur = node[cur][s[i]-'a'];
                }
                else
                {
                        return false;
                }
        }

        return (is_end[cur]>0);
}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        ini();

        int n;
        cin>>n;

        while(n--)
        {
                string s;
                cin>>s;
                Insert(s);
        }

        string a;
        cin>>a;

        cout<<prefix(a)<<endl;
        cout<<Search(a)<<endl;

        string b;

        cin>>b;

        Remove(b);               // asuming b is present in trie

        cout<<Search(a)<<endl;

        return 0;

}
