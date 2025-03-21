//The polygon is convex if the z-components of 
//the cross products are either all positive 
//or all negative. Otherwise the polygon is nonconvex.
#include <bits/stdc++.h>
using namespace std;

struct Point
{  
    double x, y;    
    Point(double x, double y): x(x), y(y) {}

    bool operator<(Point &other)
    {
        if (fabs(x - other.x) < 1e-9)
            return y < other.y;
        return x < other.x;
    }

    friend ostream& operator<<(ostream& os, const Point& a)
    {
        os << "(" << a.x << ", " << a.y << ", " << ")";
        return os;
    }
};

Point mid(0,0); //global because is used in compare funciton
int quad(Point p) //determines thje quadrant of a point
{
    if(p.x >= 0 and p.y >= 0) return 1;
    if(p.x <= 0 and p.y >= 0) return 2;
    if(p.x <= 0 and p.y <= 0) return 3;
    return 4;
}

int orientation(Point a, Point b, Point c) //checks if the line is crossing the plane
{
    int result = (b.y - a.y) * (c.x - b.x) - (c.y - b.y) * (b.x - a.x); //formula from analytical heometry for finding K with 3 points
    if(result == 0) return 0;
    if(result > 0) return 1;
    return -1;
}

bool compare(Point p1, Point q1)
{
    Point p(p1.x-mid.x, p1.y-mid.y);
    Point q(q1.x-mid.x, q1.y-mid.y);

    int one = quad(p);
    int two = quad(q);

    if(one != two) return (one < two);
    return (p.y * q.x < p.x * q.y);
}

vector<Point> merger(vector<Point> a, vector<Point> b)
{
    int n1 = a.size();
    int n2 = b.size(); //number of points in polygons a and b

    int ia = 0, ib = 0;
    for(int i=1; i<n1; i++)
    {
        if(a[i].x > a[ia].x) 
            ia = i;
    }

    for(int i=1; i<n2; i++)
    {
        if(b[i].x < b[ib].x)
            ib = i;
    }

    //find the upper tangent
    int inda = ia, indb = ib;
    bool flag = 0;
    while(!flag)
    {
        flag = 1;
        while(orientation(b[indb], a[inda], a[(inda+1)%n1]) >= 0)
            inda = (inda+1)%n1;
        
        while(orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <= 0)
        {
            indb = (n2+indb-1)%n2;
            flag = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb = ib;
    flag = 0;
    int g = 0;

    while(!flag)
    {
        flag = 1;
        while(orientation(a[inda], b[indb], b[(indb+1) % n2]) >= 0)
            indb = (indb+1)  % n2;

        while(orientation(b[indb],a[inda], a[(inda-1+n1) % n1]) <= 0)
        {
            inda = (inda-1 + n1)  % n1;
            flag = 0;
        }    
    }

    int lowera = inda, lowerb = indb;
    vector<Point> ret;

    int ind = uppera;
    ret.push_back(a[uppera]);
    while(ind != lowera)
    {
        ind = (ind+1) % n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind + 1) % n2;
        ret.push_back(b[ind]);
    }
    return ret;    
}

vector<Point> bruteHull(vector<Point> a)
{
    set<Point> s;

    for(int i=0; i<a.size(); i++)
    {
        for(int j=i+1; j<a.size(); j++)
        {
            double x1 = a[i].x, x2 = a[j].x;
            double y1 = a[i].y, y2 = a[j].y;

            double a1 = y1 - y2;
            double b1 = x2 - x1;
            double c1 = x1 * y2 - y1 * x2;
            double pos = 0, neg = 0;
            for(int k = 0; k < a.size(); k++)
            {
                if(a1 * a[k].x + b1 * a[k].y + c1 <= 0)
                    neg++;
                if(a1 * a[k].x + b1 * a[k].y + c1 >= 0)
                    pos++;
            }
            if(pos == a.size() or neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<Point> result(s.begin(), s.end());
    mid = Point(0,0);
    for(auto e : s)
        result.push_back(e);

    //sorting the points in anti clockwise order
    int n = result.size();
    for(int i = 0; i < n; i++)
    {
        mid.x += result[i].x;
        mid.y += result[i].y;
        result[i].x *= n;
        result[i].y *= n;
    }
    sort(result.begin(), result.end(), compare);
    for(int i = 0; i < n; i++)
    {
        Point temp(result[i].x / n, result[i].y / n);
        result[i] = temp;
    }
    return result;
}

vector<Point> divide(vector<Point> a)
{
    if(a.size() <= 5) return bruteHull(a);

    vector<Point> left, right;
    for(int i = 0; i < a.size() / 2; i++)
        left.push_back(a[i]);
    for(int i = a.size() / 2; i < a.size(); i++)
        right.push_back(a[i]);
    
    vector<Point> leftHull = divide(left);
    vector<Point> rightHull = divide(right);

    return merger(leftHull, rightHull);
}

int main()
{
    vector<Point> a;
    cout<<"Enter the number of points: ";
    int n; cin>>n;


    cout<<"Enter the points: "<<endl; 
    for(int i=0; i<n; i++)
    {
        int first, second; cin>>first>>second;
        Point temp(first, second);
        a.push_back(temp);
    }

    sort(a.begin(), a.end());
    vector<Point> ans = divide(a);

    cout<<"Convex Hull: "<<endl;
    for(auto e : ans)
        cout<<e.x<<" "<<e.y<<endl;

    return 0;
}
