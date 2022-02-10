//#include <bits/stdc++.h>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int Time = 0;
struct Node {
    int low;
    int time;
    list<int> nextNodes;
    Node() : low(0), time(0), nextNodes(list<int>()) {}
};

void DFS(vector<Node>& Nodes, set<pair<int, int>>& bridges, int parent, int current) {
    Nodes[current].low = Nodes[current].time = ++Time;

    for (auto& node : Nodes[current].nextNodes) {
        if (node != parent) { //避免走回頭路
            if (Nodes[node].time > 0)  //backedge
                Nodes[current].low = min(Nodes[current].low, Nodes[node].time);
            else { //tree edge
                DFS(Nodes, bridges, current, node);

                Nodes[current].low = min(Nodes[current].low, Nodes[node].low);
                if (Nodes[node].low > Nodes[current].time) { //不用等號
                    if (node < current) bridges.insert(make_pair(node, current));
                    else bridges.insert(make_pair(current, node));
                }
            }
        }
    }
}

int main() {

    int num, numLink, from, to;
    while (cin >> num) {
        if (num == 0) cout << "0\n";
        else {
            Time = 0;
            set<pair<int, int>> bridges;
            vector<Node> Nodes(num, Node());
            for (int i = 0; i < num; ++i) {
                cin >> from >> numLink;
                for (int j = 0; j < numLink; ++j) {
                    cin >> to;
                    Nodes[from].nextNodes.push_back(to);
                }
            }

            for (int i = 0; i < num; ++i)
                if (Nodes[i].time == 0)
                    DFS(Nodes, bridges, i, i);

            cout << bridges.size() << "\n";
            for (auto& link : bridges)
                cout << link.first << " " << link.second << endl;
        }
    }

    return 0;
}
