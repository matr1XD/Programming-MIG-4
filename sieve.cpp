#include <bits/stdc++.h>
using namespace std;


void sieve(int n)
{
    vector<bool> a((n+1), 1);
    for(int i=2; i*i<=n; i++)
    {
        if(a[i])
        {
            for(int j = i*i; j<=n; j+=i)
                a[j] = 0;
        }
    }

    for(int i=2; i<n; i++)
    {
        if(a[i]) cout<<i<<" ";
    }
}

int main()
{
    int n;cin>>n;
    sieve(n); 
    return 0;
}
