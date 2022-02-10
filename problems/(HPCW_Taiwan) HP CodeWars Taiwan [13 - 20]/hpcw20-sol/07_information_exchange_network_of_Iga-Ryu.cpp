#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <sstream>      // std::stringstream
#include <cmath>
#include <unordered_map>

using namespace std;

// Disjoint Set Union

class DSU
{
  public:
    // Union 2 sets into 1, replace one's root to another
    inline void union_sets(int l, int r)
  {
    sets_[find_set_root(l)] = sets_[find_set_root(r)];
  }

  // Find the root of a particular number, the root points to itself
  inline int find_set_root(int s)
  {
    while (sets_[s] != s) // Has a link to other node
    {
      s = sets_[s]; // Jump to other node
    }
    return sets_[s];
  }

  // Print sets, for debug only
  // void print_vector()
  // {
  //   for (int i = 0; i < sets_.size(); ++i)
  //   {
  //     cout<< "p[" <<i << "]="<<sets_[i]<<endl;
  //   }
  // }

  DSU(int n): sets_(n)
  {
    // Let all items point to itself
    for (auto i = 0; i < sets_.size(); ++i)
    {
      sets_[i] = i;
    }
  }
  private:
    vector < int > sets_;
};

class Solution
{
  public:
    int get_max_component_size()
  {
    int largest_size = 1;
    for (auto i: components_)
    {
      largest_size = max(largest_size, i.second);
    }
    return largest_size;
  }

  int get_group_numbers()
  {
    return components_.size();
  }

  Solution(vector < int > & _target)
  {
    target_ = _target;
    solve();
  }

  private:
    // input
    vector < int > target_;
  //<root node, size>
  unordered_map < int, int > components_;

  void solve()
  {
    int n = * max_element(target_.begin(), target_.end());
    DSU dsu(n + 1);
    for (int i: target_)
    {
      int q = sqrt(i);
      for (int f = 2; f <= q; ++f) // using sqrt is enough since we will union f and i/f
      {
        if ((i % f) == 0)
        {
          int k = i / f;
          dsu.union_sets(i, f);
          dsu.union_sets(i, i / f);
        }
      }
    }
    // Calculate the number of each set
    for (int i: target_)
    {
      ++components_[dsu.find_set_root(i)];
    }
    //dsu.print_vector();
  };
};

int main()
{
  double START,END;
  string str;
  vector<int> a;
  // Get the string
  getline(cin, str);
  // Print the words
  stringstream  ss(str);
  for (int i; ss >> i;) {
    a.push_back(i);
    if (ss.peek() == ',')
        ss.ignore();
  }
  Solution * p = new Solution(a);
  int group_number = p -> get_group_numbers();
  int max_component_size = p -> get_max_component_size();
  cout << group_number << "," << max_component_size;
};