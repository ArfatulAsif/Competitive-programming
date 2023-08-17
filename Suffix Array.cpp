
Suffix array .....
1.Finding pattern in a text nlogn.
2.Longest Common prefix LCP.
3.Longest Repeating substring LRS.
4.Longest Common substring LCS.
5.No of unique substring .
6.Longest Palindromic substring LPS.




======================== Suffix Array    [Correct Versions] ===============


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
//Suffix array : Sorted Array containing all the suffixe's
// Here in this nlongn approach we are gonna just store the index's

class Suffix
{
public:
        int index;
        pair<int,int> Rank;
};

bool cmp(const Suffix &a , const Suffix &b)
{
        return a.Rank<b.Rank;
}

vector<int> buildSuffixArray(string s)
{
        int n = s.size();

        vector<Suffix>suffix;

        for(int i=0;i<n;i++)
        {
                Suffix a;
                a.index = i;
                a.Rank.first = s[i]-'a';
                a.Rank.second = (i+1<n)? (s[i+1]-'a') : -1;

                suffix.push_back(a);
        }
        sort(suffix.begin() , suffix.end() , cmp);

        int ind[n];

        for(int k = 4 ; k< 2*n ; k*=2)
        {
                int Rank = 0;

                int prev_Rank = suffix[0].Rank.first;;

                suffix[0].Rank.first = Rank;

                ind[suffix[0].index] = 0; // ind[Suffix ID dile ] = position output dibe ..

                for(int i = 1;i<n;i++)
                {
                        if(suffix[i].Rank.first == prev_Rank && suffix[i-1].Rank.second == suffix[i].Rank.second)
                        {
                                prev_Rank = suffix[i].Rank.first;
                                suffix[i].Rank.first = Rank;
                        }
                        else
                        {
                                prev_Rank = suffix[i].Rank.first;
                                Rank++;
                                suffix[i].Rank.first = Rank;
                        }

                        ind[suffix[i].index] = i;
                }

                for(int i=0;i<n;i++)
                {
                        int nextindex = suffix[i].index + k/2;
                        suffix[i].Rank.second = (nextindex<n)? (suffix[ind[nextindex]].Rank.first) : -1;

                }

                sort(suffix.begin() , suffix.end() , cmp);
        }

        vector<int>SuffixArray;

        for(int i=0;i<n;i++)
        {
                SuffixArray.push_back(suffix[i].index);
        }

        return SuffixArray;

}




int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string txt = "abaabab";

        vector<int>SuffixArray = buildSuffixArray(txt);

        for(int i=0;i<SuffixArray.size() ;i++)
        {
                cout<<SuffixArray[i]<<" ";
        }
        cout<<endl;


}


========================================================== Finding all the occarance of the pattern in nlogn time ====================
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
//Suffix array : Sorted Array containing all the suffixe's
// Here in this nlongn approach we are gonna just store the index's

class Suffix
{
public:
        int index;
        pair<int,int> Rank;
};

bool cmp(const Suffix &a , const Suffix &b)
{
        return a.Rank<b.Rank;
}

vector<int> buildSuffixArray(string s)
{
        int n = s.size();

        vector<Suffix>suffix;

        for(int i=0;i<n;i++)
        {
                Suffix a;
                a.index = i;
                a.Rank.first = s[i]-'a';
                a.Rank.second = (i+1<n)? (s[i+1]-'a') : -1;

                suffix.push_back(a);
        }
        sort(suffix.begin() , suffix.end() , cmp);

        int ind[n];

        for(int k = 4 ; k< 2*n ; k*=2)
        {
                int Rank = 0;

                int prev_Rank = suffix[0].Rank.first;;

                suffix[0].Rank.first = Rank;

                ind[suffix[0].index] = 0; // ind[Suffix ID dile ] = position output dibe ..

                for(int i = 1;i<n;i++)
                {
                        if(suffix[i].Rank.first == prev_Rank && suffix[i-1].Rank.second == suffix[i].Rank.second)
                        {
                                prev_Rank = suffix[i].Rank.first;
                                suffix[i].Rank.first = Rank;
                        }
                        else
                        {
                                prev_Rank = suffix[i].Rank.first;
                                Rank++;
                                suffix[i].Rank.first = Rank;
                        }

                        ind[suffix[i].index] = i;
                }

                for(int i=0;i<n;i++)
                {
                        int nextindex = suffix[i].index + k/2;
                        suffix[i].Rank.second = (nextindex<n)? (suffix[ind[nextindex]].Rank.first) : -1;

                }

                sort(suffix.begin() , suffix.end() , cmp);
        }

        vector<int>SuffixArray;

        for(int i=0;i<n;i++)
        {
                SuffixArray.push_back(suffix[i].index);
        }

        return SuffixArray;

}


