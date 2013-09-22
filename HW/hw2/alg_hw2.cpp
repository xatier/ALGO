#include <iostream>
#include <cstdlib>
#include <ctime>
 
template<typename T>
class matrix {
public:
    // ctor
    matrix(int n, T init=T(0)) : size(n) {
        data = new T*[size];
        for (int i = 0; i < size; i++)
            data[i] = new T[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                data[i][j] = init;
    }
    // copy ctor
    inline matrix (const matrix<T>& m) : size(m.get_size()) {
        data = new T*[size];
        for (int i = 0; i < size; i++)
            data[i] = new T[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                data[i][j] = m[i][j];
    }
 
    // dtor
    ~matrix(void) {
        for (int i = 0; i < size; i++)
            delete [] data[i];
        delete [] data;
    }
 
    inline int get_size(void) const {
        return size;
    }
    // indexing the elements
    inline T *&operator[](int i) {
        return data[i];
    }
 
    inline T *operator[](int i) const {
        return data[i];
    }
    // print out the matrix
    inline void print(std::ostream &out) const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                out << data[i][j] << " ";
            }
            out << "\n";
        }
    }
    // assignment
    inline matrix<T>& operator=(const matrix<T>& rhs) {
        if (this == &rhs)
                return *this;
 
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                data[i][j] = rhs[i][j];
 
        return *this;
    }
 
    inline matrix<T> operator+(const matrix<T>& rhs) {
            matrix<T> c(size);
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    c[i][j] = data[i][j] + rhs[i][j];
            return c;
    }
 
    inline matrix<T> operator-(const matrix<T>& rhs) {
            matrix<T> c(size);
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    c[i][j] = data[i][j] - rhs[i][j];
            return c;
    }
    // classical algorithm
    inline matrix<T> operator^(const matrix<T>& rhs) const {
        matrix<T> c(size);
 
        for (int i = 0; i < size; i++)
            for (int k = 0; k < size; k++)
                for (int j = 0; j < size; j++)
                    c[i][j] += data[i][k] * rhs[k][j];
 
        return c;
    }
    // get partial of the matrix
    inline matrix<T> get_part(int pi, int pj) const {
        int c_size = (size & 1) ? (size + 1)>>1 : size>>1;
        matrix<T> c(c_size);
 
        
        if (size & 1) {
            for (int i = 0; i < c_size; i++)
                for (int j = 0; j < c_size; j++)
                    if (c_size*pi + i >= size || c_size*pj + j >= size)
                        c[i][j] = T(0);
                    else
                        c[i][j] = data[c_size*pi + i][c_size*pj + j];
        }
        else
            for (int i = 0; i < c_size; i++)
                for (int j = 0; j < c_size; j++)
                    c[i][j] = data[c_size*pi + i][c_size*pj + j];
 
        return c;
    }
    // store back to self
    inline void set_part(int pi, int pj, const matrix<T>& m) const {
        int c_size = (size & 1) ? (size + 1)>>1 : size>>1;
        for (int i = 0; i < c_size; i++)
            for (int j = 0; j < c_size; j++)
                if (c_size*pi + i < size && c_size*pj + j < size)
                    data[c_size*pi + i][c_size*pj + j] = m[i][j];
    }
 
    // Strassen’s algorithm
    inline matrix<T> operator*(const matrix<T> rhs) const {
        int c_size = (size & 1) ? size + 1: size;
        int l_size = c_size >> 1 ; 
        matrix<T> c(size);
        // recursive boundary
        if (size == 2) {
            // i can't use this for base case QQ
            /*
        if (size <= 10) {
            c = (*this) ^ rhs;
            return c;
            */
            
            T _a00, _a10, _a01, _a11;
            T _b00, _b10, _b01, _b11;
            T _p1, _p2, _p3, _p4, _p5, _p6, _p7;
            T _c00, _c10, _c01, _c11;
 
            _a00 = data[0][0]; _a10 = data[1][0];
            _a01 = data[0][1]; _a11 = data[1][1];
 
            _b00 = rhs[0][0]; _b10 = rhs[1][0];
            _b01 = rhs[0][1]; _b11 = rhs[1][1];
 
            _p1 = _a00 * (_b01 - _b11);
            _p2 = (_a00 + _a01) * _b11;
            _p3 = (_a10 + _a11) * _b00;
            _p4 =  _a11 * (_b10 - _b00);
            _p5 = (_a00 + _a11) * (_b00 + _b11);
            _p6 = (_a01 - _a11) * (_b10 + _b11);
            _p7 = (_a00 - _a10) * (_b00 + _b01);
 
            _c00 = _p5 + _p4 - _p2 + _p6;
            _c01 = _p1 + _p2;
            _c10 = _p3 + _p4;
            _c11 = _p5 + _p1 - _p3 - _p7;
 
            data[0][0] = _c00; data[0][1] = _c01;
            data[1][0] = _c10; data[1][1] = _c11;
 
            return *this;
            
        }
 
        matrix<T> a00(l_size), a10(l_size), a01(l_size), a11(l_size);
        matrix<T> b00(l_size), b10(l_size), b01(l_size), b11(l_size);
        matrix<T> c00(l_size), c10(l_size), c01(l_size), c11(l_size);
        matrix<T> s1(l_size), s2(l_size), s3(l_size), s4(l_size), s5(l_size);
        matrix<T> s6(l_size), s7(l_size), s8(l_size), s9(l_size), s10(l_size);
        matrix<T> p1(l_size), p2(l_size), p3(l_size),
                  p4(l_size), p5(l_size), p6(l_size),
                  p7(l_size);
 
        // tear apart the matrix QQ
        a00 = this->get_part(0, 0); a01 = this->get_part(0, 1);
        a10 = this->get_part(1, 0); a11 = this->get_part(1, 1);
 
        b00 = rhs.get_part(0, 0); b01 = rhs.get_part(0, 1);
        b10 = rhs.get_part(1, 0); b11 = rhs.get_part(1, 1);
 
        s1 = b01 - b11;
        s2 = a00 + a01;
        s3 = a10 + a11;
        s4 = b10 - b00;
        s5 = a00 + a11;
 
        s6 = b00 + b11;
        s7 = a01 - a11;
        s8 = b10 + b11;
        s9 = a00 - a10;
        s10 = b00 + b01;
 
        p1 = a00 * s1;
        p2 =  s2 * b11;
        p3 =  s3 * b00;
        p4 = a11 * s4;
        p5 =  s5 * s6;
        p6 =  s7 * s8;
        p7 =  s9 * s10;
 
        c00 = p5 + p4 - p2 + p6;
        c01 = p1 + p2;
        c10 = p3 + p4;
        c11 = p5 + p1 - p3 - p7;
 
        c.set_part(0, 0, c00);
        c.set_part(0, 1, c01);
        c.set_part(1, 0, c10);
        c.set_part(1, 1, c11);
        return c;
    }
 
 
private:
    int size;
    T **data;
};
 
 
template<typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m) {
    m.print(os);
    return os;
}
 
 
int main (void) {
// test 1
 
    const int n =  9;
    matrix<int> _A(n), _B(n);
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) {
            _A[i][j]=std::rand()%5;
            _B[i][j]=std::rand()%5;
        }
 
    std::cout << "Matrix A\n" << _A;
    std::cout << "Matrix B\n" << _B;
    std::cout << "Matrix AxB\n" << _A*_B;
    std::cout << "Matrix A^B\n" << (_A^_B);
    std::cout << "==================\n";
 
// test 2
/*
    matrix<int> A(100,1),B(100,2);
    clock_t start=clock();
    matrix<int> C(A*B);
    clock_t finish=clock();
    std::cout << (double)(finish-start)/CLOCKS_PER_SEC;
    std::cout << " seconds\n";
    std::cout <<"=====\n";
    start=clock();
    matrix<int> D(A^B);
    finish=clock();
    std::cout << (double)(finish-start)/CLOCKS_PER_SEC;
*/
    return 0;
}
