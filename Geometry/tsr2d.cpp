//za da rotirame za 90 stepeni kompleksen broj, treba tockata da ja po,nozime po i
//sekogas koga imame agli se preflrmae so kompleskna ramnina
//bidejki kompleksnite broevi sodrzat trigonometrija vo niv
//mnozenje 2x2 so vektor 2x1 ke se dobie translacija 
//za 2D ke dodaeme uste edna taka narecena homogena koordinata w, odnosno [x y w=1]
//za w=0, dobivame tocka vo beskonecnost odnosno prava vo beskonecnost

//za skaliranje samo gi menuvame 1cite od edinectnata matrica so skalarite za x i y
//mnozenje na matrici e izmisleno za poelsni transformacii niz ramnina/prostor

//graficki kartici rabotat amnogu pobrzo so martici nego CPU

//Za doma ova vo 3D 

#include <bits/stdc++.h>
using namespace std;

struct Point
{
    public:
    double e[3];    
    Point(double x = 0.0, double y = 0.0, double w = 0.0) {e[0] = (x); e[1] = (y); e[2] = (w);};

};

struct Matrix
{
    public:
    double m[3][3] = {0};
    Matrix() {for(int i=0; i<3; i++) m[i][i] = 1;}
    Matrix(int v) {for(int i=0; i<3; i++) m[i][i] = v;}

    
    Matrix operator*(const Matrix & second)
    {
        Matrix result(0);
        for(int i=0;i<3;i++)
        {
            for(int j=0; j<3; j++)
            {
                for(int k=0; k<3; k++)
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
            for(int i=0;i<3;i++)
            {
                for(int j=0; j<3; j++)
                {
                    result.e[i] += m[i][j] * second.e[j];
                    
                }
            }
        return result;
    }


};

ostream & operator<<(ostream & out, Matrix & mat)
{
    for(int i=0; i <3;i++)
    {
        for(int j=0;j<3; j++)
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
    for(int i=0; i <3;i++)
    {
        out<<p.e[i]<<" ";
    }
    out<<"]"<<endl;
    return out;
}



int main()
{
    Matrix first;
    Matrix second;
    Point p1(3, 1, 1);

   /* Translation and Scaling
    first.m[0][2] = 3;
    second.m[0][0] = 0.5;

    Matrix result = first * second;
    Point pointresult = result * p1;

    cout<<result<<endl;
    cout<<pointresult<<endl;
*/

    //Rotation
    first.m[0][2] = 3;
    second.m[0][0] = 0.5;

    Matrix rot;
    rot.m[0][0] = cos(M_PI/2);
    rot.m[1][1] = cos(M_PI/2);
    rot.m[0][1] = -1*sin(M_PI/2);
    rot.m[1][0] = sin(M_PI/2);

    Point result = rot * p1;
    cout<<result<<endl;
    return 0;
}
