#include <iostream>
#include <vector>

bool good(const std::vector<int> &boxes, int k, int r)
{
  int cows_count = 1;
  int last_box = boxes[0];
  for (int i = 1; i < boxes.size(); ++i)
  {
    if (boxes[i] - last_box >= r)
    {
      cows_count += 1;
      last_box = boxes[i];
    }
  }
  return cows_count >= k;
}

int main()
{
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
  {
    std::cin >> a[i];
  }

  int l = 0;
  int r = a[n - 1] - a[0] + 1;

  while (r - l > 1)
  {
    int m = (l + r) / 2;
    if (good(a, k, m))
    {
      l = m;
    }
    else
    {
      r = m;
    }
  }
  std::cout << l << std::endl;
  return 0;
}