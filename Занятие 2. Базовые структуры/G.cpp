#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main()
{
  deque<string> left_queue;
  deque<string> right_queue;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    string a, b;
    cin >> a;

    if (a == "-")
    {
      cout << left_queue.front() << endl;
      left_queue.pop_front();
      if (right_queue.size() > left_queue.size())
      {
        left_queue.push_back(right_queue.front());
        right_queue.pop_front();
      }
    }

    else if (a == "+")
    {
      cin >> b;
      right_queue.push_back(b);
      if (right_queue.size() > left_queue.size())
      {
        left_queue.push_back(right_queue.front());
        right_queue.pop_front();
      }
    }

    else if (a == "*")
    {
      cin >> b;
      left_queue.push_back(b);
      if (left_queue.size() - right_queue.size() > 1)
      {
        right_queue.push_front(left_queue.back());
        left_queue.pop_back();
      }
    }
  }
}