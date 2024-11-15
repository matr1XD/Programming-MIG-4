#include <bits/stdc++.h>
using namespace std;

class RadixNode
{
  public:
    string word;
    bool end;
    RadixNode * child[26];
    
    RadixNode(string word = "", bool end = false)
    {
        this->word = word;
        this->end = end;
        for(int i=0; i<26;i++) this->child[i] = nullptr;
    }
    
    ~RadixNode()
    {
        for(int i=0;i<26;i++)
        {
            delete this->child[i];
            this->child[i] = nullptr;
        }
    }
    
    int getCutPosition(RadixNode * crawl, string key)
    {
        int i=0;
        while((i < crawl->word.size()) and (i < key.size()) and (crawl->word[i] == key[i]))
        {
            i++;
        }
        return i;
    }
    
    void moveChildNodes(RadixNode * &root, RadixNode * &target)
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
    
    bool isLeafNode(RadixNode * root)
    {
        for(int i=0;i<26;i++)
        {
            if(root->child[i]) return false;
        }
        return true;
    }
    
    RadixNode * splitNodes(RadixNode * &root, string left, int pos)
    {
        bool hasChild = false;
        if(!isLeafNode(root)) hasChild=true;
        
        string right = root->word.substr(pos);;
        root->word = root->word.substr(0, pos);
        
        int ri = right[0] - 'a';
        int li = left[0] - 'a';
        
        RadixNode * leftChild, *rightChild;
        
        if(hasChild and !root->end)
        {
            leftChild = new RadixNode(left, true);
            rightChild = new RadixNode(right, false);
        }
        else
        {
            leftChild = new RadixNode(left, true);
            rightChild = new RadixNode(right, true);
        }
        
        moveChildNodes(root, rightChild);
        
        root->child[li] = leftChild;
        root->child[ri] = rightChild;
        
        return root;
    }
    
    RadixNode * Insert(string key, RadixNode * &root)
    {
        if(key.size() == 0) return root;
        
        int pos;
        RadixNode * crawl = root;
        int index = key[0]-'a';
        
        if(crawl->child[index])
        {
            crawl = crawl->child[index];
            pos = getCutPosition(crawl, key);
            key = key.substr(pos);
            
            if(pos < crawl->word.size()) crawl = splitNodes(crawl, key, pos);
            else Insert(key, crawl);
            
            if(key.size() == 0) crawl->end = true;
            else crawl->child[index] = new RadixNode(key, true);
        }
        
        return crawl;
    }
    
    string suffix;
    bool Find(RadixNode * root, string word)
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
                if(Find(root->child[i], word)) return true;
                suffix = suffix.substr(0, suffix.size() - root->child[i]->word.size());
            }
        }
        
        return (root->end and (suffix == word));
    }
    
    string suff;
    int cnt, pos;
    void Traverse(RadixNode * root)
    {
        if(root->end)
        {
            cout<<suff<<" "<<endl;
        }
        
        if(isLeafNode(root)) return;
        
        for(int i=0;i<26;i++)
        {
            if(root->child[i])
            {
                pos = suff.size();
                suff += root->child[i]->word;
                Traverse(root->child[i]);
                suff = suff.substr(0, suff.size() - root->child[i]->word.size());
            }
        }
        
        return;
    }
};

int main() {

    RadixNode *root = new RadixNode();

    root->Insert("rubens", root);
    root->Insert("romane", root);
    root->Insert("romanus", root);
    root->Insert("romulus", root);
    root->Insert("ruber", root);
    root->Insert("rubicon", root);
    root->Insert("rubicundus", root);
    
    root->Traverse(root);
    cout << root->Find(root, "ruber") << endl;
}
