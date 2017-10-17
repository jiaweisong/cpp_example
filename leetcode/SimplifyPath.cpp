#include <iostream>
using namespace std;

class Solution
{
public:
  string simplifyPath(string path)
  {
    size_t len = path.length(), i = 0, pos = 0, dot_count = 0;
    while (i < len || dot_count > 0)
    {
      if (i < len && path[i] == '.')
      {
        ++dot_count;
      }
      else
      {
        if (dot_count > 2
          || (dot_count > 0 && i < len && path[i] != '/')
          || (dot_count == 1 && pos > 0 && path[pos-1] != '/'))
        {
          while (dot_count-- > 0)
            path[pos++] = '.';
          dot_count = 0;
        }
        if (dot_count == 2)
        {
          int new_p = (pos > 1 && path[pos-1] == '/') ? pos-2 : pos-1;
          while (new_p >= 0 && path[new_p] != '/')
          {
            --new_p;
          }
          pos = new_p+1;
          dot_count = 0;
        }
        else if (dot_count == 1 || dot_count > 2)
        {
          dot_count = 0;
        }
        else
        {
          if (path[i] != '/' || (i == 0 || path[i-1] != path[i]))
            path[pos++] = path[i];
        }
      }
      ++i;
    }
    if (pos > 1 && path[pos-1] == '/')
      --pos;
    path.resize(pos);
    return path;
  }
};

int main()
{
  Solution s;
  string path;

  path = "/";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "////";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/../";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/...";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/.../";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/..hidden/";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/./aa../";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/a/./b/../../c/";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/a/./b/../c////..///";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/.//aa/./bb";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;

  path = "/.//aa./bb//aa";
  cout << "path = " << path << " result = " << s.simplifyPath(path) << endl;
  return 0;
}
