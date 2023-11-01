https://leetcode.com/discuss/interview-question/3722472/mastering-sliding-window-technique-a-comprehensive-guide
//Use Fixed Length template from this disscuss and For variable length window . use mine



======== Fixed Lenght Sliding Window ==========


        int i = 0, j = 0; // Window indices
        int sum = 0;      // Current window sum

        while (j < n)
        {
                if (j - i + 1 < k)
                {
                        // Expand the window by adding element at index j to the sum
                        sum += v[j];
                        j++;
                }
                else
                {
                        // Window size is now equal to the desired window size
                        // Calculate the answer for the window
                        sum += v[j];
                        cout << sum << endl;

                        // Move the window by incrementing indices i and j
                        sum -= v[i];
                        i++, j++;
                }
        }




/* You can use this template for any fixed length sliding window problem without any change 
 regardless of what i,j means  */


=============== Variable length Sliding window ============ (Most used)(Sometimes instead of two pointers)

         int j = 0;

         int ans = 0;

        for (int i = 0; i < n; i++)
        {

		            if( clearing previous i , has effect than check condition)
                {
			              //calculate the ans
                }


                while (some target is not met or limit is not crossed)
                {
                        j++; // increase the right pointer of the variable window
			                  //calculate the ans
                }


                while or if (target is met)
                {
                        // Calculated the ans here depending on the problem
                        j++; //while loop then j++; else for if then no j++;
                        // Calculated the ans here depending on the problem
                }

                // clear i er effect
        }



//Remember to keep tract of i,j and what they mean.. based on these calculate ans.
/* You don't have to think like this in the fixed length sliding window. But 
in variable length window you do have to think about i,j and what they means */
// j included rakhar atmost try kora


===================== Variable length Sliding Window ============== Examples problem(Sub-Array Counting : excatly k property)


https://leetcode.com/problems/subarrays-with-k-different-integers/description/?envType=list&envId=p96cfcjg

This problem is like the problem of ICPC regional 2023 solved by me
 
class Solution
{
public:
        bool isValid(unordered_map<int, int> &mp, int k, int add)
        {
                mp[add]++;
                bool ok = mp.size() <= k;
                mp[add]--;
                if (mp[add] == 0)
                {
                        mp.erase(add);
                }
                return ok;
        }

        int subArrayWithAtmostK(vector<int> &nums, int k)
        {
                int j = 0;
                int ans = 0;
                unordered_map<int, int> mp;

                mp[nums[j]]++;

                for (int i = 0; i < nums.size(); i++)
                {
                        while (j + 1 < nums.size() && isValid(mp, k, nums[j + 1]))
                        {
                                mp[nums[j + 1]]++;
                                j++; // j porjont neya  [j included]
                        }

                        if (mp.size() <= k)
                        {
                                ans += j - i + 1; // j included.
                        }

                        mp[nums[i]]--;
                        if (mp[nums[i]] == 0)
                        {
                                mp.erase(nums[i]);
                        }
                }

                return ans;
        }
        int subarraysWithKDistinct(vector<int> &nums, int k)
        {
                return subArrayWithAtmostK(nums, k) - subArrayWithAtmostK(nums, k - 1);

                // Sub Array With excatly K different integers = Sub Array With AtMost K different integers - Sub Array With AtMost (K-1) different integers
        }
};


===================== Variable length Sliding Window ============== Examples problem(Sub-Array Counting : excalty k property)

https://leetcode.com/problems/count-number-of-nice-subarrays/?envType=list&envId=p96cfcjg

class Solution
{
public:
        bool isValid(int odd, int k, int num)
        {
                odd += (num & 1);
                return odd <= k;
        }
        int atMostK(vector<int> &nums, int k)
        {
                int j = 0;
                int ans = 0;
                int odd = (nums[0] & 1);
                for (int i = 0; i < nums.size(); i++)
                {
                        while (j + 1 < nums.size() && isValid(odd, k, nums[j + 1]))
                        {
                                j++;
                                odd += (nums[j] & 1); // j included . which means j porjonto
                        }

                        if (odd <= k)
                        {
                                ans += j - i + 1; // j included
                        }

                        odd -= (nums[i] & 1);
                }

                return ans;
        }

        int numberOfSubarrays(vector<int> &nums, int k)
        {
                return atMostK(nums, k) - atMostK(nums, k - 1); //= Excatly k
        }
};


