#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
      unordered_map<int, int> index;
      index[0] = -1;
      int len = array.size();
      int preSum = 0;
      int max = 0;
      int start = -1;
      for (int i = 0; i < len; i++)
	{
	  if (isalpha(array[i][0]))
	    {
	      preSum += 1;
	    }
	  else
	    {
	      preSum -= 1;
	    }
	  if (index.count(preSum) > 0)
	    {
	      int first = index[preSum];
	      if (i - first > max)
		{
		  max = i - first;
		  start = first + 1;
		}
	    }
	  else
	    {
	      index[preSum] = i;
	    }
	}

      return vector<string> (array.begin() + start, array.begin() + start + max);
    }
};

int main()
{
  vector<string> input = {"A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"};
  Solution s;
  vector<string> output = s.findLongestSubarray(input);

  for(string v : output)
    {
      cout << v << ',';
    }
  cout << endl;
  return 0;
}
