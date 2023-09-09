====================================Application of Z fuction =====================
1.Pattern search.
2.String Compression.

  

// Longest prefix that start's at i which is also a prefix  [ tushar roy ]

vector<int> z_function(const string &s)
{
        int n = s.size();
        vector<int>z(n);
        int l = 0;
        int r = 0;
        for(int i=1;i<n;i++)
        {
                if(i<r) // which means [l to r] range has already been calculated and their value are quite like the prefix ... of [0 to (r-l+1)]
                {
                        z[i] = min(r-i , z[i-l]);
                }
                while(i+z[i]<n && s[z[i]]==s[i+z[i]])
                {
                        z[i]++;
                }
                if(i+z[i]>r)
                {
                        l = i;
                        r = i+z[i];
                }
        }

        return z;
}


int stringCompression(const string &s) //length of smallest string t such s = t+t+..+t ; Or s is the concatenation of one or more t;
{
        vector<int>z = z_function(s);

        for(int i=1;i<s.size();i++)
        {
                if(s.size()%i==0 && i+z[i]==s.size())
                {
                        return i;
                }
        }

        return s.size();

}

