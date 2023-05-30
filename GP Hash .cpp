
// Remember to use this only wheeen need to access large number of data , and only unordered map is useful

//use this hash function  , highly recommended
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
}; //For long long int to long long int


typedef gp_hash_table<int,int,custom_hash>table;






//
//struct chash {
//    int operator()(pair<int,int> x) const { return x.first* 31 + x.second; }
//};
//gp_hash_table<pair<int,int>, int, chash> table;


//This was for {pair to int} mapping


int32_t main()
{
        ios::sync_with_stdio(0);
        cin.tie(0);

       //gp_hash_table<int,int,custom_hash> m;          can do this too

        table m;


        m[1]++;
        m[2]++;
        m[1]++;
        m[1]++;

        cout<<m[1]<<endl; // works exactly like unordered map but wayyyyyyy faster
        cout<<m[0]<<endl;
        cout<<m[2]<<endl;



}





// NOTE: for BIT of fenwick tree , hash function need to be modified specifically , so For now just remember that , when needed just search gp_hash_table for BIT
// useful : https://github.com/mochow13/competitive-programming-library/blob/master/Data%20Structures/GP%20Hash%20Table.cpp
