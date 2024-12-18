#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;
struct Node {
    char chr;
    int freq;
    Node *left, *right;

    Node(char chr, int freq, Node* left = nullptr, Node* right = nullptr)
            : chr(chr), freq(freq), left(left), right(right) {}
};

struct compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq) return a->chr > b->chr;
        return a->freq > b->freq;
    }
};

void encode(Node* root, const string& str,
            map<char, string>& huffman) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffman[root->chr] = str;
    }

    encode(root->left, str + "0", huffman);
    encode(root->right, str + "1", huffman);
}

void Huffman(const string& text, ofstream& g) {
    map<char, int> freq_chr;
    for (char character : text) {
        freq_chr[character]++;
    }

    priority_queue<Node*, vector<Node*>, compare> pq;

    for (auto pair : freq_chr) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    map<char, string> huffman;
    encode(root, "", huffman);

    g << freq_chr.size() << '\n';
    for (auto pair : freq_chr) {
        g << pair.first << " " << pair.second << '\n';
    }

    string new_string;
    for (char ch : text) {
        new_string += huffman[ch];
    }
    g << new_string << '\n';
}

int main(int argc,char* argv[]) {
    ifstream f(argv[1]);
    ofstream g(argv[2]);
    stringstream ss;
    ss << f.rdbuf();
    string text = ss.str();
    f.close();

    Huffman(text,g);
    g.close();
    return 0;
}