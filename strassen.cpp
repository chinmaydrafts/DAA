#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(Matrix a, Matrix b)
{
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return res;
}

Matrix sub(Matrix a, Matrix b)
{
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return res;
}

Matrix strassen(Matrix a, Matrix b)
{
    int n = a.size();
    Matrix C(n, vector<int>(n));

    if (n == 1)
    {
        C[0][0] = a[0][0] * b[0][0];
        return C;
    }
    int k = n / 2;

    Matrix A11(k, vector<int>(k));
    Matrix A12(k, vector<int>(k));
    Matrix A21(k, vector<int>(k));
    Matrix A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k));
    Matrix B12(k, vector<int>(k));
    Matrix B21(k, vector<int>(k));
    Matrix B22(k, vector<int>(k));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = a[i][j];
            A12[i][j] = a[i][j + k];
            A21[i][j] = a[i + k][j];
            A22[i][j] = a[i + k][j + k];

            B11[i][j] = b[i][j];
            B12[i][j] = b[i][j + k];
            B21[i][j] = b[i + k][j];
            B22[i][j] = b[i + k][j + k];
        }
    }

    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, sub(B12, B22));
    Matrix M4 = strassen(A22, sub(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(sub(A21, A11), add(B11, B12));
    Matrix M7 = strassen(sub(A12, A22), add(B21, B22));

    Matrix C11 = add(sub(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(sub(add(M1, M3), M2), M6);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(Matrix A)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    int n = 2;

    Matrix A = {{1, 2},
                {3, 4}};

    Matrix B = {{5, 6},
                {7, 8}};

    Matrix C = strassen(A, B);

    cout << "Result matrix:\n";
    printMatrix(C);

    return 0;
}