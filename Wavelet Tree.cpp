
// https://www.spoj.com/problems/MKTHNUM/en/




/*

===============================
    Applications of Wavelet Tree
===============================

1. Range k-th smallest element
   - Query the k-th smallest (or largest) in subarray [L, R].
   - Example: query_kth(L, R, k)
   - Time: O(log σ)

2. Range Frequency Query
   - Count how many times a value K occurs in [L, R].
   - Example: query_count(L, R, K)
   - Time: O(log σ)

3. Count of elements ≤ K (or <, >, ≥)
   - Count how many numbers in [L, R] are ≤ K.
   - Example: query_LTE(L, R, K)
   - Time: O(log σ)

*/



const int N = 1e5 + 100;
const int Maximum = 1e5 + 100;


// Increased size to handle N * log(Max) elements
const int Nodes = 4000005;

struct WaveletTree
{
        int Tree[Nodes];

        int Left[Nodes];
        
        int left_child[Nodes];
        int  right_child[Nodes];

        int start_idx[Nodes];
        int end_idx[Nodes];

        int node_counter = 1;
        int array_ptr = 0;

        int mn_val, mx_val;
        int n;
        int input_arr[N];

        void build_impl(int parent_mid_val , bool is_left, int parent_node , int node , int low ,   int high)
        {
                start_idx[node] = ++array_ptr;

                end_idx[node] = array_ptr - 1;

                int mid = (low + high) >> 1;

                int iter_start = (node == 1)? 1: start_idx[parent_node];
                int iter_end   = (node == 1)?  n : end_idx[parent_node];

                for(int i = iter_start; i <= iter_end; i++)
                {
                        int val = (node == 1)?  input_arr[i] : Tree[i];

                        bool belongs = (node == 1) || (is_left && val <= parent_mid_val) || (!is_left && val > parent_mid_val);

                        if(belongs)
                        {
                                Tree[array_ptr] = val;
                                end_idx[node] = array_ptr;

                                // Left[i] stores count of elements going left up to index i
                                Left[array_ptr] = Left[array_ptr - 1] + (val <= mid);
                                array_ptr++;
                        }
                }

                if(low == high)
                {
                        return;
                }

                int count_in_node = end_idx[node] - start_idx[node] + 1;

                int left_elements = Left[end_idx[node]] - Left[start_idx[node] - 1];

                if(left_elements > 0)
                {
                        left_child[node] = ++node_counter;
                        build_impl(mid, true, node, left_child[node], low, mid);
                }

                if(count_in_node - left_elements > 0)
                {
                        right_child[node] = ++node_counter;

                        build_impl(mid, false, node, right_child[node], mid + 1, high);
                }
        }

        void init(int count  , vector<int> &v)
        {
                n = count;
                for(int i = 0; i < n; i++)
                {
                        input_arr[i+1] = v[i];
                }

                node_counter = 1;
                array_ptr = 0;
                mn_val = 0;
                mx_val = Maximum;

                Left[0] = 0;

                build_impl(-1, true, -1, 1, mn_val, mx_val);
        }



        // Find K-th smallest number in range [L, R]
        int query_kth(int L, int R , int k , int node = 1, int low = 0, int high = Maximum)
        {
                if(low == high)
                {
                        return low;
                }

                int mid = (low + high) >> 1;

                int cnt_left = Left[start_idx[node] + R] - Left[start_idx[node] + L - 1];

                int elements_to_left_before_L = Left[start_idx[node] + L - 1];


                int elements_to_left_upto_R = Left[start_idx[node] + R];


                if(cnt_left >= k)
                {
                        return query_kth(elements_to_left_before_L, elements_to_left_upto_R - 1, k, left_child[node], low, mid);
                }
                else
                {
                        int new_L = L - elements_to_left_before_L;

                        int new_R = R - elements_to_left_upto_R;

                        return query_kth(new_L, new_R, k - cnt_left, right_child[node], mid + 1, high);
                }
        }




        // Count occurrences of number K in range [L, R]
        int query_count(int L , int R, int k , int node = 1, int low = 0, int high = Maximum)
        {
                if(low == high)
                {
                        return Left[start_idx[node] + R] - Left[start_idx[node] + L - 1];
                }

                int mid = (low + high) >> 1;

                int elements_to_left_before_L = Left[start_idx[node] + L - 1];

                int elements_to_left_upto_R = Left[start_idx[node] + R];

                if(k <= mid)
                {
                        return query_count(elements_to_left_before_L, elements_to_left_upto_R - 1, k, left_child[node], low, mid);
                }
                else
                {
                        int new_L = L - elements_to_left_before_L;

                        int new_R = R - elements_to_left_upto_R;
                        return query_count(new_L, new_R, k, right_child[node], mid + 1, high);
                }
        }



        // Count numbers Less Than or Equal (LTE) to K in range [L, R]
        int query_LTE(int L, int R, int k, int node = 1, int low = 0, int high = Maximum)
        {
                if(L > R || k < low)
                {
                        return 0;
                }
                if(high <= k)
                {
                        return R - L + 1;
                }

                int mid = (low + high) >> 1;
                int elements_to_left_before_L = Left[start_idx[node] + L - 1];

                int elements_to_left_upto_R = Left[start_idx[node] + R];

                return query_LTE(elements_to_left_before_L, elements_to_left_upto_R - 1, k, left_child[node], low, mid) +  query_LTE(L - elements_to_left_before_L, R - elements_to_left_upto_R, k, right_child[node], mid + 1, high);
        }

} wt;









map<int,int>idx;
map<int,int>ridx;

int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

        int n;
        cin>>n;

        int q;
        cin>>q;

        vector<int>v;

        for(int i=0;i<n;i++)
        {
                int a;
                cin>>a;
                v.push_back(a);
        }

        vector<int>v1;

        v1 = v;

        sort(v1.begin(),v1.end());

        for(int i=0;i<n;i++)
        {
                idx[v1[i]] = i;
                ridx[i] = v1[i];
        }

        for(int i=0;i<n;i++)
        {
                v[i] = idx[v[i]];
        }

        wt.init(n, v);


        while(q--)
        {
                int l,r,k;
                cin>>l>>r>>k;

                l--;
                r--;

                int take = wt.query_kth(l,r,k);

                cout<<ridx[take]<<endl;


               
        }






}
