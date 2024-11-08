#include <bits/stdc++.h>
using namespace std;

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
        int p = 26;

        vector<int> p_pow(n);
        p_pow[0] = 1;
        for(int i=1; i <p_pow.size(); i++)
            p_pow[i] = (p_pow[i-1] * p);

        vector<int> h(n+1, 0);
        for(int i=0; i<n; i++)
            h[i+1] = h[i] + ((int)txt[i] - 64) * p_pow[i];
        
        int hs = 0;
        for(int i=0; i<m; i++)
            hs += ((int)pat[i] - 64) * p_pow[i];

        for(int i=0; i<n-m+1; i++)
        {
            int current = (h[i+m] - h[i]);
            if(current == hs * p_pow[i]) cout<<"Index of occurance: "<<i<<endl;
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
