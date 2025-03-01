#include <bits/stdc++.h>
using namespace std;

struct Point
{
    public:
    double e[4];    
    Point(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0) {e[0] = (x); e[1] = (y); e[2] = (z); e[3] = (w);};

};

struct Matrix
{
    public:
    double m[4][4] = {0};
    Matrix() {for(int i=0; i<4; i++) m[i][i] = 1;}
    Matrix(int v) {for(int i=0; i<4; i++) m[i][i] = v;}

    
    Matrix operator*(const Matrix & second)
    {
        Matrix result(0);
        for(int i=0;i<4;i++)
        {
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }

    Point operator*(const Point & second)
    {
        Point result;
            for(int i=0;i<4;i++)
            {
                for(int j=0; j<4; j++)
                {
                    result.e[i] += m[i][j] * second.e[j];
                }
            }
        return result;
    }

    Matrix translation(double tx, double ty, double tz)
    {
        Matrix result;
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }

    Matrix scaling(double sx, double sy, double sz)
    {
        Matrix result;
        result.m[0][0] = sx;
        result.m[1][0] = sy;
        result.m[2][0] = sz;
        return result;
    }

    Matrix rotationX(double angle)
    {
        Matrix result;
        double rad = angle * M_PI / 180.0;
        result.m[1][1] = cos(rad);
        result.m[1][2] = -sin(rad);
        result.m[2][1] = sin(rad);
        result.m[2][2] = cos(rad);
        return result;
    }

    Matrix rotationY(double angle)
    {
        Matrix result;
        double rad = angle * M_PI / 180.0;
        result.m[0][0] = cos(rad);
        result.m[0][1] = -sin(rad);
        result.m[1][0] = sin(rad);
        result.m[1][1] = cos(rad);
        return result;
    }

    Matrix rotationZ(double angle)
    {
        Matrix result;
        double rad = angle * M_PI / 180.0;
        result.m[0][0] = cos(rad);
        result.m[0][1] = -sin(rad);
        result.m[1][0] = sin(rad);
        result.m[1][1] = cos(rad);
        return result;
    }
};

ostream & operator<<(ostream & out, Matrix & mat)
{
    for(int i=0; i<4;i++)
    {
        for(int j=0; j<4; j++)
        {
            out<<mat.m[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}

ostream & operator<<(ostream & out, Point & p)
{
    out<<"[ ";
    for(int i=0; i<4;i++)
    {
        out<<p.e[i]<<" ";
    }
    out<<"]"<<endl;
    return out;
}

int main()
{
    Matrix first;
    Point p1(3, 1, 2, 1);
    
    Matrix t = first.translation(2, 3, 4);
    Matrix s = first.scaling(2, 1, 3);
    Matrix r = first.rotationX(90);

    Point p_t = t * p1;
    Point p_s = s * p1;
    Point p_r = r * p1;

    cout<<"Point: "<<p1<<endl;
    cout<<"Translated point: "<<p_t<<endl;
    cout<<"Scaled point: "<<p_s<<endl;
    cout<<"Rotated point: "<<p_r<<endl;

    return 0;
}
