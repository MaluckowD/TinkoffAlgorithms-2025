#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

string alg(string s)
{
  sort(s.begin(), s.end());
  string sorted_letters;
  set<char> letters(s.begin(), s.end());
  for (char letter : letters)
  {
    sorted_letters += letter;
  }
  set<char> set_s(s.begin(), s.end());
  bool flag = true;
  char mn = 'a';
  for (char q : set_s)
  {
    int count = 0;
    for (char c : s)
    {
      if (c == q)
      {
        count++;
      }
    }
    if (count != 1)
    {
      flag = false;
    }
    if (count % 2 != 0)
    {
      mn = min(mn, q);
    }
  }

  if (flag)
  {
    return string(1, *set_s.begin());
  }

  vector<char> arr;
  for (char q : sorted_letters)
  {
    int count = 0;
    for (char c : s)
    {
      if (c == q)
      {
        count++;
      }
    }
    count -= count % 2;
    for (int i = 0; i < count; ++i)
    {
      arr.push_back(q);
    }
  }

  int n = arr.size() + (mn != 'a');
  vector<char> ans(n);
  sort(arr.begin(), arr.end());
  int i = 0;
  while (!arr.empty())
  {
    ans[i] = arr[0];
    arr.erase(arr.begin());
    if (arr.size() > 0)
    {
      ans[n - i - 1] = arr.back();
      arr.pop_back();
    }

    i++;
  }
  if (mn != 'a')
  {
    ans[n / 2] = mn;
  }
  return string(ans.begin(), ans.end());
}

int main()
{
  int n;
  cin >> n;
  string line;
  cin >> line;
  string ans = alg(line);
  cout << ans << endl;
  return 0;
}