int stringCmp(const string &pattern , const string &txt , int pos)
{
        for(int i= 0; ( i < pattern.size())&& (pos+i<txt.size()) ;i++)
        {
                if(pattern[i]==txt[pos+i])
                {
                        continue;
                }
                else if(pattern[i]>=txt[pos+i])
                {
                        return 1;
                }
                else
                {
                        return -1;
                }
        }

        return 0;
}




//Occarance of all pattern in the txt in  nlogn time
int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string txt , pattern;

        cin>>txt>>pattern;


        vector<int>suffixArray = buildSuffixArray(txt);


        int l = 0;
        int h = txt.size()-1;

        while(l<h)
        {
                int mid = (l+h)>>1;



                if(stringCmp(pattern,txt,suffixArray[mid])>=0)
                {

                        l = mid+1;
                }
                else
                {
                        h = mid-1;
                }
        }


        l-=5;

        while(l<txt.size())
        {
                if(l<0)
                {
                        l++;
                        continue;
                }
                if(stringCmp(pattern,txt,suffixArray[l])==0)
                {
                        cout<<"Pattern Found At: "<<suffixArray[l]<<endl;

                }
                if(stringCmp(pattern,txt,suffixArray[l])<0)
                {
                        break;
                }
                l++;
        }

        return 0;






}

========================================== LCP ( longest common prefix ) =======Kasai algorithm  (gfg) =====
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
//Suffix array : Sorted Array containing all the suffixe's
// Here in this nlongn approach we are gonna just store the index's

class Suffix
{
public:
        int index;
        pair<int,int> Rank;
};

bool cmp(const Suffix &a , const Suffix &b)
{
        return a.Rank<b.Rank;
}

vector<int> buildSuffixArray(string s)
{
        int n = s.size();

        vector<Suffix>suffix;

        for(int i=0;i<n;i++)
        {
                Suffix a;
                a.index = i;
                a.Rank.first = s[i]-'a';
                a.Rank.second = (i+1<n)? (s[i+1]-'a') : -1;

                suffix.push_back(a);
        }
        sort(suffix.begin() , suffix.end() , cmp);

        int ind[n];

        for(int k = 4 ; k< 2*n ; k*=2)
        {
                int Rank = 0;

                int prev_Rank = suffix[0].Rank.first;;

                suffix[0].Rank.first = Rank;

                ind[suffix[0].index] = 0; // ind[Suffix ID dile ] = position output dibe ..

                for(int i = 1;i<n;i++)
                {
                        if(suffix[i].Rank.first == prev_Rank && suffix[i-1].Rank.second == suffix[i].Rank.second)
                        {
                                prev_Rank = suffix[i].Rank.first;
                                suffix[i].Rank.first = Rank;
                        }
                        else
                        {
                                prev_Rank = suffix[i].Rank.first;
                                Rank++;
                                suffix[i].Rank.first = Rank;
                        }

                        ind[suffix[i].index] = i;
                }

                for(int i=0;i<n;i++)
                {
                        int nextindex = suffix[i].index + k/2;
                        suffix[i].Rank.second = (nextindex<n)? (suffix[ind[nextindex]].Rank.first) : -1;

                }

                sort(suffix.begin() , suffix.end() , cmp);
        }

        vector<int>SuffixArray;

        for(int i=0;i<n;i++)
        {
                SuffixArray.push_back(suffix[i].index);
        }

        return SuffixArray;

}


