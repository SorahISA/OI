#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Solution {
public:
  Solution(int entrySize) {
    _entrySize = entrySize;
    _entryColor.resize(entrySize, 0);
    _separated = 0;
  };

  bool isBipartite(vector<vector<int>>& graph) {

    _entryColor[0] = 1;

    // Lable all entries and return false if condition fails
    for (int i = 0; i < _entrySize; ++i) {
      for (int j = 0 ; j < graph[i].size(); ++j) {
        if (_entryColor[graph[i][j]] == 0) {
          if (_entryColor[i] == 0) {
            _entryColor[i] = 1;  // If the entry not label yet.
          }
          _entryColor[graph[i][j]] = ~_entryColor[i];
        } else if (_entryColor[graph[i][j]] == _entryColor[i]) {
          return false;
        }
      }
    }

    // Separate into 2 groups
    for (int i = 0; i < _entrySize; i++) {
      if (_entryColor[i] == 1) {
        _group1.push_back(i);
      } else {
        _group2.push_back(i);
      }
    }

    _separated = 1;
    return true;
  };

  void display_output() {

    if (!_separated) {
      cout << "[0]" << endl;
      return;
    }

    display_group(_group1);
    cout << " ";
    display_group(_group2);
    return;
  }

private:
  void display_group(vector<int> &group) {
    cout << "[";
    for (int i = 0; i < group.size(); i++) {
      if (i != 0) {
        cout << ",";
      }
      cout << group.at(i);
    }
    cout << "]";
  }

  vector<int> _group1;
  vector<int> _group2;
  vector<int> _entryColor;
  int _entrySize;
  int _separated;
};

int main(int argc, char **argv) {
  string line;
  getline(std::cin, line);

  char *ptr = &line[0];

  vector<vector<int>> theGraph;
  vector<int> theEntries;
  int value;

  ptr = strtok(ptr, "[, ");
  while (ptr != NULL) {
    char *end = strstr(ptr, "]");

    value = atoi(ptr);
    theEntries.push_back(value);

    if (end) {
      theGraph.push_back(theEntries);
      theEntries.clear();
    }
    ptr = strtok(NULL, "[, ");
  }

  Solution theSolution(theGraph.size());
  theSolution.isBipartite(theGraph);
  theSolution.display_output();

  return 0;
}
