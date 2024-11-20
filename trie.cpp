#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;

    struct TrieNode
    {
        TrieNode * child[31];
        bool end;
        TrieNode()
        {
            end = false;
            for(int i=0;i<31;i++) child[i] = nullptr;
        }
    };

    class Trie
    {
        TrieNode * root;
        public:
        Trie() {root = new TrieNode();}

        int lind(int s)
        {
            if(s == 1072) return 0;
            if(s == 1073) return 1;
            if(s == 1074) return 2;
            if(s == 1075) return 3;
            if(s == 1076) return 4;
            if(s == 1107) return 5;
            if(s == 1077) return 6;
            if(s == 1078) return 7;
            if(s == 1079) return 8;
            if(s == 1109) return 9;
            if(s == 1080) return 10;
            if(s == 1112) return 11;
            if(s == 1082) return 12;
            if(s == 1083) return 13;
            if(s == 1113) return 14;
            if(s == 1084) return 15;
            if(s == 1085) return 16;
            if(s == 1114) return 17;
            if(s == 1086) return 18;
            if(s == 1087) return 19;
            if(s == 1088) return 20;
            if(s == 1089) return 21;
            if(s == 1090) return 22;
            if(s == 1116) return 23;
            if(s == 1091) return 24;
            if(s == 1092) return 25;
            if(s == 1093) return 26;
            if(s == 1094) return 27;
            if(s == 1095) return 28;
            if(s == 1119) return 29;
            if(s == 1096) return 30;
            return -1;
        }

    int lchar(int index) {
        if (index == 0) return 1072;
        if (index == 1) return 1073;
        if (index == 2) return 1074;
        if (index == 3) return 1075;
        if (index == 4) return 1076;
        if (index == 5) return 1107;
        if (index == 6) return 1077;
        if (index == 7) return 1078;
        if (index == 8) return 1079;
        if (index == 9) return 1109;
        if (index == 10) return 1080;
        if (index == 11) return 1112;
        if (index == 12) return 1082;
        if (index == 13) return 1083;
        if (index == 14) return 1113;
        if (index == 15) return 1084;
        if (index == 16) return 1085;
        if (index == 17) return 1114;
        if (index == 18) return 1086;
        if (index == 19) return 1087;
        if (index == 20) return 1088;
        if (index == 21) return 1089;
        if (index == 22) return 1090;
        if (index == 23) return 1116;
        if (index == 24) return 1091;
        if (index == 25) return 1092;
        if (index == 26) return 1093;
        if (index == 27) return 1094;
        if (index == 28) return 1095;
        if (index == 29) return 1119;
        if (index == 30) return 1096;
        return -1;
    }

    void insert(wstring s)
    {
        TrieNode * node = root;
        for(wchar_t c : s)            
        {
            int index = lind((int)c);
            if (index == -1) {
                wcerr << L"Skipping word with invalid character: " << s << endl;
                return;
            }
            if (!node->child[index]) node->child[index] = new TrieNode;
            node = node->child[index];
        }
        node->end = true;
    }

    void print(TrieNode* node, wstring current, wstring prefix, wofstream & out) 
    {
        if (node == nullptr) return;
        if (node->end) out << prefix + current << endl;

        for (int i = 0; i < 31; ++i) 
        {                
            if (node->child[i]) 
            {
                wchar_t c = (wchar_t)lchar(i);
                print(node->child[i], current + c, prefix, out);
            }
        }
    }

    void search(wstring prefix, wofstream & out) 
    {
        TrieNode* node = root;

        for (wchar_t c : prefix) 
        {
            int index = lind((int)c);
            if (index == -1 || node->child[index] == nullptr) 
            {
                out << L"No words found with prefix: " << prefix << endl;
                return;
            }
            node = node->child[index];
        }
        print(node, L"", prefix, out);
    }

};

    int main()
    {
        _wsetlocale(LC_ALL, L"");

        wifstream f("all.txt");
        wofstream out("output.txt");

        f.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
        out.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

        if (!f.is_open()) {
            wcerr << L"Error: Unable to open input file 'all.txt'." << endl;
            return 1;
        }
        if (!out.is_open()) {
            wcerr << L"Error: Unable to open output file 'output.txt'." << endl;
            return 1;
        }

        Trie t;
        t.insert(L"сара");
        t.insert(L"салса");
        t.insert(L"сарма");
        t.insert(L"скара");
        t.insert(L"ара");

        t.search(L"са", out);

        f.close();
        out.close();

    /*  
        wstring s;
        while(getline(f, s))
        {
            t.insert(s);
        }

        cout<<"Enter a prefix to search: "<<endl;
        wstring prefix;
        wcin>>prefix;
        t.search(prefix);    
    */
        return 0;
    }