vector<int>LCP_kasai(const string &txt)  //lcp[i] = longest common prefix of suffixArray[i] and suffixArray[i+1]
{
        int n = txt.size();

        vector<int>suffixArray = buildSuffixArray(txt);

        vector<int>invSuffixArray(n,0);

        vector<int>lcp(n,0);

        for(int i=0;i<n;i++)
        {
                invSuffixArray[suffixArray[i]] = i;
        }

        int k = 0;

        for(int i=0;i<n;i++)
        {
                if(invSuffixArray[i]== n-1)
                {
                        k = 0;
                        continue;
                }
                int j = suffixArray[invSuffixArray[i]+1]; //index of next suffix in the suffixArray

                while(i+k<n && j+k<n && txt[i+k]==txt[j+k])  // Current and Next tar koyta character match kore dekram
                {
                        k++;
                }
                lcp[invSuffixArray[i]] = k;

                if(k>0)
                {
                        k--;
                }

        }

        return lcp;



}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string txt;
        cin>>txt;

        vector<int>lcp = LCP_kasai(txt);

        for(int i=0;i<txt.size();i++)
        {
                cout<<lcp[i]<<endl;
        }

        return 0;


}


// Highest Value of LCP is the longest repeating substring or (LRS)


// Number of unique substring = (Number of substring) - ( sum of all LCP)
//                              = ((n(n+1))/2 - sum of lcp 


===================================== LCS ( Longest common substring ) ==============
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


class Suffix
{
public:
        int index;
        pair<int,int> Rank;
};

bool cmp(const Suffix &a , const Suffix &b)
{
        return a.Rank<b.Rank;
}

vector<int> buildSuffixArray(string s)
{
        int n = s.size();

        vector<Suffix>suffix;

        for(int i=0;i<n;i++)
        {
                Suffix a;
                a.index = i;
                a.Rank.first = s[i]-'a';
                a.Rank.second = (i+1<n)? (s[i+1]-'a') : -1;

                suffix.push_back(a);
        }
        sort(suffix.begin() , suffix.end() , cmp);

        int ind[n];

        for(int k = 4 ; k< 2*n ; k*=2)
        {
                int Rank = 0;

                int prev_Rank = suffix[0].Rank.first;;

                suffix[0].Rank.first = Rank;

                ind[suffix[0].index] = 0; // ind[Suffix ID dile ] = position output dibe ..

                for(int i = 1;i<n;i++)
                {
                        if(suffix[i].Rank.first == prev_Rank && suffix[i-1].Rank.second == suffix[i].Rank.second)
                        {
                                prev_Rank = suffix[i].Rank.first;
                                suffix[i].Rank.first = Rank;
                        }
                        else
                        {
                                prev_Rank = suffix[i].Rank.first;
                                Rank++;
                                suffix[i].Rank.first = Rank;
                        }

                        ind[suffix[i].index] = i;
                }

                for(int i=0;i<n;i++)
                {
                        int nextindex = suffix[i].index + k/2;
                        suffix[i].Rank.second = (nextindex<n)? (suffix[ind[nextindex]].Rank.first) : -1;

                }

                sort(suffix.begin() , suffix.end() , cmp);
        }

        vector<int>SuffixArray;

        for(int i=0;i<n;i++)
        {
                SuffixArray.push_back(suffix[i].index);
        }

        return SuffixArray;

}


vector<int>LCP_kasai(const string &txt)  //lcp[i] = longest common prefix of suffixArray[i] and suffixArray[i+1]
{
        int n = txt.size();

        vector<int>suffixArray = buildSuffixArray(txt);

        vector<int>invSuffixArray(n,0);

        vector<int>lcp(n,0);

        for(int i=0;i<n;i++)
        {
                invSuffixArray[suffixArray[i]] = i;
        }

        int k = 0;

        for(int i=0;i<n;i++)
        {
                if(invSuffixArray[i]== n-1)
                {
                        k = 0;
                        continue;
                }
                int j = suffixArray[invSuffixArray[i]+1]; //index of next suffix in the suffixArray

                while(i+k<n && j+k<n && txt[i+k]==txt[j+k])  // Current and Next tar koyta character match kore dekram
                {
                        k++;
                }
                lcp[invSuffixArray[i]] = k;

                if(k>0)
                {
                        k--;
                }

        }

        return lcp;



}



