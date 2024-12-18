#include <fstream>
#include <iostream>
#include <map>
#include <queue>
using namespace std;
struct Node {
    char chr;
    int freq;
    Node *left, *right;

    Node(char chr = '\0', int freq = 0, Node* left = nullptr,
         Node* right = nullptr)
            : chr(chr), freq(freq), left(left), right(right) {}
};

struct comparare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq) return a->chr > b->chr;
        return a->freq > b->freq;
    }
};

Node* buildHuffmanTree(const map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, comparare> pq;
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq, left, right);
        pq.push(merged);
    }

    return pq.top();
}

string decodeHuffman(Node* rad, const string& encodedStr) {
    string decodedText;
    Node* current = rad;
    for (char bit : encodedStr) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            decodedText += current->chr;
            current = rad;
        }
    }
    return decodedText;
}

int main(int argc,char* argv[]) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);

    int n;
    f >> n;

    map<char, int> frecv;
    char ch;
    int frv;
    for (int i = 0; i < n; ++i) {
        f>> ch >> frv;
        frecv[ch] = frv;
    }

    string encodedString;
    f >> encodedString;
    f.close();

    Node* root = buildHuffmanTree(frecv);
    string decodedString = decodeHuffman(root, encodedString);
    g << decodedString << '\n';
    g.close();
    return 0;
}