#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch2(vector<int> &list, int left, int right, int target )
{
  for (;left <= right;)
    {
      int mid = (left + right ) >> 1;
      if (list[mid] == target)
        {
          return mid;
        }
      else if (list[mid] > target)
        {
          right = mid - 1;
        }
      else if (list[mid] < target)
        {
          left = mid + 1;
        }
    }
  return -1;
}


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int one = binarySearch2(nums, left, right, target);
        int first = one, last = one;
        while(first > 0 && nums[first - 1] == nums[one])
        {
            first--;
        }
        while(last < right && nums[last + 1] == nums[one])
        {
            last++;
        }
        vector<int> ret;
        ret.push_back(first);
        ret.push_back(last);
        return  ret;
    }
};

int main()
{
    vector<int> l = {5,7,7,8,8,10};
    Solution s;
    vector<int> ret = s.searchRange(l, 8);
    cout << ret[0] << " " << ret[1] << endl;
    return 0;
}
