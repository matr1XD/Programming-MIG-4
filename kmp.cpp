#include <bits/stdc++.h>
using namespace std;

class String
{
    char * chars;
    unsigned int length;

    public:
    String(const char * chars = "")
    {
        length = strlen(chars);
        this->chars = new char[length + 1];
        strcpy(this->chars, chars);
    }

    ~String()
    {
        delete [] chars;
    }

    String &operator=(const String & s)
    {
        if(this==&s) return *this;
        delete [] chars;

        length = s.length;
        this->chars = new char[length + 1];
        strcpy(this->chars, s.chars);

        return *this;
    }

    bool operator==(const String &s) const 
    {
        if (length != s.length) 
            return false;
    return strcmp(chars, s.chars) == 0;
    }

    String(const String & s)
    {
        length = s.length;
        chars = new char[length+1];
        strcpy(chars, s.chars); 
    }

    char & operator[](int index)
    {
        return chars[index];
    }
    
    // Implement KMP on the whole string
    vector<int> findAllSubStr(String pat)
    {
        int n = length;
        int m = pat.getLength();

        vector<int> lps(m);
        vector<int> res;

        //void constrcutLPS
        int len = 0;
        lps[0] = 0;
        int i = 1;

        while(i < m)
        {
            if(pat[i] == pat[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if(len != 0)
                    len = lps[len-1];
                else
                {
                    lps[i] = 0;
                    i++;
                    len++;
                }
            }
        }

        i = 0;
        int j = 0;

        while(i < n)
        {
            if (chars[i] == pat[j])
            {
                i++;
                j++;

                if(j == m)
                {
                    res.push_back(i-j);
                    j = lps[j-1];
                }
            }
            else
            {
                if(j != 0) j = lps[j-1];
                else i++;
            }      
        }
        return res;
    }

    // Implement KMP until the first match
    int findFirstSubStr(String pat)
    {
        int n = length;
        int m = pat.getLength();

        vector<int> lps(m);
        int res;

        //void constrcutLPS
        int len = 0;
        lps[0] = 0;
        int i = 1;

        while(i < m)
        {
            if(pat[i] == pat[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if(len != 0)
                    len = lps[len-1];
                else
                {
                    lps[i] = 0;
                    i++;
                    len++;
                }
            }
        }

        i = 0;
        int j = 0;

        while(i < n)
        {
            if (chars[i] == pat[j])
            {
                i++;
                j++;

                if(j == m)
                {
                    res = i-j;
                    break;
                }
            }
            else
            {
                if(j != 0) j = lps[j-1];
                else i++;
            }      
        }
        return res;
    }

    // Implement KMP in reverse (search from the end of both strings).
    // The lookup table should be done from last character
    int findLastSubStr(const String & subStr);
    int* findAllSubStrReverse(const char * subStr);

    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.chars;
        return os;
    }

    unsigned int getLength()
    {
        return length;
    }
};

int main()
{
    String str("aabaacaadaabaaba");
    String pattern("aaba");
    cout << "String: " << str << endl;

    vector<int> occurrences = str.findAllSubStr(pattern);
    int firstOccurrence = str.findFirstSubStr(pattern);

    cout << "Index of ALL occurrences of "<<pattern<<": "<<endl;
    for(int i=0; i < occurrences.size(); i++) cout<<occurrences[i]+1<<endl;
    
    cout<<"Index of FIRST occurance of "<<pattern<<": "<<firstOccurrence + 1;

    //Adding +1 so the output will be 1-indexed
    return 0;
}