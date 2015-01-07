#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

int main(int argc,char ** argv) {
    if(argc < 3) {
        puts("Parametres not enough.");
        return 0;
    }
    int a,b;
    sscanf(argv[1], "%d", &a);
    sscanf(argv[2], "%d", &b);
    printf("[%d, %d]\n", a, b);
    int cnt = 0;

    for(int i = a;i <= b;i++) {
        bool mark = true;
        for(int j = 2;j <= sqrt(i);j++) {
            if(i % j == 0) {
                mark = false;
                break;
            }
        }
        if(mark) {
            cnt++;
            cout << i << endl;
        }
    }
    cout << "total: " << cnt << endl;
}
