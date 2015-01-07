#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>
#include <cassert>
#include <bitset>

using namespace std;

class Sieve {
    public:
        Sieve();
        Sieve(const int &);

        void sieve();
        void print(int start = 0, int end = 0);

        int size, prime_count;
        vector <bool> is_prime;
        vector <int> prime;
};

Sieve::Sieve(): size(0), prime_count(0){
    is_prime.clear();
    prime.clear();
}

Sieve::Sieve(const int &n): size(n + 1), prime_count(0) {
    is_prime.resize(size);
    int prime_size = size / round(log(size) / 2);
    prime.resize(prime_size);
}

void Sieve::sieve() {
    fill(is_prime.begin(), is_prime.end(), true);
    prime[prime_count++] = 2;
    for(int x = 3; x < size; x += 2) {
        if(is_prime[x]) {
            prime[prime_count++] = x;
            assert(prime_count <= size);
            for(int j = x * 3; j < size; j += x) {
                is_prime[j] = false;
            }
        }
    }
    prime.resize(prime_count);
    cout << "prime: " << prime.size() << endl;
}

void Sieve::print(int start, int end) {
    auto s = lower_bound(prime.begin(), prime.end(), start);
    auto e = upper_bound(prime.begin(), prime.end(), end);
    cout << "[" << start << ", " << end << "]: ";
    int cnt = 0;
    for(auto idx = s; idx != e; idx++) {
        cout << *idx << ", ";
        cnt++;
    }
    cout << endl;
    cout << "count: " << cnt << endl;
}

int main() {
    int num;
    while(cin >> num) {
        Sieve s(num);
        clock_t start = clock();
        s.sieve();
        clock_t end = clock();
        cout << "time: " << (end - start) / 1000. << " ms." << endl;
        int a, b;
        char opt;
        while(cin >> opt) {
            if(opt == 'g') {
                cin >> a >> b;
                s.print(a, b);
            } else if(opt == 'q') {
                break;
            } else {
            }
        }
    }
}