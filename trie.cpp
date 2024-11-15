#include <iostream>
using namespace std;

struct TrieNode
{
    TrieNode * child[26];
    bool end;
    TrieNode()
    {
        end = false;
        for(int i=0;i<26;i++) child[i] = nullptr;
    }
};

class Trie
{
    TrieNode * root;
    public:
    Trie()
    {
        root = new TrieNode();
    }
    
    void insert(string s)
    {
        TrieNode * node = root;
        for(int i=0;i<s.size();i++)
        {
            if(node->child[s[i]-'a'] == nullptr)
            {
                node->child[s[i]-'a'] = new TrieNode;
            }
            node = node->child[s[i]-'a'];
        }
        node->end = true;
    }
    
    bool search(string s)
    {
        TrieNode * node = root;
        for(int i=0;i<s.size();i++)
        {
            if(node->child[s[i]-'a'] == nullptr) return false;
            node = node->child[s[i] - 'a'];
        }
        return true;
    }
    
    void print(TrieNode* node, string prefix) const
    {
        if (node->end) {
            cout << prefix << endl;
        }
        for (int i = 0; i < 26; i++) {
            if (node->child[i]) {
                print(node->child[i],
                      prefix + char('a' + i));
            }
        }
    }
    
    void print() const { print(root, ""); }
};

int main()
{
    Trie t;
    t.insert("geek");
    t.insert("coder");
    
    cout<<t.search("geek");
    cout<<t.search("coders");
    
    t.insert("coders");
    cout<<t.search("coders");

    return 0;
}
