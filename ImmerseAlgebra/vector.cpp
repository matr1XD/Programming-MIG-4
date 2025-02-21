//za da cuvame vector treba da chuvame samo krajna tocka, pocetnata sekgoas da ni e (0,0)
//ako ne e vo (0,0) ke ja odneseme
//tocka vo prostor == vektor vo prostor odnosno tockata e vrvot na vektorot
// |v| = sqrt(x^2 + y^2 + ... ) Euclid distance
// tg(a) = y / x
// dot product e merka za slicnost megu vektori 
// dot product ako imame koordinati, samo mnoziz x1 so x2, y1 so y2 i se sobira
// vector product e za da formirame ramnina od 2 tocki iako sakame da ja fiksirame so 3ta tocka

//struktura za tocki vo 3d sistem
// dot i cross product

#include <bits/stdc++.h>
using namespace std;

class Point
{
    double x, y, z;    
    public:
    Point(double x, double y, double z): x(x), y(y), z(z) {}

    Point addVectors(Point a, Point b)
    {
        Point result(a.x + b.x, a.y + b.y, a.z + b.z);
        return result;
    }

    Point scalarMulti(Point a, double s)
    {
        Point result(a.x * s, a.y * s, a.z * s);
        return result;
    }

    double dotproduct(Point a, Point b)
    {
        double pro = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
        return pro;
    } 

    Point crossproduct(Point a, Point b)
    {
        double cross = a.x * b.x + a.x * b.y + a.x * b.z + a.y * b.x + a.y * b.y + a.y * b.z + a.z * b.x + a.z * b.y + a.z * b.z;
        double s1 = a.y * b.z - a.z * b.y;
        double s2 = a.z * b.x - a.x * b.z;
        double s3 = a.x * b.y - a.y * b.x;

        Point result(s1, s2, s3);
        return result;
    }

    double modul(Point a)
    {
        double result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
        return result;
    }

    friend ostream& operator<<(ostream& os, const Point& a)
    {
        os<<"("<<a.x<<", "<<a.y<<", "<<a.z<<")";
        return os;
    }
};


int main()
{
    
    double x, y, z;
    double s = 2;
    x = 1; y = 2; z = 3;
    Point a(x, y, z);
    Point b(x+1, y+1, z+1);
    Point c(x+2, y+2, z+2);
    cout<<"Module value of vector a: "<<a.modul(a)<<endl;
    cout<<"Vector addition "<<a.addVectors(a,b)<<endl;
    cout<<"Vector multi"<<a.scalarMulti(a, s)<<endl;
    cout<<"Dot product "<<a.dotproduct(a,b)<<endl;
    cout<<"Cross product "<<a.crossproduct(a,b)<<endl;
    
    return 0;
}
