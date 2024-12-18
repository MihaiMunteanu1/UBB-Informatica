#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> parinte;
    vector<int> rank;

public:
    explicit UnionFind(int size) : parinte(size), rank(size, 0) {
        for (int i = 0; i < size; ++i) {
            parinte[i] = i;
        }
    }

    int gasireNod(int node) {
        int rad = node;

        while (rad != parinte[rad]) {
            rad = parinte[rad];
        }

        while (node != rad) {
            int next = parinte[node];
            parinte[node] = rad;
            node = next;
        }

        return rad;
    }

    void unionIntreNoduri(int nod1, int nod2) {
        int rad1 = gasireNod(nod1);
        int rad2 = gasireNod(nod2);

        if (rad1 != rad2) {
            if (rank[rad1] > rank[rad2]) {
                parinte[rad2] = rad1;
            } else {
                parinte[rad2] = rad1;
                if (rank[rad2] == rank[rad1]) {
                    rank[rad2]++;
                }
            }
        }
    }
};

bool comparare(const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
    if (a.second != b.second) {
        return a.second < b.second;
    } else {
        return a.first.first < b.first.first;
    }
}

vector<pair<pair<int, int>, int>> tree_sort(vector<pair<pair<int, int>, int>>& tree) {
    sort(tree.begin(), tree.end(), comparare);
    return tree;
}

vector<pair<pair<int, int>, int>> Kruskal(vector<pair<pair<int, int>, int>>& tree, int src) {
    vector<pair<pair<int, int>, int>> T;
    UnionFind union_find(src);
    for (const auto& t : tree) {
        int nod1 = t.first.first;
        int nod2 = t.first.second;
        if (union_find.gasireNod(nod1) != union_find.gasireNod(nod2)) {
            union_find.unionIntreNoduri(nod2, nod1);
            auto m = make_pair(t.first, t.second);
            T.push_back(m);
            if (T.size() == src - 1) {
                break;
            }
        }
    }
    return T;
}

int main(int argc,char* argv[]) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    int v, e;
    f >> v >> e;
    vector<pair<pair<int, int>, int>> tree(e);

    for (int i = 0; i < e; ++i) {
        int x, y, w;
        f >> x >> y >> w;
        if (x > y)
            swap(x, y);
        tree[i] = make_pair(make_pair(x, y), w);
    }

    auto tr = tree_sort(tree);
    auto T = Kruskal(tr, v);

    int sum = 0;
    for (const auto& t : T) {
        sum += t.second;
    }

    g << sum << "\n";
    g << T.size() << "\n";
    for (const auto& t : T) {
        g << t.first.first << " " << t.first.second << "\n";
    }

    f.close();
    g.close();
    return 0;
}
