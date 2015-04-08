#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
class AVL {
    public:
        AVL * prt, * lc, * rc;
        T val;
        int size;
        AVL();
        AVL(const T && v);
        void insert(const T & v);
};

template <typename T>
AVL<T>::AVL(): val(T(0)), size(0), prt(NULL), lc(NULL), rc(NULL) {
}

template <typename T>
AVL<T>::AVL(const T && v): val(v), size(1), prt(NULL), lc(NULL), rc(NULL) {
}

template <typename T>
void AVL<T>::insert(const T & v) {
    // new node
    if(this->size == 0) {
        this->size = 1;
        this->val = v;
    }

    if(v < this->val) {
    }
}

int main() {
    AVL<int> * tree = new AVL<int>();
    tree->insert(1);
    cout << tree->val << endl;
}
