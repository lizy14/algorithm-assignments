
/*
文件名: 
描　述: Compare naive matrix multiplication and the Strassen's algorithm.

作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2016-02-24

环　境: Visual Studio 2012 (MSVC++ 11.0)
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using std::vector;

#include "timing.h"

class Matrix{
public:
    vector<vector<int> > m;
    int size;
    void resize(int size_){
        size = size_;
        m.resize(size, vector<int>(size));
    }
    void randomize(){
        for(auto& v : m){
            for(auto& i : v){
                i = std::rand();
            }
        }
    }
    vector<int>& operator[](int x){
        return m[x];
    }
    void print(){
        for(auto& v : m){
            for(auto& i : v){
                std::cout << i << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

namespace MatrixMultiplication{
//works only for matrices 2^n by 2^n

Matrix naive(Matrix a, Matrix b){

    if(a.size != b.size)
        throw "size mismatch\n";

    int n = a.size;
    Matrix c;
    c.resize(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            c[i][j] = 0;
            for(int k=0; k<n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
    
}

void partition(Matrix a, Matrix m[]){
    /*
    0 1
    2 3
    */

    /*
    11 12
    21 22
    */
    int n = a.size;
    for(int i=0; i<4; i++){
        m[i].resize(n/2);
    }

    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            m[0][i][j] = a[i][j];
        }
    }
    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            m[1][i][j] = a[i][j + n/2];
        }
    }
    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            m[2][i][j] = a[i + n/2][j];
        }
    }
    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            m[3][i][j] = a[i + n/2][j + n/2];
        }
    }
}
Matrix operator+(Matrix& a, Matrix& b){
    int n = a.size;
    if(a.size != b.size)
        throw "size mismatch";
    Matrix c;
    c.resize(n);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            c[i][j] = a[i][j]+b[i][j];
    return c;
}
Matrix operator-(Matrix& a, Matrix& b){
    int n = a.size;
    if(a.size != b.size)
        throw "size mismatch";
    Matrix c;
    c.resize(n);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            c[i][j] = a[i][j]-b[i][j];
    return c;
}

Matrix recursive(Matrix& a, Matrix& b){
    if(a.size != b.size)
        throw "size mismatch\n";

    int n = a.size;
    Matrix c;
    c.resize(n);

    if(n==1){
        c[0][0] = a[0][0] * b[0][0];
    }else{
        Matrix C[4];
        {
            Matrix A[4], B[4], S[10];
            partition(a, A);
            partition(b, B);

            C[0] = recursive(A[0], B[0]) + recursive(A[1],B[2]);
            C[1] = recursive(A[0], B[1]) + recursive(A[1],B[3]);
            C[2] = recursive(A[3], B[0]) + recursive(A[3],B[2]);
            C[3] = recursive(A[2], B[1]) + recursive(A[3],B[3]);
        }

        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i][j] = C[0][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i][j + n/2] = C[1][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i + n/2][j] = C[2][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i + n/2][j + n/2] = C[3][i][j];

    }
    return c;
}
Matrix strassen(Matrix& a, Matrix& b){
    if(a.size != b.size)
        throw "size mismatch\n";

    int n = a.size;
    Matrix c;
    c.resize(n);
    
    if(n==1){
        c[0][0] = a[0][0] * b[0][0];
    }else{
        Matrix C[4];
        {
        Matrix P[7];
        {
        Matrix A[4], B[4], S[10];
        partition(a, A);
        partition(b, B);

        S[0] = B[1]-B[3];
        S[1] = A[0]+A[1];
        S[2] = A[2]+A[3];
        S[3] = B[2]-B[0];
        S[4] = A[0]+A[3];
        S[5] = B[0]+B[3];
        S[6] = A[1]-A[3];
        S[7] = B[2]+B[3];
        S[8] = A[0]-A[2];
        S[9] = B[0]+B[1];

        P[0] = strassen(A[0], S[0]);
        P[1] = strassen(S[1], B[3]);
        P[2] = strassen(S[2], B[0]);
        P[3] = strassen(A[3], S[3]);
        P[4] = strassen(S[4], S[5]);
        P[5] = strassen(S[6], S[7]);
        P[6] = strassen(S[8], S[9]);
        }

        
        C[0] = P[4] + P[3] - P[1] + P[5];
        C[1] = P[0] + P[1];
        C[2] = P[2] + P[3];
        C[3] = P[4] + P[0] - P[2] - P[6];
        }

        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i][j] = C[0][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i][j + n/2] = C[1][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i + n/2][j] = C[2][i][j];
        for(int i=0; i<n/2; i++)
            for(int j=0; j<n/2; j++)
                c[i + n/2][j + n/2] = C[3][i][j];

    }
    return c;
}
}

int main(){
    Timing timer;
#ifdef _DEBUG
    int size = 4;{
#else
    for(int size=1; size>0; size*=2){
#endif
    
        std::cout << "size: " << size << '\n';
        const int times = 10;
        Matrix a, b;
        a.resize(size);
        b.resize(size);
        a.randomize();
        b.randomize();

    
        timer.setDivisor(times);
    
   

        timer.start();
        for(int i=0; i<times; i++){
            Matrix c = MatrixMultiplication::recursive(a, b);
#ifdef _DEBUG
            c.print();
#endif
        }
        timer.end();
        timer.reportCPUtime();


        timer.start();
        for(int i=0; i<times; i++){
            Matrix c = MatrixMultiplication::strassen(a, b);
#ifdef _DEBUG
            c.print();
#endif
        }
        timer.end();
        timer.reportCPUtime();
    }

    return system("pause");
}