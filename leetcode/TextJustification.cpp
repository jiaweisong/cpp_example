#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  vector<string> fullJustify(vector<string>& words, int maxWidth)
  {
    vector<string> result;
    result.reserve(words.size());
    int start = 0, curr = 0, total_length = 0, str_length = 0, even_space = 0, mod = 0;

    while (curr < words.size() || start < curr)
    {
      if (curr < words.size() && total_length + words[curr].length() <= maxWidth)
      {
        auto& str = words[curr];
        total_length += (str.length() + 1);
        str_length   += str.length();
        ++curr;
      }
      else
      {
        int remain_space = maxWidth - str_length;
        int str_num      = curr - start;
        string combined_word;
        if (str_num == 1)
        {
          combined_word.assign(words[start++] + std::string(remain_space, ' '));
        }
        else if (curr < words.size())
        {
          even_space = remain_space/(str_num - 1);
          mod = remain_space % (str_num - 1);
          while (start < curr)
          {
            combined_word.append(words[start]);
            if (start != curr - 1)
              combined_word.append(even_space + (mod-- > 0 ? 1 : 0), ' ');
            ++start;
          }
        }
        else
        {
          while (start < curr)
          {
            combined_word.append(words[start]);
            if (start != curr - 1)
              combined_word.append(1, ' ');
            ++start;
          }
          combined_word.append(maxWidth - combined_word.length(), ' ');
        }
        result.push_back(combined_word);
        total_length = 0; str_length = 0; str_num = 0;
      }
    }
    if (result.empty() && maxWidth > 0)
    {
      result.emplace_back(std::string(maxWidth, ' '));
    }
    return result;
  }
};


int main()
{
  Solution s;
  vector<string> input, result;
  int width = 0;

  input = {};
  width = 16;
  result = s.fullJustify(input, width);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout <<"\"" << *it << "\"" << endl;
  }
  cout << endl;

  input = {"justification...", "This", "is", "an", "example", "of", "text", "justification."};
  width = 16;
  result = s.fullJustify(input, width);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout <<"\"" << *it << "\"" << endl;
  }
  cout << endl;

  input = {"What","must","be","shall","be."};
  width = 12;
  result = s.fullJustify(input, width);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout <<"\"" << *it << "\"" << endl;
  }
  cout << endl;
  return 0;
}
