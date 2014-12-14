#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifndef N
#define N 1000000
#endif

int num[N];

void get_median(int l, int r) {
    if(l < r) {
        int m = rand()%(r-l+1) + l;
        swap(num[m], num[r]); // random swap
        int j = l;
        for(int i = l; i < r; i++) {
            if(num[i] < num[r]) {
                swap(num[i], num[j]);
                j++;
            }
        }
        swap(num[j], num[r]);
        if(j == N/2) {
            return ;
        }
        else if(j > N/2) {
            get_median(l, j);
        }
        else {
            get_median(j + 1, r);
        }
    }
}

int main() {

    /* 1 */
    cout << "natural sequence" << endl;

    for(int i = 0; i < N; i++) {
        num[i] = i;
    }
    random_shuffle(num, num + N);

    // sort and output
    clock_t start = clock(), end;
    sort(num, num + N);
    end = clock();
    cout << "sort time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;
    //for(int i = 0; i < N; i++) cout << num[i] << (i==N-1?'\n':' ');

    // partial sort
    random_shuffle(num, num + N);
    start = clock();
    get_median(0, N-1);
    end = clock();
    cout << "O(N) median time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;
    //for(int i = 0; i < N; i++) cout << num[i] << (i==N-1?'\n':' ');

    /* 2 */
    cout << "all same sequence" << endl;

    fill(num, num + N, N);
    start = clock();
    sort(num, num + N);
    end = clock();
    cout << "sort time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;

    fill(num, num + N, N);
    random_shuffle(num, num + N);
    start = clock();
    get_median(0, N-1);
    end = clock();
    cout << "O(N) median time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;

    /* 3 */
    cout << "half and half sequence" << endl;

    fill(num, num + N/2, N/2);
    fill(num + N/2, num + N, N);
    start = clock();
    sort(num, num + N);
    end = clock();
    cout << "sort time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;

    fill(num, num + N/2, N/2);
    fill(num + N/2, num + N, N);
    random_shuffle(num, num + N);
    start = clock();
    get_median(0, N-1);
    end = clock();
    cout << "O(N) median time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;

    /* 4 */
    cout << "triple separate sequence" << endl;

    fill(num, num + N/3, N/3);
    fill(num + N/3, num + N*2/3, N*2/3);
    fill(num + N*2/3, num + N, N);
    start = clock();
    sort(num, num + N);
    end = clock();
    cout << "sort time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;

    fill(num, num + N/3, N/3);
    fill(num + N/3, num + N*2/3, N*2/3);
    fill(num + N*2/3, num + N, N);
    random_shuffle(num, num + N);
    start = clock();
    get_median(0, N-1);
    end = clock();
    cout << "O(N) median time: " << (end - start) / 1000. << "ms." << endl;
    cout << num[N/2] << endl;
}
