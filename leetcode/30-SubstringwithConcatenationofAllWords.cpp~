#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  bool DeepSearch(int start, string& s, unordered_map<string,int>& word_map, int count, int word_length)
  {
    if (0 == count)
    {
      return true;
    }
    if (start <= s.length() - word_length)
    {
      string word = s.substr(start, word_length);
      if (word_map.find(word) != word_map.end() && word_map[word] > 0)
      {
        --word_map[word];
        --count; 
        bool ret = DeepSearch(start+word_length, s, word_map, count, word_length);
        ++word_map[word];
        return ret;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> ret;
    unordered_map<string,int> word_map;
    int word_length = words.empty() ? 1 : words[0].length();
    for (int i = 0; i < words.size(); ++i)
    {
      if (word_map.find(words[i]) != word_map.end())
      {
        ++word_map[words[i]];
      }
      else
      {
        word_map[words[i]] = 1;
      }
    }
    int count = words.size();
    int length = s.length() - (word_length * count);
    for (int i = 0; i <= length; ++i)
    {
      if (DeepSearch(i, s, word_map, count, word_length))
      {
        ret.push_back(i);
      }
    }
    return ret;    
  }
};

int main()
{
  Solution s;
  vector <int> ret;
  //vector<string> words = {"bar", "foo"};
  //vector<string> words = {"word","good","best","good"};
  vector<string> words = {"fooo","barr","wing","ding","wing"};
  //ret = s.findSubstring("barfoothefoobarman", words);
  //ret = s.findSubstring("wordgoodgoodgoodbestword",words);
  ret = s.findSubstring("lingmindraboofooowingdingbarrwingmonkeypoundcake",words);
  for (int i = 0; i < ret.size(); ++i)
  {
    cout<<ret[i]<<"    ";
  }
  cout<<endl;
  return 0;
}
