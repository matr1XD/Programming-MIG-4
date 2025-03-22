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
        os<<"("<<a.x<<", "<<a.y<<")";
        return os;
    }
};

int ccw(Point a, Point b, Point c)
{
    double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if(area < 0) return -1; //clockwise
    if(area > 0) return 1; //counterclockwise
    return 0; //collinear
}

Point getMinY(vector<Point> & points) //find the point with the lowest Y coordinate
{
    double tempx = points[0].x;
    double tempy = points[0].y;
    int index = 0;
    for(int i = 1; i < points.size(); i++)
    {
        if(tempy < points[i].y)
        {
            tempy = points[i].y;
            tempx = points[i].x;
            index = i;
        }
        else if(tempy == points[i].y and tempx < points[i].x)
        {
            tempy = points[i].y;
            tempx = points[i].x;
            index = i;
        }
    }
    return points[index];
}

bool compare(Point b, Point c, Point ref) //lambda function
{
    if(b.x == ref.x and b.y == ref.y) return true;
    if(c.x == ref.x and c.y == ref.y) return false;

    int turn = ccw(ref, b, c);
    if(turn == 0)
    {
        return(b.x < c.x) or (b.x == c.x and b.y < c.y);
    }
    return turn > 0;
}

void sortAngle(vector<Point> & points, Point & ref)
{
    sort(points.begin(), points.end(), [&ref](const Point& b, const Point& c) {
        return compare(b, c, ref);
    });
}

vector<Point> convexhull(vector<Point> points)
{
    stack<Point> s;
    Point mini = getMinY(points);
    sortAngle(points, mini);

    s.push(points[0]);
    s.push(points[1]);

    for(int i = 2; i < points.size(); i++)
    {
        Point next = points[i];
        Point p = s.top();
        s.pop();

        while(!s.empty() and ccw(s.top(), p, next) <= 0)
        {
            p = s.top();
            s.pop();
        }

        s.push(p);
        s.push(next);
    }

    Point p = s.top();
    s.pop();
    if(ccw(s.top(), p, mini) > 0)
    {
         s.push(p);
    }

    vector<Point> result;
    while(!s.empty())
    {
        result.push_back(s.top());
        s.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    vector <Point> points = {{0,3}, {2,2}, {1,1}, {2,1}, {3,0}, {0,0}, {3,3}};
    vector <Point> result = convexhull(points);

    cout<<"Convex hull: "<<endl;
    for(int i = 0; i < result.size(); i++)
        cout<<result[i]<<endl;

    return 0;
}
