#include <cstdio>
#include <cassert>
#include <cstring>

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#include <typeinfo>

using namespace std;

template <typename T>
class Matrix {
    public:
        Matrix<T>();

        Matrix<T>(const size_t &, const size_t &);
        Matrix<T>(const vector < vector <T> > &);
        Matrix<T>(vector < vector <T> > &&);

        Matrix<T>(const Matrix <T> &);
        Matrix<T>(Matrix <T> &&);

        ~Matrix<T>();

        Matrix<T> & operator = (const Matrix<T> &);

        void check() const;

        size_t row_size() const;
        size_t col_size() const;

        static Matrix<T> unit(const size_t &);
 
        vector <T> operator ()(const size_t &) const;
        vector <T> & operator ()(const size_t &);
        vector <T> operator [](const size_t &) const;
        vector <T> & operator [](const size_t &);
        T operator ()(const size_t &, const size_t &) const;
        T & operator ()(const size_t &, const size_t &);

        Matrix<T> operator * (const Matrix<T> &) const;
        Matrix<T> operator * (const T &) const;
        Matrix<T> operator ^ (const long long &) const;

        void print(const string & prompt = "") const;

    private:
        vector < vector <T> > _;
};

/***** default constructor *****/
template <typename T>
Matrix<T>::Matrix() {
    _.clear();
}
/***** default constructor *****/

/***** constructor *****/
template <typename T>
Matrix<T>::Matrix(const size_t & r, const size_t & c) {
    _.resize(r);
    for(size_t i = 0; i < r; i++) {
        _[i].resize(c);
    }
}

template <typename T>
Matrix<T>::Matrix(const vector < vector <T> > & elements): _(elements) {
}
/***** constructor *****/

/***** move constructor *****/
template <typename T>
Matrix<T>::Matrix(vector < vector <T> > && elements) {
    if(&_ != &elements) {
        _.clear();
        _ = std::move(elements);
        elements.clear();
    }
}
/***** move constructor *****/

/***** copy constructor *****/
template <typename T>
Matrix<T>::Matrix(const Matrix <T> & another): _(another._) {
}
/***** copy constructor *****/

/***** move constructor *****/
template <typename T>
Matrix<T>::Matrix(Matrix <T> && another) {
    if(this != &another) {
        _.clear();
        _ = std::move(another._);
        another._.clear();
    }
}
/***** move constructor *****/

/***** destructor *****/
template <typename T>
Matrix<T>::~Matrix() {
    // cout << "Destructing ..." << endl;
    _.clear();
}
/***** destructor *****/

/***** = operator *****/
template <typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix<T> & another) {
    // *this = Matrix<T>(another); // why this lead to infinite recursion
    // <=== obviously
    _ = vector < vector <T> > (another._);
    return *this;
}
/***** = operator *****/

template <typename T>
void Matrix<T>::check() const {
    size_t r = row_size();
    for(size_t i = 0; i < r; i++) {
        assert(col_size() == (*this)[i].size());
    }
}

template <typename T>
size_t Matrix<T>::row_size() const {
    return _.size();
}

template <typename T>
size_t Matrix<T>::col_size() const {
    assert(row_size() > 0);
    return _[0].size();
}

template <typename T>
Matrix<T> Matrix<T>::unit(const size_t & size) {
    Matrix<T> ret(size, size);
    for(size_t i = 0; i < size; i++) {
        ret(i, i) = 1;
    }
    return ret;
}

/***** (i) operator *****/
template <typename T>
vector <T> Matrix<T>::operator ()(const size_t &i) const {
    assert(i < row_size());
    return _[i];
}

template <typename T>
vector <T> & Matrix<T>::operator ()(const size_t &i) {
    assert(i < row_size());
    return _[i];
}
/***** (i) operator *****/

/***** [i] operator *****/
template <typename T>
vector <T> Matrix<T>::operator [](const size_t & i) const {
    assert(i < row_size());
    return _[i];
}

template <typename T>
vector <T> & Matrix<T>::operator [](const size_t & i) {
    assert(i < row_size());
    return _[i];
}
/***** [i] operator *****/

/***** (i, j) operator *****/
template <typename T>
T Matrix<T>::operator ()(const size_t & i, const size_t & j) const {
    assert(i < row_size() && j < col_size());
    return _[i][j];
}

template <typename T>
T & Matrix<T>::operator ()(const size_t & i, const size_t & j) {
    assert(i < row_size() && j < col_size());
    return _[i][j];
}
/***** (i, j) operator *****/

/***** * operator with another matrix *****/
template <typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T> & another) const {
    check();
    assert(col_size() == another.row_size());

    size_t r = row_size(), c = another.col_size();
    Matrix<T> ret(r, c);
    for(size_t i = 0; i < r; i++) {
        for(size_t j = 0; j < c; j++) {
            T temp = 0;
            for(size_t k = 0; k < col_size(); k++) {
                temp = temp + (*this)(i, k) * another(k, j);
            }
            ret[i][j] = temp;
        }
    }
    return ret;
}
/***** * operator with another matrix *****/

/***** * operator with scaling factor *****/
template <typename T>
Matrix<T> Matrix<T>::operator * (const T & _s) const {
    Matrix<T> ret(*this);
    size_t r = row_size, c = col_size();
    for(size_t i = 0; i < r; i++) {
        for(size_t j = 0; j < c; j++) {
            ret(i, j) = ret(i, j) * _s;
        }
    }
    return ret;
}
/***** * operator with scaling factor *****/

/***** ^ operator *****/
template <typename T>
Matrix<T> Matrix<T>::operator ^ (const long long & _pow) const { // cannot use template
    size_t r = row_size(), c = col_size();
    assert(r == c); // symmetric matrix
    Matrix<T> ret = Matrix<T>::unit(r);
    Matrix<T> m = *this;
    long long pow = _pow;
    while(pow > 0ll) {
        if(pow & 1ll) {
            ret = m * ret;
        }
        m = m * m;
        pow >>= 1;
    }
    return ret;
}
/***** ^ operator *****/

template <typename T>
void Matrix<T>::print(const string & _prompt) const {
    check();
    string prompt;
    if(_prompt=="") prompt = "Default";
    else prompt = _prompt;
    cout << "Matrix <" << prompt << ">:" << endl;

    for(size_t i = 0; i < row_size(); i++) {
        cout << "|";
        for(size_t j = 0; j < col_size(); j++) {
            cout << (*this)(i, j) << (j==col_size()-1?"|\n":", ");
        }
    }
}

void test_construct() {
    vector < vector <int> > v(2), v2;
    v[0].push_back(1);
    v[0].push_back(1);
    v[1].push_back(2);
    v[1].push_back(2);

    (Matrix<int>::unit(10)).print("size_10 unit");

    Matrix <int> m(v), m2(std::move(m));
    m.print("m");
    m2.print("m2");
    (m2 * m2 * m2).print("m2 * m2 * m2");
    
    (m2 ^ 3).print("m2^3");
}

void unit_test() {
    test_construct();
}

int main() {
    unit_test();
}