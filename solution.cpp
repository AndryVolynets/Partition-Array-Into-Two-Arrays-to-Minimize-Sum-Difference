class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        const int half_size = nums.size() / 2;
        const int quarter_size = nums.size() / 4;

        vector<vector<int>> s1(quarter_size + 1); 
        vector<vector<int>> s2(quarter_size + 1);

        dfs(nums, 0, half_size, 0, 0, s1);
        dfs(nums, half_size, nums.size(), 0, 0, s2);
       
        return countDiff(
            s1, 
            s2, 
            quarter_size, 
            accumulate(nums.begin(), nums.begin() + half_size, 0), 
            accumulate(nums.begin() + half_size, nums.end(), 0)
        );
    }

    inline int countDiff(vector<vector<int>> s1, vector<vector<int>> s2, int quarter_size, const int sum1, const int sum2) 
    {
        int min_diff = 0x7fffffff;

        for (int k = 0; k <= quarter_size; ++k)
        {
            sort(s2[k].begin(), s2[k].end());

            for (int s1_sum : s1[k])
            {
                int conn = (sum1 + sum2) / 2 - (sum1 - s1_sum);

                auto it = lower_bound(s2[k].begin(), s2[k].end(), conn);

                int diff = (sum1 - sum2 - 2 * s1_sum);
                int absolute_diff = getMinDiff(s2[k], diff, it);
                
                min_diff = min(min_diff, absolute_diff);
            }
        }

        return min_diff;
    }

    inline int getMinDiff(const vector<int>& s2_k, int diff, vector<int>::iterator& it_value) 
    {
        int min_diff = 0x7fffffff;

        if (!(it_value != s2_k.end() || it_value != s2_k.begin())) {
            return min_diff;
        }
        else
        {
            if (it_value != s2_k.end()) {
                min_diff = min(min_diff, abs(diff + (*it_value) * 2));
            }
            if (it_value != s2_k.begin()) {
                min_diff = min(min_diff, abs(diff + (*(--it_value)) * 2));
            }
            return min_diff;
        }
    }


    void dfs(vector<int>& nums, int i, int end, int k, int sum, vector<vector<int>>& sums) {
        if (i != end && k < nums.size() / 4) {
            dfs(nums, i + 1, end, k, sum, sums);
            dfs(nums, i + 1, end, k + 1, sum + nums[i], sums);
        }
        else {
            sums[k].push_back(sum);
        }
    }
};