int LCSubstring(const string &a , const string &b)
{
        int n = a.size();
        int m = b.size();

        string s = a+"#"+b;

        vector<int>lcp = LCP_kasai(s);
        vector<int>SuffixArray = buildSuffixArray(s);

        int mx = 0;

        for(int i=0;i<s.size();i++)
        {
                if(mx<lcp[i])
                {
                        bool one = SuffixArray[i]<n;
                        bool two = SuffixArray[i+1]<n;

                        bool flag = one^two;
                        
                        
                        if(flag)
                        {
                                mx = lcp[i];
                        }
                }
        }

        return mx;


}



int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        string a,b;
        cin>>a>>b;


        cout<<LCSubstring(a,b)<<endl;

        return 0;



}


================================== Longest Palindromic substring (LPS) ================

s = s +"#"+rev(s) 
finding max lcp of this string is the answer.

	

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
//Suffix array : Sorted Array containing all the suffixe's
// Here in this nlongn approach we are gonna just store the index's

class Suffix
{
public:
        int index;
        pair<int,int> Rank;
};

bool cmp(const Suffix &a , const Suffix &b)
{
        return a.Rank<b.Rank;
}

vector<int> buildSuffixArray(string s)
{
        int n = s.size();

        vector<Suffix>suffix;

        for(int i=0;i<n;i++)
        {
                Suffix a;
                a.index = i;
                a.Rank.first = s[i]-'a';
                a.Rank.second = (i+1<n)? (s[i+1]-'a') : -1;

                suffix.push_back(a);
        }
        sort(suffix.begin() , suffix.end() , cmp);

        int ind[n];

        for(int k = 4 ; k< 2*n ; k*=2)
        {
                int Rank = 0;

                int prev_Rank = suffix[0].Rank.first;;

                suffix[0].Rank.first = Rank;

                ind[suffix[0].index] = 0; // ind[Suffix ID dile ] = position output dibe ..

                for(int i = 1;i<n;i++)
                {
                        if(suffix[i].Rank.first == prev_Rank && suffix[i-1].Rank.second == suffix[i].Rank.second)
                        {
                                prev_Rank = suffix[i].Rank.first;
                                suffix[i].Rank.first = Rank;
                        }
                        else
                        {
                                prev_Rank = suffix[i].Rank.first;
                                Rank++;
                                suffix[i].Rank.first = Rank;
                        }

                        ind[suffix[i].index] = i;
                }

                for(int i=0;i<n;i++)
                {
                        int nextindex = suffix[i].index + k/2;
                        suffix[i].Rank.second = (nextindex<n)? (suffix[ind[nextindex]].Rank.first) : -1;

                }

                sort(suffix.begin() , suffix.end() , cmp);
        }

        vector<int>SuffixArray;

        for(int i=0;i<n;i++)
        {
                SuffixArray.push_back(suffix[i].index);
        }

        return SuffixArray;

}


vector<int>LCP_kasai(const string &txt)  //lcp[i] = longest common prefix of suffixArray[i] and suffixArray[i+1]
{
        int n = txt.size();

        vector<int>suffixArray = buildSuffixArray(txt);

        vector<int>invSuffixArray(n,0);

        vector<int>lcp(n,0);

        for(int i=0;i<n;i++)
        {
                invSuffixArray[suffixArray[i]] = i;
        }

        int k = 0;

        for(int i=0;i<n;i++)
        {
                if(invSuffixArray[i]== n-1)
                {
                        k = 0;
                        continue;
                }
                int j = suffixArray[invSuffixArray[i]+1]; //index of next suffix in the suffixArray

                while(i+k<n && j+k<n && txt[i+k]==txt[j+k])  // Current and Next tar koyta character match kore dekram
                {
                        k++;
                }
                lcp[invSuffixArray[i]] = k;

                if(k>0)
                {
                        k--;
                }

        }

        return lcp;



}

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;
        string s;
        cin>>s;

        string s1 = s;

        reverse(s1.begin() , s1.end());

        s = s+"#"+s1;

        vector<int>lcp = LCP_kasai(s);

        int mx = 0;

        for(int i=0;i<s.size();i++)
        {
                mx = max(mx , lcp[i]);
        }


        cout<<mx<<endl;

        return 0;


}



