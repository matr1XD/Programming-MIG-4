#include <bits/stdc++.h>
using namespace std;

class PatriciaNode
{
    string word;
    bool end;
    PatriciaNode * child[26];
  public: 
    PatriciaNode(string word = "", bool end = false)
    {
        this->word = word;
        this->end = end;
        for(int i=0; i<26;i++) this->child[i] = nullptr;
    }
    
    ~PatriciaNode()
    {
        for(int i=0;i<26;i++)
        {
            delete this->child[i];
            this->child[i] = nullptr;
        }
    }
    
    int getCutPosition(PatriciaNode * node, string s)
    {
        int i=0;
        while((i < node->word.size()) and (i < s.size()) and (node->word[i] == s[i]))
        {
            i++;
        }
        return i;
    }
    
    void moveChildNodes(PatriciaNode * &root, PatriciaNode * &target)
    {
        root->end = false;
        for(int i=0;i<26;i++)
        {
            if(root->child[i])
            {
                target->child[i] = root->child[i];
                root->child[i] = nullptr;
            }
        }
        return;
    }
    
    bool isLeafNode(PatriciaNode * root)
    {
        for(int i=0;i<26;i++)
        {
            if(root->child[i]) return false;
        }
        return true;
    }
    
    PatriciaNode * splitNodes(PatriciaNode * &root, string left, int pos)
    {
        bool hasChild = false;
        if(!isLeafNode(root)) hasChild=true;
        
        string right = root->word.substr(pos);;
        root->word = root->word.substr(0, pos);
        
        int ri = right[0] - 'a';
        int li = left[0] - 'a';
        
        PatriciaNode * leftChild, *rightChild;
        
        if(hasChild and !root->end)
        {
            leftChild = new PatriciaNode(left, true);
            rightChild = new PatriciaNode(right, false);
        }
        else
        {
            leftChild = new PatriciaNode(left, true);
            rightChild = new PatriciaNode(right, true);
        }
        
        moveChildNodes(root, rightChild);
        
        root->child[li] = leftChild;
        root->child[ri] = rightChild;
        
        return root;
    }
    
    PatriciaNode* insertNode(string s, PatriciaNode * &root)
    {
        if (s.empty()) return root;

        PatriciaNode* node = root;
        int index = s[0] - 'a';

        if (!node->child[index])
        {
            node->child[index] = new PatriciaNode(s, true);
            return node->child[index];
        }

        node = node->child[index];
        int pos = getCutPosition(node, s);

        if (pos == node->word.size())
        {
            string remainingKey = s.substr(pos);

            if (!remainingKey.empty()) return insertNode(remainingKey, node);
            else
            {
                node->end = true;
                return node;
            }
        }

        string remainingKey = s.substr(pos);
        string remainingNodeWord = node->word.substr(pos);

        PatriciaNode* newChild = new PatriciaNode(remainingNodeWord, node->end);
        for (int i = 0; i < 26; i++)
        {
            newChild->child[i] = node->child[i];
            node->child[i] = nullptr;
        }

        node->word = node->word.substr(0, pos);
        node->end = false;

        node->child[remainingNodeWord[0] - 'a'] = newChild;

        if (!remainingKey.empty())
        {
            PatriciaNode* newKeyNode = new PatriciaNode(remainingKey, true);
            node->child[remainingKey[0] - 'a'] = newKeyNode;
        }
        else node->end = true;

        return node;
    }

    
    string suffix;
    bool searchNode(PatriciaNode * root, string word)
    {
        int cnt, pos;
        if(root->end and suffix == word) return true;
        
        if(isLeafNode(root)) return false;
        
        for(int i=0;i<26;i++)
        {
            if(root->child[i])
            {
                pos = suffix.size();
                suffix += root->child[i]->word;
                if(searchNode(root->child[i], word)) return true;
                suffix = suffix.substr(0, suffix.size() - root->child[i]->word.size());
            }
        }
        
        return (root->end and (suffix == word));
    }
    
    string suff = "";
    int cnt, pos;
    void printNode(PatriciaNode * root)
    {
        if(root->end) cout<<suff<<" "<<endl;
        
        if(isLeafNode(root)) return;
        
        for(int i=0;i<26;i++)
        {
            if(root->child[i])
            {
                pos = suff.size();
                suff += root->child[i]->word;
                printNode(root->child[i]);
                suff = suff.substr(0, suff.size() - root->child[i]->word.size());
            }
        }
        
        return;
    }
};

int main() {

    PatriciaNode *root = new PatriciaNode();

    root->insertNode("rubens", root);
    root->insertNode("romane", root);
    root->insertNode("romanus", root);
    root->insertNode("romulus", root);
    root->insertNode("ruber", root);
    root->insertNode("rubicon", root);
    root->insertNode("rubicundus", root);
    
    root->printNode(root);
    cout << root->searchNode(root, "ruber") << endl;
}
