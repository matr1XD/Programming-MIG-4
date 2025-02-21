#include <bits/stdc++.h>
using namespace std;

class Matrix
{
    int row, col;
    vector<vector<double>> m;

    public:
    Matrix() : row(0), col(0) {};

    Matrix(int row, int col) : row(row), col(col) {
        m.resize(row, vector<double>(col, 0.0));
    }

    double & at(int i, int j)
    {
        if(!(i<0 or i>=row or j<0 or j>=col))
            return m[i][j];
    }

    int numR() {return row;}
    int numC() {return col;}

    double & operator()(int i, int j)
    {
        return at(i,j);
    }

    void print()
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<m[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    Matrix operator+(Matrix & other)
    {
        Matrix result(row, col);
        for(int i=0;i<row;i++)
        {
            for(int j=0; j <col; j++)
            {
                result.m[i][j] = m[i][j] + other.m[i][j];
            }
        }
        return result;
    }

    Matrix operator*(Matrix &other) 
    {
        Matrix result(row, other.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < other.col; j++) {
                for (int k = 0; k < col; k++) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    friend istream& operator>>(istream &in, Matrix & mat) 
    {
        for (int i = 0; i < mat.row; i++) 
        {
            for (int j = 0; j < mat.col; j++) 
            {
                in >> mat.m[i][j];
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream &out, Matrix & mat) 
    {
        for (int i = 0; i < mat.row; i++) {
            for (int j = 0; j < mat.col; j++) {
                out << setw(10) << mat.m[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    Matrix identitymatrix(int n)
    {
        Matrix result(n,n);
        for(int i=0;i<n;i++)
            result(i, i) = 1.0;
        return result;
    }

    Matrix zeromatrix(int r, int c)
    {
        Matrix result(r, c);
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                result(i, j) = 0.0;
            }
        }
        return result;
    }

    Matrix transpose()
    {
        Matrix result(col, row);
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                result(j, i) = m[i][j];
            }
        }
        return result;
    }

    Matrix inverse() 
    {
        if(!(row != col))
        {
            
        int n = row;
        
        //Augmented matrix
        vector<vector<double>> aug(n, vector<double>(2 * n, 0.0));
        for(int i = 0; i < n; i++) 
        {
            for(int j = 0; j < n; j++) 
            {
                aug[i][j] = m[i][j];
            }
            aug[i][n + i] = 1.0; // Set the identity matrix on the right.
        }
        
        //elimination
        for (int i = 0; i < n; i++) 
        {
            double pivot = aug[i][i];
            if (fabs(pivot) < 1e-9) 
            {
                // Try to swap with a lower ro
                bool swapped = false;
                for (int k = i + 1; k < n; k++) 
                {
                    if (fabs(aug[k][i]) > 1e-9) 
                    {
                        swap(aug[i], aug[k]);
                        pivot = aug[i][i];
                        swapped = true;
                        break;
                    }
                }
                if (!swapped)
                    throw runtime_error("Matrix is singular and cannot be inverted.");
            }
            
            for (int j = 0; j < 2 * n; j++) 
                aug[i][j] /= pivot;
            
            for (int k = 0; k < n; k++) 
            {
                if (k != i) 
                {
                    double factor = aug[k][i];
                    for (int j = 0; j < 2 * n; j++)
                        aug[k][j] -= factor * aug[i][j];
                }
            }
        }
        
        Matrix inv(n, n);
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                inv(i, j) = aug[i][n + j];
            }
        }
        return inv;
    }
    }

    double determinant()
    {
        int n = row;
        vector<vector<double>> temp = m;
        double det = 1.0;
        int sign = -1;

        for(int i=0; i<n; i++)
        {
            int pivotR = i;
            for(int k = i+1; k<n; k++)
            {
                if(fabs(temp[k][i]) > fabs(temp[pivotR][i]))
                    pivotR = k;
            }

            if (fabs(temp[pivotR][i]) < 1e-9)
                return 0.0; //If pivot is zero, determinant is zero

            if(pivotR != i)
            {
                swap(temp[i], temp[pivotR]);
                sign *= -1;
            }

            det *= temp[i][i];

            for(int k = i+1; k<n; k++)
            {
                double factor = temp[k][i] / temp[i][i];
                for(int j = i; j<n; j++)
                    temp[k][j] -= factor * temp[i][j];
            }
        }
        return det * sign;   
    }

    Matrix minor(int r, int c)
    {
        Matrix result(row - 1, col - 1);
        int newRow = 0, newCol = 0;

        for(int i=0;i<row;i++)
        {
            if(i == r) continue;
            newCol = 0;
            for(int j = 0; j < col; j++)
            {
                if(j == c) continue;
                result(newRow, newCol) = m[i][j];
                newCol++;
            }
            newRow++;
        }  

        return result;
    }

    int rank()
    {
        vector<vector<double>> temp = m;
        int rank = 0;
        int n = row, m = col;

        for (int i = 0; i < min(n, m); i++) {
            int pivotRow = i;
            for (int j = i + 1; j < n; j++) {
                if (fabs(temp[j][i]) > fabs(temp[pivotRow][i]))
                    pivotRow = j;
            }
            if (fabs(temp[pivotRow][i]) < 1e-9) continue;
            swap(temp[i], temp[pivotRow]);
            rank++;
            for (int j = i + 1; j < n; j++) {
                double factor = temp[j][i] / temp[i][i];
                for (int k = i; k < m; k++) {
                    temp[j][k] -= factor * temp[i][k];
                }
            }
        }
        return rank;
    }

    vector<double> eigenvalues()
    {
        Matrix A = *this;
        int n = row;
        vector<double> eigvals;
        vector<double> coeffs(n+1, 0);
        coeffs[n] = 1;
        for(int i = 0; i < n; i++)
            coeffs[n - 1] -= m[i][i];

        for(double lambda = -100; lambda <= 100; lambda+=0.1)
        {
            double value = 1;
            for(int i = 0; i < n; i++)
                value *= (lambda - m[i][i]);
            if(fabs(value) < 1e-3)
                eigvals.push_back(lambda);
        }

        return eigvals;
    }
};

int main()
{
    int r = 3, c = 3;
    cout<<"Enter elements of A: "<<endl;
    Matrix A(r, c);
    cin>>A;
    
    cout<<"Enter elements of B: "<<endl;
    Matrix B(r, c);
    cin>>B;

    Matrix C = A + B;
    cout<<"A + B: "<<endl<<C<<endl;

    Matrix D = A * B;
    cout<<"A * B: "<<endl<<D<<endl;

    cout<<"Transpose of A: "<<endl;
    Matrix E = A.transpose();
    cout<<E<<endl;

    cout<<"Determinant od A: "<<endl<<A.determinant()<<endl;

    cout<<"Inverse of A: "<<endl;
    Matrix F = A.inverse();
    cout<<F<<endl;

    cout<<"Identity matric: "<<endl;
    Matrix G = A.identitymatrix(3);
    cout<<G<<endl;

    cout<<"Zero matrix: "<<endl;
    Matrix H = A.zeromatrix(3, 3);;
    cout<<H<<endl;

    cout<<"Minor of A without row 1 and col 0"<<endl;
    Matrix M = A.minor(1, 0);
    cout<<M<<endl;

    cout<<"Rank od A: "<<endl<<A.rank()<<endl;

    return 0;
}
