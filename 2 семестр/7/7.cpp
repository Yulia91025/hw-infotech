#include <iostream>
using namespace std;
template <typename T, int N, int M>
class Matrix {
public:  T** data = new T * [N];

    Matrix() {
        for (int i = 0; i < N; i++)
            data[i] = new T[M];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                data[i][j] = 0;
    }
    ~Matrix() {
        for (int i = 0; i < N; i++)
            delete[] data[i];
        delete[] data;
    }
    void set(int i, int j, T value) {
        data[i-1][j-1] = value;
    }
    T get(int i, int j) {
        return data[i-1][j-1];
    }
    void trans() {
        Matrix<T, M, N> C;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                C.data[j][i] = data[i][j];
        C.print();
    }
    void print() {
        for (int i = 0; i < N; i++) {
            for (int j =0; j < M; j++)
                std::cout<<data[i][j]<<"  ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    int size_r() {
        return N;
    }
    int size_c() {
        return M;
    }
    Matrix& operator =(const Matrix& A) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                data[i][j] = A.data[i][j];
        return *this;
    }
    Matrix& operator +(const Matrix& A) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                data[i][j] = data[i][j] + A.data[i][j];
        return *this;
    }
    Matrix& operator -(const Matrix& A) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                data[i][j] = data[i][j] - A.data[i][j];
        return *this;
    }
    Matrix& operator *(const Matrix& A) {
        if (N != M) {
            std::cout << "Matrix isn't square " << std::endl; 
            return *this;
        }
        else {
            Matrix C;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++)
                {
                    C.data[i][j] = 0;
                    for (int k = 0; k < N; k++)
                        C.data[i][j] += A.data[i][k] * data[k][j];
                }
            }
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) 
                    data[i][j] = C.data[i][j];
            return *this;
        }
    }
};

template<typename T, int N> // специализация вектора
class Matrix<T, N, 1> {
private:
    T* data = new T[N];
public:
    Matrix() {
        for (int i = 0; i < N; i++)
            data[i] = 0;
    }
    ~Matrix() {
        delete[] data;
    }
    void set(int i, T value) {
        data[i] = value;
    }
    T get(int i) {
        return data[i];
    }
    void print() {
        for (int i = 0; i < N; i++) 
                std::cout << data[i] << "  ";
            std::cout << std::endl<<std::endl;
    }
    void trans() {
        Matrix<T, 1, N> C;
        for (int i = 0; i < N; i++)
                C.set(i,data[i]);
        C.print();
    }
    int size_r() {
        return N;
    }
    Matrix& operator =(const Matrix& A) {
        for (int i = 0; i < N; i++)
            data[i] = A.data[i];
        return *this;
    }
    Matrix& operator +(const Matrix& A) {
        for (int i = 0; i < N; i++)
            data[i] = data[i] + A.data[i];
        return *this;
    }
    Matrix& operator -(const Matrix& A) {
        for (int i = 0; i < N; i++)
            data[i] = data[i] - A.data[i];
        return *this;
    }
    Matrix& operator *(Matrix<T,1,N>& A) {
        for (int i = 0; i < N; i++)
            data[i] = data[i] * A.get(i);
        return *this;
    }
};
template<typename T, int M>
class Matrix<T, 1, M> {
private:
    T* data = new T[M];
public:
    Matrix() {
        for (int j = 0; j < M; j++)
            data[j] = 0;
    }
    ~Matrix() {
        delete[] data;
    }
    void set(int i, T value) {
        data[i] = value;
    }
    T get(int i) {
        return data[i];
    }
    void print() {
            for (int j = 0; j < M; j++)
                std::cout << data[j] << std::endl;
            std::cout << std::endl;
    }
    void trans() {
        Matrix<T, M, 1> C;
        for (int i = 0; i < M; i++)
            C.set(i, data[i]);
        C.print();
    }
    int size_c() {
        return M;
    }
    Matrix& operator =(const Matrix& A) {
        for (int j = 0; j < M; j++)
            data[j] = A.data[j];
        return *this;
    }
    Matrix& operator +(const Matrix& A) {
        for (int j = 0; j < M; j++)
            data[j] = data[j] + A.data[j];
        return *this;
    }
    Matrix& operator -(const Matrix& A) {
        for (int j = 0; j < M; j++)
            data[j] = data[j] - A.data[j];
        return *this;
    }
    Matrix& operator *(Matrix<T, M, 1>& A) {
        for (int i = 0; i < M; i++)
            data[i] = data[i] * A.get(i);
        return *this;
    }
};
int main() {
    Matrix<int, 5, 9> A;
    A.set(3, 2, 6);
    std::cout << A.get(3, 2) << " ";
    Matrix<double, 4, 1> B;
    B.set(3, 8);
    std::cout << B.get(3);
    std::cout << std::endl;
    Matrix<double, 1, 3> C;
    C.set(2, 7.5);
    A.print();
    B.print();
    C.print();
    Matrix<int, 5, 9> D;
    D = A;
    D.print();
    D.trans();
    B.trans();
    C.trans();
    D + A;
    D.print();
    B + B;
    C - C;
    B.print();
    C.print();
    Matrix<int, 5, 5> E;
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)
            E.set(i, j, i + j-2);
    E.print();
    Matrix<int, 5, 5> F;
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++)
            F.set(i, j, 2);
    F.print();
    E* F;
    E.print();
    A* A;
    A.print();
    Matrix<double, 1, 4> T;
    T.set(3, 8);
    T.print();
    B* T;
    B.print();
}