#include <bits/stdc++.h>
using namespace std;

class String
{
    char * txt;
    unsigned int length;

    public:
    String(const char * txt = "")
    {
        length = strlen(txt);
        this->txt = new char[length + 1];
        strcpy(this->txt, txt);
    }

    ~String()
    {
        delete [] txt;
    }

    String &operator=(const String & s)
    {
        if(this==&s) return *this;
        delete [] txt;

        length = s.length;
        this->txt = new char[length + 1];
        strcpy(this->txt, s.txt);

        return *this;
    }

    bool operator==(const String &s) const 
    {
        if (length != s.length) 
            return false;
    return strcmp(txt, s.txt) == 0;
    }

    String(const String & s)
    {
        length = s.length;
        txt = new char[length+1];
        strcpy(txt, s.txt); 
    }

    char & operator[](int index)
    {
        return txt[index];
    }
    
    void rk(String pat)
    {
        int m = pat.getLength();
        int n = length;
        vector<int> t((n-m+1+1),0); //hash value for txt
        int p = 0; //hash value for pattern

        for(int i=0; i<m; i++)
        {
            t[0] += (int)txt[i]-96;
        }

        for(int i=1; i<(n-m)+1+1; i++)
        {
            t[i] = t[i-1] + (int)txt[i+m-1]-96 - (int)txt[i-1]+96;
        }

        for(int i=0; i<m; i++) p+=(int)pat[i]-96;

        int j=0;
        for(int i=0;i<=n-m;i++)
        {
            if(p == t[i])
            {
                for(j=0; j<m; j++)
                {
                    if(txt[i+j] != pat[j]) break;
                }

                if(j == m)
                {
                    cout<<"Pattern found at index "<<i<<endl;
                }
            }
        }
    }

    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.txt;
        return os;
    }

    unsigned int getLength()
    {
        return length;
    }
};


int main()
{
    String txt("geeksforgeeks");
    String pat("geek");

    txt.rk(pat);
    return 0;
}