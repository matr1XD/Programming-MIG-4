#include <bits/stdc++.h>
using namespace std;

class Line
{
    double y, x, k, m;
    double a, b, c, d; //ax + by + cz + d = 0

    public:
    Line(double a, double b, double c, double d): a(a), b(b), c(c), d(d) {}
    Line() : a(0), b(0), c(0), d(0) {}

    friend bool gaussian(Line lines[3], double & x, double & y, double & z);
    friend istream & operator>>(istream & in, Line & line);

};

istream& operator>>(istream &in, Line &line) {
    in >> line.a >> line.b >> line.c >> line.d;
    return in;
}

bool gaussian(Line lines[3], double & x, double & y, double & z)
{
    int n = 3;
    double m[n][n+1];
    for(int i=0;i<n;i++)
    {
        m[i][0] = lines[i].a;
        m[i][1] = lines[i].b;
        m[i][2] = lines[i].c;
        m[i][3] = -lines[i].d; //ax + by + cz = -d
    }

    for(int i=0;i<n;i++)
    {
        int pivot = i;
        for(int j = i+1; j<n; j++)
        {
            if(fabs(m[j][i]) > fabs(m[pivot][i]))
                pivot = j;
        }

        //Swap rows if necessary
        for(int k = i; k < n+1; k++)
        {
            double temp = m[i][k];
            m[i][k] = m[pivot][k];
            m[pivot][k] = temp;
        }

        for(int j = i+1; j < n; j++)
        {
            double factor = m[j][i] / m[i][i];
            for(int k = i; k < n+1; k++)
            {
                m[j][k] -= factor * m[i][k];
            }
        }
    }

    double sol[n];
    for(int i=n-1; i>=0; i--)
    {
        double sum = m[i][n];
        for(int j = i+1; j<n; j++)
            sum -= m[i][j] * sol[j];
        sol[i] = sum / m[i][i];
    }

    x = sol[0];
    y = sol[1];
    z = sol[2];
    return true;
}


int main()
{
    Line lines[3];
    cout <<"Enter coefficients for 3 lines (a, b, c, d) as ax + by + cz + d = 0:"<<endl;
    
    for(int i = 0; i < 3; i++) 
    {
        cout<<"Line "<<i + 1<<": ";
        cin>>lines[i];
    }
    
    double x, y, z;
    if (gaussian(lines, x, y, z)) 
    {
        cout<<"Solution:" <<endl;
        cout<<"x = " <<x<<endl;
        cout<<"y = " <<y<<endl;
        cout<<"z = " <<z<<endl;
    } 
    else
        cout <<"No solutions"<<endl;
    return 0;
}