=============================================== Suffix Array O(nlogn) ======= counting sort =============

//Intermediary
//Young kid on the block
//AIAsif try's "Continuing the journey"
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define endl "\n"
//#define int long long int
#define ordered_set tree< int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
const int N = 2e6+100;

vector<int>SA;
vector<int>LCP;
vector<int>inv_SA;
vector<int>tempSA;

vector<int>RA , tempRA;  // rank array and temporary rank array
int cnt[N];
string str; // str = s1+"#"+s2+"$"

int n; // n = size of s1+"#"+s2+"$"
int m;  // m = size of s2;

void reset(int n)
{
        SA.assign(n,0);
        LCP.assign(n,0);
        inv_SA.assign(n,0);
        tempSA.assign(n,0);
        RA.assign(n,0);
        tempRA.assign(n,0);

}

void countingSort(int k)  // O(n)
{
        int sum = 0;
        int maxi = max(256 , n); // up to 255 ASCII chars or length of n
        memset(cnt , 0 , sizeof(cnt));  // clear frequency table

        for(int i=0;i<n;i++)  // count the frequency of each integer rank
        {
                cnt[(i+k<n)? RA[i+k] : 0 ]++;
        }
        for(int i=0;i<maxi ;i++)
        {
                int temp = cnt[i];
                cnt[i] = sum;
                sum += temp;
        }
        for(int i=0;i<n;i++) // shuffle the suffix array if necessary
        {
                tempSA[cnt[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        }
        for(int i=0;i<n;i++) // update the suffix array SA
        {
                SA[i] = tempSA[i];
        }

}

void computeSA()
{ // this version can go up to 100000 characters
	int i, k, r;
	for (i = 0; i < n; i++)
        {
                RA[i] = str[i]; // initial rankings
        }
	for (i = 0; i < n; i++)
        {
                SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
        }
	for (k = 1; k < n; k <<= 1)
	{							// repeat sorting process log n times
		countingSort(k);		// actually radix sort: sort based on the second item
		countingSort(0);		// then (stable) sort based on the first item
		tempRA[SA[0]] = r = 0;	// re-ranking; start from rank r = 0
		for (i = 1; i < n; i++) // compare adjacent suffixes
                {
                        tempRA[SA[i]] =	(RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;	// if same pair => same rank r; otherwise, increase r
                }
		for (i = 0; i < n; i++) // update the rank array RA
                {
                        RA[i] = tempRA[i];
                }
		if (RA[SA[n - 1]] == n - 1)
			break; // nice optimization trick
	}
}



void computeLCP ()
{

	vector <int> phi(n, -1);

	for (int i=0; i<n; i++)
	{
		if (i) phi[SA[i]]=SA[i-1];
		inv_SA[SA[i]]=i;
	}

	int mxm=0;
	for (int i=0; i<n; i++)
	{
		if (phi[i]==-1) continue;

		while (str[i+mxm] == str[phi[i]+mxm])
                {
                        mxm++;
                }

		LCP[inv_SA[i]] = mxm;
		mxm = max(mxm-1, 0);
	}

}

int owner(int idx)
{
	return (idx < n - m -1) ? 1 : 2;
}

pair<int,int> LCS()  // longest common Substring
{
	int idx = 0, maxLCP = -1;
	for (int i = 1; i < n; i++)
	{
		if (owner(SA[i])!=owner(SA[i-1]) && LCP[i] > maxLCP)
			maxLCP = LCP[i], idx = i;
	}
	return pair<int,int>(maxLCP, idx);
}


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);


        int t;
        t=1;

        while(t--)
        {
                string s1,s2;
                cin>>s1>>s2;

                str = s1+"#"+s2+"$";

                n = str.size();
                m = s2.size();

                reset(n);

                computeSA();
                computeLCP();

                pair<int,int> ans = LCS();


                cout<<ans.first<<endl;
        }



        return 0;


}


