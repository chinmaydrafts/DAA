#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void printhuffman(Node *root, string code)
{
    if (!root)
        return;
    if (!root->left && !root->right) // leaf node
    {
        cout << root->ch << ":" << root->freq << ":" << code << endl;
    }
    printhuffman(root->left, code + "0");
    printhuffman(root->right, code + "1");
}

int main()
{
    string str;
    cout << "Enter string :";
    cin >> str;

    unordered_map<char, int> mp;
    for (char ch : str)
    {
        mp[ch]++;
    }

    priority_queue<Node *, vector<Node *>, compare> pq;

    for (auto it : mp)
    {
        pq.push(new Node(it.first, it.second));
    }

    while (pq.size() > 1)
    {
        Node *t1 = pq.top();
        pq.pop();
        Node *t2 = pq.top();
        pq.pop();

        Node *merged = new Node('$', t1->freq + t2->freq);
        merged->left = t1;
        merged->right = t2;

        pq.push(merged);
    }

    cout << "Huffman codes :" << endl;
    Node *root = pq.top();
    string code = "";
    printhuffman(root, code);   
}